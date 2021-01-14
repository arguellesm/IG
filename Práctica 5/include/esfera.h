// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h
// -----------------------------------------------------------------------------

#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"

// Esfera: clase derivada de ObjRevolucion

class Esfera : public ObjRevolucion
{
private:
	float radio;

public:
	Esfera(const int nv, const int num_instancias, const float radio, std::string textura="");
};

#endif
