// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: tetrahedro.h
// -----------------------------------------------------------------------------


#ifndef TETRAEDRO_H_INCLUDED
#define TETRAEDRO_H_INCLUDED

#include "aux.h"

// Clases derivadas de Malla3D (definen constructores específicos)
// Tetraedro con centro en el origen 

class Tetraedro: public Malla3D
{
   public:
      Tetraedro(float l=1);
} ;

#endif
