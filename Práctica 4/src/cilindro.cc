#include "aux.h"
#include "cilindro.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Cilindro
// -----------------------------------------------------------------------------

Cilindro::Cilindro(const int nv, const int num_instancias, const float altura, const float radio)
{
    // Atributos
    this->altura = altura;
    this->radio  = radio;

    // Crear y rellenar vector de puntos
    std::vector<Tupla3f> perfil;
    perfil.resize(2);
    perfil[0] = Tupla3f(radio,  altura/2, 0);
    perfil[1] = Tupla3f(radio, -altura/2, 0);

    // Usar crearMalla con el vector de puntos
    crearMalla(perfil, num_instancias, true);

    // Vector de colores 
    c.resize(v.size());
    for(int i=0; i<v.size(); i=i+2){
        c[i]   = Tupla3f(180/255.0, 228/255.0, 228/255.0);
        c[i+1] = Tupla3f(137/255.0, 210/255.0, 208/255.0);
    }

    // Vectores de colores para modo ajedrez
    cAjP.resize(v.size());                            // Pares
    cAjI.resize(v.size());                            // Impares

    for(int i=0; i<v.size(); i++){
        cAjP[i]   = Tupla3f(180/255.0, 228/255.0, 228/255.0);
    }

    for(int i=0; i<v.size(); i++){
        cAjI[i]   = Tupla3f(137/255.0, 210/255.0, 208/255.0);
    }

    // Calcular las normales
    calcular_normales();
}
