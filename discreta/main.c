#include "API.h"

int main(void){
    GrafP G = NuevoGraf();
    LeerGrafo(G);
    OrdenWelshPowell(G);
    printf("GREEDY: %u", Greedy(G));
    return 0;
}
