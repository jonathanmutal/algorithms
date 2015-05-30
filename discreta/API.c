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

  while((c = getc(stdin)) == 'c'){
    fgets(linea, 80, stdin);
  }

  fscanf(stdin, "%s" "%u" "%u", edge, &n, &m);
  
  G->n = n;
  G->m = m;
  G->list_ady_vert = calloc(n + 1, sizeof(u32*));
  G->orden = calloc(n + 1, sizeof(u32));
  G->coloreo = calloc(n + 1,sizeof(u32));
  G->tabla_trad = calloc(n + 1, sizeof(u32));
  G->grado = calloc(n + 1, sizeof(u32));
  G->colores_usados = n;

  u32 *tabla_aux = calloc(n + 1, sizeof(u32));

  for(u32 i = 1; i <= G->n; i++) {
      tabla_aux[i] = 30;
      G->list_ady_vert[i] = calloc(30, sizeof(u32));
      G->coloreo[i] = i;
      G->orden[i] = i;
  }

  for(u32 i = 0; i < G->m ; i++) {


      fscanf(stdin,"%s" "%u" "%u", edge, &izq, &der);
      trad_izq = 0;
      trad_der = 0;

      for(u32 i = 1; i <= tam; i++) {
        if(G->tabla_trad[i] == izq) {
            trad_izq = i;
            break;
        }
      }

      if(trad_izq == 0) {
        tam += 1;   
        G->tabla_trad[tam] = izq;
        trad_izq = tam;
      }


      for(u32 i = 1; i <= tam; i++) {
        if(G->tabla_trad[i] == der) {
          trad_der = i;
          break;
        }
      }

      if(trad_der == 0) {
          tam += 1;   
          G->tabla_trad[tam] = der;
          trad_der = tam;
      }


      if(tabla_aux[trad_izq] == G->grado[trad_izq]) {
         tabla_aux[trad_izq] += 30;
         G->list_ady_vert[trad_izq] = realloc(G->list_ady_vert[trad_izq], tabla_aux[trad_izq] * sizeof(u32));
      }
      G->list_ady_vert[trad_izq][G->grado[trad_izq]] = trad_der;
      G->grado[trad_izq] = G->grado[trad_izq] + 1;


      if(tabla_aux[trad_der] == G->grado[trad_der]) {
         tabla_aux[trad_der] += 30;
         G->list_ady_vert[trad_der] = realloc(G->list_ady_vert[trad_der], tabla_aux[trad_der] * sizeof(u32));
      }
      G->list_ady_vert[trad_der][G->grado[trad_der]] = trad_izq;
      G->grado[trad_der] = G->grado[trad_der] + 1;

  }
    
  free(tabla_aux);
  tabla_aux = NULL;
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

    u32 pos = 0;
    u32 *aux = calloc(G->n + 1, sizeof(u32));

    for(u32 i = 1; i <= G->n; i++)
        G->coloreo[i] = 0;

    for(u32 i = 1; i <= G->n; i++){

        pos = 0;

        for(u32 j = 0; j < G->grado[G->orden[i]]; j++){
            aux[G->coloreo[G->list_ady_vert[G->orden[i]][j]]] = G->coloreo[G->list_ady_vert[G->orden[i]][j]];
        }

        for(u32 j = 1; j <= G->colores_usados; j++){
            if(aux[j] == 0) {
                G->coloreo[G->orden[i]] = j;
                pos = j;
                break;
            } else {
                aux[j] = 0;
            }
        }

        if(pos == 0) {
            G->colores_usados += 1;
            G->coloreo[G->orden[i]] = G->colores_usados;
        }

        for(u32 j = pos; j <= G->colores_usados; j ++) {
            aux[j] = 0;
        }
    }

    free(aux);
    aux = NULL;
    return G->colores_usados;
}

void OrdenWelshPowell(GrafP G) {
    radix(G->grado, G->orden, G->n);
}

void ChicoGrande(GrafP G) {

    u32 *aux[G->colores_usados + 1];


    for(u32 i = 1; i <= G->colores_usados; i++){
        aux[i] = calloc(2, sizeof(u32));
        aux[i][0] = i;
    }

    for(u32 i = 1; i <= G->n; i++)
        aux[G->coloreo[i]][1] += 1;

    radix_mod(aux, G->colores_usados);

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

void GrandeChico(GrafP G) {

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
