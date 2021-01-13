// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h
// -----------------------------------------------------------------------------

#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"

// Cilindro2: clase derivada de ObjRevolucion

class Cilindro : public ObjRevolucion
{
private:
	float altura;
	float radio;
public:
	Cilindro(const int nv, const int num_instancias, const float altura, const float radio);	
};


#endif
