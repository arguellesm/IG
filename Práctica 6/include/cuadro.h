// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: cuadro.h
// -----------------------------------------------------------------------------

#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

// Cuadro (Práctica 5)

class Cuadro : public Malla3D
{
public:
    Cuadro(float alto, float ancho, std::string textura);
};

#endif
