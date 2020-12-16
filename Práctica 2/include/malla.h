// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: malla.h
// -----------------------------------------------------------------------------

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

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
   
   // Tabla de normales
   // PROXIMA PRACTICA

   // IDs de VBOs
   GLuint id_vbo_v = 0;
   GLuint id_vbo_f = 0;
   GLuint id_vbo_c = 0;

   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)
   
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
   void draw(int modo, bool ajedrez);

   // Análoga a glDrawElements, permite visualizar o no las tapas en ObjRevolucion
   virtual void dibujarElementos();
   virtual void dibujarElementosDif();
   virtual void dibujarElementosAjedrez();
};


#endif
