

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

    // Cámaras
    Camara cam1 = Camara({0.0,300.0,1000.0}, {0.0,100.0,0.0}, {0.0,1.0,0.0}, true, -500, 500, 400, -400, Front_plane*4, Back_plane);
    Camara cam2 = Camara({0.0,900.0,300.0}, {0.0,50.0,0.0}, {0.0,50.0,0.0}, false, -300, 300, 400, -400, Front_plane*4, Back_plane);
    Camara cam3 = Camara({600.0,300.0,0.0}, {0.0,50.0,0.0}, {0.0,50.0,0.0}, false, -300, 300, 400, -400, Front_plane*4, Back_plane);
    camaras.push_back(cam1);
    camaras.push_back(cam2);
    camaras.push_back(cam3);

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
    // Materiales de objetos texturizados en selección
    cubo->setMaterial(amarillo);
    cartel->setMaterial(amarillo);
    palo->setMaterial(amarillo);
    panel->setMaterial(amarillo);
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

    dibujarObjetos();
}

void Escena::dibujarObjetos()
{
    // Suelo
    if(cuboAct){
        glPushMatrix();
            glTranslatef(0.0,  -40.0,   0.0);
            glScalef(10.0,0.5,10.0);
            cubo->draw(modoDibujado,ajedrezActivado,texturaCubo);
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
            palo->draw(modoDibujado,ajedrezActivado,texturaCartel);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(55.0, 25.0, -90.0);
            glScalef(1,1,0.15);
            glRotatef(90,1,0,0);
            panel->draw(modoDibujado,ajedrezActivado,texturaCartel);
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
        glDisable(GL_LIGHTING);
    }

    // Luz posicional (Sol)
    if(lposAct){
        glEnable(GL_LIGHTING);
        glPushMatrix();
            glTranslatef(   0.0, 0.0,  0.0);
            sol->draw(modoDibujado,ajedrezActivado);
        glPopMatrix();
        glDisable(GL_LIGHTING);
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
        cout << "   C: Modo de selección de cámaras" << endl;
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
                printf("\n   1: Corona\n   2: Pétalos\n   3: Tallo\n   4: Hoja\n   5: De toda la flor\n   6: Sol\n   7: De toda la escena\n");
            }
        break;
        case 'M':    // Modo de animación manual
         	modoMenu=SELMANUAL;
            animacionAutomatica = false;
            printf("\n> ¿Qué quieres mover?:\n   1: Corona de la flor\n   2: Pétalos\n   3: Tallo\n   4: Hoja\n   Q: Salir\n");
        break;
        case 'C':   // Modo de selección de cámaras
            modoMenu=SELCAMARA;
            printf("\n> ¿Qué cámara quieres ver?:\n   1: Cámara 1 (Ortogonal)\n   2: Cámara 2 (Perspectiva)\n   3: Cámara 3 (Perspectiva)\n   Q: Salir\n");
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
            case '2':   // Apertura de los pétalos
                cout << "Has seleccionado el movimiento de los pétalos. ¿Qué quieres hacer?" << endl;
                cout << "   +: Abrir\n   -: Cerrar" << endl;
                animacionActiva = PETALOS;
            break;
            case '3':   // Subir o bajar el tallo
                cout << "Has seleccionado el movimiento del tallo. ¿Qué quieres hacer?" << endl;
                cout << "   +: Subir\n   -: Bajar" << endl;
                animacionActiva = TALLO;
            break;
            case '4':   // Giro de la hoja
                cout << "Has seleccionado el movimiento de la hoja. ¿Qué quieres hacer?" << endl;
                cout << "   +: Subir\n   -: Bajar" << endl;
                animacionActiva = HOJA;
            break;
            case '+':
                switch (animacionActiva) {
                    case CORONA: flor1->setGiro(5); flor2->setGiro(5); flor3->setGiro(5);
                    break;
                    case PETALOS: flor1->setApertura(5); flor2->setApertura(5); flor3->setApertura(5);
                    break;
                    case TALLO: flor1->setAltura(0.3); flor2->setAltura(0.3); flor3->setAltura(0.3);
                    break;
                    case HOJA: flor1->setAngHoja(1); flor2->setAngHoja(1); flor3->setAngHoja(1);
                    break;
                }
            break;
            case '-':
                switch (animacionActiva) {
                    case CORONA: flor1->setGiro(-5); flor2->setGiro(-5); flor3->setGiro(-5);
                    break;
                    case PETALOS: flor1->setApertura(-5); flor2->setApertura(-5); flor3->setApertura(-5);
                    break;
                    case TALLO: flor1->setAltura(-0.3); flor2->setAltura(-0.3); flor3->setAltura(-0.3);
                    break;
                    case HOJA: flor1->setAngHoja(-1); flor2->setAngHoja(-1); flor3->setAngHoja(-1);
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
            case '2':   // Velocidad de la apertura de los pétalos
                cout << "   +: Aumentar velocidad de apertura\n   -: Disminuir velocidad de apertura" << endl;
                animacionActiva = PETALOS;
            break;
            case '3':   // Velocidad del tallo
                cout << "   +: Aumentar velocidad del tallo\n   -: Disminuir velocidad del tallo" << endl;
                animacionActiva = TALLO;
            break;
            case '4':   // Velocidad de la hoja
                cout << "   +: Aumentar velocidad de la hoja\n   -: Disminuir velocidad de la hoja" << endl;
                animacionActiva = HOJA;
            break;
            case '5':   // Velocidad de la flor
                cout << "   +: Aumentar velocidad de la flor\n   -: Disminuir velocidad de la flor" << endl;
                animacionActiva = FLOR;
            break;
            case '6':   // Velocidad del sol
                cout << "   +: Aumentar velocidad del sol\n   -: Disminuir velocidad del sol" << endl;
                animacionActiva = SOL;
            break;
            case '7':   // Velocidad general
                cout << "   +: Aumentar velocidad en general\n   -: Disminuir velocidad en general" << endl;
                animacionActiva = GENERAL;
            break;
            case '+':
                switch (animacionActiva) {
                    case CORONA: animacionCorona *= 1.20;
                    break;
                    case PETALOS: animacionPetalos *=1.20;
                    break;
                    case TALLO: animacionTallo *= 1.20;
                    break;
                    case HOJA: animacionHoja *= 1.20;
                    break;
                    case FLOR:
                        animacionCorona *= 1.20;
                        animacionPetalos *=1.20;
                        animacionTallo *= 1.20;
                        animacionHoja *= 1.20;
                    break;
                    case SOL: animacionSol += 0.20;
                    break;
                    case GENERAL:
                        animacionCorona *= 1.20;
                        animacionPetalos *=1.20;
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
                    case PETALOS: animacionPetalos *=0.80;
                    break;
                    case TALLO: animacionTallo *= 0.80;
                    break;
                    case HOJA: animacionHoja *= 0.80;
                    break;
                    case FLOR:
                        animacionCorona *= 0.80;
                        animacionPetalos *=0.80;
                        animacionTallo *= 0.80;
                        animacionHoja *= 0.80;
                    break;
                    case SOL: animacionSol -= 0.20;
                    break;
                    case GENERAL:
                        animacionCorona *= 0.80;
                        animacionPetalos *=0.80;
                        animacionTallo *= 0.80;
                        animacionHoja *= 0.80;
                        animacionSol -= 0.20;
                    break;
                }
            break;
        }
    }

    // Modo de selección de cámara
    if(modoMenu==SELCAMARA){
        switch(toupper(tecla))
        {
            case '1': camaraActiva = 0;
                cout << "   -> Camara 1 activada" << endl;
            break;
            case '2': camaraActiva = 1;
                cout << "   -> Camara 2 activada" << endl;
            break;
            case '3': camaraActiva = 2;
                cout << "   -> Camara 3 activada" << endl;
            break;
        }
        change_observer();
        change_projection(1.0);
    }

   return salir;
}

//--------------------------------------------------------------------------

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[camaraActiva].rotarExaminar('Y', -2*(M_PI/180));
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarExaminar('Y',  2*(M_PI/180));
         break;
	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarExaminar('X', -2*(M_PI/180));
         break;
	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarExaminar('X',  2*(M_PI/180));
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva].zoom(0.8);
         change_projection(1.0);
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva].zoom(1.2);
         change_projection(1.0);
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
   camaras[camaraActiva].setProyeccion();
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
   camaras[camaraActiva].setObserver();
}

//--------------------------------------------------------------------------
// Funciones para los eventos de ratón y la cámara
//--------------------------------------------------------------------------*

void Escena::clickRaton(int boton, int estado, int x, int y)
{
    if(estado == GLUT_DOWN){
        switch (boton) {
            // Botón derecho (cámara)
            case GLUT_RIGHT_BUTTON:
                xant = x;
                yant = y;
                moviendo_raton = true;
            break;
            // Botón izquierdo (seleccionar)
            case GLUT_LEFT_BUTTON:
                dibujaSeleccion();
                analizarPixel(x,y);
            break;
            // Scroll hacia arriba
            case 3:
                camaras[camaraActiva].zoom(0.8);
                change_projection(1.0);
            break;
            // Scroll hacia abajo
            case 4:
                camaras[camaraActiva].zoom(1.2);
                change_projection(1.0);
            break;
        }
    }else{
        switch (boton) {
            case GLUT_RIGHT_BUTTON: moviendo_raton = false;
            break;
        }
    }
}

void Escena::ratonMovido(int x, int y)
{
    if(moviendo_raton){
        if(objetoSeleccionado == NULO){
            camaras[camaraActiva].girar((x-xant)*(M_PI/180)*0.2, (y-yant)*(M_PI/180)*0.2);
        }else{
            camaras[camaraActiva].rotarExaminar('X', (y-xant)*(M_PI/180)*0.2);
            camaras[camaraActiva].rotarExaminar('Y', (x-yant)*(M_PI/180)*0.2);
        }
        xant = x;
        yant = y;
    }
}

//--------------------------------------------------------------------------
// Funciones para seleccionar objetos con el ratón
//--------------------------------------------------------------------------*

void Escena::dibujaSeleccion()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ajedrezActivado = false;
    change_observer();
    glDisable(GL_DITHER);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);

    // Colores para la codificación
    // Suelo
    cubo->setColor({0.0,0.0,0.0});
    // Cartel
    cartel->setColor({0.0,0.0,1.0});
    panel->setColor({0.0,0.0,1.0});
    palo->setColor({0.0,0.0,1.0});
    // Árboles
    arbol1->setColor({0.0,1.0,0.0});
    arbol2->setColor({0.0,1.0,1.0});
    arbol3->setColor({1.0,0.0,0.0});
    arbol4->setColor({1.0,0.0,1.0});
    arbol5->setColor({1.0,1.0,0.0});
    arbol6->setColor({1.0,1.0,1.0});
    // Flores
    flor1->setColor({0.0,0.0,0.5});
    flor2->setColor({0.0,0.5,0.0});
    flor3->setColor({0.0,0.5,0.5});
    // Sol
    sol->setColor({0.5,0.0,0.0});

    dibujarObjetos();

    glEnable(GL_DITHER);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void Escena::analizarPixel(int x, int y)
{
    GLfloat p[2];                                                   // pixel leído
    GLint viewport[4];                                              // para width (3)
    glGetIntegerv(GL_VIEWPORT,viewport);                            // guarda viewport
    glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_FLOAT,p);

    // Suelo
    if(p[0]==0.0 && p[1]==0.0 && p[2]==0.0){
        camaras[camaraActiva].mover(0.0,25.0,0.0);
        objetoSeleccionado = (objetoSeleccionado==S) ? NULO : S;
        texturaCubo = !texturaCubo;
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Suelo") << endl;
    // Cartel
    }else if(p[0]==0.0 && p[1]==0.0 && p[2]<0.4){
        camaras[camaraActiva].mover(55.0,25.0,-90.0);
        objetoSeleccionado = (objetoSeleccionado==C) ? NULO : C;
        texturaCartel = !texturaCartel;
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Cartel") << endl;
    // Árbol 1
    }else if(p[0]==0.0 && p[1]==1.0 && p[2]==0.0){
        camaras[camaraActiva].mover(0.0,25.0,-200.0);
        objetoSeleccionado = (objetoSeleccionado==A1) ? NULO : A1;
        if(objetoSeleccionado!=NULO){arbol1->setMaterial(amarillo);}else{arbol1->setMaterial(marron);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 1") << endl;
    // Árbol 2
    }else if(p[0]==0.0 && p[1]==1.0 && p[2]==1.0){
        camaras[camaraActiva].mover(-140.0,25.0,-20.0);
        objetoSeleccionado = (objetoSeleccionado==A2) ? NULO : A2;
        if(objetoSeleccionado!=NULO){arbol2->setMaterial(amarillo);}else{arbol2->setMaterial(verde);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 2") << endl;
    // Árbol 3
    }else if(p[0]==1.0 && p[1]==0.0 && p[2]==0.0){
        camaras[camaraActiva].mover(-150.0,25.0,-160.0);
        objetoSeleccionado = (objetoSeleccionado==A3) ? NULO : A3;
        if(objetoSeleccionado!=NULO){arbol3->setMaterial(amarillo);}else{arbol3->setMaterial(kombu);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 3") << endl;
    // Árbol 4
    }else if(p[0]==1.0 && p[1]==0.0 && p[2]==1.0){
        camaras[camaraActiva].mover(210.0,25.0,176.0);
        objetoSeleccionado = (objetoSeleccionado==A4) ? NULO : A4;
        if(objetoSeleccionado!=NULO){arbol4->setMaterial(amarillo);}else{arbol4->setMaterial(verde);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 4") << endl;
    // Árbol 5
    }else if(p[0]==1.0 && p[1]==1.0 && p[2]==0.0){
        camaras[camaraActiva].mover(150.0,25.0,230.0);
        objetoSeleccionado = (objetoSeleccionado==A5) ? NULO : A5;
        if(objetoSeleccionado!=NULO){arbol5->setMaterial(amarillo);}else{arbol5->setMaterial(kombu);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 5") << endl;
    // Árbol 6
    }else if(p[0]==1.0 && p[1]==1.0 && p[2]==1.0){
        camaras[camaraActiva].mover(-190.0,25.0,-100.0);
        objetoSeleccionado = (objetoSeleccionado==A6) ? NULO : A6;
        if(objetoSeleccionado!=NULO){arbol6->setMaterial(amarillo);}else{arbol6->setMaterial(marron);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Árbol 6") << endl;
    // Flor 1
    }else if(p[0]==0.0 && p[1]==0.0 && p[2]<0.6){
        camaras[camaraActiva].mover(-90.0,25.0,50.0);
        objetoSeleccionado = (objetoSeleccionado==F1) ? NULO : F1;
        if(objetoSeleccionado!=NULO){flor1->setMaterial(amarillo, amarillo, amarillo, amarillo, amarillo);}else{flor1->setMaterial(verde, amarillo, blanco, verde, arcilla);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Flor 1") << endl;
    // Flor 2
    }else if(p[0]==0.0 && p[1]<0.6 && p[2]==0.0){
        camaras[camaraActiva].mover(-180.0,25.0,100.0);
        objetoSeleccionado = (objetoSeleccionado==F2) ? NULO : F2;
        if(objetoSeleccionado!=NULO){flor2->setMaterial(amarillo, amarillo, amarillo, amarillo, amarillo);}else{flor2->setMaterial(verde, amarillo, azul, verde, arcilla);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Flor 2") << endl;
    // Flor 3
    }else if(p[0]==0.0 && p[1]<0.6 && p[2]<0.6){
        camaras[camaraActiva].mover(-120.0,25.0,180.0);
        objetoSeleccionado = (objetoSeleccionado==F3) ? NULO : F3;
        if(objetoSeleccionado!=NULO){flor3->setMaterial(amarillo, amarillo, amarillo, amarillo, amarillo);}else{flor3->setMaterial(verde, amarillo, blanco, verde, arcilla);}
        cout << "   > " << (objetoSeleccionado==NULO ? "Nada seleccionado" : "Flor 3") << endl;
    }
}

//--------------------------------------------------------------------------
// Funciones para la animación automática del modelo jerárquico y el Sol
//--------------------------------------------------------------------------*

void Escena::animarEscena()
{
    // Animar flores (Modelo jerárquico)
    animarFlor(flor1);
    animarFlor(flor2);
    animarFlor(flor3);

    // Animar luz poscional
    sol->setPosicion(animacionSol);
}

void Escena::animarFlor(Flor* flor)
{
    flor->setAltura(animacionTallo);
    flor->setApertura(animacionPetalos);
    flor->setGiro(animacionCorona);
    flor->setAngHoja(animacionHoja);
}
