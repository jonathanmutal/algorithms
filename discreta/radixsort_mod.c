#include "API.h"
/**
 * Para más información del algoritmo: http://es.wikipedia.org/wiki/Ordenamiento_Radix
 * Este algoritmo se basa en la implementación de Austin G. Walters. Link: http://austingwalters.com/radix-sort-in-c/
 * Diferencia1: Implementamos un arreglo, donde cada casilla tiene una tupla [Indice, valor], donde ordenamos por valor.
 * Queremos devolver el arreglo ordenado de acuerdo a las tuplas, siguiendo el valor, respetando la posición inicial.
 */


u32 findLargestNum_mod(u32 **array, u32 size){
  // Encontrar el valor más grande del las tuplas del arreglo.

  u32 i;
  u32 largestNum = 0;
  
  for(i = 1; i <= size; i++){
    if(array[i][1] > largestNum)
      largestNum = array[i][1];
  }
  
  return largestNum;
}
 
void radix_mod(u32 **array, u32 size){

  // Entrada: array: Lo que vamos a querer ordenar, cada casilla tiene una tupla [Indice, Valor]. Lo ordenaremos por
  //                 valor, pero queremos seguir manteniendo la posición inicial.
  //          size: tamaño del arreglo.
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
  u32 significantDigit = 1;
  u32 largestNum = findLargestNum_mod(array, size);

/**------------------------------------------------------------------ **/

  // Iteración para alojar espacio en memoria.
  for(u32 i = 1; i <= size; i ++) {
    semiSorted[i] = calloc(2, sizeof(u32));
    array_aux[i] = calloc(2, sizeof(u32));
    array_aux[i][0] = array[i][0];  // En el primer elemento de la tupla, van los índices iniciales
    array_aux[i][1] = array[i][1];  // En el segundo elemento de la tupla, va el valor
  }

// Itera hasta que encuentre el número con mayor digito significativo.
  while (largestNum / significantDigit > 0){

    u32 bucket[11] = { 0 }; // Arreglo para guardar los números de digitos que estamos viendo.

    // Cuenta la cantidad de dígitos que van a ir dentro de bucket. Como no usamos la posición 0 del arreglo, sumamos 1.
    // (array_ayx[i][1] / significantDigit). El resultado dara el dígito que estamos ordenando, que irá en la posición 
    // de ese digito. Por ejemplo, si el digito es 0, ira en la posición 0, pero como le sumamos uno, irá en la posición 1.

    for (i = 1; i <= size; i++)
      bucket[((array_aux[i][1] / significantDigit) % 10) + 1]++;

    /**
     * Sumo elementos de bucket, para luego acomodarlos en el arreglo semiSorted. Luego de esta iteración tendremos la
     * posición de cada uno de los elementos en bucket.
     */

    for (i = 2; i < 11; i++)
      bucket[i] += bucket[i - 1];

    /**
    * Seguimos manteniendo los índices iniciales y valores iniciales, pero en diferentes posiciones.
    * Aquí ordenamos en semi-sorted de acuerdo a las posiciones de bucket.
    * Adquiere los índices después del final de cada ubicación de bucket.
    * Ordenamos del último elemento al primero del array_aux.
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
   * Rellenamos array con las posiciones de los elementos de array_aux(que habíamos rellenado incialmente) y
   * los valores. Y liberamos memoria.
   */

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

  // Revertimos el orden de en el que está ordenado.

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
