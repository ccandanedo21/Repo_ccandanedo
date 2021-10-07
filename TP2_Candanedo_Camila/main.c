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

float convertirNum(char *numero);

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

    char dato[30];
    int indiceFila = 0;

    if ((f= fopen("SSL-TP2.html","rt")))
    {
        while (fgets(buffer,2048,f))
        {
            if ((pchar = strstr(buffer, "data-order")) && strstr(buffer, "Cdo.</td>"))
            {
                int posicionColumna = 0; // Columna 0 pertenece a la especie
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

                while ((pchar = strstr(pchar, "<td"))) // Divido las columnas
                {
                    posicionColumna++;
                    while (*pchar != '>') // Busco cuando comienza una celda
                        pchar++;
                    int i = 0;
                    pchar++;
                    if(posicionColumna == 7) { //Se agrega este avance extra porque en la columna 7, Variacion, hay un Span Style
                        while (*pchar != '>')
                            pchar++;
                        pchar++;
                    }
                    while(*pchar != '<') //Mientras no termine la celda, leo su info.
                    {
                        dato[i] = *pchar;
                        i++;
                        pchar++;
                    }
                    dato[i] = '\0';

                    float numero;

                    switch (posicionColumna) {
                        case 3: // Si es la columna Compra
                            numero = convertirNum(dato);
                            v[indiceFila].precioDeCompra = numero;
                            break;
                        case 4: // Si es la columna Venta
                            numero = convertirNum(dato);
                            v[indiceFila].precioDeVenta = numero;
                            break;
                        case 8: // Si es la columna Apertura
                            numero = convertirNum(dato);
                            v[indiceFila].apertura = numero;
                            break;
                        case 9: // Si es la columna MIN
                            numero = convertirNum(dato);
                            v[indiceFila].precioMinimo = numero;
                            break;
                        case 10: // Si es la columna MAX
                            numero = convertirNum(dato);
                            v[indiceFila].precioMaximo = numero;
                            break;
                    }
                }
                indiceFila++; // Sigo con las otras filas
            }
        }
    }
    return;
}

float convertirNum(char *numero) {
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
    f = fopen("Excel_TP2_Candanedo.csv", "wt");
    fprintf(f,"Listado de las cotizaciones de compra y de venta\n\n");
    fprintf(f,"Especie;Precio de compra;Precio de venta;Apertura; Precio Maximo;Precio Minimo\n");
    int i= 0;
    while (strlen(v[i].especie) != 0)
    {
        fprintf(f,"%s;%.2f;%.2f;%.2f;%.2f;%.2f\n",v[i].especie,v[i].precioDeCompra,v[i].precioDeVenta,v[i].apertura,v[i].precioMaximo,v[i].precioMinimo); // Uso %.2f para mostrar menos decimales (unicamente por prolijidad)
        i++;
    }
    fprintf(f,"\Trabajo Practico N°2 | Candanedo Camila.\n");
    fclose(f);

    printf("Se creo archivo CSV\n");

    return;
}

void escribirArchivoHTML(struct Cotizacion v[], int tam)
{
    FILE *f;
    f = fopen("HTML_TP2_Candanedo.html","wt");
    fprintf(f,"<html><body>\n");

    fprintf(f,"<hr>\n");
    fprintf(f,"<h1>Bolsa de Comercio de Buenos Aires</h1>\n");
    fprintf(f,"<hr>\n");

    fprintf(f,"<h4>En color verde se muestran las filas de las especies cuyo precio de compra y precio de venta es menor al precio de apertura.</h4>\n");

    fprintf(f,"<table border=1>\n");
    fprintf(f,"<th>Especie</th><th>Precio de compra</th><th>Precio de venta</th><th>Apertura</th>\n");

    int i=0;
    while (strlen(v[i].especie) != 0)
    {
        if (((v[i].precioDeCompra < v[i].apertura) && (v[i].precioDeVenta < v[i].apertura))){
            fprintf(f,"<tr>\n");
            fprintf(f,"<td style=\"color:green\">%s</td><td>%.2f</td><td>%.2f</td><td>%.2f</td>\n",v[i].especie,v[i].precioDeCompra, v[i].precioDeVenta, v[i].apertura); // Ninguno cumple la condicion, por esto no se ve verde en el archivo
        }else{
            fprintf(f,"<tr>\n");
            fprintf(f,"<td>%s</td><td>%.2f</td><td>%.2f</td><td>%.2f</td>\n",v[i].especie,v[i].precioDeCompra, v[i].precioDeVenta, v[i].apertura); // Uso %.2f para mostrar menos decimales (unicamente por prolijidad)
        }
        fprintf(f,"</tr>\n");
        i++;
    }
    fprintf(f,"</table>");

    fprintf(f,"<h6>Trabajo Practico N°2 | Candanedo Camila.</h6>\n");
    fprintf(f,"</body>");
    fprintf(f,"</html>");
    fclose(f);

    printf("Se creo archivo HTML\n");
    return;

}


int main()
{
    FILE *f;
    char *pchar;
    char buffer[2048];
    char especie[10];
    char variacion[10];
    int valorUsuario = 0;

    printf("Ingrese el numero de la tarea a realizar: \n\n");
    printf("1- Listar en pantalla las especies cuyo porcentaje de variacion es negativo. \n");
    printf("2- Listar las cotizaciones de compra y de venta en un archivo .CSV\n");
    printf("3- Listar las especies con su precio de compra, venta y apertura en un archivo .HTML\n");

    scanf("%d", &valorUsuario);

    if (valorUsuario == 1){
//PUNTO A
        if ((f = fopen("SSL-TP2.html","rt")))
    {
        while (fgets(buffer,8192,f))
        {
            if ((pchar = strstr(buffer, "data-order")) && strstr(buffer, "Cdo.</td>"))
            {
                //Busco el nombre de todas las especies
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
                // Busco las variaciones
                if ((pchar = strstr(buffer, "<span style=")))
                {
                    while (*pchar != '>')
                        pchar++;

                    int i = 0;
                    pchar++;

                    if (*pchar == '-') //Filtro las negativas
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
    }

    struct Cotizacion vector[100];
    inicializarVectorCotizacion(vector,100);
    cargarVector(vector,100);

    if (valorUsuario == 2){
//PUNTO B
        escribirArchivoCSV(vector, 100);
    } if (valorUsuario == 3){
//PUNTO C
        escribirArchivoHTML(vector, 150);
    } if( valorUsuario != 1 && valorUsuario != 2 && valorUsuario != 3){
         printf("Los numeros validos son 1,2 y 3 \n");
    }

    return 0;
}







