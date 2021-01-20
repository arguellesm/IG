#include "sol.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Sol
// -----------------------------------------------------------------------------

Sol::Sol(){
    sol  = new Esfera(100, 50, 30.0,"./textures/sign.jpg");
    lpos = new LuzPosicional (GL_LIGHT2,{0.0,150.0,0.0},{0.70f,0.70f,0.70f,1.0f},{0.70f,0.70f,0.70f,1.0f},{0.70f,0.70f,0.70f,1.0f});
}

void Sol::draw(int modo, bool ajedrez){
    rad = posicion * (M_PI/180);
    x   = cos(rad) * 300;
    z   = sin(rad) * 300;

    glPushMatrix();
        glPushMatrix();
            glTranslatef(x,z,0);
            sol->draw(modo,ajedrez);
        glPopMatrix();
        glPopMatrix();
            glTranslatef(x,z,0);
            lpos->activar();
        glPopMatrix();
    glPopMatrix();
}

void Sol::setPosicion(float angulo){
    posicion += direccion ? angulo : -angulo;
}

void Sol::setMaterial(const Material& mat){
    sol->setMaterial(mat);
}

void Sol::setColor(const Tupla3f& color){
    sol->setColor(color);
}

void Sol::activar(){
    lpos->activar();
}

void Sol::desactivar(){
    lpos->desactivar();
}
