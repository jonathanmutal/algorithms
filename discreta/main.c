#include "API.h"

int main(void){
    GrafP G = NuevoGraf();
    LeerGrafo(G);
    printf("Grafo Cargado...");
    printf("GREEDY: %u\n", Greedy(G));
    GrandeChico(G);
    printf("GREEDY2: %u \n", Greedy(G));
//    ImprimeGrafo(G);
    return 0;
}
