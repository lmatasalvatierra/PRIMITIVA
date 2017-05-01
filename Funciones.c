#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Variables.h"


void generarBoleto (FILE *boletos, struct CONFIG *c)
{
    int i=0, j=0, n=1, k, num, bloque, nboletos, reintegro;
    struct PRIMITIVA BOLETO;
    char identbol[8];
    for(j=0; j<8; j++)
        {
            for(i=0; i<6; i++)
                        {
                        BOLETO.bloques[j][i]=0;
                        }
        }
    j=0;
    i=0;
    printf("Cuantos boletos quiere sellar:");
    scanf ("%d", &nboletos);
    printf("Cuantos bloques quiere sellar:");
    scanf ("%d", &bloque);
    while (n<=nboletos)
    {
        while (j<bloque && bloque<=8)
        {
            while (i<6)
            {
                num = rand()%49+1;
                if (existeElem(BOLETO, j, num)==0)
                {
                    BOLETO.bloques[j][i]= num;
                    i++;
                }
            }
            i=0;
            j++;
        }
        BOLETO.reintegro=rand()%10;
        strcpy(BOLETO.ubilot,c->codpos);
        strcat(BOLETO.ubilot, "-");
        strcat(BOLETO.ubilot, c->numadm);
        itoa (c->idbol, identbol, 10);
        strcat(BOLETO.ubilot, "-");
        strcat(BOLETO.ubilot, identbol);
        BOLETO.apuestas=bloque;
        fwrite(&BOLETO, sizeof(struct PRIMITIVA), 1, boletos);
        n++;
        (c->idbol)++;
    }
}

int existeElem (struct PRIMITIVA BOLETO, int bloque , int num)
{
   int i=0, existe=0;

   while ( i<6 && existe==0)
     if (BOLETO.bloques[i][bloque]== num)
          existe = 1;
     else i++;

   return existe;
}

int existeElemS (int sorteo[6], int bloque , int num)
{
   int i=0, existe=0;

   while ( i<6 && existe==0)
     if (sorteo[i]== num)
          existe = 1;
     else i++;

   return existe;
}

void escrutinio (struct GANADORES *g,  int sorteo[6], int sortcomp, int sortrein, float *recaudsort, float *recaudrein)
{
    int j=0;
    *recaudrein=0;
    FILE *boletos;
    FILE *aciertos;
    struct ACIERTOS cats;
    struct PRIMITIVA BOLETO;
    cats.cat6=0;
    cats.cat5c=0;
    cats.cat5=0;
    cats.cat4=0;
    cats.cat3=0;
    cats.catre=0;
    (g->numgan6)=0;
    (g->numgan4)=0;
    (g->numgan3)=0;
    (g->numgan5c)=0;
    (g->numgan5)=0;

    boletos=fopen("boleto2.dat","rb");
                    if(boletos==NULL)
                     {
                         printf("No se ha podido acceder al fichero");
                     }
    aciertos=fopen("aciertos.dat","wb");
                    if(boletos==NULL)
                     {
                         printf("No se ha podido acceder al fichero");
                     }
    while (fread(&BOLETO, sizeof(struct PRIMITIVA), 1, boletos))
    {
        strcpy(cats.ubilot,BOLETO.ubilot);
        while(j<8)
        {
            if (acierto(sorteo, BOLETO, j)==6)
            {
                (cats.cat6)++;
                (g->numgan6)++;
            }
            if (acierto(sorteo, BOLETO, j)==4)
            {
                (cats.cat4)++;
                (g->numgan4)++;
            }
            if (acierto(sorteo, BOLETO, j)==3)
            {
                (cats.cat3)++;
                (g->numgan3)++;
            }
            if (aciertoComp(sortcomp, BOLETO, j)==1 && acierto(sorteo, BOLETO, j)==5)
            {
                (cats.cat5c)++;
                (g->numgan5c)++;
            }
            if (aciertoComp(sortcomp, BOLETO, j)==0 && acierto(sorteo, BOLETO, j)==5)
            {
                (cats.cat5)++;
                (g->numgan5)++;
            }
            j++;
        }
        *recaudsort+=BOLETO.apuestas;   //apuestas== coste de boleto
        if (BOLETO.reintegro==sortrein)
        {
            cats.catre=BOLETO.apuestas;
            *recaudrein+=BOLETO.apuestas;
        }
        if ((cats.cat6)!=0 || (cats.cat5c)!=0 || (cats.cat5)!=0 || (cats.cat4)!=0 || (cats.cat3)!=0 || (cats.catre)!=0)
        {
            fwrite (&cats, sizeof(struct ACIERTOS), 1, aciertos); // Escribe los aciertos que ha conseguido
        }
        cats.cat6=0;
        cats.cat5c=0;
        cats.cat5=0;
        cats.cat4=0;
        cats.cat3=0;
        cats.catre=0;
    }
    fclose(boletos);
    fclose(aciertos);
}

void verPremiados(FILE *premios)
{
        struct PREMIADOS premiacion;
        premios=fopen("premios.dat","rb");
        if(premios==NULL)
            {
                printf("No se ha podido acceder al fichero");
            }
        while (fread(&premiacion, sizeof(struct PREMIADOS), 1, premios))
        {
            printf ("%s    %12.2lf\n", premiacion.ubilot, premiacion.pretotal);
        }
        fclose(premios);

}

int acierto(int sorteo [6], struct PRIMITIVA BOLETO, int j)
{
    int i=0, k=0, existe=0, numaciertos=0;

    while(i<6)
            {
                while(k<6 && existe==0)
                {
                    if (sorteo[i]==BOLETO.bloques[j][k])
                    {
                        numaciertos++;
                        existe=1;
                    }
                    else k++;
                }
                i++;
                k=0;
                existe=0;
            }
    return numaciertos;
}

int aciertoComp(int comp , struct PRIMITIVA BOLETO, int j)
{
    int i=0, k=0, existe=0;

    while(i<6 && existe==0)
            {
                while(k<6 && existe==0)
                {
                    if (comp==BOLETO.bloques[j][k])
                    {
                        existe=1;
                    }
                    else k++;
                }
                i++;
                k=0;
            }
    return existe;
}


void calcularPremios (FILE *premios, FILE *aciertos, float recaudsort, float recaudrein, struct GANADORES gan)
{
    struct PREMIADOS premio;
    struct ACIERTOS acertar;
    struct PAGOS pago;
    recaudsort=0.55*recaudsort;
    recaudsort=recaudsort-recaudrein;
    recaudsort=recaudsort/5.0;
    if (gan.numgan3!=0)
        pago.pago3=recaudsort/gan.numgan3;
    else pago.pago3=0;
    if (gan.numgan4!=0)
        pago.pago4=recaudsort/gan.numgan4;
    else pago.pago4=0;
    if (gan.numgan5!=0)
        pago.pago5=recaudsort/gan.numgan5;
    else pago.pago5=0;
    if (gan.numgan5c!=0)
        pago.pago5c=recaudsort/gan.numgan5c;
    else pago.pago5c=0;
    if (gan.numgan6!=0)
        pago.pago6=recaudsort/gan.numgan6;
    else pago.pago6=0;


    aciertos=fopen("aciertos.dat","rb");
        if(premios==NULL)
            {
                printf("No se ha podido acceder al fichero");
            }
    premios=fopen("premios.dat","wb");
        if(premios==NULL)
            {
                printf("No se ha podido acceder al fichero");
            }
     while ( fread(&acertar, sizeof(struct ACIERTOS), 1, aciertos))
    {
        premio.pretotal=acertar.cat3*pago.pago3+acertar.cat4*pago.pago4+acertar.cat5*pago.pago5+acertar.cat5c*pago.pago5c+acertar.cat6*pago.pago6+acertar.catre;
        strcpy(premio.ubilot,acertar.ubilot);
        fwrite(&premio, sizeof(struct PREMIADOS), 1, premios);
    }
    fclose(aciertos);
    fclose(premios);
}

