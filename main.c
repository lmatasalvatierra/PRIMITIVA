#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Variables.h"

int main ()
{
    unsigned short opcion;
    int estado=0;
    float recaudsort, recaudrein;
    int sorteo[6], sortcomp, sortrein, num, i=0;
    struct CONFIG configuracion;
    FILE *boletos;
    FILE *config;
    FILE *aciertos;
    FILE *premios;
    struct GANADORES ganar;
    srand(time(NULL));

    config=fopen("config.dat","rb");                // Lee los valores del config.dat y los almacena en configuracion
    if(config==NULL)
        {
                printf("No se ha podido acceder al fichero\n");
        }
        else
        {
            fread(&configuracion, sizeof(struct CONFIG), 1, config);
            fclose(config);
        }
    do
    {
        printf("1.- Abrir sellado de boletos.");
        printf("\n2.- Sellar boletos.");
        printf("\n3.- Cerrar sellado de boletos.");
        printf("\n4.- Realizar el sorteo.");
        printf("\n5.- Escrutinio.");
        printf("\n6.- Calculo de premios.");
        printf("\n7.- Ver premiados.");
        printf("\n      0.- Salir.");
        printf("\nElija una opcion:");
        scanf ("%u",&opcion);
        switch(opcion)
        {
            case 1:
                    if (estado==0)
                    {


                        estado=1;
                        boletos=fopen("boleto2.dat","wb");
                        if(boletos==NULL)
                        {printf("No se ha podido acceder al fichero\n");
                            return 2;
                        }
                        else
                        {
                        system("CLS");
                        printf("Ya esta disponible el sellado de boletos.\n");
                        }
                    }
                break;
            case 2:
                if(estado==1)
                    {
                        generarBoleto (boletos, &configuracion);
                        system("CLS");
                    }

                else printf ("\n No esta en el estado correspondiente");
                break;
            case 3:
                    if(estado==1)
                    {
                        estado=2;
                        fclose(boletos);
                        config=fopen("config.dat","wb");
                        if(config==NULL)
                        {
                            printf("No se ha podido acceder al fichero\n");
                        }
                        else
                        {
                        fwrite(&configuracion, sizeof(struct CONFIG), 1, config);
                        fclose(config);
                        }
                        system("CLS");
                    }
                     else printf ("\n No esta en el estado correspondiente");
                break;
            case 4:
                    if (estado==2)
                    {
                        while (i<6)
                        {
                            num = rand()%49+1;
                            if (existeElemS(sorteo, i, num)==0)
                            {
                                sorteo[i]= num;
                                i++;
                            }
                        }
                    sortrein=rand()%10;
                    sortcomp=rand()%49+1;
                    estado=3;
                    system("CLS");
                    }
                    else printf ("\n No esta en el estado correspondiente");
                break;
            case 5:
                    if(estado==3)
                    {
                        estado=4;
                        recaudsort=0;
                        recaudrein=0;
                        escrutinio (&ganar, sorteo, sortcomp, sortrein, &recaudsort, &recaudrein);
                        system("CLS");
                    }
                     else printf ("\n No esta en el estado correspondiente");
                break;
            case 6:
                    if(estado==4)
                    {
                        estado=5;
                        calcularPremios (premios, aciertos, recaudsort, recaudrein, ganar);
                        system("CLS");
                    }
                     else printf ("\n No esta en el estado correspondiente");
                break;
            case 7:
                    if(estado==5)
                    {
                        verPremiados(premios);
                        printf("\n");
                    }
                     else printf ("\n No esta en el estado correspondiente");
                break;
        }
    }while (opcion!=0);
}
