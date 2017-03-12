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
#include "Engine/3D/plane.hpp"

int main(int, char const**) {

  //Plane plane(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
  //std::cout << plane.inside(glm::vec3(0.0, 1.9, 0.0)) << '\n';
  //std::cout << plane.inside(glm::vec3(8921.0, 2.1, 93.0)) << '\n';
  //std::cout << plane.inside(glm::vec3(0.0, 1.9, 0.0), 0.2) << '\n';
  //std::cout << plane.inside(glm::vec3(8921.0, 1.9, 93.0), 0.01) << '\n';
  
  app = new Game::AppImpl;
  app->mainloop();
  delete app;
  Profiler::formatInfo(std::cout);
  
  return EXIT_SUCCESS;
}
