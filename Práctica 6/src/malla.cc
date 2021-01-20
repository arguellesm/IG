#include "aux.h"
#include "math.h"		// sqrt, pow
#include "malla.h"
using namespace std;

// -----------------------------------------------------------------------------
// Clase Malla3D
// -----------------------------------------------------------------------------

// Crear Vertex Buffer Object (VBO
GLuint Malla3D::crearVBO(GLuint tipo, GLuint tam_bytes, GLvoid * puntero_ram)
{
	GLuint id_vbo;					// ID de VBO
	glGenBuffers(1, & id_vbo);		// Crear nuevo VBO
	glBindBuffer(tipo, id_vbo);		// Activar el VBO usando el ID
	// Transferencia de datos desde la RAM a la CPU
	glBufferData(tipo, tam_bytes, puntero_ram, GL_STATIC_DRAW);
	glBindBuffer(tipo, 0);			// Desactivar VBO
	return id_vbo;					// Devolver ID resultado
}

// Visualización en modo ajedrez
void Malla3D::draw_modoAjedrez()
{
	// Activar array de vértices común
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());

	// Dibuja caras pares e impares
	dibujarElementosAjedrez();

	// Deshabilitar array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);
}

// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato()
{
	// Habilitar e indicar array de vertices y color
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
   	glColorPointer( 3, GL_FLOAT, 0, c.data());

   	// Habilitar e indicar array de normales
   	if(glIsEnabled(GL_LIGHTING)){
   		glEnableClientState(GL_NORMAL_ARRAY);
   		glNormalPointer(GL_FLOAT, 0, nv.data());
   		m.aplicar();
   	}

	// Dibujar usando vértices indexados
   	dibujarElementos();
	// Deshabilitar array de vertices
	glDisableClientState(GL_VERTEX_ARRAY);
	//Deshabilitar array de normales
	if(glIsEnabled(GL_LIGHTING))
		glDisableClientState(GL_NORMAL_ARRAY);
}

// Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void Malla3D::draw_ModoDiferido()
{
	// Crear VBO si no tienen ID válido (es 0)
	if(id_vbo_v==0)
		id_vbo_v = crearVBO(GL_ARRAY_BUFFER, sizeof(v[0])*v.size(), v.data());
	if(id_vbo_f==0)
		id_vbo_f = crearVBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(f[0])*f.size(), f.data());
	if(id_vbo_c==0)
		id_vbo_c = crearVBO(GL_ARRAY_BUFFER, sizeof(c[0])*c.size(), c.data());
	if(id_vbo_n==0)
		id_vbo_n = crearVBO(GL_ARRAY_BUFFER, sizeof(nv[0])*nv.size(), nv.data());

	// Habilitar tabla de vertices y de colores
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//Localizacion y formato de la tabla de vertice
	glBindBuffer(GL_ARRAY_BUFFER, id_vbo_v);	// Activa VBO vertices
	glVertexPointer(3, GL_FLOAT, 0, 0);			// Formato y offset (=0)
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Desactiva VBO vertices

	// Visualizar triangulos
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_vbo_f);	// Activa VBO triangulos
	dibujarElementosDif();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);			// Desactiva VBO triangulos

	// Especificar localización y formato de la tabla de colores
	glBindBuffer(GL_ARRAY_BUFFER,id_vbo_c); 	// Activar VBO de colores
	glColorPointer( 3,GL_FLOAT, 0, 0 ); 		// Formato y offset (=0)
	glBindBuffer(GL_ARRAY_BUFFER, 0 ); 			// Desactivar VBO de colores

	// Especificar localización y formato del array de normales
   	if(glIsEnabled(GL_LIGHTING)){
   		glBindBuffer(GL_ARRAY_BUFFER, id_vbo_n);
   		glNormalPointer(GL_FLOAT, 0, 0);
   		glBindBuffer(GL_ARRAY_BUFFER, 0);
   		m.aplicar();
   	}

	// Desactivar uso de array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// Función de visualización de la malla
void Malla3D::draw(int modo, bool ajedrez, bool textura)
{
	if(ajedrez){
		draw_modoAjedrez();
	}else{
		if (!ct.empty() && textura){
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
			t->activar();
		}
		switch(modo){
			case 1: draw_ModoInmediato();
			break;
			case 2: draw_ModoDiferido();
			break;
		}
		if(!ct.empty() && textura){
			glDisable(GL_TEXTURE_2D);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
	}
}

// Análoga a glDrawElements (Modo Inmediato)
void Malla3D::dibujarElementos(){
	glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, f.data());
}

// Análoga a glDrawElements (Modo Diferido)
void Malla3D::dibujarElementosDif(){
	glDrawElements(GL_TRIANGLES, f.size()*3, GL_UNSIGNED_INT, 0);
}

// Análoga a glDrawElements (Modo Ajedrez)
void Malla3D::dibujarElementosAjedrez(){
	// Dibujar caras pares
	glColorPointer( 3, GL_FLOAT, 0, cAjP.data());
   	glDrawElements(GL_TRIANGLES, f_par.size()*3, GL_UNSIGNED_INT, f_par.data());
	// Dibujar caras impares
   	glColorPointer( 3, GL_FLOAT, 0, cAjI.data());
   	glDrawElements(GL_TRIANGLES, f_imp.size()*3, GL_UNSIGNED_INT, f_imp.data());
}

void Malla3D::setColor(const Tupla3f& color){
	for(int i=0; i<v.size(); i++)
		c[i] = color;
}

void Malla3D::setMaterial(const Material& mat){
	m = Material(mat);
}

void Malla3D::calcular_normales(){
	Tupla3f a, b;		// Vectores auxiliares
	Tupla3f mc, nc; 	// Vector perpendicular y normal

	nf.resize(f.size());
	nv.resize(v.size());

	// Normales de las caras
	for(int i=0; i<f.size(); i++){
		a = v[f[i](1)] - v[f[i](0)];	// a = q-p
		b = v[f[i](2)] - v[f[i](0)];	// b = r-p
		mc = a.cross(b);				// Producto vectorial

		if(mc.lengthSq() != 0.0)		// Si el módulo no es 0,
			nc = mc.normalized();		// normalizar vector

		nf[i] = nc;
	}

	// Normales de los vértices
	for(int i=0; i<f.size(); i++){
		nv[f[i](0)] = nv[f[i](0)] + nf[i];
		nv[f[i](1)] = nv[f[i](1)] + nf[i];
		nv[f[i](2)] = nv[f[i](2)] + nf[i];
	}


	for(int i=0; i<nv.size(); i++)
		if(nv[i].lengthSq() != 0.0)
			nv[i] = nv[i].normalized();
}
