

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

using namespace std;

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0;
    Observer_angle_y  = 0.0;
    objetoActivo = NINGUNO;
    
    ejes.changeAxisSize( 5000 );

    // Ojetos de la escena
    cubo = new Cubo(100);
    tetraedro = new Tetraedro(50);
    
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
    glClearColor( 252/255.0, 237.5/255.0, 227.5/255.0, 0.0 );   // color para limpiar la pantalla		 

	glEnable(GL_DEPTH_TEST);       // se habilita el z-bufer
	glEnable(GL_CULL_FACE);        // se habilita cull-face

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

	change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

// **************************************************************************
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
    ejes.draw();
        
    // Tamaño de linea y puntos
    glPointSize(5);
    glLineWidth(1.5);

    switch( modoVisualizacion )
    {
        case GL_POINT:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
        case GL_LINE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
        case GL_FILL:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    }

    if(ajedrezActivado)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    switch (objetoActivo){
        case CUBO:
            cubo->draw(modoDibujado,ajedrezActivado);
            break;
        
        case TETRAEDRO:
            tetraedro->draw(modoDibujado,ajedrezActivado);
            break;
    }       
}

//**************************************************************************
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
	using namespace std;
	cout << "-Tecla pulsada: '" << tecla << "'" << endl;
	bool salir=false;

	switch(toupper(tecla))
	{
		case 'Q':
        	if (modoMenu!=NADA){
                cout << "Volviendo al menú principal" << endl;
            	modoMenu=NADA;            
         	}else{
                cout << "Adiós!" << endl;
            	salir=true;
            }
        break;
    	case 'O':     // Modo selección de objeto
        	modoMenu=SELOBJETO; 
         	printf("Opciones disponibles:\n  C: Cubo\n  T: Tetraedro\n  Q: Salir\n");
        break;
		case 'V':    // Modo selección de visualización
         	modoMenu=SELVISUALIZACION;
         	printf("Opciones disponibles:\n  P: Puntos\n  L: Lineas\n  S: Solido\n  A: Ajedrez\n  Q: Salir\n");
        break;
       	case 'D':    // Modo selección de dibujado
         	modoMenu=SELDIBUJADO;
            printf("Opciones disponibles:\n  1: Modo Inmediato\n  2: Modo Diferido\n  Q: Salir");
        break;
        default:
            cout << "Opciones disponibles:" << endl;
            cout << "  O: Modo de selección de objeto" << endl;
            cout << "  V: Modo de selección de visualización" << endl;
            cout << "  D: Modo de selección de dibujado" << endl;
            cout << "  Q: Salir del programa" << endl;
    }

    // SELECCIÓN DE OBJETO
    if (modoMenu==SELOBJETO){
    	switch(toupper(tecla))
    	{
    		case 'C':   // Visualizar cubo
    			cout << "Cubo activado" << endl;
    			objetoActivo = CUBO;
    		break;
    		case 'T':   // Visualizar tetraedro
    			cout << "Tetraedro activado" << endl;
    			objetoActivo = TETRAEDRO;
    		break;
    	}
    }

    // SELECCIÓN DE VISUALIZACIÓN
    if (modoMenu==SELVISUALIZACION){
        switch(toupper(tecla))
        {
            case 'P':   // Ver puntos
                cout << "Modo de visualización: Puntos." << endl;
                ajedrezActivado = ajedrezActivado ? !ajedrezActivado : ajedrezActivado;
                modoVisualizacion = GL_POINT;
            break;
            case 'L':   // Ver lineas
                cout << "Modo de visualización: Líneas." << endl;
                ajedrezActivado = ajedrezActivado ? !ajedrezActivado : ajedrezActivado;
                modoVisualizacion = GL_LINE;
            break;
            case 'S':   // Ver solido
                cout << "Modo de visualización: Sólido." << endl;
                ajedrezActivado = ajedrezActivado ? !ajedrezActivado : ajedrezActivado;
                modoVisualizacion = GL_FILL;
            break;
            case 'A':   // Ver en ajedrez
                cout << "Modo de visualización: Ajedrez." << endl;
                ajedrezActivado = !ajedrezActivado;
            break;
        }
    }

    // SELECCIÓN DE DIBUJADO
    if (modoMenu==SELDIBUJADO){
        switch(toupper(tecla))
        {
            case '1':   // Activar dibujo en modo inmediato
                cout << "Dibujado en modo Inmediato" << endl;
                modoDibujado = 1;
            break;
            case '2':   // Activar dibujo en modo diferido
                cout << "Dibujado en Modo Diferido" << endl;
                modoDibujado = 2;
            break;
        }
    }


   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y--;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x--;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
