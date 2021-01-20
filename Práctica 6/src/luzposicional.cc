#include "aux.h"
#include "luzposicional.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Luz Direccional
// -----------------------------------------------------------------------------

LuzPosicional::LuzPosicional(GLenum idLuz, Tupla3f pos, Tupla4f camb, Tupla4f cesp, Tupla4f cdif)
{
	id 			   = idLuz;
	posicion	   = {pos(0), pos(1), pos(2), 1.0}; 	// posicional, w!=0
	colorAmbiente  = camb;
	colorDifuso	   = cdif;
	colorEspecular = cesp;
}
