#include "camara.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Cámara
// -----------------------------------------------------------------------------

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, bool tipo, float left, float right, float top, float bottom, float near, float far)
{
    this->eye    = eye;
    this->at     = at;
    this->up     = up;

    this->tipo   = tipo;

    this->left   = left;
    this->right  = right;
    this->top    = top;
    this->bottom = bottom;
    this->near   = near;
    this->far    = far;
}


void Camara::rotarExaminar(unsigned char eje, float angulo)
{
    eye = eye - at;
    Tupla3f eye_aux = eye;
    switch(toupper(eje)){
        case 'X':
            eye(1) = (eye_aux(1) *  cos(angulo)) - (eye_aux(2) * sin(angulo));
            eye(2) = (eye_aux(1) *  sin(angulo)) + (eye_aux(2) * cos(angulo));
        break;
        case 'Y':
            eye(0) = (eye_aux(0) *  cos(angulo)) + (eye_aux(2) * sin(angulo));
            eye(2) = (eye_aux(0) * -sin(angulo)) + (eye_aux(2) * cos(angulo));
        break;
        case 'Z':
            eye(0) = (eye_aux(0) *  cos(angulo)) - (eye_aux(2) * sin(angulo));
            eye(1) = (eye_aux(0) *  sin(angulo)) + (eye_aux(1) * cos(angulo));
        break;
    }
    eye = eye + at;
}

void Camara::rotarFirstPerson(unsigned char eje, float angulo)
{
    at = at - eye;
    Tupla3f at_aux = at;
    switch(toupper(eje)){
        case 'X':
            at(1) = (at_aux(1) *  cos(angulo)) - (at_aux(2) * sin(angulo));
            at(2) = (at_aux(1) *  sin(angulo)) + (at_aux(2) * cos(angulo));
        break;
        case 'Y':
            at(0) = (at_aux(0) *  cos(angulo)) + (at_aux(2) * sin(angulo));
            at(2) = (at_aux(0) * -sin(angulo)) + (at_aux(2) * cos(angulo));
        break;
        case 'Z':
            at(0) = (at_aux(0) *  cos(angulo)) - (at_aux(2) * sin(angulo));
            at(1) = (at_aux(0) *  sin(angulo)) + (at_aux(1) * cos(angulo));
        break;
    }
    at = at + eye;
}


void Camara::mover(float x, float y, float z)
{
    at  = {x,y,z};
}

void Camara::girar(float x, float y)
{
    rotarFirstPerson('X', y);
    rotarFirstPerson('Y', x);
}

void Camara::zoom(float factor)
{
    left *= factor;
    right *= factor;
    top *= factor;
    bottom *= factor;
}

void Camara::setObserver()
{
    gluLookAt(
        eye(0), eye(1), eye(2),
        at(0), at(1), at(2),
        up(0), up(1), up(2)
    );
}

void Camara::setProyeccion()
{
    if(tipo){
        glOrtho(left, right, bottom, top, near, far);
    }else{
        glFrustum(left, right, bottom, top, near, far);
    }
}
