#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "girasol.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELILUMINACION, SELALPHA, SELBETA, SELDIBUJADO} menu;
typedef enum {NINGUNO, CUBO, TETRAEDRO, PEON, ARBOL, CILINDRO, CONO, ESFERA} objetoVisible;

class Escena
{

    private:
    
    // PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
    // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_distance;
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    void clear_window();

    // Objetos para los menús
    menu modoMenu=NADA;
    objetoVisible objetoActivo;             // indica el objeto a dibujar
    int modoDibujado = 1;                   // indica el modo de dibujado
    GLenum modoVisualizacion = GL_FILL;     // modo puntos/linea/solido
    bool ajedrezActivado     = false;       // modo ajedrez
    bool tapasActivadas      = true;        // mostrar u ocultar tapas en ObjRevolucion

    // Objetos de la escena
    Ejes ejes;
    Cubo           * cubo      = nullptr;             
    Tetraedro      * tetraedro = nullptr; 
    ObjPLY         * arbol1    = nullptr;
    ObjPLY         * arbol2    = nullptr;
    ObjPLY         * arbol3    = nullptr;   
    ObjRevolucion  * peon01    = nullptr;
    ObjRevolucion  * peon02    = nullptr;
    
    /*Cilindro       * cilindro  = nullptr;
    Cono           * cono      = nullptr;
    Esfera         * esfera    = nullptr;*/

    LuzDireccional * ldir      = nullptr;
    LuzPosicional  * lpos      = nullptr; 
    Esfera         * foco      = nullptr;
    Girasol        * girasol   = nullptr;

    // True cuando el objeto indicado está activo
    bool cuboAct=1, tetrAct=1, arboAct=1, peonAct=1, ciliAct=1, conoAct=1, esfeAct=1, giraAct=1; 
    // True cuando la luz indicada está activa
    bool ldirAct=1, lposAct=1;
    
    public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight );

	// Dibujar
	void dibujar();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y );
	void teclaEspecial( int Tecla1, int x, int y );

    // Animación automática
    void animarModeloJerarquico();
};
#endif
