// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: luzdireccional.h
// -----------------------------------------------------------------------------

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz
{
protected:
	float alpha;
	float beta;
public:
	// Inicializar la fuente de luz
	LuzDireccional(GLenum idLuz, Tupla2f dir, Tupla4f camb, Tupla4f cesp, Tupla4f cdif);

	// Calcular la posicion en base a alpha y beta
	void calculaPosicion(float alpha, float beta);

	// Cambiar angulos
	void setAlpha (float incremento);
	void setBeta  (float incremento);

	// Pasar grados a radianes
	inline float radianes(float grados) {return (grados*M_PI/180);}
};

#endif
