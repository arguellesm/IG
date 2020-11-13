// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   protected:

   // Tabla de vertices
   std::vector<Tupla3f> v;    // 3 floats por vértice
   // Tabla de caras
   std::vector<Tupla3i> f;    // 3 enteros por cada cara o triángulo
   // Vector de color genérico
   std::vector<Tupla3f> c;    // 3 floats por vértice
   // Vectores de color para el modo ajedrez
   std::vector<Tupla3f> cAjP;
   std::vector<Tupla3f> cAjI;
   
   // Tabla de normales
   // PROXIMA PRACTICA

   // IDs de VBOs
   GLuint id_vbo_v = 0;
   GLuint id_vbo_f = 0;

   void calcular_normales(); // calcula tabla de normales de vértices (práctica 3)

   
   public:

   // Crear VBO
   GLuint crearVBO(GLuint tipo, GLuint tam_bytes, GLvoid * puntero_ram);

  // dibuja el objeto en modo ajedrez
   void draw_modoAjedrez();

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(int modo, bool ajedrez);
};


#endif
