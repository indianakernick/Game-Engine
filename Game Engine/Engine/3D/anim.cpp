//
//  anim.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "anim.hpp"

Graphics3D::Anim *anim;

using namespace Res;

Graphics3D::Anim::Anim(Res::ID meshID)
  : meshID(meshID) {
  MeshOpenGL::Ptr mesh = getMesh();
  assert(mesh->hasAnimations());
  boneTransforms.resize(mesh->getBones().size());
}

void Graphics3D::Anim::update(uint64_t delta) {
  switch (state) {
    case RUNNING:
      progress += millisToTicks(delta) * speed;
      doRunning();
      break;
    case TRANSITIONING:
      transitionProgress += millisToTicks(delta) * speed;
      doTransitioning();
      break;
    case PAUSED:
    case STOPPED:
      //nothing
      break;
  }
}

const std::vector<glm::mat4> &Graphics3D::Anim::getBoneTransforms() const {
  return boneTransforms;
}

void Graphics3D::Anim::play(ID id, uint64_t start, uint64_t transition) {
  assert(id != NONE);
  assert(valid(id));
  
  if (transition == 0 || current == NONE) {
    state = RUNNING;
    current = id;
    setTicksPerMillisecond();
    next = NONE;
    progress = millisToTicks(start);
    duration = getDuration(current);
  } else if (current != NONE) {
    state = TRANSITIONING;
    next = id;
    nextProgress = millisToTicks(start);
    nextDuration = getDuration(next);
    transitionProgress = 0;
    transitionDuration = millisToTicks(transition);
  }
}

void Graphics3D::Anim::pause() {
  assert(state == RUNNING || state == TRANSITIONING);
  state = PAUSED;
  pausedTransition = state == TRANSITIONING;
}

void Graphics3D::Anim::resume() {
  assert(state == PAUSED);
  if (pausedTransition) {
    state = TRANSITIONING;
  } else {
    state = RUNNING;
  }
}

void Graphics3D::Anim::togglePause() {
  if (state == RUNNING || state == TRANSITIONING) {
    pause();
  } else if (state == PAUSED) {
    resume();
  }
}

void Graphics3D::Anim::setNext(ID id) {
  assert(id != NONE);
  assert(valid(id));
  next = id;
  nextProgress = 0;
  nextDuration = getDuration(next);
}

void Graphics3D::Anim::cancelNext() {
  next = NONE;
  nextProgress = 0;
  nextDuration = 0;
}

void Graphics3D::Anim::loop(bool status) {
  willLoop = status;
}

void Graphics3D::Anim::loopNext(bool status) {
  willLoopNext = status;
}

void Graphics3D::Anim::setSpeed(double newSpeed) {
  speed = newSpeed;
}

MeshOpenGL::Ptr Graphics3D::Anim::getMesh() const {
  return resCache->get<MeshOpenGL>(meshID);
}

bool Graphics3D::Anim::valid(ID id) const {
  return id < getMesh()->getAnimations().size();
}

bool Graphics3D::Anim::handleEndRun() {
  if (progress > duration) {
    if (willLoop) {
      progress -= duration;
    } else if (next == NONE) {
      state = STOPPED;
      current = NONE;
      progress = 0;
    } else {
      state = TRANSITIONING;
      transitionProgress = progress - duration;
      transitionDuration = DEFAULT_TRANSITION;
      progress = duration;
      
      doTransitioning();
    }
    return true;
  } else {
    return false;
  }
}

bool Graphics3D::Anim::handleEndTrans() {
  if (transitionProgress > transitionDuration) {
    state = RUNNING;
    current = next;
    next = NONE;
    willLoop = willLoopNext;
    willLoopNext = false;
    progress = nextProgress;
    nextProgress = 0;
    duration = nextDuration;
    nextDuration = false;
    
    doRunning();
    return true;
  } else {
    return false;
  }
}

void Graphics3D::Anim::setTicksPerMillisecond() {
  assert(state == RUNNING || state == TRANSITIONING);
  ticksPerMillisecond = getMesh()->getAnimations().at(current).ticksPerSecond / 1000.0;
}

Graphics3D::Anim::Time Graphics3D::Anim::millisToTicks(uint64_t millis) const {
  return millis * ticksPerMillisecond;
}

uint64_t Graphics3D::Anim::ticksToMillis(Time ticks) const {
  return ticks / ticksPerMillisecond;
}

Graphics3D::Anim::Time Graphics3D::Anim::getDuration(ID anim) {
  return getMesh()->getAnimations()[anim].duration;
}

glm::mat4 makeMat(const glm::vec3 &translation,
                  const glm::quat &rotation,
                  const glm::vec3 &scaling) {
  //scaling rotation translation
  return glm::translate({}, translation) *
         glm::scale(
           glm::mat4_cast(rotation),
           scaling
         );
}

template <typename T>
T interpolate(const T &, const T &, float);

template <>
glm::vec3 interpolate<glm::vec3>(const glm::vec3 &a, const glm::vec3 &b, float t) {
  return glm::mix(a, b, t);
}

template <>
glm::quat interpolate<glm::quat>(const glm::quat &a, const glm::quat &b, float t) {
  return glm::slerp(a, b, t);
}

template <>
glm::mat4 interpolate<glm::mat4>(const glm::mat4 &a, const glm::mat4 &b, float t) {
  glm::vec3 aScaling;
  glm::quat aRotation;
  glm::vec3 aTranslation;
  glm::vec3 aSkew;
  glm::vec4 aPerspective;
  glm::decompose(a, aScaling, aRotation, aTranslation, aSkew, aPerspective);
  
  glm::vec3 bScaling;
  glm::quat bRotation;
  glm::vec3 bTranslation;
  glm::vec3 bSkew;
  glm::vec4 bPerspective;
  glm::decompose(b, bScaling, bRotation, bTranslation, bSkew, bPerspective);
  
  return makeMat(
    interpolate(aTranslation, bTranslation, t),
    interpolate(aRotation, bRotation, t),
    interpolate(aScaling, bScaling, t)
  );
}

template <typename T>
T Graphics3D::Anim::getKey(const MeshOpenGL::SubChannel<T> &subChannel,
                           Time progress) const {
  if (subChannel.size() == 1) {
    return subChannel[0].value;
  } else if (subChannel.size() == 2) {
    return interpolate(
      subChannel[0].value,
      subChannel[1].value,
      Math::invLerp(
        progress,
        subChannel[0].time,
        subChannel[1].time
      )
    );
  } else {
    MeshOpenGL::SubChannelKey<T> key;
    key.time = progress;
    auto upper = std::lower_bound(
      subChannel.begin(),
      subChannel.end(),
      key,
      [](const auto &a, const auto &b) {
        return a.time < b.time;
      }
    );
    //the first keyframe will always have a time of 0.
    //if the progress is 0, lower_bound will return begin
    if (upper == subChannel.begin()) {
      return upper->value;
    } else {
      auto lower = upper - 1;
      return interpolate(
        lower->value,
        upper->value,
        Math::invLerp(
          progress,
          lower->time,
          upper->time
        )
      );
    }
  }
}

glm::mat4 Graphics3D::Anim::getKeyTransform(
  const MeshOpenGL::Channel &channel
) const {
  return makeMat(
    getKey(channel.translation, progress),
    getKey(channel.rotation, progress),
    getKey(channel.scaling, progress)
  );
}

glm::mat4 Graphics3D::Anim::getKeyTransform(
  const MeshOpenGL::Channel &currentChannel,
  const MeshOpenGL::Channel &nextChannel
) const {
  assert(state == TRANSITIONING);
  return makeMat(
    //translation
    interpolate(
      getKey(currentChannel.translation, progress),
      getKey(nextChannel.translation, nextProgress),
      transitionProgress / transitionDuration
    ),
    //rotation
    interpolate(
      getKey(currentChannel.rotation, progress),
      getKey(nextChannel.rotation, nextProgress),
      transitionProgress / transitionDuration
    ),
    //scaling
    interpolate(
      getKey(currentChannel.scaling, progress),
      getKey(nextChannel.scaling, nextProgress),
      transitionProgress / transitionDuration
    )
  );
}

std::vector<glm::mat4> Graphics3D::Anim::getBoneNodeTransforms(
  const MeshOpenGL::BoneNodes &boneNodes,
  const MeshOpenGL::Animation &anim
) const {
  assert(state == RUNNING);
  std::vector<glm::mat4> boneNodeTransforms(boneNodes.size());
  
  for (MeshOpenGL::ChannelID c = 0; c < boneNodes.size(); c++) {
    const MeshOpenGL::Channel &channel = anim.channels[c];
    if (channel.dummy) {
      boneNodeTransforms[c] = boneNodes[c].transform;
    } else {
      boneNodeTransforms[c] = getKeyTransform(channel);
    }
  }
  
  return boneNodeTransforms;
}

std::vector<glm::mat4> Graphics3D::Anim::getBoneNodeTransforms(
  const MeshOpenGL::BoneNodes &boneNodes,
  const MeshOpenGL::Animation &currentAnim,
  const MeshOpenGL::Animation &nextAnim
) const {
  assert(state == TRANSITIONING);
  std::vector<glm::mat4> boneNodeTransforms(boneNodes.size());
  
  for (MeshOpenGL::ChannelID c = 0; c < boneNodes.size(); c++) {
    const MeshOpenGL::Channel &currentChannel = currentAnim.channels[c];
    const MeshOpenGL::Channel &nextChannel = nextAnim.channels[c];
    if (currentChannel.dummy) {
      if (nextChannel.dummy) {
        boneNodeTransforms[c] = boneNodes[c].transform;
      } else {
        //getKeyTransform calls makeMat then interpolate<glm::mat4>
        //calls glm::decompose so this is suboptimal
        boneNodeTransforms[c] = interpolate(
          boneNodes[c].transform,
          getKeyTransform(nextChannel),
          transitionProgress / transitionDuration
        );
      }
    } else {
      if (nextChannel.dummy) {
        boneNodeTransforms[c] = interpolate(
          getKeyTransform(currentChannel),
          boneNodes[c].transform,
          transitionProgress / transitionDuration
        );
      } else {
        //we should end up here most of the time
        boneNodeTransforms[c] = getKeyTransform(currentChannel, nextChannel);
      }
    }
  }
  
  return boneNodeTransforms;
}

//this transform      = parent * translation * rotation * scaling * offset
//this child's parent = parent * translation * rotation * scaling

void Graphics3D::Anim::relativeTransforms(
  std::vector<glm::mat4> &transforms,
  const MeshOpenGL::BoneNodes &boneNodes,
  MeshOpenGL::ChannelID root
) const {
  const MeshOpenGL::BoneNode &rootNode = boneNodes[root];
  for (size_t n = 0; n < rootNode.children.size(); n++) {
    transforms[rootNode.children[n]] = transforms[root] * transforms[rootNode.children[n]];
    relativeTransforms(transforms, boneNodes, rootNode.children[n]);
  }
}

void Graphics3D::Anim::finalTransform(const std::vector<glm::mat4> &transforms,
                                      const MeshOpenGL::Bones &bones) {
  for (size_t b = 0; b < bones.size(); b++) {
    const MeshOpenGL::Bone &bone = bones[b];
    boneTransforms[b] = transforms[bone.channel] * bone.offset;
  }
}

void Graphics3D::Anim::doRunning() {
  if (handleEndRun()) {
    return;
  }
  MeshOpenGL::Ptr mesh = getMesh();
  const MeshOpenGL::Animation &anim = mesh->getAnimations().at(current);
  
  const MeshOpenGL::BoneNodes &boneNodes = mesh->getBoneNodes();
  std::vector<glm::mat4> boneNodeTransforms =
    getBoneNodeTransforms(boneNodes, anim);
  relativeTransforms(boneNodeTransforms, boneNodes);
  finalTransform(boneNodeTransforms, mesh->getBones());
}

void Graphics3D::Anim::doTransitioning() {
  if (handleEndTrans()) {
    return;
  }

  MeshOpenGL::Ptr mesh = getMesh();
  const MeshOpenGL::Animation &currentAnim =
    mesh->getAnimations().at(current);
  const MeshOpenGL::Animation &nextAnim =
    mesh->getAnimations().at(next);
  
  const MeshOpenGL::BoneNodes &boneNodes = mesh->getBoneNodes();
  std::vector<glm::mat4> boneNodeTransforms =
    getBoneNodeTransforms(boneNodes, currentAnim, nextAnim);
  
  relativeTransforms(boneNodeTransforms, boneNodes);
  finalTransform(boneNodeTransforms, mesh->getBones());
}
