#include "aux.h"
#include "objrevolucion.h"
#include "objply.h"
#include "ply_reader.h"
#include "math.h"			// M_PI (número pi), cos, sin
#include "algorithm"		// reverse

using namespace std;


// -----------------------------------------------------------------------------
// Clase ObjRevolucion
// -----------------------------------------------------------------------------


ObjRevolucion::ObjRevolucion() {}

// objeto de revolución obtenido a partir de un perfil (en un PLY)
ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje_r, bool textura)
{
	// Obtener perfil de objeto PLY
	ply::read_vertices(archivo, perfil);
	// Inicializar tablas de vértices y triángulos
	crearMalla(perfil, num_instancias, tapa_sup&&tapa_inf, eje_r);
	// Inicializar tablas de colores
	inicializaColores();
	// Calcular las normales
    calcular_normales();
	// Calcular coordenadas de textura
	if (textura) {calcular_textura(perfil, num_instancias);}
}

// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, char eje_r, bool textura)
{
	// Inicializar tablas de vértices y triángulos
	crearMalla(archivo, num_instancias, tapa_sup&&tapa_inf, eje_r);
	// Inicializar tablas de colores
	inicializaColores();
	// Calcular las normales
    calcular_normales();
	// Calcular coordenadas de textura
	if (textura) {calcular_textura(archivo, num_instancias);}
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil, int num_instancias, const bool tapas, char eje_r)
{
	// Número de vértices del perfil
	int nv = perfil.size();
	// Coordenadas de polo norte y polo sur
	Tupla3f pnorte, psur;
	// Variables auxiliares para tabla de vértices
	float x, y, z, angulo;
	// Vértice auxiliar para tabla de vértices
	Tupla3f vaux;
	// Indices auxiliares para tabla de triángulos
	int a, b;
	// Triángulo auxiliar para las tapas
	Tupla3i tapa;

	// Ordenar vértices en orden ascendente si no lo están
	if(perfil.front()(1) > perfil.back()(1)){
		reverse(perfil.begin(), perfil.end());
	}

	double epsilon = std::numeric_limits<double>::epsilon();

	// Extraer polo norte
	if(fabs(perfil.back()(0))<epsilon && fabs(perfil.back()(2))<epsilon){
		pnorte = perfil.back();
		perfil.pop_back();
	}else{
		// Si no hay, calcular proyección
		pnorte = Tupla3f(0,perfil.back()(1),0);
	}

	// Extraer polo sur
	if(fabs(perfil.front()(0))<epsilon && fabs(perfil.front()(2))<epsilon){
		psur   = perfil.front();
		perfil.erase(perfil.begin());
	}else{
		// Si no hay, calcular proyección
		psur   = Tupla3f(0,perfil.front()(1),0);
	}


	// Limpiar tablas de vértices y triángulos
	v.clear();
	f.clear();

	// Calcular vértices en función del eje de rotación
	switch(toupper(eje_r)){

		// Rotación sobre el Eje X
		case 'X':
			// Rellenar tabla de vértices
			for(int i=0; i<num_instancias; i++){
				// Calcular ángulo de rotación
				angulo = (2 * M_PI * i)/num_instancias;
				for(int j=0; j<nv; j++){
					// Rotar cada componente del vértice
					x =  perfil[j](0);
					y = (perfil[j](1) *  cos(angulo)) - (perfil[j](2) * sin(angulo));
					z = (perfil[j](1) *  sin(angulo)) + (perfil[j](2) * cos(angulo));

					// Añadir vertice rotado a la tabla de vertices
					v.push_back({x,y,z});
				}
			}
		break;

		// Rotación sobre el Eje Y
		case 'Y':
			// Rellenar tabla de vértices
			for(int i=0; i<num_instancias; i++){
				// Calcular ángulo de rotación
				angulo = (2 * M_PI * i)/num_instancias;
				for(int j=0; j<nv; j++){
					// Rotar cada componente del vértice
					x = (perfil[j](0) *  cos(angulo)) + (perfil[j](2) * sin(angulo));
					y =  perfil[j](1);
					z = (perfil[j](0) * -sin(angulo)) + (perfil[j](2) * cos(angulo));

					// Añadir vertice rotado a la tabla de vertices
					v.push_back({x,y,z});
				}
			}
		break;

		// Rotación sobre el Eje Z
		case 'Z':
			// Rellenar tabla de vértices
			for(int i=0; i<num_instancias; i++){
				// Calcular ángulo de rotación
				angulo = (2 * M_PI * i)/num_instancias;
				for(int j=0; j<nv; j++){
					// Rotar cada componente del vértice
					x = (perfil[j](0) *  cos(angulo)) - (perfil[j](2) * sin(angulo));
					y = (perfil[j](0) *  sin(angulo)) + (perfil[j](1) * cos(angulo));
					z =  perfil[j](2);

					// Añadir vertice rotado a la tabla de vertices
					v.push_back({x,y,z});
				}
			}
		break;
		default:
			cerr << eje_r << " no es un eje de rotacion valido para ObjRevolucion " << endl;
	}

	// Rellenar tabla de triángulos
	for(int i=0; i<num_instancias; i++){
		for(int j=0; j<nv-1; j++){
			a = (nv*i)+j;
			b = (nv*((i+1)%num_instancias))+j;

			//Añadir triángulos a la tabla de triángulos
			f.push_back(Tupla3i(a,b  ,b+1));
			f.push_back(Tupla3i(a,b+1,a+1));
		}
	}

	// Si se quieren añadir tapas a la malla
	if(tapas){
		// Número de vertices (sin los centrales) implicados en las tapas
		tapas_size = num_instancias*2;

		// Añadir polo sur
		v.push_back(psur);
		// Insertar triángulos tapa inferior
		for(int i=0; i<num_instancias; i++){
			a = (nv*i)%(nv*num_instancias);
			b = (nv*(i+1))%(nv*num_instancias);
			f.push_back(Tupla3i(v.size()-1,b,a));
		}

		// Añadir polo norte
		v.push_back(pnorte);
		// Insertar triángulos tapa superior
		for(int i=0; i<num_instancias; i++){
			a = ((nv*(i+1))-1)%(nv*num_instancias);
			b = ((nv*(i+2))-1)%(nv*num_instancias);
			f.push_back(Tupla3i(v.size()-1,a,b));
		}
	}

	// Separa caras pares e impares (Modo Ajedrez)
	for(int i=0; i<f.size(); i++){
		(i%2==0) ? f_par.push_back(f[i]) : f_imp.push_back(f[i]);
	}
}

void ObjRevolucion::dibujarElementos(){
	if(tapasVisibles)
		glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
	else
		glDrawElements(GL_TRIANGLES, f.size()*3 - tapas_size*3, GL_UNSIGNED_INT, f.data());
}

void ObjRevolucion::dibujarElementosDif(){
	if(tapasVisibles)
		glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, f.size()*3 - tapas_size*3, GL_UNSIGNED_INT, 0);
}

void ObjRevolucion::dibujarElementosAjedrez(){
	if(tapasVisibles){
		// Dibujar caras pares
		glColorPointer( 3, GL_FLOAT, 0, cAjP.data());
	   	glDrawElements(GL_TRIANGLES, f_par.size()*3, GL_UNSIGNED_INT, f_par.data());
		// Dibujar caras impares
	   	glColorPointer( 3, GL_FLOAT, 0, cAjI.data());
	   	glDrawElements(GL_TRIANGLES, f_imp.size()*3, GL_UNSIGNED_INT, f_imp.data());
	}else{
		// Dibujar caras pares
		glColorPointer( 3, GL_FLOAT, 0, cAjP.data());
	   	glDrawElements(GL_TRIANGLES, f_par.size()*3 - (tapas_size*3)/2, GL_UNSIGNED_INT, f_par.data());
		// Dibujar caras impares
	   	glColorPointer( 3, GL_FLOAT, 0, cAjI.data());
	   	glDrawElements(GL_TRIANGLES, f_imp.size()*3 - (tapas_size*3)/2, GL_UNSIGNED_INT, f_imp.data());
	}
}

void ObjRevolucion::inicializaColores()
{
	// Colores en modo puntos, lineas y sólido
	c.resize(v.size());
    for(int i=0; i<v.size(); i=i+2){
      c[i]   = Tupla3f(248/255.0, 196/255.0,  98/255.0);
      c[i+1] = Tupla3f(233/255.0, 183/255.0, 114/255.0);
    }

    // Colores en modo ajedrez
    cAjP.resize(v.size());   		  	// Pares
    cAjI.resize(v.size());     			// Impares

    for(int i=0; i<v.size(); i++){
      cAjP[i]   = Tupla3f(248/255.0, 196/255.0,  98/255.0);
    }

    for(int i=0; i<v.size(); i++){
      cAjI[i]   = Tupla3f(233/255.0, 183/255.0, 114/255.0);
    }
}

void ObjRevolucion::calcular_textura(std::vector<Tupla3f> archivo, int num_instancias)
{
	ct.resize(v.size());
	int tam = archivo.size();
	std::vector<float> distancias;
	float s, t, d = 0;

	distancias.push_back(d);
	for(int i=1; i<tam; i++){
		d = distancias[i-1] + sqrt(pow(archivo[i](0) - archivo[i-1](0), 2) +
								   pow(archivo[i](1) - archivo[i-1](1), 2) +
								   pow(archivo[i](2) - archivo[i-1](2), 2) );
		distancias.push_back(d);
	}

	for(int i=0; i<num_instancias; i++){
		s = i/(num_instancias-1);
		for(int j=0; i<tam; i++){
			t = distancias[j]/distancias[tam-1];
			ct.push_back({s,t});
		}
	}
}
