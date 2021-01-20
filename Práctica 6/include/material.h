// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: material.h
// -----------------------------------------------------------------------------

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"
#include "luz.h"


class Material
{
private:
	Tupla4f difuso;
	Tupla4f especular;
	Tupla4f ambiente;
	float   brillo;

public:
	Material(Tupla4f dif, Tupla4f esp, Tupla4f amb, float br);
	Material(const Material& mat);
	void aplicar();
};

#endif