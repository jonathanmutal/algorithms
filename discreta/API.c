#include "API.h"


struct vertice{
  uint32_t nombre;
  uint32_t color;
  struct vertice *vecinos;
};

typedef struct vertice *vertice_t;

struct GrafSt{
  vertice_t vertices;
};


GrafP NuevoGraf(void){
  return NULL;
}

int LeerGrafo(GrafP G){
  char c;
  bool done = false;
  uint32_t n;
  uint32_t m;

  while(!done){
    c = getc(stdin);

    if(c == 'p') {
      char edge[4];
      fscanf(stdin, "%s" "%"PRIu32 "%"PRIu32, edge, &n, &m);
      G = calloc(1, sizeof(struct GrafSt));
      G->vertices = malloc(n * sizeof(struct vertice));

    } else if(c == 'e'){
      fscanf(stdin, "%"PRIu32 "%"PRIu32, &n, &m);

    } else if(c == 'c'){
      char linea[80];
      fgets(linea, 80, stdin);

    } else if(c == -1){
      done = true;
    }
  }
  return n;
}
