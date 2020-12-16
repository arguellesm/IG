// -----------------------------------------------------------------------------
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h
// -----------------------------------------------------------------------------

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// Clases derivadas de Malla3D (definen constructores específicos)
// Objeto Revolución

class ObjRevolucion : public Malla3D
{
public:
	bool tapasVisibles = true;
	ObjRevolucion();
   	ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, char eje_r='Y') ;
   	ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true, char eje_r='Y') ;
   		
protected:
    void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, const bool tapas, char eje_r='Y');

private:
	std::vector<Tupla3f> perfil;
	unsigned int tapas_size = 0;
	bool crearTapaSur = false;
	bool crearTapaNor = false;	
	// Funciones para no dibujar las tapas
	void dibujarElementos() override;				
	void dibujarElementosDif() override;
	void dibujarElementosAjedrez() override;
	void inicializaColores();

};


#endif
