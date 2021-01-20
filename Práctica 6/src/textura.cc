#include "textura.h"
#include "jpg_imagen.hpp"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Textura
// -----------------------------------------------------------------------------

Textura::Textura(std::string archivo)
{
    // Puntero a imagen
    jpg::Imagen * pimg = NULL;

    // Cargar la imagen
    pimg = new jpg::Imagen(archivo);

    alto  = pimg->tamX();           // numero de columnas
    ancho = pimg->tamY();           // numero de filas
    data  = pimg->leerPixels();
}

void Textura::activar()
{
    gluBuild2DMipmaps(
        GL_TEXTURE_2D,
        GL_RGB,             // formato interno
        ancho,
        alto,
        GL_RGB,             // formato y orden de los texels en ram
        GL_UNSIGNED_BYTE,   // tipo de cada texel
        data
    );
}
