#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PROXIMA_POSICAO_SEM_HEADER (int)buffer2[i + 1] + 3

void ReadBinFile(char *argv) {
  static const size_t BufferSize = 259; //259, memoria 256 + 3 bits processador
  
  int i;
  FILE *ptr;
  unsigned char buffer2[BufferSize];

  ptr = fopen(argv, "rb");
  const size_t fileSize =
      fread(buffer2, sizeof(unsigned char), BufferSize, ptr);

  if(fileSize < 4 || fileSize > 259){
    printf("ERRO: Número de bytes incompatível\n");
    return;
  }
  if(buffer2[0] != 42){
    printf("ERRO: Número Mágico não é 42\n");
    return;
  }
  

  int isFinished = 0;
  bool flagN;
  bool flagZ;
  
  for (i = buffer2[2] + 3; i < (fileSize / sizeof(unsigned char)); i++) {
    if (isFinished == 1) {
      break;
    }

    switch ((int)buffer2[i]) {
    case 0:
      break;
    case 16:
      buffer2[PROXIMA_POSICAO_SEM_HEADER] = (int)buffer2[1];
      i++;
      break;
    case 32:
      buffer2[1] = buffer2[PROXIMA_POSICAO_SEM_HEADER];
      i++;
      break;
    case 48:
      buffer2[1] += buffer2[PROXIMA_POSICAO_SEM_HEADER];
      i++;
      break;
    case 96:
      buffer2[1] = (int)buffer2[1] * (-1);
      break;
    case 128:
      i = PROXIMA_POSICAO_SEM_HEADER - 1;
      break;
    case 144:
      if (flagN == true) {
        i = PROXIMA_POSICAO_SEM_HEADER - 1;
      }
    case 160:
      if (flagZ == true) {
        i = PROXIMA_POSICAO_SEM_HEADER - 1;
      }
      break;
    case 240:
      isFinished = 1;
    }
    
    if(buffer2[1] == 0){
      flagZ = true;
    }
    else{
      flagZ = false;
    }
    
    if(buffer2[1] > 127){
      flagN = true;
    }
    else{
      flagN = false;
    }
    
    buffer2[2] = i - 3;
  }
  printf("Acumulador: %d\n", buffer2[1]);
  printf("PC: %d\n", buffer2[2]);
  printf("Flag N: %d\n", flagN);
  printf("Flag Z: %d\n", flagZ);
  for (i = 3; i < (fileSize / sizeof(unsigned char)); i++) {
    printf(" %d", (int)buffer2[i]);
  }
  fclose(ptr);
}

int main(int argc, char *argv[]) {
  ReadBinFile(argv[1]);
  return 0;
}