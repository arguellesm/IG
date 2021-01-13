#ifndef _ESCENA_H
#define _ESCENA_H

#include <vector>
#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "esfera.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "flor.h"
#include "cuadro.h"
#include "sol.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELILUMINACION, SELALPHA, SELBETA, SELDIBUJADO, SELMANUAL, SELVELOCIDAD} menu;
typedef enum {NINGUNO, CUBO, ARBOL, ESFERA} objetoVisible;
typedef enum {CORONA, TALLO, HOJA, FLOR, SOL, GENERAL} animacion;

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
    animacion animacionActiva;              // indica la parte del MJ a animar

    // Objetos de la escena
    Ejes ejes;
    Cubo      * cubo      = nullptr;
    Tetraedro * tetraedro = nullptr;
    ObjPLY    * arbol1    = nullptr;
    ObjPLY    * arbol2    = nullptr;
    ObjPLY    * arbol3    = nullptr;
    ObjPLY    * arbol4    = nullptr;
    ObjPLY    * arbol5    = nullptr;
    ObjPLY    * arbol6    = nullptr;
    Cuadro    * cartel    = nullptr;
    Cubo      * palo      = nullptr;
    Cubo      * panel     = nullptr;
    Esfera    * foco      = nullptr;
    Flor      * flor1     = nullptr;
    Flor      * flor2     = nullptr;
    Flor      * flor3     = nullptr;
    Sol       * sol       = nullptr;

    // Luces
    LuzDireccional * ldir      = nullptr;
    LuzPosicional  * lpos      = nullptr;

    // True cuando el objeto indicado está activo
    bool cuboAct=1, arboAct=1, cartAct=1,florAct=1;
    // True cuando la luz indicada está activa
    bool ldirAct=1, lposAct=1;
    // Parámetros para la animación automática
    float animacionTallo  = 0.3;
    float animacionCorona = 1;
    float animacionHoja   = 1;
    float animacionSol    = 0.8;

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
    bool animacionAutomatica = true;
    void animarModeloJerarquico();

    bool inline getAnimacionAutomatica(){return animacionAutomatica;}
};
#endif
