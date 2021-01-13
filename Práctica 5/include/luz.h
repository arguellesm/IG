// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -----------------------------------------------------------------------------

#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

// Clase abstracta luz

class Luz
{
protected:
	GLenum  id;
	Tupla4f posicion;
	Tupla4f colorAmbiente;
	Tupla4f colorDifuso;
	Tupla4f colorEspecular;

public:
	void activar();
	void desactivar();
};

#endif
