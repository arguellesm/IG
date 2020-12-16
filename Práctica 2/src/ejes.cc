#include "aux.h"
#include "ejes.h"

// -----------------------------------------------------------------------------

Ejes::Ejes()
{
    axisSize = 1000;
    createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::changeAxisSize( float newSize )
{
	axisSize = newSize;
	createArrayData();
}
// -----------------------------------------------------------------------------

void Ejes::createArrayData()
{

	colorArray[0]  = 255/255.0; colorArray[1]  = 175/255.0; colorArray[2]  = 135/255.0;	// Clarito	[X]
	colorArray[3]  = 255/255.0; colorArray[4]  = 175/255.0; colorArray[5]  = 135/255.0;	
	colorArray[6]  = 255/255.0; colorArray[7]  = 142/255.0; colorArray[8]  = 114/255.0;	// Medio	[Y]
	colorArray[9]  = 255/255.0; colorArray[10] = 142/255.0; colorArray[11] =  94/255.0;	
	colorArray[12] = 237/255.0; colorArray[13] = 106/255.0; colorArray[14] = 114/255.0; // Oscuro	[Z]	
	colorArray[15] = 237/255.0; colorArray[16] = 106/255.0; colorArray[17] = 114/255.0;	

	vertexArray[0]  = -axisSize; vertexArray[1]  = 0;		 vertexArray[2]  = 0;			// -1000,0,0   (EJE X)
	vertexArray[3]  = axisSize;  vertexArray[4]  = 0;		 vertexArray[5]  = 0;			//  1000,0,0
	vertexArray[6]  = 0; 		 vertexArray[7]  = -axisSize; vertexArray[8] = 0;			//  0,-1000,0  (EJE Y)
	vertexArray[9]  = 0; 		 vertexArray[10] = axisSize; vertexArray[11] = 0;			//  0, 1000,0
	vertexArray[12] = 0; 		 vertexArray[13] = 0;		 vertexArray[14] = -axisSize;	//  0,0,-1000  (EJE Z)
	vertexArray[15] = 0; 		 vertexArray[16] = 0;		 vertexArray[17] = axisSize;	//  0,0, 1000
}
 

void Ejes::draw()
{
	// Habilita el array de vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	// Indicar que está en vertexArray
	glVertexPointer(3, GL_FLOAT, 0, vertexArray );
	// Habilitar el color
	glEnableClientState(GL_COLOR_ARRAY);
	// Indicar que está en colorArray
	glColorPointer(3, GL_FLOAT, 0, colorArray );
	// Interpretar los ejes como líneas uniendo 0-1 2-3 4-5
	glDrawArrays( GL_LINES, 0, 6 ) ; // param1 indica a partir de qué vertice y param2 cuántos vértices
}
