#include "API.h"

struct GrafSt {
  u32 *list_ady_vert;
  u32 *orden;
  u32 *tabla_trad;
  u32 *coloreo;
  u32 *grado;
  u32 colores_usados;
  u32 n;
  u32 m;
};

GrafP NuevoGraf(void) {
  return NULL;
}

int LeerGrafo(GrafP G){
  char c;
  bool done = false;
  u32 n, m;
  u32 izq, der;
  u32 trad_izq, trad_der;
  u32 tam = 0;

  u32 *tabla_aux;

  while(!done){
    c = getc(stdin);

    if(c == 'p') {
      char edge[4];
      fscanf(stdin, "%s" "%u" "%u", edge, &n, &m);
      G = calloc(1, sizeof(struct GrafSt));
      G->n = n;
      G->m = m;

    } else if(c == 'e'){
      fscanf(stdin, "%u" "%u", &izq, &der);


      tabla_aux = calloc(n + 1, sizeof(u32));

      G->list_ady_vert = calloc(n + 1, sizeof(u32));
      G->orden = calloc(n + 1, sizeof(u32));
      G->coloreo = calloc(n + 1 ,sizeof(u32));
      G->tabla_trad = calloc(n + 1, sizeof(u32));
      G->grado = calloc(n + 1, sizeof(u32));
      G->colores_usados = 0;


      for(u32 i = 1; i <= n; i++) {
        tabla_aux[i] = 30;
      }

      for(u32 i = 1; i <= n; i++) {
        G->list_ady_vert[i] = calloc(30, sizeof(u32));
      }

      for(u32 i = 1; i <= tam; i++) {
        if(G->tabla_trad[i] == izq) {
            trad_izq = i;
            break;
        }

        if(trad_izq == 0) {
          G->tabla_trad[tam + 1] = izq;
          trad_izq = tam + 1;
          tam = tam + 1;   
        }

        if(tabla_aux[trad_izq] == G->grado[trad_izq]) {
           realloc(G->list_ady_vert[trad_izq], 30 * sizeof(u32));
        }
        G->grado[trad_izq] += 1;
        G->list_ady_vert[trad_izq][G->grado[trad_izq]] = trad_der;
      }

      for(u32 i = 1; i <= tam; i++) {
        if(G->tabla_trad[i] == der) {
            trad_der = i;
            break;
        }

        if(trad_der == 0) {
          G->tabla_trad[tam + 1] = der;
          trad_der = tam + 1;
          tam = tam + 1;   
        }

        if(tabla_aux[trad_der] == G->grado[trad_der]) {
          realloc(G->list_ady_vert[trad_der], 30 * sizeof(u32));/*ver bien*/
        }
        G->grado[trad_izq] += 1;
        G->list_ady_vert[trad_der][G->grado[trad_der]] = trad_izq;
      }

    } else if(c == 'c'){
      char linea[80];
      fgets(linea, 80, stdin);

    } else if(c == -1){
      done = true;
    }

  }
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
