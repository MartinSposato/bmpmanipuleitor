#ifndef FUNCIONES_SPOSATO_H_INCLUDED
#define FUNCIONES_SPOSATO_H_INCLUDED

#include <stdio.h>
#include <stdint.h>     //para usar uint8, uint16, etc.

///Estructuras

//Para el siguiente grupo de estructuras busco evitar el "padding" (relleno)

#pragma pack(push, 1)   //comienza acá

typedef struct
{
    uint16_t tipo;            // "BM" = 0x4D42
    uint32_t tamanoArchivo;
    uint16_t reservado1;
    uint16_t reservado2;
    uint32_t offsetDatos;
}CabeceraArchivo;            //14 bytes en total

typedef struct
{
    uint32_t tamanoCabecera;
    int32_t  ancho;
    int32_t  alto;
    uint16_t planos;
    uint16_t bitsPorPixel;
    uint32_t compresion;
    uint32_t tamanoImagen;
    int32_t  resolucionX;
    int32_t  resolucionY;
    uint32_t coloresUsados;
    uint32_t coloresImportantes;
}CabeceraImagen;            //40 bytes en total

#pragma pack(pop)   //termina acá el grupo de estructuras

typedef struct
{
    uint8_t azul;
    uint8_t verde;
    uint8_t rojo;
}Pixel;

typedef struct
{
    CabeceraArchivo cabeceraArchivo;
    CabeceraImagen cabeceraImagen;
    Pixel **matrizPixeles;
}Imagen;

// Primitivas

int promediar(int *, int* )

compararAltoImagenes(); //compara el alto de las imágenes y devuelve la la diferencia
compararAnchoImagenes();    //compara ancho de imágenes y devuelve la diferencia

//No primitivas



#endif // FUNCIONES_SPOSATO_H_INCLUDED
