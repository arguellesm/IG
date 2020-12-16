#include "objply.h"
#include "ply_reader.h"
 
// -----------------------------------------------------------------------------
// Clase ObjPLY
// -----------------------------------------------------------------------------

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{

	// leer la lista de caras y vértices
	ply::read( nombre_archivo, this->v, this->f );

    // Separa caras pares e impares (Modo Ajedrez)
    for(int i=0; i<f.size(); i++){
        (i%2==0) ? f_par.push_back(f[i]) : f_imp.push_back(f[i]);   
    }

    // Vector de colores
	c.resize(v.size());     
    for(int i=0; i<v.size(); i=i+2){
        c[i]   = Tupla3f(193/255.0, 154/255.0, 154/255.0);
        c[i+1] = Tupla3f(212/255.0, 183/255.0, 176/255.0);
    }

    // Vectores de colores para modo ajedrez
    cAjP.resize(v.size());   		  	// Pares
    cAjI.resize(v.size());     			// Impares

    for(int i=0; i<v.size(); i++){
      cAjP[i]   = Tupla3f(193/255.0, 154/255.0, 154/255.0);
    }

    for(int i=0; i<v.size(); i++){
      cAjI[i]   = Tupla3f(212/255.0, 183/255.0, 176/255.0);
    }

}


