// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: flor.h
// -----------------------------------------------------------------------------

#ifndef FLOR_H_INCLUDED
#define FLOR_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"
#include "cubo.h"

class Flor
{
public:
	Flor();
	void draw(int modo, bool ajedrez);
	void setMaterial(const Material& mat_tal, const Material& mat_pis, const Material& mat_pet, const Material& mat_hoj, const Material& mat_mac);
	void setAltura(float valor);
	void setAngPetalos(float valor);
	void setAngHoja(float valor);

private:
	// Elementos del modelo
	Cilindro * tallo       = nullptr;
	Esfera   * eje 		   = nullptr;
	Esfera   * pistilo     = nullptr;
	Esfera   * hoja        = nullptr;
	Cilindro * maceta      = nullptr;
	std::vector<Esfera *> petalos;

	// Valores de los grados de libertad
	bool creciendo    = true;
	bool subiendo     = true;
	float crecimiento = 0;
	float ang_petalos = 0;
	float ang_hoja    = 0;
	float rad, a, b;
};

#endif
