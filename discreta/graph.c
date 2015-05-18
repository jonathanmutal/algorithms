#include "graph.h"
#include "helpers.h"

struct GrafSt {
   u32 *list_ady_vert
   u32 *orden
   u32 *tabla_trad
   unsigned int *coloreo
   unsigned int *grado
   unsigned int colores_usados
   unsigned int n,m;
};

GrafP NuevoGraf(void) {
    GrafpSt G;
    GrafP GP;
    GP = &G;
    return (GP);
}

int DestruirGraf(GrafP G) {

}

int LeerGrafo(GrafP G) {
    unsigned int n, m;
    unsigned int tam = 0;
    unsigned int *tabla_aux;
    u32 izq, der;
    u32 trad_izq, trad_der;
    char *line;
    char number[20];
    flag = 1;

    
    tabla_aux = calloc(n + 1, sizeof(unsigned int));

    G->list_ady_vert = calloc(n + 1, sizeof(* u32));
    G->orden = calloc(n + 1, sizeof(u32));
    G->coloreo = calloc(n + 1 ,sizeof(u32));           
    G->tabla_trad = calloc(n + 1, sizeof(u32));
    G->grado = calloc(n + 1, sizeof(u32));
    G->colores_usados = 0;

    for(u32 i = 1; i <= n; i++) {
        tabla_aux[i] = 30;
    }

    for(u32 i = 1; i <= n; i++) {
        G->list_ady_vert[i] = calloc(30, sizeof(u32));
    }

    for(u32 i = 1; i <= tam; i++) {
        if(tabla_trad[i] == izq) {
            trad_izq = i;
            break;
        }
    
    if(trad_izq == 0) {
        tabla_trad[tam + 1] = izq;
        izq_trad = tam + 1;
        tam = tam + 1;   
    }

    for(int i = 1; i <= tam; i++) {
        if(tabla_trad[i] == der) {
            trad_der = i;
            break;
        }
    if(trad_der == 0) {
        tabla_trad[tam + 1] = der;
        der_trad = tam + 1;
        tam = tam + 1;   
    }


    if(tabla_aux[izq_trd] == grado[izq_trad]) {
       G->list_ady_vert[izq_trad] = realloc(30, sizeof(u32));/*ver bien*/
    }
    grado[izq_trad] = grado[izq_trad] + 1;
    G->list_ady_vert[izq_trad][grado[izq_trad]] = der_trad;
            
    }

    if(tabla_aux[der_trad] == grado[der_trad]) {
       G->list_ady_vert[der_trad] = realloc(30, sizeof(u32));/*ver bien*/
    }
    grado[izq_trad] = grado[der_trad] + 1;
    G->list_ady_vert[der_trad][grado[der_trad]] = izq_trad;
            
    }    

            

        
}

int ImprimeGrafo(GrafP G) {
    u32 temp;

    printf("p edge %u %u\n", n, m);

    for(int i = 1, i <= n; i++) {
        for (int j = 0 ; j < G->grado[i]; j++) {    
            if(i < G->list_ady_vert[i][j]) {
                printf("e %u %u\n", G->tabla_trad[i], G->tabla_trad[G->list_ady_vert[i][j]]);             
            }    
        }            
    }
    return 1;
}

u32 NumeroVerticesDeColor(GrapP G, u32 i)

u32 ImprimirColor(GrafP G, u32 i)

u32 CantidadDeColores(GrafP G)


