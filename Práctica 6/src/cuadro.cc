#include "aux.h"
#include "malla.h"
#include "cuadro.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Cuadro
// -----------------------------------------------------------------------------

Cuadro::Cuadro(float alto, float ancho, std::string textura)
{
    // Vértices
    v.resize(4);
    v[0] = Tupla3f(0,0,0);
    v[1] = Tupla3f(alto,0,0);
    v[2] = Tupla3f(0,ancho,0);
    v[3] = Tupla3f(alto,ancho,0);

    // Triángulos
    f.resize(2);
    f[0] = Tupla3i(2,0,1);
    f[1] = Tupla3i(1,3,2);

    // Vector de colores
    c.resize(v.size());
    for(int i=0; i<v.size(); i=i+2){
        c[i]   = Tupla3f(180/255.0, 228/255.0, 228/255.0);
        c[i+1] = Tupla3f(137/255.0, 210/255.0, 208/255.0);
    }

    // Normales
    calcular_normales();

    // Textura
    t = new Textura(textura);
    ct.resize(4);
    ct[0] = Tupla2f(0,0);
    ct[1] = Tupla2f(1,0);
    ct[2] = Tupla2f(0,1);
    ct[3] = Tupla2f(1,1);
}
