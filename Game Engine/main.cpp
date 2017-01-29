#include <iostream>

//a really bad implementation of merge sort
void mergeSort(int *array, int size, int *result) {
  if (array == result) {//actually it can, i just don't know how
    throw std::runtime_error("Mergesort cannot be performed in-place");
  }
  if (size == 1) {
    *result = *array;
  } else if (size == 2) {
    if (array[0] < array[1]) {
      result[0] = array[0];
      result[1] = array[1];
    } else {
      result[0] = array[1];
      result[1] = array[0];
    }
  } else {
    int leftSize = size / 2;
    int rightSize = leftSize + size % 2;
    int *leftPart = new int[leftSize];
    int *rightPart = new int[rightSize];
    
    mergeSort(array, leftSize, leftPart);
    mergeSort(array + leftSize, rightSize, rightPart);
    
    int *leftI = leftPart;
    int *rightI = rightPart;
    int *endResult = result + size;
    while (result < endResult) {
      if (*leftI < *rightI && leftI < leftPart + leftSize) {
        *result = *leftI;
        result++;
        leftI++;
      } else {
        *result = *rightI;
        result++;
        rightI++;
      }
    }
    
    delete[] leftPart;
    delete[] rightPart;
  }
}

#include "Engine/Time/get.hpp"
#include <cmath>
#include <thread>
#include "Engine/Time/stopwatch.hpp"
#include "Engine/Time/timer.hpp"
#include "Engine/Memory/bits.hpp"
#include "Engine/Resource/cache.hpp"
#include "Engine/Math/byteconstants.hpp"
#include <functional>
#include <string>
#include "Engine/Utils/profiler.hpp"
#include "Engine/Memory/bitmapview.hpp"
#include "Engine/Memory/view.hpp"
#include <unordered_map>
#include "Engine/Time/interval.hpp"
#include "Engine/ID/guid.hpp"
#include "Engine/Math/format.hpp"
#include "Engine/Math/range.hpp"
#include "Engine/Game Logic/actor.hpp"
#include "Engine/Game Logic/actor factory.hpp"
#include "Engine/Game Logic/component.hpp"
#include "Engine/Memory/bits.hpp"
#include "Engine/3D/matstack.hpp"
#include "Engine/3D/color.hpp"
#include "Engine/Utils/move test.hpp"
#include "Engine/3D/transform.hpp"
#include "Engine/Math/pow.hpp"
#include "Libraries/tinyxml2.hpp"
#include "Engine/Utils/logger.hpp"
#include "Engine/Application/impl.hpp"
#include "Engine/Math/fixed point.hpp"
#include "Engine/3D/OpenGL/type enum.hpp"
#include "Engine/Utils/any.hpp"
#include "Engine/Utils/move test.hpp"

using namespace Resource;

template <typename T, typename U>
T caster(const U &);

template <>
glm::vec3 caster(const aiVector3D &aiVector) {
  return {aiVector.x, aiVector.y, aiVector.z};
}

template <>
glm::quat caster(const aiQuaternion &aiQuat) {
  return {aiQuat.w, aiQuat.x, aiQuat.y, aiQuat.z};
}

template <>
Handles::MeshOpenGL::SubChannelKey<glm::vec3> caster(const aiVectorKey &aiKey) {
  return {
    static_cast<Handles::MeshOpenGL::Time>(aiKey.mTime),
    caster<glm::vec3>(aiKey.mValue),
  };
}

template <>
Handles::MeshOpenGL::SubChannelKey<glm::quat> caster(const aiQuatKey &aiKey) {
  return {
    static_cast<Handles::MeshOpenGL::Time>(aiKey.mTime),
    caster<glm::quat>(aiKey.mValue),
  };
}

void copyChannel(
  Handles::MeshOpenGL::Channel &channel,
  const aiNodeAnim *aiChannel
) {
  channel.dummy = false;
  
  channel.translation.reserve(aiChannel->mNumPositionKeys);
  channel.rotation.reserve(aiChannel->mNumRotationKeys);
  channel.scaling.reserve(aiChannel->mNumScalingKeys);
  
  for (unsigned int k = 0; k < aiChannel->mNumPositionKeys; k++) {
    channel.translation.emplace_back(
      caster<Handles::MeshOpenGL::SubChannelKey<glm::vec3>>(
        aiChannel->mPositionKeys[k]
      )
    );
  }
  for (unsigned int k = 0; k < aiChannel->mNumRotationKeys; k++) {
    channel.rotation.emplace_back(
      caster<Handles::MeshOpenGL::SubChannelKey<glm::quat>>(
        aiChannel->mRotationKeys[k]
      )
    );
  }
  for (unsigned int k = 0; k < aiChannel->mNumScalingKeys; k++) {
    channel.scaling.emplace_back(
      caster<Handles::MeshOpenGL::SubChannelKey<glm::vec3>>(
        aiChannel->mScalingKeys[k]
      )
    );
  }
}

float num = 32.0f;

aiVector3D randVec3() {
  return {num++, num++, num++};
}

aiQuaternion randQuat() {
  return {num++, num++, num++, num++};
}

template <typename T>
T lerp(const T &, const T &, float);

template <>
glm::vec3 lerp<glm::vec3>(const glm::vec3 &a, const glm::vec3 &b, float t) {
  return glm::mix(a, b, t);
}

template <>
glm::quat lerp<glm::quat>(const glm::quat &a, const glm::quat &b, float t) {
  return glm::slerp(a, b, t);
}

template <typename T>
T getKey(const ResHnds::MeshOpenGL::SubChannel<T> &subChannel,
         double progress) {
  if (subChannel.size() == 1) {
    return subChannel[0].value;
  } else if (subChannel.size() == 2) {
    return lerp(
      subChannel[0].value,
      subChannel[1].value,
      Math::invLerp(
        progress,
        subChannel[0].time,
        subChannel[1].time
      )
    );
  } else {
    ResHnds::MeshOpenGL::SubChannelKey<T> key;
    key.time = progress;
    auto upper = std::lower_bound(
      subChannel.begin(),
      subChannel.end(),
      key,
      [](const auto &a,
         const auto &b) {
        return a.time < b.time;
      }
    );
    //the first keyframe will always have a time of 0.
    //if the progress is 0, lower_bound will return begin
    if (upper == subChannel.begin()) {
      return upper->value;
    } else {
      auto lower = upper - 1;
      return lerp(
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

int main(int, char const**) {
  /*ResHnds::MeshOpenGL::SubChannel<glm::vec3> channel;
  channel.push_back({0.0, {2.0f, 3.0f, 4.0f}});
  channel.push_back({3.0, {0.0f, 0.0f, 0.0f}});
  channel.push_back({6.0, {1.0f, 1.0f, 1.0f}});
  channel.push_back({9.0, {4.0f, 6.0f, 8.0f}});
  
  for (double i = 0.0; i < 10.0; i++) {
    std::cout << i << "  " << getKey(channel, i) << '\n';
  }*/
  /*aiNodeAnim aiChannel;
  aiChannel.mPositionKeys = new aiVectorKey[3];
  aiChannel.mRotationKeys = new aiQuatKey[3];
  aiChannel.mScalingKeys = new aiVectorKey[3];
  aiChannel.mNumPositionKeys = 3;
  aiChannel.mNumRotationKeys = 3;
  aiChannel.mNumScalingKeys = 3;
  
  aiChannel.mPositionKeys[0] = {0.0f, randVec3()};
  aiChannel.mPositionKeys[1] = {1.0f, randVec3()};
  aiChannel.mPositionKeys[2] = {2.0f, randVec3()};
  
  aiChannel.mRotationKeys[0] = {3.0f, randQuat()};
  aiChannel.mRotationKeys[1] = {4.0f, randQuat()};
  aiChannel.mRotationKeys[2] = {5.0f, randQuat()};
  
  aiChannel.mScalingKeys[0] = {6.0f, randVec3()};
  aiChannel.mScalingKeys[1] = {7.0f, randVec3()};
  aiChannel.mScalingKeys[2] = {8.0f, randVec3()};
  
  Handles::MeshOpenGL::Channel channel;
  
  copyChannel(channel, &aiChannel);
  
  int a = 783;
  a++;*/
  /*const size_t COUNT = 10'000'000;
  {
    Profiler p("Profiler");
    for (size_t i = 0; i < COUNT; i++) {
      Profiler p("Profiler iter");
    }
  }
  uint64_t *duration = new uint64_t[COUNT];
  {
    Profiler p("StopWatch ctor start stop");
    for (size_t i = 0; i < COUNT; i++) {
      Time::StopWatch<std::chrono::nanoseconds> s(true);
      duration[i] = s.stop();
    }
  }
  delete [] duration;
  duration = new uint64_t[COUNT];
  {
    Profiler p("StopWatch ctor start get");
    for (size_t i = 0; i < COUNT; i++) {
      Time::StopWatch<std::chrono::nanoseconds> s(true);
      duration[i] = s.get();
    }
  }
  delete [] duration;
  duration = new uint64_t[COUNT];
  {
    Profiler p("StopWatch start stop");
    for (size_t i = 0; i < COUNT; i++) {
      Time::StopWatch<std::chrono::nanoseconds> s;
      s.start();
      duration[i] = s.stop();
    }
  }
  delete [] duration;
  duration = new uint64_t[COUNT];
  {
    Profiler p("StopWatch start get");
    for (size_t i = 0; i < COUNT; i++) {
      Time::StopWatch<std::chrono::nanoseconds> s;
      s.start();
      duration[i] = s.get();
    }
  }
  delete [] duration;
  
  Profiler::formatInfo(std::cout);*/
  
  app = new Game::AppImpl;
  app->mainloop();
  delete app;
  
  return EXIT_SUCCESS;
}
