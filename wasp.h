#ifndef WASP_H
#define WASP_H

#include <stdint.h>

struct wasp
{
  uint8_t* pMem;
  uint16_t memSize;
};

enum wasp_error
{
  WASP_OK,
  WASP_BAD_USAGE,
  WASP_INIT_FAILED,
};

int wasp_init(struct wasp* pWasp, const char* pMemFile);

void wasp_destroy(struct wasp* pWasp);

#endif // WASP_H
