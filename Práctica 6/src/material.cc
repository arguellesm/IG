#include "aux.h"
#include "material.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Material
// -----------------------------------------------------------------------------

Material::Material(Tupla4f dif, Tupla4f esp, Tupla4f amb, float br){
	difuso	  = dif;
	especular = esp;
	ambiente  = amb;
	brillo 	  = br;
}

Material::Material(const Material& mat){
	difuso	  = mat.difuso;
	especular = mat.especular;
	ambiente  = mat.ambiente;
	brillo 	  = mat.brillo;
}

void Material::aplicar(){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}


