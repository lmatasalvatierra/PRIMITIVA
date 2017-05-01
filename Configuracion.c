#include <stdio.h>
#include <stdlib.h>

struct Codigo
{
    char CP[6];
    char CA[3];
    int CI;
    float Precio;
};
int main()
{
    struct Codigo C1;
    printf("Codigo Postal: ");
    gets(C1.CP);
    printf("Codigo de Administracio: ");
    gets(C1.CA);
    C1.CI=0;
    C1.Precio=1.00;
    FILE*CODIGO;
        if(!(CODIGO=fopen("config.dat", "wb")))
            {
                printf("No se ha podido aceder al fichero");
                return 1;
            }
        printf("Fichero abierto");
        fwrite(&C1,sizeof(C1), 1, CODIGO);
        fclose(CODIGO);
}
