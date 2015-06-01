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

    if(G == NULL)
        return 0;

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

  /*Leer grafo, aloja el grafo pasado por la entrada stdin en memoria. 
    Para esto realizamos una traduccion de los vertices para que sus nombres
    queden entre 1 y n. Hacemos esto para poder indexar la tabla de vertices de 
    adyacencia por el vertice mismo y tener acceso a la tabla de adyacencia  de
    manera constante.

    Primero ignora los comentarios si el primer caracter de la linea
    es 'c'. Una vez que se terminan los comentarios scanea el numero de aristas
    y vertices. Ya teniendo estos datos puede alojar memoria para las distintas
    tablas necesarias. Luego entra en un for que va de 1 a la cantidad de aristas,
    tomando cada arista de la stadin, realizando la traducción para el vertice izquierdo 
    y derecho, y aumentando el grado de cada vertice en 1, y coloca el vertice izq
    traducido en una tabla auxiliar vertices_izq y el derecho en otra tabla
    auxiliar vertices_der, los vertices de un mismo indice en estas tablas representan
    una arista. Una vez que se tiene  la traducción y el grado de cada vertice se 
    pide memoria para sus listas de adyacencia de tamaño exacto utilizando el 
    grado y por ultimo, completo las listas de adyacencias de cada vertice
    usando los arreglos vertices_der y vertices_izq*/

  char c; // usado para la lectura
  char edge[5];// usado para la lectura
  char linea[80]; // usado para la lectura
  u32 n, m; // numero de vertices y numero de aristas
  u32 trad_der, trad_izq; // traducción del vertice derecho e izquierdo de la arista
  u32 izq,der; // vertice izquierdo y derecho de una arista
  u32 tam = 0; // tamaño de la tabla de traducción (traducidos hasta el momento)
  u32* vertices_der; // arreglo auxiliar para llevar todos los vertices derechos de las aristas
  u32* vertices_izq; // arreglo auxiliar para llevar todos los vertices izquierdos de las aristas
  u32* tabla_aux; // necesaria para saber la posición en la que debo poner un nuevo vertice 
                  // en la tabla de adyacencia de un vertice



  /*Ignoro todos los comentarios*/
  while((c = getc(stdin)) == 'c'){
    if(fgets(linea, 80, stdin) == NULL)
        return -1;
  }

  /*Leo la cantidad de vertices y aristas*/

  if(fscanf(stdin, "%s" "%u" "%u", edge, &n, &m) == 0)
    return -1;

  /*Ya teniendo el numero de vertices y aristas pido memoria para las tablas */
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


  /*Genero el coloreo y orden inicial*/
  for(u32 i = 1; i <= G->n; i++) {
      G->coloreo[i] = i;
      G->orden[i] = i;
  }


  /*En este for que va de 1 hasta m , voy leyendo cada una 
    de las aristas de stdin, traduzco los vertices y voy aumentando su grado*/
 

  for(u32 i = 0; i < G->m ; i++) {

      /*leo una arista y coloco los vertices en izq y der*/
      if(fscanf(stdin,"%s" "%u" "%u", edge, &izq, &der) == 0)
        return -1;


      trad_izq = 0;
      trad_der = 0;

      /*busco la traducción de el verice izq si */
      for(u32 i = 1; i <= tam; i++) {
          if(G->tabla_trad[i] == izq) {
              trad_izq = i;
              G->grado[trad_izq] = G->grado[trad_izq] + 1;
              break;
          }
      }

      /*Si trad_izq sigue en 0 es porque este vertice todavia no se a traducido
        aumento tam en 1 y coloco el vertice en esa posición del arreglo 
        y me quedo con su indice que va a ser la traduccion y el nombre del
        vertice durante toda la ejecución del programa, tambien aumento su grado*/

      if(trad_izq == 0) {
          tam += 1;   
          G->tabla_trad[tam] = izq;
          trad_izq = tam;
          G->grado[trad_izq] = G->grado[trad_izq] + 1;
        
      }

      /*coloco la traducción en la tabla de vertices_izq */
      vertices_izq[i] = trad_izq; 

      /*igual ahora pero para el vertice derecho*/
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
  
  /*En este punto ya he traducido todos los vertices y tengo el grado de cada 
    uno, pido memoria para sus tablas de adyacencia usando su grado*/
  for(u32 i = 1; i <= G->n; i++) {
      G->list_ady_vert[i] = calloc(G->grado[i], sizeof(u32));
    }


  /*En este for , voy llenando las tablas de aydacencia de cada vertices 
    ultilizando los arreglos auxliares de vertices izquieros y derechos 
    que para un mismo indice son una arista*/ 
    
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

    if(G == NULL) {
        return 0;
    }

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
    u32 *dsatur; // tabla para llevar el dsatur de cada vertice
    u32 *tabla_aux; // tabla auxiliar necesaria para el coloreo greedy
    u32 vertice; //vertice eligo para colorear     
    u32 coloractual; // color que acabo de utilizar para colorear el vertice
    u32 color_nuevo; // bandera que es 1 si el el color usado para colorear el 
                     // es unuevo , 0 sino.

    /* alojo memoria para llevar el dsatur y la tabla auxiliar*/

    dsatur = calloc(G->n + 1, sizeof(u32));
    tabla_aux = calloc(G->n + 1, sizeof(u32));

    /*---------------------------------------*/

    
    /*Inicializo el coloreo en 0*/
    for(u32 i = 1; i <= G->n; i++) {
        G->coloreo[i] = 0;
    } 
    G->colores_usados = 0;

    /*Ordeno los vertices por grado Welsh Powell*/
    

    OrdenWelshPowell(G);

    /*En este for, en cada iteración se eligira el vertice de mayor dsatur(
      si hay varios desempata con el grado), y se  actualiza el dsatur de cada
      vecino del vertice coloreado en caso de ser necesario*/     
    for (u32 i = 1 ; i <= G->n ; i++) { 

       /************ busqueda del vertice de mayor dsatur y grado************ */
       

        u32 max;
        max = G->orden[1];

        /*En este for, recorro G->orden buscando el vertice de mayor dsatur como
          G->orden esta ordenado Welsh Powell el primer vertice que encuentre 
          con la mayor saturación tambien sera al mismo tiempo el de mayor grado
          tambien verifico que el vertice que este tomando no este coloreado aún
          */
        for(u32 j = 1; j <= G->n; j++) {
            if((G->coloreo[G->orden[j]] == 0) && dsatur[max] < dsatur[G->orden[j]]) {
                max = G->orden[j];
                if(dsatur[max] == G->colores_usados) {
                    break;
                }
            }
        }
            
        /*************************coloreo de vertice***************************/       
        vertice = max;

        /*coloreo el vertice de la forma greedy, tomando el minimo color no 
          usado entre los colores de los vecinos*/

        G->coloreo[vertice] = greedy_min_col(G, vertice, tabla_aux);
        coloractual = G->coloreo[vertice];

        /**********************************************************************/

        /*verifico si es un color nuevo y aumento colores usados en dicho caso*/

        if(G->colores_usados < G->coloreo[vertice]) {
            G->colores_usados+= 1;
            color_nuevo = 1;
        } else { 
            color_nuevo = 0;
        
        }
        /**********************************************************************/

        /*--------actualización del dsatur de cada vecino del vertice---------*/

        /*En este for actualizo el dsatur de cada vecino del vertice en caso de 
         ser necesario. Si el vecino ya fue coloreado no hace falta aumentar 
         su dsatur por lo que no se actualiza. Si el vecino aún no ha sido 
         coloreado entonces debo fijarme si alguno de los vecinos del vecino 
         a actulizar fue coloreado con el mismo color, si esto pasa entonces no
         debo aumentar su dsatur, si tengo que aumentarlo en el caso contrario. 
         Si el color es nuevo ningun vecino del vecino puede haber sido
         colereado con dicho color por lo que actualizo directamente saleantean_
         dome la busqueda del color entre los vecinos del vecino a actualizar*/

        for(u32 j = 0; j < G->grado[vertice]; j++) {
            u32 vec = G->list_ady_vert[vertice][j];
            u32 actualizar = 0;// es 0 si el vecino ya se ha coloreado, 1 sino
            
            if(G->coloreo[vec] == 0){
                actualizar = 1;
            }
        
            /* Si el color no es nuevo y si aun no se a coloreado este vertice
             entro al if , en el for si encuentro un vecino distinto del 
             vertice recien coloreado y que este coloreado con el mismo color
             actualizo su dsatur*/
            if(!color_nuevo && actualizar) {    
                for(u32 i = 0; i < G->grado[vec] ; i++) {  
                    if(G->list_ady_vert[vec][i] != vertice && (G->coloreo[G->list_ady_vert[vec][i]] == coloractual)) {
                        actualizar = 0;
                        break;
                    }
                 }
            }
                        
            if(actualizar) {
                dsatur[vec] = dsatur[vec] + 1;
            }

        }
        /*********************************************************************/
    }
    
    free(dsatur);
    free(tabla_aux);

    return G->colores_usados;
}


/* hace un swap de el vertice en la posición i con el de la posicion j en la tabla*/
void swap(u32 i, u32 j, u32* tabla) {
    u32 aux;

    aux = tabla[i];
    tabla[i] = tabla[j];
    tabla[j] = aux;
}


void OrdenAleatorio(GrafP G) {

     /* Genera un orden aleatorio de las clases de colores , de la siguiente
     forma, en un array de tamaño cantidad colores usados : colores_aux , pone
     todos los colores usados y en un for (que pasa por todos los indices de
     de colores_aux) eligo una  posicion random y hago swap del color que esta 
     en esa posicion random con la del color que esta en la posición i. Una vez
     que tengo esta lista de colores ordenada de forma random, voy pasando todos 
     los vertices en dicho orden de colores a un arreglo orden_result que sera
     intercambiado con el orden que ya tenia el grafo. Al inicio corro orden 
     GrandeChico para tener todos los vertices de un mismo color contiguos 
     asi solo hace falta encontrar el inicio de cada color e y pasando todos los
     vertices de dicho color a orden_result(poniendolos en el orden aleatorio 
     generado)*/

    u32* colores_aux = calloc(G->colores_usados + 1, sizeof(u32));// tabla donde voy desordenar los colores de forma random
    u32* orden_result = calloc(G->n + 1,sizeof(u32)); // aca va el orden resultado 
    u32 pos_random; // posicion random para hacer swap
    u32 pos; // pos va a ser necesaria para encontrar el inicio de una clase de color
    u32 tam = 0;//para llevar hasta donde tengo elementos en orden_result
    u32 color;

    srand(time(NULL));

    /*Ordeno Grande y chico al principio para tener todos vertices de una misma
      clase contiguos(al final lo necesito)*/

    GrandeChico(G);
    
    /*Lleno la tabla_aux con los colores ordenados de menor a mayor*/
    for(u32 i = 1; i <= G->colores_usados; i++) {
        colores_aux[i] = i;
    }

    /*Desordeno la lista de colores en este for , haciendo swap del vertice 
      en la posición i con uno en una posición random*/ 
    for(u32 i = 1 ; i <= G->colores_usados; i++) {
        pos_random = (rand() % G->colores_usados) + 1;
        swap(i , pos_random, colores_aux);
    }


    /*En este punto ya tengo un orden random de los colores, ahora voy a 
      ir pasando a el arreglo orden_result todos los vertices del mismo color
      en el orden que tengo en colores_aux*/

    /*En este for voy a ir pasando todos los vertices de cada clase de color 
      en el nuevo orden*/

    for(u32 i = 1; i <= G->colores_usados; i++) {
        color = colores_aux[i];
        pos = 1;
        
        /*recorro G->orden buscando el comienzo de la clase de color */
        for(u32 j = 1; j <= G->n; j++) {
            if(G->coloreo[G->orden[j]] == color) {
               pos = j;
               break;
            }
        }
        /*pongo en el array todos los vertices con ese color y paro el while
          cuando llego a vertice que arranca la proxima clase de color*/
        while(G->coloreo[G->orden[pos]] == color && pos <= G->n) {
            tam = tam + 1;
            orden_result[tam] = G->orden[pos];
            pos = pos + 1;
        }
     
    }

    /*descarto el antiguo orden y lo reemplazo por el nuevo*/
    free(G->orden);
    G->orden = orden_result;
    free(colores_aux);  
 
}
