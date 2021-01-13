

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
    cubo      = new Cubo(50,"./textures/grass.jpg");
    tetraedro = new Tetraedro(20);
    arbol1    = new ObjPLY("./plys/fractree.ply");
    arbol2    = new ObjPLY("./plys/fractree.ply");
    arbol3    = new ObjPLY("./plys/fractree.ply");
    arbol4    = new ObjPLY("./plys/fractree.ply");
    arbol5    = new ObjPLY("./plys/fractree.ply");
    arbol6    = new ObjPLY("./plys/fractree.ply");
    cartel    = new Cuadro(50,50,"./textures/sign.jpg");
    palo      = new Cubo(50,"./textures/wood.jpg");
    panel     = new Cubo(60,"./textures/wood.jpg");
    flor1     = new Flor();
    flor2     = new Flor();
    flor3     = new Flor();

    // Luces de la escena
    ldir      = new LuzDireccional(GL_LIGHT1,{M_PI,M_PI},{0.20f,0.20f,0.20f,1.0f},{0.20f,0.20f,0.20f,1.0f},{0.20f,0.20f,0.20f,1.0f});
    sol       = new Sol();

    // Materiales
    Material marron   = Material({0.0368627,0.0313725,0.0247058,1.0f},{0.368627,0.313725,0.247058,1.0f},{0.368627,0.313725,0.247058,1.0f},15.8f);
    Material verde    = Material({ 0.0f,0.0f,0.0f,1.0f },{ 0.1f,0.35f,0.1f,1.0f},{0.45f,0.55f,0.45f,1.0f },32.0f);
    Material arcilla  = Material({ 0.19125f, 0.0735f, 0.0225f, 1.0f },{0.7038f, 0.27048f, 0.0828f, 1.0f },{0.256777f, 0.137622f, 0.086014f, 1.0f },12.8f);
    Material amarillo = Material({ 0.24725f, 0.1995f, 0.0745f, 1.0f },{0.75164f, 0.60648f, 0.22648f, 1.0f },{0.628281f, 0.555802f, 0.366065f, 1.0f },51.2f);
    Material blanco   = Material({0.650f,0.600f,0.600f,1.0f},{0.000f,0.000f,0.000f,1.0f},{0.650f,0.600f,0.600f,1.0f},90.00f);
    Material kombu    = Material({0.156862,0.211764,0.094117,1.0f},{0.156862,0.211764,0.094117,1.0f},{0.156862,0.211764,0.094117,1.0f},12.3f);
    Material azul    = Material({0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f},{0.435f,0.690f,0.674f,1.0f}, 0.00f);

    // Asignar materiales a los objetos de la escena
    arbol1->setMaterial(marron);
    arbol2->setMaterial(verde);
    arbol3->setMaterial(kombu);
    arbol4->setMaterial(verde);
    arbol5->setMaterial(kombu);
    arbol6->setMaterial(marron);
    flor1->setMaterial(verde, amarillo, blanco, verde, arcilla);
    flor2->setMaterial(verde, amarillo, azul, verde, arcilla);
    flor3->setMaterial(verde, amarillo, blanco, verde, arcilla);
    sol->setMaterial(amarillo);
}

//--------------------------------------------------------------------------
// Inicialización de la escena (se ejecuta cuando ya se ha creado la ventana,
// por tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//--------------------------------------------------------------------------

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
    //glClearColor( 252/255.0, 237.5/255.0, 227.5/255.0, 0.0 );   // color para limpiar la pantalla
    glClearColor( 202/255.0, 227.5/255.0, 247.5/255.0, 0.0 );   // color para limpiar la pantalla

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

    if(ajedrezActivado){
        glDisable (GL_LIGHTING);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    // Suelo
    if(cuboAct){
        glPushMatrix();
            glTranslatef(0.0,  -40.0,   0.0);
            glScalef(10.0,0.5,10.0);
            cubo->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }

    // Árboles
    if(arboAct){
        glPushMatrix();
            glTranslatef(   0.0, 100.0,-200.0);
            glScalef(30.0,30.0,30.0);
            arbol1->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-140.0,   75.0,-20.0);
            glScalef(20.0,20.0,20.0);
            arbol2->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-150.0,   150.0,-160.0);
            glScalef(40.0,40.0,40.0);
            arbol3->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(210.0, 87.0,176.0);
            glScalef(25.0,25.0,25.0);
            arbol4->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(150.0,   75.0,230.0);
            glScalef(20.0,20.0,20.0);
            arbol5->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-190.0,   75.0, -100.0);
            glScalef(23.0,23.0,23.0);
            arbol6->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }

    // Cartel
    if(cartAct) {
        glPushMatrix();
            glTranslatef(80.0, 50.0, -85.0);
            glRotatef(180,0,0,1);
            cartel->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(55.0, 0.0, -90.0);
            glScalef(0.15,1,0.15);
            glRotatef(90,1,0,0);
            palo->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(55.0, 25.0, -90.0);
            glScalef(1,1,0.15);
            glRotatef(90,1,0,0);
            palo->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
    }

    // Flores
    if(florAct){
        glPushMatrix();
            glTranslatef(-90.0, -35.0, 50.0);
            glScalef(1.2,1.2,1.2);
            flor1->draw(modoDibujado, ajedrezActivado);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-180.0, -35.0, 100.0);
            glScalef(1.2,1.2,1.2);
            flor2->draw(modoDibujado, ajedrezActivado);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-120.0, -35.0, 180.0);
            glScalef(1.2,1.2,1.2);
            flor3->draw(modoDibujado, ajedrezActivado);
        glPopMatrix();
    }

    // Luz direccional (fija)
    if(ldirAct){
        glEnable(GL_LIGHTING);
        glPushMatrix();
            ldir->activar();
        glPopMatrix();
    }

    // Luz posicional (Sol)
    if(lposAct){
        glEnable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(   0.0, 0.0,  0.0);
            sol->draw(modoDibujado,ajedrezActivado);
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
        cout << "   I: Modo de selección de la iluminación" << endl;
        cout << "   A: Activar/Desactivar animación automática" << endl;
        cout << "   M: Modo de animación manual" << endl;
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
         	printf("\n> Selecciona un objeto:\n   A: Árboles\n   C: Cartel\n   F: Flores\n   S: Suelo\n   Q: Salir\n");
        break;
		case 'V':    // Modo selección de visualización
         	modoMenu=SELVISUALIZACION;
         	printf("\n> Selecciona visualización:\n   P: Puntos\n   L: Lineas\n   S: Solido\n   A: Ajedrez\n   T: Activar/Desactivar tapas\n   I: Iluminación\n   Q: Salir\n");
        break;
        case 'I':    // Modo selección de iluminación
            modoMenu=SELILUMINACION;
            printf("\n> Modo Iluminación\n   1: Activar/Desactivar Luz direccional\n   2: Activar/Desactivar Sol (Luz puntual)\n   A: Cambiar ángulo alpha\n   B: Cambiar ángulo beta\n");
        break;
       	case 'D':    // Modo selección de dibujado
         	modoMenu=SELDIBUJADO;
            printf("\n> Escoge modo de dibujado:\n   1: Modo Inmediato\n   2: Modo Diferido\n   Q: Salir\n");
        break;
        case 'A':    // Activar/Desactivar animación automática
            animacionAutomatica = !animacionAutomatica;
            cout << "\n> Animación automática " << (animacionAutomatica ? "activada" : "desactivada") <<endl;
            if(animacionAutomatica){
                modoMenu=SELVELOCIDAD;
                printf("\n> ¿De qué quieres cambiar la velocidad?:\n");
                printf("\n   1: Corona\n   2: Tallo\n   3: Hoja\n   4: De toda la flor\n   5: Sol\n   6: De toda la escena\n");
            }
        break;
        case 'M':    // Modo de animación manual
         	modoMenu=SELMANUAL;
            //animacionAutomatica = false;
            printf("\n> ¿Qué quieres mover?:\n   1: Corona de la flor\n   2: Tallo\n   3: Hoja\n   Q: Salir\n");
        break;
    }

    // SELECCIÓN DE OBJETO
    if (modoMenu==SELOBJETO){
    	switch(toupper(tecla))
    	{

            case 'A':   // Visualizar árboles
                cout << "> Árboles " << ( arboAct ? "desactivados" : "activados" ) << endl;
                arboAct = !arboAct;
            break;
            case 'C':   // Visualizar cartel
                cout << "> Cartel " << ( arboAct ? "desactivado" : "activado" ) << endl;
                cartAct = !cartAct;
            break;
            case 'F':   // Visualizar flores
                cout << "> Flores " << ( arboAct ? "desactivadas" : "activadas" ) << endl;
                florAct = !florAct;
            break;
            case 'S':   // Visualizar cubo
    			cout << "> Suelo " << ( cuboAct ? "desactivado" : "activado" ) << endl;
                cuboAct = !cuboAct;
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
                    sol->desactivar();
                else
                    sol->activar();
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
            case '<': ldir->setAlpha(-20);
            break;
            case '>': ldir->setAlpha(20);
            break;
        }
    }

    // Variación del ángulo Beta
    if(modoMenu==SELBETA){
        switch(toupper(tecla))
        {
            case '<': ldir->setBeta(-20);
            break;
            case '>': ldir->setBeta(20);
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

    // ANIMACIÓN MANUAL
    if (modoMenu==SELMANUAL){
        switch(toupper(tecla))
        {
            case '1':   // Giro de la corona
                cout << "Has seleccionado el movimiento de la corona. ¿Qué quieres hacer?" << endl;
                cout << "   +: Giro horario\n   -: Giro antihorario" << endl;
                animacionActiva = CORONA;
            break;
            case '2':   // Subir o bajar el tallo
                cout << "Has seleccionado el movimiento del tallo. ¿Qué quieres hacer?" << endl;
                cout << "   +: Subir\n   -: Bajar" << endl;
                animacionActiva = TALLO;
            break;
            case '3':   // Giro de la hoja
                cout << "Has seleccionado el movimiento de la hoja. ¿Qué quieres hacer?" << endl;
                cout << "   +: Subir\n   -: Bajar" << endl;
                animacionActiva = HOJA;
            break;
            case '+':
                switch (animacionActiva) {
                    case CORONA: flor1->setAngPetalos(5);
                    break;
                    case TALLO: flor1->setAltura(0.3);
                    break;
                    case HOJA: flor1->setAngHoja(1);
                    break;
                }
            break;
            case '-':
                switch (animacionActiva) {
                    case CORONA: flor1->setAngPetalos(-5);
                    break;
                    case TALLO: flor1->setAltura(-0.3);
                    break;
                    case HOJA: flor1->setAngHoja(-1);
                    break;
                }
            break;
        }
    }

    // VELOCIDAD DE ANIMACIÓN
    if (modoMenu==SELVELOCIDAD){
        switch(toupper(tecla))
        {
            case '1':   // Velocidad de la corona
                cout << "   +: Aumentar velocidad de la corona\n   -: Disminuir velocidad de la corona" << endl;
                animacionActiva = CORONA;
            break;
            case '2':   // Velocidad del tallo
                cout << "   +: Aumentar velocidad del tallo\n   -: Disminuir velocidad del tallo" << endl;
                animacionActiva = TALLO;
            break;
            case '3':   // Velocidad de la hoja
                cout << "   +: Aumentar velocidad de la hoja\n   -: Disminuir velocidad de la hoja" << endl;
                animacionActiva = HOJA;
            break;
            case '4':   // Velocidad de la flor
                cout << "   +: Aumentar velocidad de la flor\n   -: Disminuir velocidad de la flor" << endl;
                animacionActiva = FLOR;
            break;
            case '5':   // Velocidad del sol
                cout << "   +: Aumentar velocidad del sol\n   -: Disminuir velocidad del sol" << endl;
                animacionActiva = SOL;
            break;
            case '6':   // Velocidad general
                cout << "   +: Aumentar velocidad en general\n   -: Disminuir velocidad en general" << endl;
                animacionActiva = GENERAL;
            break;
            case '+':
                switch (animacionActiva) {
                    case CORONA: animacionCorona *= 1.20;
                    break;
                    case TALLO: animacionTallo *= 1.20;
                    break;
                    case HOJA: animacionHoja *= 1.20;
                    break;
                    case FLOR:
                        animacionCorona *= 1.20;
                        animacionTallo *= 1.20;
                        animacionHoja *= 1.20;
                    break;
                    case SOL: animacionSol += 0.20;
                    break;
                    case GENERAL:
                        animacionCorona *= 1.20;
                        animacionTallo *= 1.20;
                        animacionHoja *= 1.20;
                        animacionSol += 0.20;
                    break;
                }
            break;
            case '-':
                switch (animacionActiva) {
                    case CORONA: animacionCorona *= 0.80;
                    break;
                    case TALLO: animacionTallo *= 0.80;
                    break;
                    case HOJA: animacionHoja *= 0.80;
                    break;
                    case FLOR:
                        animacionCorona *= 0.80;
                        animacionTallo *= 0.80;
                        animacionHoja *= 0.80;
                    break;
                    case SOL: animacionSol -= 0.20;
                    break;
                    case GENERAL:
                        animacionCorona *= 0.80;
                        animacionTallo *= 0.80;
                        animacionHoja *= 0.80;
                        animacionSol -= 0.20;
                    break;
                }
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

//--------------------------------------------------------------------------
// Funcion para la animación automática del modelo jerárquico
//--------------------------------------------------------------------------*

void Escena::animarModeloJerarquico()
{
    // Animar flores (Modelo jerárquico)
    flor1->setAltura(animacionTallo);
    flor1->setAngPetalos(animacionCorona);
    flor1->setAngHoja(animacionHoja);

    flor2->setAltura(animacionTallo);
    flor2->setAngPetalos(animacionCorona);
    flor2->setAngHoja(animacionHoja);

    flor3->setAltura(animacionTallo);
    flor3->setAngPetalos(animacionCorona);
    flor3->setAngHoja(animacionHoja);

    // Animar luz poscional
    sol->setPosicion(animacionSol);
}
