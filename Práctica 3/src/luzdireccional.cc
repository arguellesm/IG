#include "aux.h"
#include "math.h"				// sin, cos
#include "luzdireccional.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Luz Direccional
// -----------------------------------------------------------------------------

LuzDireccional::LuzDireccional(GLenum idLuz, Tupla2f dir, Tupla4f camb, Tupla4f cesp, Tupla4f cdif)
{
	id 			   = idLuz;
	alpha 		   = dir(0);
	beta		   = dir(1);
	calculaPosicion(alpha, beta);
	colorAmbiente  = camb;
	colorDifuso	   = cdif;
	colorEspecular = cesp;
	
}

void LuzDireccional::calculaPosicion(float alpha, float beta)
{
	int r = 300;
	posicion[0] = r*sin(alpha)*cos(beta);
	posicion[1] = r*sin(alpha)*sin(beta);
	posicion[2] = r*cos(alpha);
	posicion[3] = 0.0;						// direccional, w=0
}


void LuzDireccional::setAlpha(float incremento)
{
	alpha += incremento;
}

void LuzDireccional::setBeta(float incremento)
{
	beta += incremento;
}