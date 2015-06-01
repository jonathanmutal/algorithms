#include "API.h"
/**
 * Para más información del algoritmo: http://es.wikipedia.org/wiki/Ordenamiento_Radix
 * Este algoritmo se basa en la implementación de Austin G. Walters. Link: http://austingwalters.com/radix-sort-in-c/
 * Diferencia1: Implementamos un arreglo, donde cada casilla tiene una tupla [Indice, valor], donde ordenamos por valor.
 * Una vez que esta ordenado por valor, rellenamos el arreglo de orden con los Indices, de acuerdo a como este ordenado
 * por valor.
 * Diferencia2: Ordenamos de mayor a menor.
 */

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
  // Encontrar el número más grande del arrego

  u32 i;
  u32 largestNum = 0;
  
  for(i = 1; i <= size; i++){
    if(array[i] > largestNum)
      largestNum = array[i];
  }
  
  return largestNum;
}
 
void radixSort(u32 *array, u32 *orden, u32 size){
  // Entrada: array: Lo que vamos a querer ordenar.
  //          orden: Las posiciones ya ordenado, es el resultado.
  //          size: Tamaño del arreglo.
  // Se usa base 10 para ordenar.

/**------------------------------------------------------------------ **/

  u32 i;
  /** 
   * Para el proceso de ordenación. Arreglo semi-ordenado, para que en cada iteración se ordene. Es un arreglo donde en
   * cada casilla es una tupla de índice y valor([Indice, Valor])
   */
  u32 *semiSorted[size + 1];
  /** 
   * Arreglo auxiliar para mantener la posiciones inciales. Es un arreglo donde cada casilla es un tupla de ínidce y
   * valor.
   */
  u32 *array_aux[size + 1];
  u32 significantDigit = 1;    // Digito significativo. Aumenta en potencias de 10, para ir ordenando digitos.
  u32 largestNum = findLargestNum(array, size);  // Número más largo(mayor digito significativo).

/** ------------------------------------------------------------------ **/

  // Iteración para alojar espacio en memoria.
  for(u32 i = 1; i <= size; i ++) {
    semiSorted[i] = calloc(2, sizeof(u32));
    array_aux[i] = calloc(2, sizeof(u32));
    array_aux[i][0] = i;          // En el primer elemento de la tupla, van los índices iniciales
    array_aux[i][1] = array[i];   // En el segundo elemento de la tupla, va el valor
  }


  // Itera hasta que encuentre el número con mayor digito significativo.
  while (largestNum / significantDigit > 0){

    u32 bucket[11] = { 0 };  // Arreglo para guardar los números de digitos que estamos viendo.

    // Cuenta la cantidad de dígitos que van a ir dentro de bucket. Como no usamos la posición 0 del arreglo, sumamos 1.
    // (array_ayx[i][1] / significantDigit). El resultado dara el dígito que estamos ordenando, que irá en la posición 
    // de ese digito. Por ejemplo, si el digito es 0, ira en la posición 0, pero como le sumamos uno, irá en la posición 1.

    for (i = 1; i <= size; i++)
      bucket[((array_aux[i][1] / significantDigit) % 10) + 1]++;

    /**
     * Sumo elementos de bucket, para luego acomodarlos en el arreglo semiSorted. Luego de esta iteración tendremos la
     * posición de cada uno de los elementos en bucket.
     */

    for (i = 10; i > 1; i--)
      bucket[i - 1] += bucket[i];

    /**
    * Seguimos manteniendo los índices iniciales y valores iniciales, pero en diferentes posiciones.
    * Aquí ordenamos en semi-sorted de acuerdo a las posiciones de bucket.
    * Adquiere los índices después del final de cada ubicación de bucket.
    * Ordenamos del último elemento al primero del array_aux.
    * En bucket estara almacenada las posiciones de cada número(ordenada por el dígito).
    */

    for (i = size; i > 0; i--){
      semiSorted[bucket[((array_aux[i][1] / significantDigit) % 10) + 1]][0] = array_aux[i][0];
      semiSorted[bucket[((array_aux[i][1] / significantDigit) % 10) + 1] --][1] = array_aux[i][1];
    }

    // Rellenamos el array_aux con la nueva ordenación.

    for (i = 1; i <= size; i++){
      array_aux[i][0] = semiSorted[i][0];
      array_aux[i][1] = semiSorted[i][1];
    }

    significantDigit *= 10;
  }

  /**
   * Rellenamos orden sólo con las posiciones de los elementos de array_aux(que habíamos rellenado incialmente) y
   * liberamos memoria.
   */

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

