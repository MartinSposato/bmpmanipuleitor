#include <funciones_sposato.h>

#include <stdlib.h>
#include <string.h>

Imagen *leerImagen(const char *ruta)    //el nombre es la ruta de almacenamiento de la imagen
{
    FILE* archivo = fopen(ruta, "rb");  //apertura del archivo en modo lectura binaria
    if (archivo == NULL)
    {
        fprintf(stderr, "Error: No se pudo abrir el archivo '%s'. Verifique la ruta.\n", ruta);
        return NULL;
    }

}
