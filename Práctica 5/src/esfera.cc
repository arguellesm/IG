#include "aux.h"
#include "esfera.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Esfera
// -----------------------------------------------------------------------------

Esfera::Esfera(const int nv, const int num_instancias, const float radio)
{
    // Coordenadas auxiliares para generar el perfil
    float x, y;
    
    // Atributos
    this->radio = radio;
    
    // Crear y rellenar perfil
    std::vector<Tupla3f> perfil;
    perfil.clear();
    for(int i=0; i<nv; i++){
        x = radio * sin((i*M_PI*1.0)/(nv-1));
        y = radio * cos((i*M_PI*1.0)/(nv-1));
        perfil.push_back(Tupla3f(x, y, 0.0));
    }
    
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