#include "aux.h"
#include "luz.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Luz
// -----------------------------------------------------------------------------

void Luz::activar()
{
	glEnable(GL_LIGHTING);
	glEnable(id);
	glLightfv(id, GL_POSITION, posicion);
	glLightfv(id, GL_AMBIENT , colorAmbiente);
	glLightfv(id, GL_DIFFUSE , colorDifuso);
	glLightfv(id, GL_SPECULAR, colorEspecular);
}

void Luz::desactivar()
{
	glDisable(id);
}
