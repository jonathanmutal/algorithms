#include "API.h"
// Para print array(DEBUGEO)
void printArray(u32 **array, int mode, u32 size){
  
  u32 i;
  printf("[ ");
  for (i = 1; i <= size; i++)
    printf("%u ", array[i][mode]);
  printf("]\n");
}

void printOrden(u32 *array, u32 size){
  
  u32 i;
  printf("[ ");
  for (i = 1; i <= size; i++)
    printf("%u ", array[i]);
  printf("]\n");
}

u32 findLargestNum(u32 *array, u32 size){

  u32 i;
  u32 largestNum = 0;
  
  for(i = 1; i <= size; i++){
    if(array[i] > largestNum)
      largestNum = array[i];
  }
  
  return largestNum;
}
 
void radixSort(u32 *array, u32 *orden, u32 size){

  u32 i;
  u32 *semiSorted[size + 1];
  u32 *array_aux[size + 1];
  u32 significantDigit = 1;
  u32 largestNum = findLargestNum(array, size);

  for(u32 i = 1; i <= size; i ++) {
    semiSorted[i] = calloc(2, sizeof(u32));
    array_aux[i] = calloc(2, sizeof(u32));
    array_aux[i][0] = i;
    array_aux[i][1] = array[i];
  }


  while (largestNum / significantDigit > 0){

    u32 bucket[11] = { 0 };

    for (i = 1; i <= size; i++)
      bucket[((array_aux[i][1] / significantDigit) % 10) + 1]++;

    for (i = 2; i < 11; i++)
      bucket[i] += bucket[i - 1];

    for (i = size; i > 0; i--){
      semiSorted[bucket[((array_aux[i][1] / significantDigit) % 10) + 1]][0] = array_aux[i][0];
      semiSorted[bucket[((array_aux[i][1] / significantDigit) % 10) + 1] --][1] = array_aux[i][1];
    }


    for (i = 1; i <= size; i++){
      array_aux[i][0] = semiSorted[i][0];
      array_aux[i][1] = semiSorted[i][1];
    }

    significantDigit *= 10;
  }

  for(u32 i = 1; i <= size; i++){
    orden[i] = array_aux[i][0];
    free(array_aux[i]);
    free(semiSorted[i]);
    array_aux[i] = NULL;
    semiSorted[i] = NULL;
  }

}

void radix(u32 *array, u32 *orden, u32 size) {
  radixSort(array, orden, size);
}

void radix_rever(u32 *array, u32 *orden, u32 size) {
  radix(array, orden, size);
  u32 tmp = 0;
  for(u32 i = 1, j = size; i <= size/2 && j > size/2; i++, j--){
    tmp = orden[i];
    orden[i] = orden[j];
    orden[j] = tmp;
  }
  printOrden(orden, size);
}
