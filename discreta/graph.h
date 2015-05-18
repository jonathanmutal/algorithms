#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdbool.h>
#include <stdio.h>


typedef struct GrafSt *GrafP;
typedef unsigned int u32;

GrafP NuevoGraf(void);

int DestruirGraf(GrafP G);

int LeerGrafo(GrafP G);

int ImprimeGrafo(GrapfP)

u32 NumeroVerticesDeColor(GrapP G, u32 i);

u32 ImprimirColor(GrafP G, u32 i);

u32 CantidadDeColores(GrafP G);


#endif 
