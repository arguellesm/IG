// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
// -----------------------------------------------------------------------------

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"
using namespace std;

class Camara
{
private:
    // Proyección ortogonal (0) o perspectiva (1)
    bool tipo;
    // Parámetros extrínsecos
    Tupla3f eye, at, up;
    // Parámetros intrínsecos
    float left, right, top, bottom, near, far;

public:
	Camara(Tupla3f eye, Tupla3f at, Tupla3f up, bool tipo, float left, float right, float top, float bottom, float near, float far);

    // Rota alrededor de at
    void rotarExaminar(unsigned char eje, float angulo);
    // Rota alrededor de eye
    void rotarFirstPerson(unsigned char eje, float angulo);

    void mover(float x, float y, float z);
    void girar(float x, float y);
    void zoom(float factor);
    void setObserver();
    void setProyeccion();

    // Gets
    inline float getLeft(){return left;}
    inline float getRight(){return right;}
    inline float getTop(){return top;}
    inline float getBottom(){return bottom;}
};

#endif
