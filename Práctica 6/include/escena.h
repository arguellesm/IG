#ifndef _ESCENA_H
#define _ESCENA_H

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
#include "camara.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELILUMINACION, SELALPHA, SELBETA, SELDIBUJADO, SELMANUAL, SELVELOCIDAD, SELCAMARA} menu;
typedef enum {NINGUNO, CUBO, ARBOL, ESFERA} objetoVisible;
typedef enum {CORONA, PETALOS, TALLO, HOJA, FLOR, SOL, GENERAL} animacion;
typedef enum {S, C, A1, A2, A3, A4, A5, A6, F1, F2, F3, NULO} objetoSelec;

class Escena
{
private:

    // variables que controlan la ventana y la transformacion de perspectiva
    GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();
    void clear_window();

    // Objetos para los menús
    menu modoMenu=NADA;                     // indica el submenú
    objetoVisible objetoActivo;             // indica el objeto a dibujar
    int modoDibujado = 1;                   // indica el modo de dibujado
    GLenum modoVisualizacion = GL_FILL;     // modo puntos/linea/solido
    bool ajedrezActivado     = false;       // modo ajedrez
    bool tapasActivadas      = true;        // mostrar u ocultar tapas en ObjRevolucion
    animacion animacionActiva;              // indica la parte del MJ a animar
    objetoSelec objetoSeleccionado = NULO;  // indica el objeto seleccionado

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

    // Materiales
    Material marron   = Material({0.0368627,0.0313725,0.0247058,1.0f},{0.368627,0.313725,0.247058,1.0f},{0.368627,0.313725,0.247058,1.0f},15.8f);
    Material verde    = Material({ 0.0f,0.0f,0.0f,1.0f },{ 0.1f,0.35f,0.1f,1.0f},{0.45f,0.55f,0.45f,1.0f },32.0f);
    Material arcilla  = Material({ 0.19125f, 0.0735f, 0.0225f, 1.0f },{0.7038f, 0.27048f, 0.0828f, 1.0f },{0.256777f, 0.137622f, 0.086014f, 1.0f },12.8f);
    Material amarillo = Material({ 0.24725f, 0.1995f, 0.0745f, 1.0f },{0.75164f, 0.60648f, 0.22648f, 1.0f },{0.628281f, 0.555802f, 0.366065f, 1.0f },51.2f);
    Material blanco   = Material({0.650f,0.600f,0.600f,1.0f},{0.000f,0.000f,0.000f,1.0f},{0.650f,0.600f,0.600f,1.0f},90.00f);
    Material kombu    = Material({0.156862,0.211764,0.094117,1.0f},{0.156862,0.211764,0.094117,1.0f},{0.156862,0.211764,0.094117,1.0f},12.3f);
    Material azul     = Material({0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f},0.00f);

    // Luces
    LuzDireccional * ldir      = nullptr;
    LuzPosicional  * lpos      = nullptr;

    // Cámaras
    std::vector<Camara> camaras;
    int camaraActiva = 0;

    // True cuando el objeto indicado está activo
    bool cuboAct=1, arboAct=1, cartAct=1,florAct=1;
    // True cuando la luz indicada está activa
    bool ldirAct=1, lposAct=1;
    // Parámetros para la animación automática
    float animacionTallo   = 0.3;
    float animacionPetalos = 1;
    float animacionCorona  = 1;
    float animacionHoja    = 1;
    float animacionSol     = 0.8;
    // True cuando haya que dibujar con textura (selección)
    bool texturaCubo = true, texturaCartel = true;

public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight );

	// Dibujar
	void dibujar();
    void dibujarObjetos();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y );
	void teclaEspecial( int Tecla1, int x, int y );

    // Animación automática
    bool animacionAutomatica = true;
    void animarEscena();
    void animarFlor(Flor* flor);
    bool inline getAnimacionAutomatica(){return animacionAutomatica;}

    // Eventos del ratón para la cámara
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);
    bool moviendo_raton = false;
    int xant = 0;
    int yant = 0;

    // Seleccionar Objetos
    void dibujaSeleccion();
    void analizarPixel(int x, int y);
};
#endif
