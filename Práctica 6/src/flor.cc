#include "flor.h"
#include "malla.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Girasol
// -----------------------------------------------------------------------------

Flor::Flor(){
	tallo   = new Cilindro(100, 50, 40.0, 2.0);
	eje  	= new Esfera(100,50,2.0);
	pistilo = new Esfera(100, 50, 5.0);
	for(int i=0; i<4; i++){
		petalos.push_back(new Esfera(100,50, 5.0));
	}
	hoja    = new Esfera(100,50, 5.0);
	maceta  = new Cilindro(100, 50, 20.0, 10.0);
}

void Flor::draw(int modo, bool ajedrez){
	glPushMatrix();
		glPushMatrix();
			// Crecimiento en altura de la flor
			glTranslatef(0,crecimiento,0);

			// Tallo completo
			glPushMatrix();
				glTranslatef(0,20,0);
				tallo->draw(modo, ajedrez);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0,40,0);
				eje->draw(modo, ajedrez);
			glPopMatrix();

			// Cabeza de la flor
			glPushMatrix();
				// Giro completo
				glRotatef(ang_petalos,0,1,0);

				// Pistilo
				glPushMatrix();
					glTranslatef(0,40,0);
					glScalef(1.0,0.4,1.0);
					pistilo->draw(modo, ajedrez);
				glPopMatrix();

				// Pétalos
				glPushMatrix();
					glTranslatef(0,40,-5);
					glRotatef(apertura,1,0,0);
					glScalef(1.0,0.4,1.0);
					petalos.at(0)->draw(modo, ajedrez);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(5,40,0);
					glRotatef(apertura,0,0,1);
					glScalef(1.0,0.4,1.0);
					petalos.at(1)->draw(modo, ajedrez);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,40,5);
					glRotatef(-apertura,1,0,0);
					glScalef(1.0,0.4,1.0);
					petalos.at(2)->draw(modo, ajedrez);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-5,40,0);
					glRotatef(-apertura,0,0,1);
					glScalef(1.0,0.4,1.0);
					petalos.at(3)->draw(modo, ajedrez);
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

void Flor::setMaterial(const Material& mat_tal, const Material& mat_pis, const Material& mat_pet, const Material& mat_hoj, const Material& mat_mac){
	tallo->setMaterial(mat_tal);
	eje->setMaterial(mat_tal);

	pistilo->setMaterial(mat_pis);

	for(int i=0; i<4; i++){
		petalos.at(i)->setMaterial(mat_pet);
	}

	hoja->setMaterial(mat_hoj);
	maceta->setMaterial(mat_mac);
}

void Flor::setAltura(float valor){
	if(crecimiento+valor >= 10 || crecimiento+valor <= 0)
		creciendo = false;
	if(crecimiento-valor <= 0  || crecimiento-valor >= 10)
		creciendo = true;

	crecimiento += creciendo ? valor : -valor;
}

void Flor::setApertura(float valor){
	if(apertura+valor >= 110 || apertura+valor <= 0)
		abriendose = false;
	if(apertura-valor <= 0  || apertura-valor >= 110)
		abriendose = true;

	apertura += abriendose ? valor : -valor;
}

void Flor::setGiro(float valor){
	ang_petalos += valor;
}

void Flor::setAngHoja(float valor){
	if(ang_hoja+valor >= 30   || ang_hoja+valor <= -30)
		subiendo = false;
	if (ang_hoja-valor <= -30 || ang_hoja-valor >= 30)
		subiendo = true;

	ang_hoja += subiendo ? valor : -valor;
}

void Flor::setColor(const Tupla3f& color){
	tallo->setColor(color);
	eje->setColor(color);
	pistilo->setColor(color);
	hoja->setColor(color);
	maceta->setColor(color);
	for(int i=0; i<4; i++){
		petalos.at(i)->setColor(color);
	}
}
