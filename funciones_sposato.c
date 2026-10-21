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

    //Verificación de tipo de archivo BMP
    if (img->cabeceraArchivo.tipo != 0x4D42)    //si no es "BM" (0x4D42 = "BM")
    {
        fprintf(stderr, "Error: El archivo '%s' no es un BMP válido.\n", ruta);     //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo

        return NULL;
    }
    
    //Verificación de si el archivo es de 24 bits y sin compresión
    if (img->cabeceraImagen.bitsPorPixel != 24)
    {
        fprintf(stderr, "Error: El archivo '%s' no es de 24 bits (es de %d bits).\n", ruta, img->cabeceraImagen.bitsPorPixel);  //mensaje en consola
        free(img);          //libero memoria
        fclose(archivo);    //cierro archivo
    
        return NULL;
    }
}
