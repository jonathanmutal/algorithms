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

int LeerGrafo(GrafP G){
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
  G->colores_usados = 0;

  u32 *tabla_aux = calloc(n + 1, sizeof(u32));

  for(u32 i = 1; i <= G->n; i++) {
      tabla_aux[i] = 30;
      G->list_ady_vert[i] = calloc(30, sizeof(u32));
  }

  while((c = getc(stdin)) != -1){

    if (c == 'e'){
      fscanf(stdin, "%u" "%u", &izq, &der);

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
