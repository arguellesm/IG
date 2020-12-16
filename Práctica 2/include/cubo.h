// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: cubo.h
// -----------------------------------------------------------------------------

#ifndef CUBO_H_INCLUDED
#define CUBO_H_INCLUDED

#include "aux.h"

// Clases derivadas de Malla3D (definen constructores específicos)
// Cubo con centro en el origen y lado unidad por defecto

class Cubo : public Malla3D
{

public:
   Cubo(float l=1);
};

#endif
