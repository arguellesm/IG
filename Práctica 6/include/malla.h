// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: malla.h
// -----------------------------------------------------------------------------

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
using namespace std;


// Clase para objetos 3D (mallas indexadas)

class Malla3D
{
   protected:

   // Tabla de vertices
   std::vector<Tupla3f> v;          // 3 floats por vértice
   // Tabla de caras
   std::vector<Tupla3i> f;          // 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_par;      // Vector de caras pares (Modo Ajedrez)
   std::vector<Tupla3i> f_imp;      // Vector de caras impares (Modo Ajedrez)
   // Vector de color genérico
   std::vector<Tupla3f> c;          // 3 floats por vértice
   std::vector<Tupla3f> cAjP;       // Color de las caras pares (Modo Ajedrez)
   std::vector<Tupla3f> cAjI;       // Color de las caras impares (Modo Ajedrez)

   // Tablas de normales
   std::vector<Tupla3f> nf;         // Normales de caras
   std::vector<Tupla3f> nv;         // Normales de vertices

   // Tabla de textura
   std::vector<Tupla2f> ct;
   Textura * t = nullptr;

   // Material
   Material m = Material({0.24725,0.1995,0.0745,1.0},
                         {0.75164,0.60648,0.22648f,1.0},
                         {0.628281,0.555802,0.366065,1.0}, 51.2);

   // IDs de VBOs
   GLuint id_vbo_v = 0;
   GLuint id_vbo_f = 0;
   GLuint id_vbo_c = 0;
   GLuint id_vbo_n = 0;

   // Calcula la tabla de normales de vértices
   void calcular_normales();

   public:

   // Crear VBO
   GLuint crearVBO(GLuint tipo, GLuint tam_bytes, GLvoid * puntero_ram);
   // Dibuja el objeto en modo ajedrez
   void draw_modoAjedrez();
   // Dibuja el objeto en modo inmediato
   void draw_ModoInmediato();
   // Dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();
   // Redibuja el objeto (llama a uno de los draw anteriores)
   void draw(int modo, bool ajedrez, bool textura=true);
   // Asignar material
   void setMaterial(const Material& mat);
   // Asignar color
   void setColor(const Tupla3f& color);


   // Análogas a glDrawElements, permite visualizar o no las tapas en ObjRevolucion
   virtual void dibujarElementos();
   virtual void dibujarElementosDif();
   virtual void dibujarElementosAjedrez();
};


#endif
