#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED
#include <stdio.h>

struct PRIMITIVA
    {
        char ubilot[17];
        int bloques[8][6];
        int reintegro;
        int apuestas;
    };
struct CONFIG
    {
        char codpos [6];
        char numadm[3];
        int idbol;
        float precio;
    };
struct ACIERTOS
    {
        char ubilot[17];
        int cat6;
        int cat5c;
        int cat5;
        int cat4;
        int cat3;
        int catre;
    };
struct PREMIADOS
    {
        char ubilot[17];
        double pretotal;
    };
struct PAGOS
    {
        float pago6;
        float pago5;
        float pago5c;
        float pago4;
        float pago3;
    };
struct GANADORES
    {
        int numgan3;
        int numgan4;
        int numgan5;
        int numgan5c;
        int numgan6;
    };

int existeElem (struct PRIMITIVA BOLETO, int bloque , int num);
int existeElemS (int sorteo[6], int bloque , int num);
void generarBoleto (FILE *boletos, struct CONFIG *c);
void verPremiados(FILE *premios);
void escrutinio (struct GANADORES *g,  int sorteo[6], int sortcomp, int sortrein, float *recaudsort, float *recaudrein);
int acierto (int sorteo [6], struct PRIMITIVA BOLETO, int j);
int aciertoComp(int comp , struct PRIMITIVA BOLETO, int j);
void calcularPremios (FILE *premios, FILE *aciertos, float recaudsort, float recaudrein, struct GANADORES gan);




#endif // VARIABLES_H_INCLUDED
