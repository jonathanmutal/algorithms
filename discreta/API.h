#ifndef _API_H
#define _API_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct GrafSt *GrafP;

typedef unsigned int u32;

GrafP NuevoGraf(void);

int DestruirGraf(GrafP G);

int LeerGrafo(GrafP G);

int ImprimeGrafo(GrafP G);

u32 NumeroVerticesDeColor(GrafP G, u32 i);

u32 ImprimirColor(GrafP G, u32 i);

u32 CantidadDeColores(GrafP G);

u32 Greedy(GrafP G);

void OrdenWelshPowell(GrafP G);

void radix(u32 *array, u32 *orden, u32 size);

void radix_rever(u32 *array, u32 *orden, u32 size);

void GrandeChico(GrafP G);

void ChicoGrande(GrafP G);

void Revierte(GrafP G);

#endif
