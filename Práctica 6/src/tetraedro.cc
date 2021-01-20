#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include "math.h"			

// -----------------------------------------------------------------------------
// Clase Tetrahedro
// -----------------------------------------------------------------------------

Tetraedro::Tetraedro(float lado)
{
	
	float aux = lado * sqrt(2);			// lado del cubo en el que estaría inscrito

	// inicializar la tabla de vértices
	v.resize(8);
	v[0] = Tupla3f(-aux,-aux, aux);		// vértice 0
	v[1] = Tupla3f(-aux, aux,-aux);		// vértice 1
	v[2] = Tupla3f( aux,-aux,-aux);		// vértice 2
	v[3] = Tupla3f( aux, aux, aux); 	// vértice 3

	// inicializar la tabla de caras o triángulos:
	f.resize(4);
	f[0] = Tupla3i(0,3,1);				// triángulo 0
	f[1] = Tupla3i(0,2,3);				// triángulo 1
	f[2] = Tupla3i(3,2,1);				// triángulo 2
	f[3] = Tupla3i(0,1,2);				// triángulo 3

	// Separa caras pares e impares (Modo Ajedrez)
	for(int i=0; i<f.size(); i++){
		(i%2==0) ? f_par.push_back(f[i]) : f_imp.push_back(f[i]);	
	}

	// Vector de colores
	c.resize(v.size());     
    for(int i=0; i<v.size(); i=i+2){
      c[i]   = Tupla3f(154/255.0, 130/255.0, 175/255.0);
      c[i+1] = Tupla3f(195/255.0, 182/255.0, 221/255.0);
    }

    // Vectores de colores para modo ajedrez
    cAjP.resize(v.size());   		  	// Pares
    cAjI.resize(v.size());     			// Impares

    for(int i=0; i<v.size(); i++){
      cAjP[i]   = Tupla3f(154/255.0, 130/255.0, 175/255.0);
    }

    for(int i=0; i<v.size(); i++){
      cAjI[i]   = Tupla3f(195/255.0, 182/255.0, 221/255.0);
    }

    // Calcular las normales
    calcular_normales();

}

