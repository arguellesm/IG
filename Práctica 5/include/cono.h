// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: cono.h
// -----------------------------------------------------------------------------

#ifndef CONO_H_INCLUDED
#define CONO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"

// Cono: clase derivada de ObjRevolucion

class Cono : public ObjRevolucion
{
private:
	float altura;
	float radio;
public:
	Cono(const int nv, const int num_instancias, const float altura, const float radio);
};


#endif