#include "memory.h"
#define STBI_MALLOC(size) allocate(size)
#define STBI_FREE(ptr) deallocate(ptr)
#define STBI_REALLOC(ptr, size) reallocate(ptr, size)
#define STBI_FAILURE_USERMSG
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
