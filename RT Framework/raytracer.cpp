#include <assert.h>
#include "raytracer.h"
#include "image.h"

/*-<==>-----------------------------------------------------------------
/ 
/----------------------------------------------------------------------*/
CRayTracer::CRayTracer() 
: max_recursion_level( 10 )
, background_color( COLOR(0.5,0.5,0.5) )
{ }

/*-<==>-----------------------------------------------------------------
/ Create an image, and for each pixel in the screen create a line
/ and retrieve which color is seen through this line
/ Save the image to a file
/----------------------------------------------------------------------*/
void CRayTracer::render() {
  // Pendiente de implementar correctamente

	//for each pixel
	// Cline = camera.getlin
	//
	CBitmap img( camera.getXRes(),  camera.getYRes(), 24 );

	for(int i=0; i < img.getXRes(); i++){
		for(int j=0; j < img.getYRes(); j++){
			CLine line = camera.getLineAt(i, j);
			trace(line);
			img.setPixel(i, j, line.color);
		}
	}
	img.saveTGA("prueba.tga");
}

/*-<==>-----------------------------------------------------------------
/ Find which object and at which 't' the line hits and object
/ from the scene.
/ Returns true if the object hits some object
/----------------------------------------------------------------------*/
bool CRayTracer::intersects(CLine &line) {
	// Example of traversing all the objects registered in the scene
	// Same thing for lights
	SCALAR min_t_hit = std::numeric_limits<SCALAR>::max();
	bool objectHit = false;
	LRTObjects::iterator i = objects.begin();
	while( i != objects.end() ) {
		CRTObject *obj = *i++;
		SCALAR t_hit;
		bool hits = obj->hits(line, t_hit);
		if(hits)
		{
			objectHit = true;
			if( min_t_hit > t_hit && t_hit > 0)
			{
				 min_t_hit = t_hit;
				 line.obj = obj;
			}
		}
	}

	line.t = min_t_hit;
	return objectHit;
}
/*-<==>-----------------------------------------------------------------
/ Returns in line.color the color captured by the line.
/----------------------------------------------------------------------*/
void CRayTracer::trace(CLine &line) {
	// Pendiente de implementar correctamente
	if( intersects( line ) )
	{
		VECTOR hitpos = line.getIntersection(); // punto de intererseccion
		VECTOR Normal = line.obj->getNormal(hitpos);
		int n = lights.size();
		for( LLights::const_iterator it = lights.begin(); it != lights.end(); ++it ) {
			CLight *light = *it;
			VECTOR L = light->getLocation()-hitpos;
			L.normalize();
			SCALAR diffuse_amount = Normal.dot( L );
			if (diffuse_amount < 0) diffuse_amount = 0;
			
			// difusa
			VECTOR color = line.obj->getMaterial()->getDiffuseColor(hitpos); 
			color = color.filter(L);
			line.addColor(color * diffuse_amount);
			
			// luz especular
			VECTOR R = 2 *Normal*(Normal.dot(L))-L;

			SCALAR RE=R.dot(-line.dir); // se corressponde al alfa
			// Si se da el caso en que es negativo, no tiene especular
			if(RE>=0){
				VECTOR especular = VECTOR(0.5,0.5,0.5)
				  *pow(RE,lights.size())/**0.8f*/;

				especular*=(1-line.obj->getMaterial()->getReflectance(hitpos));	
				especular = especular.filter(light->getColor());
				line.addColor(especular);
			}
		}
	}
	else
	{
		line.addColor(background_color);
	}
}

/*-<==>-----------------------------------------------------------------
/ Default background 
/----------------------------------------------------------------------*/
void CRayTracer::background(CLine &line) {
  line.color = background_color;
}

