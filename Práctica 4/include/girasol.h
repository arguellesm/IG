// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: girasol.h
// -----------------------------------------------------------------------------

#ifndef GIRASOL_H_INCLUDED
#define GIRASOL_H_INCLUDED

#include "aux.h"
#include "cilindro.h"
#include "esfera.h"
#include "cubo.h"

class Girasol 
{
public:
	Girasol();
	void draw(int modo, bool ajedrez);
	void setMaterial(const Material& mat_tal, const Material& mat_pis, const Material& mat_pet, const Material& mat_hoj, const Material& mat_mac);
	void setAltura(float valor);
	void setGiro(float valor);
	void setAngPetalos(float valor);
	void setAngHoja(float valor);

private:
	// Elementos del modelo
	Cilindro * tallo1      = nullptr;
	Cilindro * tallo2      = nullptr;
	Esfera   * eje 		   = nullptr;
	Esfera   * pistilo     = nullptr;
	Esfera   * hoja        = nullptr;
	Cilindro * maceta      = nullptr;
	std::vector<Esfera *> petalos;

	// Valores de los grados de libertad
	bool creciendo    = true;
	bool oeste 	      = true;
	bool subiendo     = true;
	float crecimiento = 0;
	float giro  	  = 0;
	float ang_petalos = 0;
	float ang_hoja    = 0;
	float rad, a, b;

	// Asignación de materiales
	void setMaterialTallo(const Material& mat);
	void setMaterialPistilo(const Material& mat);
	void setMaterialPetalos(const Material& mat);
	void setMaterialHoja(const Material& mat);
	void setMaterialMaceta(const Material& mat);
};

#endif