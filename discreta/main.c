#include "API.h"

int main(void){
    GrafP G = NuevoGraf();
    LeerGrafo(G);
    printf("Grafo Cargado...\n");
    OrdenWelshPowell(G);
    printf("GREEDY: %u\n", Greedy(G));
    printf("DSATUR: %u\n", DSATUR(G));
//    ImprimeGrafo(G);
    return 0;
}
