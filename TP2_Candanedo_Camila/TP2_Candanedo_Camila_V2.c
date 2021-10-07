#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cotizacion
{
    char especie[10];
    float precioDeCompra;
    float precioDeVenta;
    float apertura;
    float precioMaximo;
    float precioMinimo;
};

float convertirANumero(char *numero);

void inicializarVectorCotizacion(struct Cotizacion v[], int tamanio)
{
    for (int i =0; i<tamanio; i++)
        strcpy(v[i].especie,"");
    return;
}

void cargarVector(struct Cotizacion v[], int tamanio)
{
    FILE *f;
    char *pchar;
    char buffer[2048];
    char especies[20];
    // char preciosDeCompra[10];
    // char preciosDeVenta[10];
    // char aperturas[10];
    // char preciosMaximo[10];
    // char preciosMinimo[10];

    char dato[30];
    int indiceFila = 0;

    if ((f= fopen("SSL-TP2.html","rt")))
    {
        while (fgets(buffer,2048,f))
        {
            /*Especies */
            if ((pchar = strstr(buffer, "data-order")) && strstr(buffer, "Cdo.</td>"))
            {
                int posicionColumna = 0; // posicion 0 es la especie
                while (*pchar != '>')
                    pchar++;
                int i = 0;
                pchar++;
                while(*pchar != '<')
                {
                    especies[i] = *pchar;
                    i++;
                    pchar++;
                }
                especies[i] = '\0';
                strcpy(v[indiceFila].especie, especies);
                /*preciosDeCompra */
                // if ((pchar = strstr(buffer, "Cdo.</td"))) //&& strstr(buffer, "</td><td> <span style="))
                // {
                //     for (int b=0; b<4; b++)
                //     {
                //         while (*pchar != '>')
                //             pchar++;
                //     }
                //     int i = 0;
                //     pchar++;
                //     while(*pchar != '<')
                //     {
                //         preciosDeCompra[i] = *pchar;
                //         i++;
                //         pchar++;
                //     }
                //     preciosDeCompra[i] = '\0';

                //     for (int j =0; j<tamanio; j++)
                //     {
                //         strcpy(v[j].especie,especies);
                //         strcpy(v[j].precioDeCompra,preciosDeCompra);
                //     }
                // }

                while ((pchar = strstr(pchar, "<td")))
                {
                    posicionColumna++;
                    while (*pchar != '>')
                        pchar++;
                    int i = 0;
                    pchar++;
                    if(posicionColumna == 7) { //Se agrega este avance extra porque en la columna Variacion hay un span
                        while (*pchar != '>')
                            pchar++;
                        pchar++;
                    }
                    while(*pchar != '<')
                    {
                        dato[i] = *pchar;
                        i++;
                        pchar++;
                    }
                    dato[i] = '\0';

                    float numero;

                    switch (posicionColumna) {
                        case 3: // columna compra
                            numero = convertirANumero(dato);
                            v[indiceFila].precioDeCompra = numero;
                            break;
                        case 4: // columna venta
                            numero = convertirANumero(dato);
                            v[indiceFila].precioDeVenta = numero;
                            break;
                        case 8: // columna apertura
                            numero = convertirANumero(dato);
                            v[indiceFila].apertura = numero;
                            break;
                        case 9: // columna minimo
                            numero = convertirANumero(dato);
                            v[indiceFila].precioMinimo = numero;
                            break;
                        case 10: // columna maximo
                            numero = convertirANumero(dato);
                            v[indiceFila].precioMaximo = numero;
                            break;
                    }
                }
                indiceFila++;
            }
        }
    }
    return;
}

float convertirANumero(char *numero) {
    char aux[16] = {'\0'};
    int j = 0;
    for(int i = 0; numero[i] != '\0'; i++) {
        if(numero[i] == '.') {
            continue;
        }
        aux[j] = numero[i] == ',' ? '.' : numero[i];
        j++;
    }
    aux[j] = '\0';

    return atof(aux);
}


void escribirArchivoCSV(struct Cotizacion v[], int tam)
{
    FILE *f;
    f = fopen("archivoExcel.csv", "wt");

    fprintf(f,"Especie;Precio de compra;Precio de venta;Apertura; Precio Maximo;Precio Minimo\n");
    int i= 0;
    while (strlen(v[i].especie) != 0)
    {
        fprintf(f,"%s;%f;%f;%f;%f;%f\n",v[i].especie,v[i].precioDeCompra,v[i].precioDeVenta,v[i].apertura,v[i].precioMaximo,v[i].precioMinimo);
        i++;
    }
    fclose(f);
    return;
}

void escribirArchivoHTML(struct Cotizacion v[], int tam)
{
    FILE *f;
    f = fopen("tablaDeEspecies.html","wt");
    fprintf(f,"<html><body>\n");
    fprintf(f,"<h1>Especies que bla bla</h1>\n");
    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Especie</th><th>Precio de compra</th><th>Precio de venta</th><th>Apertura</th>\n");

    int i=0;
    while (strlen(v[i].especie) != 0)
    {
        fprintf(f,"<tr>\n");
        fprintf(f,"<td>%s</td><td>%f</td>\n",v[i].especie,v[i].precioDeCompra);
                //<td>%d</td><td>%d</td><td>%d</td>
                //,v[i].precioDeCompra, v[i].precioDeVenta, v[i].apertura
        fprintf(f,"</tr>\n");
        i++;
    }
    fprintf(f,"</table>");
    fprintf(f,"</body>");
    fprintf(f,"</html>");
    fclose(f);
    return;

}


int main()
{
    FILE *f;
    char *pchar;
    char buffer[2048];
    char especie[10];
    char variacion[10];


//PUNTO A
    if ((f = fopen("SSL-TP2.html","rt")))
    {
        while (fgets(buffer,2048,f))
        {
            if ((pchar = strstr(buffer, "data-order")) && strstr(buffer, "Cdo.</td>"))
            {
                /*Solo busco el nombre de tooodas las especies */
                while (*pchar != '>')
                    pchar++;
                int i = 0;
                pchar++;
                while(*pchar != '<')
                {
                    especie[i] = *pchar;
                    i++;
                    pchar++;
                }
                especie[i] = '\0';

                // NOTA: este if hay que ponerlo dentro del if de arriba, sino repetis especies en negativo. Tienen que ser solo las de "Cdo"
                // Busco solo las variaciones negativas
                if ((pchar = strstr(buffer, "<span style="))) //&& strstr(buffer, "% </span><i style="))  <-- esta condicion esta demas
                {
                    /*Guardo el numero de la variacion */
                    while (*pchar != '>')
                        pchar++;

                    int i = 0;
                    pchar++;

                    if (*pchar == '-')
                    {
                        while(*pchar != '%')
                        {
                            variacion[i] = *pchar;
                            i++;
                            pchar++;
                        }
                        variacion[i] = '\0';
                        //Solo imprimo las especies que guarde antes, pero que tienen las variaciones negativas
                        printf("La especie %s", especie);
                        printf(" tiene una variacion negativa de %s\n", variacion);
                    }
                }
            }

        }
        fclose(f);
    }
    struct Cotizacion vector[100];
    inicializarVectorCotizacion(vector,100);
    cargarVector(vector,100);
//PUNTO B
    escribirArchivoCSV(vector, 100);
//PUNTO C
    escribirArchivoHTML(vector, 150);


    return 0;
}







