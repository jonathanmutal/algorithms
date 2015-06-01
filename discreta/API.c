#include "API.h"

struct GrafSt {
  u32 **list_ady_vert;
  u32 *orden;
  u32 *tabla_trad;
  u32 *coloreo;
  u32 *grado;
  u32 colores_usados;
  u32 n;
  u32 m;
};

GrafP NuevoGraf(void) {
  GrafP GP = calloc(1, sizeof(struct GrafSt));
  return GP;
}

int DestruirGraf(GrafP G) {
    for(u32 i = 1; i <= G->n; i++) free(G->list_ady_vert[i]);
    free(G->list_ady_vert);
    free(G->orden);
    free(G->tabla_trad);
    free(G->coloreo);
    free(G->grado);
    free(G);
    return 1;
}

int LeerGrafo(GrafP G) {
  char c;
  char edge[5];
  char linea[80];
  u32 n, m;
  u32 trad_der, trad_izq;
  u32 izq,der;
  u32 tam = 0;
  u32* vertices_der;
  u32* vertices_izq;
  u32* tabla_aux;

  while((c = getc(stdin)) == 'c'){
    if(fgets(linea, 80, stdin) == NULL)
        return -1;
  }

  if(fscanf(stdin, "%s" "%u" "%u", edge, &n, &m) == 0)
    return -1;

  G->n = n;
  G->m = m;
  G->list_ady_vert = calloc(n + 1, sizeof(u32*));
  G->orden = calloc(n + 1, sizeof(u32));
  G->coloreo = calloc(n + 1,sizeof(u32));
  G->tabla_trad = calloc(n + 1, sizeof(u32));
  G->grado = calloc(n + 1, sizeof(u32));
  G->colores_usados = n;

  vertices_izq = calloc(m, sizeof(u32));
  vertices_der = calloc(m, sizeof(u32));
  tabla_aux = calloc(n + 1, sizeof(u32));

  for(u32 i = 1; i <= G->n; i++) {
      G->coloreo[i] = i;
      G->orden[i] = i;
  }

  for(u32 i = 0; i < G->m ; i++) {


      if(fscanf(stdin,"%s" "%u" "%u", edge, &izq, &der) == 0)
        return -1;

      trad_izq = 0;
      trad_der = 0;


      for(u32 i = 1; i <= tam; i++) {
          if(G->tabla_trad[i] == izq) {
              trad_izq = i;
              G->grado[trad_izq] = G->grado[trad_izq] + 1;
              break;
          }
      }

      if(trad_izq == 0) {
          tam += 1;   
          G->tabla_trad[tam] = izq;
          trad_izq = tam;
          G->grado[trad_izq] = G->grado[trad_izq] + 1;
        
      }

      vertices_izq[i] = trad_izq; 

      for(u32 i = 1; i <= tam; i++) {
          if(G->tabla_trad[i] == der) {
              trad_der = i;
              G->grado[trad_der] = G->grado[trad_der] + 1;
              break;
          }
      }
                
      if(trad_der == 0) {
          tam += 1;   
          G->tabla_trad[tam] = der;
          trad_der = tam;
          G->grado[trad_der] = G->grado[trad_der] + 1;
      }

      vertices_der[i] = trad_der;   
  }
  
  for(u32 i = 1; i <= G->n; i++) {
      G->list_ady_vert[i] = calloc(G->grado[i], sizeof(u32));
    }
   
  for(u32 i = 0; i < G->m ; i++) {
      izq = vertices_izq[i];
      der = vertices_der[i];

      G->list_ady_vert[izq][tabla_aux[izq]] = der;
      tabla_aux[izq] = tabla_aux[izq] + 1;

      G->list_ady_vert[der][tabla_aux[der]] = izq;
      tabla_aux[der] = tabla_aux[der] + 1;
      
      }
 
  free(tabla_aux);
  free(vertices_izq);
  free(vertices_der);
  return n;
}


int ImprimeGrafo(GrafP G) {
    printf("p edge %u %u\n", G->n, G->m);

    for(u32 i = 1; i <= G->n; i++) {
        for (u32 j = 0 ; j < G->grado[i]; j++) {
            if(i < G->list_ady_vert[i][j]) {
                printf("e %u %u\n", G->tabla_trad[i], G->tabla_trad[G->list_ady_vert[i][j]]);
            }
        }
    }
    return 1;
}

u32 NumeroVerticesDeColor(GrafP G, u32 i) {
    u32 ncolores = 0;
    for(u32 j = 1; j <= G->n; j++) {
        if(G->coloreo[j] == i){
            ncolores += 1;
        }
    }
    return ncolores;
}

u32 ImprimirColor(GrafP G, u32 i) {
    u32 tabla_aux[G->n];
    u32 ncolores = 0;

    for(u32 i = 1; i <= G->n; i++) {
        if(G->coloreo[i] == i) {
            tabla_aux[ncolores] = G->tabla_trad[i];
            ncolores += 1;
        }
    }

    if(ncolores > 0) {
        printf("Vertices de Color %u: \n", i);
        for(u32 i = 0; i < ncolores - 1; i++){
            printf("%u, ", tabla_aux[i]);
        }
        printf("%u.\n", tabla_aux[ncolores - 1]);
    } else {
        printf("No hay vertices de color %u\n", i);
    }

    return ncolores;
}

u32 CantidadDeColores(GrafP G) {
    return G->colores_usados;
}

u32 Greedy(GrafP G) {
    G->coloreo[G->orden[1]] = 1;
    G->colores_usados = 1;

/** -------------------------------------- */

    u32 pos = 0; // Para ayudarnos a encontrar el color.
    u32 *aux = calloc(G->n + 1, sizeof(u32)); // Tabla aux donde se almacenara los colores ya usados.

/** -------------------------------------- */

    // Dejamos sin color a todos los vertices
    for(u32 i = 1; i <= G->n; i++)
        G->coloreo[i] = 0;

    // Recorremos todos los vertices. Coloreando de acuerdo al orden.
    for(u32 i = 1; i <= G->n; i++){

        pos = 0;

        // Dado un vertice por el orden, procesamos los vecinos de esté vertice.
        // Agregamos los colores al arreglo auxiliar. Pos "i" almacenamos el color "i".
        // Las posiciones "i" que tengan 0, son colores que no se han usado.

        for(u32 j = 0; j < G->grado[G->orden[i]]; j++){
            aux[G->coloreo[G->list_ady_vert[G->orden[i]][j]]] = G->coloreo[G->list_ady_vert[G->orden[i]][j]];
        }

        // Buscamos en la tabla hasta que haya un color sin usar, es decir hasta que en alguna posición j el valor de
        // esa casilla sea 0. Mientras tanto, reiniciamos la tabla(rellamos con 0's). Si encontramos la posicion j,
        // seteamos j a pos, así podemos reiniciarla a partir de allí.

        for(u32 j = 1; j <= G->colores_usados; j++){
            if(aux[j] == 0) {
                G->coloreo[G->orden[i]] = j;
                pos = j;
                break;
            } else {
                aux[j] = 0;
            }
        }

        // Si no encontramos la posicion j, añadimos un nuevo color y coloreamos ese vertice con este color.

        if(pos == 0) {
            G->colores_usados += 1;
            G->coloreo[G->orden[i]] = G->colores_usados;
        }

        // Reiniciamos la tabla aux, seteando todo en 0.

        for(u32 j = pos; j <= G->colores_usados; j ++) {
            aux[j] = 0;
        }
    }

    free(aux);
    aux = NULL;
    return G->colores_usados;
}

void OrdenWelshPowell(GrafP G) {
    // Comentado en radixsort.c
    radix(G->grado, G->orden, G->n);
}

void ChicoGrande(GrafP G) {

/** -------------------------------------- */

    u32 *aux[G->colores_usados + 1]; // Auxiliar de tamaño colores_usados + 1(No utilizamos el 0). Lo usamos para contar
                                     // el número de colores. Es decir en la pos "i" del arreglo sera el color "i". En cada
                                     // posición(color) almacenaremos el número de vertices con el color de la posición.

/** -------------------------------------- */

    // Aux es un arreglo, donde cada elemento es una t-upla. En la posición 0 de la t-upla ira la posición inicial(color)
    // y en la 1 ira un valor, en esté caso el número de vertices con ese color.

    for(u32 i = 1; i <= G->colores_usados; i++){
        aux[i] = calloc(2, sizeof(u32));
        aux[i][0] = i;
    }

    // Contamos cuantos vertices de cada color hay.

    for(u32 i = 1; i <= G->n; i++)
        aux[G->coloreo[i]][1] += 1;

    // Ordenamos por cantidad de color(elemento 2 de la t-upla), de menor a mayor.

    radix_mod(aux, G->colores_usados);

    // Aquí sumamos el elemento 2 de la t-upla(cantidad de color) de cada color, con el color anterior.

    for(u32 i = 2; i <= G->colores_usados; i ++)
        aux[i][1] += aux[i - 1][1];

    // En esta iteración ordenamos los vertices en orden y liberamos espacio en memoria.
    // Se ordena de acuerdo a los valores de aux.

    for(u32 i = 1; i <= G->colores_usados; i++) {

        for(u32 j = 1; j <= G->n; j++) {
            if(aux[i][0] == G->coloreo[j]) {
                G->orden[aux[i][1]--] = j;
            }
        }

        free(aux[i]);
    }
}

void GrandeChico(GrafP G) {
    // Idem que ChicoGrande, salvo que revertimos el orden en radix_mod_rever.

    u32 *aux[G->colores_usados + 1];


    for(u32 i = 1; i <= G->colores_usados; i++){
        aux[i] = calloc(2, sizeof(u32));
        aux[i][0] = i;
    }

    for(u32 i = 1; i <= G->n; i++)
        aux[G->coloreo[i]][1] += 1;

    radix_mod_rever(aux, G->colores_usados);

    for(u32 i = 2; i <= G->colores_usados; i ++)
        aux[i][1] += aux[i - 1][1];

    for(u32 i = 1; i <= G->colores_usados; i++) {

        for(u32 j = 1; j <= G->n; j++) {
            if(aux[i][0] == G->coloreo[j]) {
                G->orden[aux[i][1]--] = j;
            }
        }

        free(aux[i]);
    }
}

void Revierte(GrafP G) {
    // Comentado en radixsort.c
    radix(G->coloreo, G->orden, G->n);
}

u32 greedy_min_col(GrafP G , u32 vertice, u32 *tabla_aux) {
    u32 color = 0;
    for(u32 i = 0; i < G->grado[vertice]; i++) {

        tabla_aux[G->coloreo[G->list_ady_vert[vertice][i]]] = G->coloreo[G->list_ady_vert[vertice][i]];
    }

    for(u32 i = 1; i <= G->colores_usados; i++) {
        if(tabla_aux[i] == 0) {
            color = i;
            break;
        }
    }
    if(color == 0){
        color = G->colores_usados + 1;
    }
    for(u32 i = 1; i <= G->colores_usados; i++) {
        tabla_aux[i] = 0;
    }
    
    return color;

}

u32 DSATUR (GrafP G) {
    u32 *dsatur;
    u32 *tabla_aux;
    u32 vertice;        
    u32 coloractual;
    u32 color_nuevo;

    /* alojo memoria para llevar el dsatur */

    dsatur = calloc(G->n + 1, sizeof(u32));
    tabla_aux = calloc(G->n + 1, sizeof(u32));

    /*---------------------------------------*/

    
    /*Inicializo el coloreo en 0*/
    for(u32 i = 1; i <= G->n; i++) {
        G->coloreo[i] = 0;
    } 
    G->colores_usados = 0;

    /*Ordeno los vertices por grado*/

    OrdenWelshPowell(G);

    /*Coloreo dsatur*/     
    for (u32 i = 1 ; i <= G->n ; i++) { 

       /* busqueda del vertice de mayor dsatur y grado */
        u32 max;
        max = G->orden[1];

        for(u32 j = 1; j <= G->n; j++) {
            if((G->coloreo[G->orden[j]] == 0) && dsatur[max] < dsatur[G->orden[j]]) {
                max = G->orden[j];
                if(dsatur[max] == G->colores_usados) {
                    break;
                }
            }
        }

        /*coloreo el vertice de la forma greedy*/
        vertice = max;
        G->coloreo[vertice] = greedy_min_col(G, vertice, tabla_aux);
        coloractual = G->coloreo[vertice];

        /*verifico si es un color nuevo y aumento colores usados en dicho caso*/

        if(G->colores_usados < G->coloreo[vertice]) {
            G->colores_usados+= 1;
            color_nuevo = 1;
        } else { 
            color_nuevo = 0;
        }

        /*actualización del dsatur de cada vecino del vertice*/
        for(u32 j = 0; j < G->grado[vertice]; j++) {
            u32 vec = G->list_ady_vert[vertice][j];
            u32 actualizar = 0;
            
            if(G->coloreo[vec] == 0){
                actualizar = 1;
            }
            
            if(!color_nuevo && actualizar) {    
                for(u32 i = 0; i < G->grado[vec] ; i++) {     
                    if(G->list_ady_vert[vec][i] == vertice || (G->coloreo[G->list_ady_vert[vec][i]] == coloractual)) {
                        actualizar = 0;
                        break;
                    }
                }
            }
                        
            if(actualizar) {
                dsatur[vec] = dsatur[vec] + 1;
            }

        }
    }
    
    free(dsatur);
    free(tabla_aux);

    return G->colores_usados;
}

void swap(u32 i, u32 j, u32* tabla) {
    u32 aux;

    aux = tabla[i];
    tabla[i] = tabla[j];
    tabla[j] = aux;
}


void OrdenAleatorio(GrafP G) {

    u32* colores_aux = calloc(G->colores_usados + 1, sizeof(u32));
    u32* orden_result = calloc(G->n + 1,sizeof(u32));
    u32 pos_random, pos, tam, color;
    tam = 0;

    srand(time(NULL));

    GrandeChico(G);

    for(u32 i = 1; i <= G->colores_usados; i++) {
        colores_aux[i] = i;
    }

    for(u32 i = 1 ; i <= G->colores_usados; i++) {
        pos_random = (rand() % G->colores_usados) + 1;
        swap(i , pos_random, colores_aux);
    }
    for(u32 i = 1; i <= G->colores_usados; i++) {
        color = colores_aux[i];
        pos = 1;

        for(u32 j = 1; j <= G->n; j++) {
            if(G->coloreo[G->orden[j]] == color) {
               pos = j;
               break;
            }
        }
        while(G->coloreo[G->orden[pos]] == color && pos <= G->n) {
            tam = tam + 1;
            orden_result[tam] = G->orden[pos];
            pos = pos + 1;
        }
     
    }
    free(G->orden);
    G->orden = orden_result;
    free(colores_aux);  
 
}

