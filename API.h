#ifndef API_H
#define API_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

typedef struct GrafSt *GrafP;

GrafP NuevoGraf(void);

int LeerGrafo(GrafP G);

#endif
