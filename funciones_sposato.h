#ifndef FUNCIONES_SPOSATO_H_INCLUDED
#define FUNCIONES_SPOSATO_H_INCLUDED

//Estructuras

typedef struct
{
    int red;
    int green;
    int blue;
}Pixel;

typedef struct
{
    int alto;
    int ancho;
    int tamanio_imagen;
    int tamanio_pixel;
    int inicio_datos;
}Imagen;

// Primitivas

int promediar(int *, int* )

compararAltoImagenes(); //compara el alto de las imágenes y devuelve la la diferencia
compararAnchoImagenes();    //compara ancho de imágenes y devuelve la diferencia

//No primitivas



#endif // FUNCIONES_SPOSATO_H_INCLUDED
