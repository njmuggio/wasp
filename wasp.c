#include <stdio.h>
#include <stdlib.h>

#include "wasp.h"

int main(int argc, char** pArgv)
{
  if (argc != 2)
  {
    printf("Usage: %s memFile\n", pArgv[0]);
    return WASP_BAD_USAGE;
  }

  struct wasp machine;
  int status = wasp_init(&machine, pArgv[1]);

  if (status != WASP_OK)
  {
    wasp_destroy(&machine);
    fprintf(stderr, "Failed to init WASP\n");
    return status;
  }

  do
  {
    status = wasp_cycle(&machine);
  } while (status == WASP_OK);

  wasp_destroy(&machine);
  return WASP_OK;
}

int wasp_init(struct wasp* pWasp, const char* pMemFile)
{
  pWasp->memSize = 16384;
  pWasp->pMem = calloc(pWasp->memSize, sizeof(char));

  FILE* pFile = fopen(pMemFile, "r");
  if (!pFile)
  {
    perror("Opening memFile");
    return WASP_INIT_FAILED;
  }

  if (0 < fread(pWasp->pMem, pWasp->memSize, sizeof(char), pFile))
  {
    perror("Reading memFile");
    return WASP_INIT_FAILED;
  }

  if (0 != fclose(pFile))
  {
    perror("Closing memFile");
    return WASP_INIT_FAILED;
  }

  return WASP_OK;
}

void wasp_destroy(struct wasp* pWasp)
{
  free(pWasp->pMem);
  pWasp->pMem = NULL;
  pWasp->memSize = 0;
}
