#include "sphere.h"

/*-<==>-----------------------------------------------------------------
/ Constructor
/----------------------------------------------------------------------*/
CSphere::CSphere(SCALAR a_radius) 
: radius( a_radius ) {
}

/*-<==>-----------------------------------------------------------------
/ 
/----------------------------------------------------------------------*/
bool CSphere::hits (const CLine &line, SCALAR &t_hit) {
  // Pendiente de implementar correctamente
	
	// REVISADA

	VECTOR aux = line.loc - loc;
	SCALAR b = aux.dot(line.dir);
	SCALAR c = aux.dot(aux) - radius*radius;
	SCALAR d = b*b - c;
	if (d<0)
			return false; // Noqueremos negativos pq no toca linea con esfera
	else{
		SCALAR tm = -b - sqrt(d); // -b - SQRT(b^2 -4ac)
		SCALAR tM = -b + sqrt(d);// -b + SQRT(b^2 -4ac)
		if(tm > 0)	{
			t_hit = tm;
			return true;
		}
		
		if(tM > 0){
			t_hit = tM;
			return true;
		}
	}
	  return false;
}

VECTOR CSphere::getNormal(const VECTOR &hit_loc) {
  // Pendiente de implementar correctamente
	VECTOR normal =  hit_loc - loc;
	normal = normal/radius;
	return normal;
	//return VECTOR(0,0,0);
}

