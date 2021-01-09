#include "girasol.h"
#include "malla.h"
using namespace std;


// -----------------------------------------------------------------------------
// Clase Girasol
// -----------------------------------------------------------------------------

Girasol::Girasol(){
	tallo1 = new Cilindro(100, 50, 40.0, 2.0);
	tallo2 = new Cilindro(100, 50, 5.0, 2.0);
	eje  	= new Esfera(100,50,1.0);
	pistilo = new Esfera(100, 50, 5.0);
	for(int i=0; i<4; i++){
		petalos.push_back(new Esfera(100,50, 5.0));
	}
	hoja    = new Esfera(100,50, 5.0);
	maceta  = new Cilindro(100, 50, 20.0, 20.0);
}


void Girasol::draw(int modo, bool ajedrez){
	glPushMatrix();
		glPushMatrix();
			// Crecimiento en altura del girasol
			glTranslatef(0,crecimiento,0);

			// Tallo completo
			glPushMatrix();
				glTranslatef(0,20,0);
				tallo1->draw(modo, ajedrez);
			glPopMatrix();
			
			glPushMatrix();
				glPushMatrix();
					glTranslatef(0,40,0);
					glRotatef(giro,1,0,0);
					eje->draw(modo, ajedrez);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,41,0);
					glRotatef(giro,1,0,0);
					tallo2->draw(modo, ajedrez);
				glPopMatrix();

				glPushMatrix();
					// Pistilo
					glPushMatrix();
						glTranslatef(0,46,0);
						glScalef(1.0,0.4,1.0);
						pistilo->draw(modo, ajedrez);
					glPopMatrix();

					// Pétalos
					rad = ang_petalos * (M_PI/180);
					a	= cos(rad) * 5;
					b 	= sin(rad) * 5;

					glPushMatrix();
						glTranslatef(a,46,-b);
						glScalef(1.0,0.4,1.0);
						petalos.at(0)->draw(modo, ajedrez);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(b,46,a);
						glScalef(1.0,0.4,1.0);
						petalos.at(1)->draw(modo, ajedrez);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-a,46,b);
						glScalef(1.0,0.4,1.0);
						petalos.at(2)->draw(modo, ajedrez);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(-b,46,-a);
						glScalef(1.0,0.4,1.0);
						petalos.at(3)->draw(modo, ajedrez);
					glPopMatrix();

					glRotatef(giro,1,0,0);
				glPopMatrix();

			glPopMatrix();

			// Hoja
			rad = ang_hoja * (M_PI/180);
			glPushMatrix();
				glTranslatef(4,30,0);
				glRotatef(ang_hoja,0,0,1);
				glScalef(1.0,0.3,0.3);
				hoja->draw(modo, ajedrez);
			glPopMatrix();
		glPopMatrix();

		// Maceta
		glPushMatrix();
			glTranslatef(0.0,0.0,0.0);
			maceta->draw(modo, ajedrez);
		glPopMatrix();
	glPopMatrix();
}

void Girasol::setMaterial(const Material& mat_tal, const Material& mat_pis, const Material& mat_pet, const Material& mat_hoj, const Material& mat_mac){
	tallo1->setMaterial(mat_tal);
	tallo2->setMaterial(mat_tal);
	eje->setMaterial(mat_tal);

	pistilo->setMaterial(mat_pis);

	for(int i=0; i<4; i++){
		petalos.at(i)->setMaterial(mat_pet);
	}

	hoja->setMaterial(mat_hoj);
	maceta->setMaterial(mat_mac);
}

void Girasol::setAltura(float valor){
	if(crecimiento+valor >= 10)
		creciendo = false;
	else if (crecimiento-valor <= 0)
		creciendo = true;

	crecimiento += creciendo ? valor : -valor;
}

void Girasol::setGiro(float valor){
	if(giro+valor >= 90)
		oeste = false;
	else if (giro-valor <= -90)
		oeste = true;

	giro += oeste ? valor : -valor;
}

void Girasol::setAngPetalos(float valor){
	ang_petalos += valor;
}

void Girasol::setAngHoja(float valor){
	if(ang_hoja+valor >= 30)
		subiendo = false;
	else if (ang_hoja-valor <= -30)
		subiendo = true;

	ang_hoja += subiendo ? valor : -valor;
}

