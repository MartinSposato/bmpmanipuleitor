#include "funciones_sposato.h"

#include <stdlib.h>
#include <string.h>

Imagen *leerImagen(const char *ruta)    //el nombre es la ruta de almacenamiento de la imagen
{
    //Apertura de archivo
    FILE *archivo = fopen(ruta, "rb");  //se abre en modo lectura binaria

    if (archivo == NULL)    //si no se detecta archivo
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo '%s'. Verifique la ruta.\n", ruta); //mensaje en consola

        return NULL;
    }

    //Se reserva memoria dinámica para la estructura principal
    Imagen *img = malloc(sizeof(Imagen));

    if (img == NULL)
    {
        fprintf(stderr, "Error: Memoria insuficiente para la estructura Imagen.\n");    //mensaje en consola
        fclose(archivo);    //cierro archivo

        return NULL;
    }

    //Leer cabeceras
    fread(&img->cabeceraArchivo, sizeof(CabeceraArchivo), 1, archivo);  //cabecera archivo
    fread(&img->cabeceraImagen, sizeof(CabeceraImagen), 1, archivo);    //cabecera imagen

    //Verificaciones:

    //Verificación de tipo de archivo BMP
    if (img->cabeceraArchivo.tipo != 0x4D42)    //si no es "BM" (0x4D42 = "BM")
    {
        fprintf(stderr, "Error: El archivo '%s' no es un BMP válido.\n", ruta);     //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo

        return NULL;
    }

    //Verificación de si el archivo es de 24 bits
    if (img->cabeceraImagen.bitsPorPixel != 24)
    {
        fprintf(stderr, "Error: El archivo '%s' no es de 24 bits (es de %d bits).\n", ruta, img->cabeceraImagen.bitsPorPixel);  //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo

        return NULL;
    }

    //Verificación de que el archivo no está comprimido
    if (img->cabeceraImagen.compresion != 0)
    {
        fprintf(stderr, "Error: El archivo '%s' está comprimido. Solo se admiten BMP sin compresión.\n", ruta); //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo
        return NULL;
    }

    //Posiciono el cursor donde comienzan los píxeles
    fseek(archivo, img->cabeceraArchivo.offsetDatos, SEEK_SET);

    //Reservación de memoria dinámica

    //Reservo memoria dinámica para la matriz de píxeles
    img->matrizPixeles = malloc(img->cabeceraImagen.alto * sizeof *img->matrizPixeles);

    if (img->matrizPixeles == NULL)
    {
        fprintf(stderr, "Error: Memoria insuficiente para la matriz de píxeles.\n");    //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo

        return NULL;
    }

    //Se reserva memoria para cada fila
    // Recorremos cada fila de la imagen (una por cada píxel de alto)
    int i;
    for (i = 0; i < img->cabeceraImagen.alto; i++)
    {
        //Se reserva memoria para todas las columnas de esta fila
        // (ancho píxeles, cada uno del tamaño de un Pixel)
        img->matrizPixeles[i] = malloc(img->cabeceraImagen.ancho * sizeof *img->matrizPixeles[i]);

        if (img->matrizPixeles[i] == NULL)  //Verificamos si la reserva falló (no hay memoria suficiente)
        {
            fprintf(stderr, "Error: Memoria insuficiente para una fila de píxeles.\n");

            //Libero las filas que ya se habían reservado antes del error
            for (int j = 0; j < i; j++)
            {
                free(img->matrizPixeles[j]);
            }

            free(img->matrizPixeles);   //Libero el arreglo de punteros a filas

            free(img);  //Libero la estructura Imagen

            fclose(archivo);    //Cierro el archivo que quedó abierto

            return NULL;    //si hubo error retorna NULL
        }
    }
    
    //Calcular padding (relleno) de cada fila
    int anchoBytes = img->cabeceraImagen.ancho * 3;
    int padding = (4 - (anchoBytes % 4)) % 4;

}
