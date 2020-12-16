#include "aux.h"
#include "malla.h"
#include "cubo.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Cubo
// -----------------------------------------------------------------------------

Cubo::Cubo(float lado)
{
   float semilado = lado/2;

   // Tabla de vértices (tal que el cubo queda centrado en el origen)
   v.resize(8);
   v[0] = Tupla3f(-semilado,-semilado,-semilado);    // vértice 0
   v[1] = Tupla3f(-semilado,-semilado, semilado);    // vértice 1
   v[2] = Tupla3f(-semilado, semilado,-semilado);    // vértice 2
   v[3] = Tupla3f(-semilado, semilado, semilado);    // vértice 3
   v[4] = Tupla3f( semilado,-semilado,-semilado);    // vértice 4
   v[5] = Tupla3f( semilado,-semilado, semilado);    // vértice 5
   v[6] = Tupla3f( semilado, semilado,-semilado);    // vértice 6
   v[7] = Tupla3f( semilado, semilado, semilado);    // vértice 7

   // Tabla de caras o triángulos (sentido antihorario)
   f.resize(12);
   f[0]  = Tupla3i(1,7,3);                           // triángulo 0
   f[1]  = Tupla3i(1,5,7);                           // triángulo 1
   f[2]  = Tupla3i(0,3,2);                           // triángulo 2
   f[3]  = Tupla3i(0,1,3);                           // triángulo 3
   f[4]  = Tupla3i(4,2,6);                           // triángulo 4
   f[5]  = Tupla3i(4,0,2);                           // triángulo 5
   f[6]  = Tupla3i(5,6,7);                           // triángulo 6
   f[7]  = Tupla3i(5,4,6);                           // triángulo 7
   f[8]  = Tupla3i(7,2,3);                           // triángulo 8
   f[9]  = Tupla3i(7,6,2);                           // triángulo 9
   f[10] = Tupla3i(0,5,1);                           // triángulo 10
   f[11] = Tupla3i(0,4,5);                           // triángulo 11

   // Separa caras pares e impares (Modo Ajedrez)
   for(int i=0; i<f.size(); i++){
      (i%2==0) ? f_par.push_back(f[i]) : f_imp.push_back(f[i]);   
   }

   // Vector de colores 
   c.resize(v.size());
   for(int i=0; i<v.size(); i=i+2){
      c[i]   = Tupla3f(177/255.0, 209/255.0, 182/255.0);
      c[i+1] = Tupla3f( 77/255.0, 168/255.0, 159/255.0);
   }

   // Vectores de colores para modo ajedrez
   cAjP.resize(v.size());                            // Pares
   cAjI.resize(v.size());                            // Impares

   for(int i=0; i<v.size(); i++){
      cAjP[i]   = Tupla3f(177/255.0, 209/255.0, 182/255.0);
   }

   for(int i=0; i<v.size(); i++){
      cAjI[i]   = Tupla3f( 77/255.0, 168/255.0, 159/255.0);
   }

   // Calcular las normales
    calcular_normales();

}

