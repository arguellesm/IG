#include "aux.h"
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
	// Guardar las caras en el vector correspondiente
	// distribuyeCaras();

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

	// Dibujar usando vértices indexados
   	dibujarElementos();
	// Deshabilitar array de vertices
	glDisableClientState(GL_VERTEX_ARRAY);
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

	// Desactivar uso de array de vértices
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

// Función de visualización de la malla
void Malla3D::draw(int modo, bool ajedrez)	
{
	if(ajedrez){
		draw_modoAjedrez();
	}else{
		if(modo==1)
			draw_ModoInmediato();
		if(modo==2)
			draw_ModoDiferido();
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



