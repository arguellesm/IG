// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: luz.h
// -----------------------------------------------------------------------------

#ifndef SOL_H_INCLUDED
#define SOL_H_INCLUDED

#include "aux.h"
#include "luzposicional.h"
#include "esfera.h"

class Sol
{
private:
	LuzPosicional * lpos = nullptr;
	Esfera        * sol  = nullptr;
    float posicion = 0;
	bool direccion = true;
	float rad, x, z;

public:
	Sol();
	void draw(int modo, bool ajedrez);
    void setMaterial(const Material& mat);
    void setPosicion(float angulo);
	void activar();
	void desactivar();

};

#endif
