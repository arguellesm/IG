// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: textura.h
// -----------------------------------------------------------------------------

#ifndef TEXTURA_H_INCLUDED
#define TEXTURA_H_INCLUDED

#include "aux.h"

// Textura (Práctica 5)

class Textura
{
private:
	GLuint textura_id = 0;
	unsigned char *data;
	int alto, ancho;

public:
	Textura(std::string archivo);
	void activar();
};

#endif
