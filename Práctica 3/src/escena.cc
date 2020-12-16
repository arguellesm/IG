

#include "aux.h"        // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"     // includes de cada objeto
using namespace std;


//--------------------------------------------------------------------------
// constructor de la escena (no puede usar ordenes de OpenGL)
//--------------------------------------------------------------------------

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0;
    Observer_angle_y  = 0.0;
    objetoActivo      = NINGUNO;
    
    ejes.changeAxisSize( 5000 );

    // Ojetos de la escena
    cubo      = new Cubo(50);
    tetraedro = new Tetraedro(20);
    arbol     = new ObjPLY("./plys/fractree.ply");
    peon01    = new ObjRevolucion("./plys/peon.ply",50,true,true);
    peon02    = new ObjRevolucion("./plys/peon.ply",50,true,true);
    cilindro  = new Cilindro(100, 50, 50.0, 30.0);
    cono      = new Cono(100, 50, 50.0, 30.0);
    esfera    = new Esfera(100, 50, 30.0);
    foco      = new Esfera(100, 50, 10.0);

    // Luces de la escena
    ldir      = new LuzDireccional(GL_LIGHT1,{50.0,50.0},    {0.01f,0.01f,0.01f,1.0f},{0.0f,0.0f,0.0f,1.0f},{0.0f,0.0f,0.0f,1.0f});
    lpos      = new LuzPosicional (GL_LIGHT2,{0.0,150.0,0.0},{0.70f,0.70f,0.70f,1.0f},{0.70f,0.70f,0.70f,1.0f},{0.70f,0.70f,0.70f,1.0f});

    // Materiales
    Material naranja = Material({0.812f,0.600f,0.372f,1.0f},{0.812f,0.600f,0.372f,1.0f},{0.812f,0.600f,0.372f,1.0f}, 9.00f);
    Material lila    = Material({0.427f,0.349f,0.478f,1.0f},{0.427f,0.349f,0.478f,1.0f},{0.427f,0.349f,0.478f,1.0f}, 9.00f);
    Material verde   = Material({0.172f,0.549f,0.447f,0.9f},{0.172f,0.549f,0.447f,0.9f},{0.172f,0.549f,0.447f,0.9f}, 9.00f);
    Material azul    = Material({0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f}, 9.00f);
    Material blanco  = Material({0.650f,0.600f,0.600f,1.0f},{0.000f,0.000f,0.000f,1.0f},{0.650f,0.600f,0.600f,1.0f},90.00f);
    Material negro   = Material({0.000f,0.000f,0.000f,1.0f},{0.220f,0.200f,0.230f,1.0f},{0.220f,0.200f,0.230f,1.0f},90.00f);
    
    // Asignar materiales a los objetos de la escena
    cubo ->setMaterial(verde);
    tetraedro->setMaterial(lila);
    arbol->setMaterial(naranja);
    peon01->setMaterial(blanco);
    peon02->setMaterial(negro);
    cilindro->setMaterial(azul);
    cono->setMaterial(azul);
    esfera->setMaterial(azul);
    foco->setMaterial(naranja);
}

//--------------------------------------------------------------------------
// Inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//--------------------------------------------------------------------------

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
    glClearColor( 252/255.0, 237.5/255.0, 227.5/255.0, 0.0 );   // color para limpiar la pantalla		 

	glEnable(GL_DEPTH_TEST);       // se habilita el z-bufer
	glEnable(GL_CULL_FACE);        // se habilita cull-face
    glEnable(GL_NORMALIZE);        // evita que se distorsionen las normales 

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

	change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

// --------------------------------------------------------------------------
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
// --------------------------------------------------------------------------

void Escena::dibujar()
{
	// Limpiar la pantalla
    glDisable (GL_LIGHTING);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
	change_observer();
    ejes.draw();
    glEnable(GL_LIGHTING);
    // Tipo de sombreado: suave
    glShadeModel(GL_SMOOTH);
        
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

    if(cuboAct){
        glPushMatrix();
            glTranslatef(-100.0,   0.0,   0.0);
            cubo->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(tetrAct){
        glPushMatrix();
            glTranslatef( 100.0,   0.0,   0.0);
            tetraedro->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(arboAct){
        glPushMatrix();
            glTranslatef(   0.0,   0.0,   0.0);
            glScalef(20.0,20.0,20.0);
            arbol->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(peonAct){
        glPushMatrix();
            glTranslatef(   50.0,   0.0, 100.0);
            glScalef(20.0,20.0,20.0);
            peon01->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(  -50.0,   0.0, 100.0);
            glScalef(20.0,20.0,20.0);
            peon02->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(ciliAct){
        glPushMatrix();
            glTranslatef(   0.0,   0.0,-100.0);
            cilindro->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(conoAct){
        glPushMatrix();
            glTranslatef(-100.0,   0.0,-100.0);
            cono->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }
    if(esfeAct){
        glPushMatrix();
            glTranslatef( 100.0,   0.0,-100.0);
            esfera->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();  
    } 
    if(ldirAct){
        glEnable(GL_LIGHTING);
        glPushMatrix();
            ldir->activar();
        glPopMatrix();
    }
    if(lposAct){
        glEnable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(   0.0, 150.0,  0.0);
            foco->draw(modoDibujado,ajedrezActivado);
            lpos->activar();
        glPopMatrix();

    }
}

//--------------------------------------------------------------------------
// Función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//--------------------------------------------------------------------------

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
	using namespace std;
	cout << "   -Tecla pulsada: '" << tecla << "'" << endl;
	bool salir=false;

    if(modoMenu==NADA){
        cout << "\n> Opciones disponibles:" << endl;
        cout << "   O: Modo de selección de objeto" << endl;
        cout << "   V: Modo de selección de visualización" << endl;
        cout << "   D: Modo de selección de dibujado" << endl;
        cout << "   Q: Salir del programa" << endl;
}

	switch(toupper(tecla))
	{
		case 'Q':
        	if (modoMenu!=NADA){
                cout << "> Volviendo al menú principal" << endl;
            	modoMenu=NADA;            
         	}else{
                cout << "\n> Adiós!\n" << endl;
            	salir=true;
            }
        break;
    	case 'O':     // Modo selección de objeto
        	modoMenu=SELOBJETO; 
         	printf("\n> Selecciona un objeto:\n   C: Cubo\n   T: Tetraedro\n   P: Peon\n   A: Árbol fractal\n   I: Cilindro\n   K: Cono\n   E: Esfera\n   Q: Salir\n");
        break;
		case 'V':    // Modo selección de visualización
         	modoMenu=SELVISUALIZACION;
         	printf("\n> Selecciona visualización:\n   P: Puntos\n   L: Lineas\n   S: Solido\n   A: Ajedrez\n   T: Activar/Desactivar tapas\n   Q: Salir\n");
        break;
        case 'I':    // Modo selección de iluminación
            modoMenu=SELILUMINACION;
            printf("\n> Modo Iluminación\n   1: Activar/Desactivar Luz 1\n   1: Activar/Desactivar Luz 2\n   A: Cambiar ángulo alpha\n   B: Cambiar ángulo beta\n");
        break;
       	case 'D':    // Modo selección de dibujado
         	modoMenu=SELDIBUJADO;
            printf("\n> Escoge modo de dibujado:\n   1: Modo Inmediato\n   2: Modo Diferido\n   Q: Salir");
        break;
    }

    // SELECCIÓN DE OBJETO
    if (modoMenu==SELOBJETO){
    	switch(toupper(tecla))
    	{
    		case 'C':   // Visualizar cubo
    			cout << "> Cubo " << ( cuboAct ? "desactivado" : "activado" ) << endl;
                cuboAct = !cuboAct;
    			//objetoActivo = CUBO;
    		break;
    		case 'T':   // Visualizar tetraedro
    			cout << "> Tetraedro " << ( tetrAct ? "desactivado" : "activado" ) << endl;
                tetrAct = !tetrAct;
    			//objetoActivo = TETRAEDRO;
    		break;
            case 'P':   // Visualizar peón
                cout << "> Peon " << ( peonAct ? "desactivado" : "activado" ) << endl;
                peonAct = !peonAct;
                //objetoActivo = PEON;
            break;
            case 'A':   // Visualizar árbol fractal
                cout << "> Árbol " << ( arboAct ? "desactivado" : "activado" ) << endl;
                arboAct = !arboAct;
                //objetoActivo = ARBOL;
            break;
            case 'I':   // Visualizar cilindro
                cout << "> Cilindro " << ( ciliAct ? "desactivado" : "activado" ) << endl;
                ciliAct = !ciliAct;
                //objetoActivo = CILINDRO;
            break;
            case 'K':   // Visualizar cono
                cout << "> Cono " << ( conoAct ? "desactivado" : "activado" ) << endl;
                conoAct = !conoAct;
                //objetoActivo = CONO;
            break;
            case 'E':   // Visualizar esfera
                cout << "> Esfera " << ( esfeAct ? "desactivada" : "activada" ) << endl;
                esfeAct = !esfeAct;
                //objetoActivo = ESFERA;
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
            case 'T':   // Activar o desactivar tapas
                cout << "Tapas " << ( tapasActivadas ? "desactivadas" : "activadas" ) << endl;
                // Actualizar variable de la escena
                tapasActivadas = !tapasActivadas;
                // Actualizar atributo en los objetos
                peon01->tapasVisibles=tapasActivadas;
                peon02->tapasVisibles=tapasActivadas;
                cilindro->tapasVisibles=tapasActivadas;
                cono->tapasVisibles=tapasActivadas;
                esfera->tapasVisibles=tapasActivadas;
            break;
        }
    }

    // SELECCIÓN DE ILUMINACIÓN
    if(modoMenu==SELILUMINACION){
        switch(toupper(tecla))
        {
            case '1':   // Activar/Desactivar Luz 1 
                if(ldirAct)
                    ldir->desactivar();
                else
                    ldir->activar();
                ldirAct = !ldirAct;
            break; 
            case '2':   // Activar/Desactivar Luz 2
                if(lposAct)
                    lpos->desactivar();
                else
                    lpos->activar();
                lposAct = !lposAct;
            break;
            case 'A':   // Cambiar al modo variación del ángulo alpha
                modoMenu = SELALPHA;
                printf("\n> Opciones disponibles:\n  <: Decrementar alpha\n  >: Aumentar alpha\n");
            break;  
            case 'B':   // Cambiar al modo variación del ángulo beta
                modoMenu = SELBETA;
                printf("\n> Opciones disponibles:\n  <: Decrementar beta\n  >: Aumentar beta\n");
            break;  
        }
    }

    // Variación del ángulo Alpha
    if(modoMenu==SELALPHA){
        switch(toupper(tecla))
        {
            case '<':
                ldir->setAlpha(-10);
            break;
            case '>':
                ldir->setAlpha(10);
            break;
        }
    }

    // Variación del ángulo Beta
    if(modoMenu==SELBETA){
        switch(toupper(tecla))
        {
            case '<':
                ldir->setBeta(-10);
            break;
            case '>':
                ldir->setBeta(10);
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

//--------------------------------------------------------------------------

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
}

//--------------------------------------------------------------------------
// Funcion para definir la transformación de proyeccion
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//--------------------------------------------------------------------------*

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}

//--------------------------------------------------------------------------
// Funcion que se invoca cuando cambia el tamaño de la ventana
//--------------------------------------------------------------------------*

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//--------------------------------------------------------------------------
// Funcion para definir la transformación de vista (posicionar la camara)
//--------------------------------------------------------------------------*

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
