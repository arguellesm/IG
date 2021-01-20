// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: luzposicional.h
// -----------------------------------------------------------------------------

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"


class LuzPosicional : public Luz
{
public:
	// Inicializar la fuente de luz
	LuzPosicional(GLenum idLuz, Tupla3f pos, Tupla4f camb, Tupla4f cesp, Tupla4f cdif);
};

#endif