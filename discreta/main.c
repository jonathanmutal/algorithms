#include "API.h"

int main(void){
    GrafP G = NuevoGraf();

    u32 leerGraf = LeerGrafo(G);

    if(leerGraf == 0) {
        printf("X(G) = 1\n");
        return 0;
    }

    u32 dsatur = DSATUR(G);

    if(dsatur == 2) {
        printf("Grafo Bipartito\n");
        DestruirGraf(G);
        return 0;
    }

    OrdenWelshPowell(G);
    u32 ordenWelshPowell = Greedy(G);

    printf("DSATUR: Colores usados: %u\n", dsatur);
    printf("Welsh-Powell: Colores usados: %u\n", ordenWelshPowell);

    if(ordenWelshPowell == 3 || dsatur == 3) {
        printf("X(G) == 3\n");
        DestruirGraf(G);
        return 0;
    }

//    printf("Grafo Cargado...\n");
//    printf("Dsatur %u\n", DSATUR(G));
//    OrdenWelshPowell(G);
//    printf("GREEDY OrdenWelshPowell: %u\n", Greedy(G));
//    Revierte(G);
//    printf("GREEDY Revierte: %u\n", Greedy(G));
//    GrandeChico(G);
//    printf("GREEDY GrandeChico: %u\n", Greedy(G));
//    ChicoGrande(G);
//    printf("Greedy ChicoGrande: %u\n", Greedy(G));
//    DestruirGraf(G);
    return 0;
}
