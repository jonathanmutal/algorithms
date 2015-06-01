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

    u32 tabla_prob[100];

    for(u32 i = 66; i <= 99; i++)
        tabla_prob[i] = 1;
    
    for(u32 i = 30; i <= 65; i++)
        tabla_prob[i] = 2;

    for(u32 i = 10 ; i <= 30 ; i++)
        tabla_prob[i] = 3;

    for(u32 i = 0 ; i < 10; i++)
        tabla_prob[i] = 4;
  

    srand(time(NULL)); 

    for(u32 i = 1; i <= 10; i++)  {
        u32 random;
       
        random = (rand() % 100);
        random = tabla_prob[random];

        switch(random) {
        
        case 1:
            GrandeChico(G);
            Greedy(G);
            break;
        case 2:
            ChicoGrande(G);
            Greedy(G);
            break;
        case 3:
            Revierte(G);
            Greedy(G);
            break;
        case 4:
            OrdenAleatorio(G);
            Greedy(G);
            break;
        }

        }
    
        printf("Mejor color luego de Greedy iterado 10 veces : %u\n", CantidadDeColores(G));

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
