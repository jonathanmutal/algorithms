#include "API.h"

u32 findLargestNum_mod(u32 **array, u32 size){

  u32 i;
  u32 largestNum = 0;
  
  for(i = 1; i <= size; i++){
    if(array[i][1] > largestNum)
      largestNum = array[i][1];
  }
  
  return largestNum;
}
 
void radix_mod(u32 **array, u32 size){

  u32 i;
  u32 *semiSorted[size + 1];
  u32 *array_aux[size + 1];
  u32 significantDigit = 1;
  u32 largestNum = findLargestNum_mod(array, size);

  for(u32 i = 1; i <= size; i ++) {
    semiSorted[i] = calloc(2, sizeof(u32));
    array_aux[i] = calloc(2, sizeof(u32));
    array_aux[i][0] = array[i][0];
    array_aux[i][1] = array[i][1];
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
    array[i][0] = array_aux[i][0];
    array[i][1] = array_aux[i][1];
    free(array_aux[i]);
    free(semiSorted[i]);
    array_aux[i] = NULL;
    semiSorted[i] = NULL;
  }

}

void radix_mod_rever(u32 **array, u32 size) {
  radix_mod(array, size);
  u32 tmp0 = 0;
  u32 tmp1 = 0;
  for(u32 i = 1, j = size; i <= size/2 && j > size/2; i++, j--){
    tmp0 = array[i][0];
    tmp1 = array[i][1];
    array[i][0] = array[j][0];
    array[i][1] = array[j][1];
    array[j][0] = tmp0;
    array[j][1] = tmp1;
  }
}
