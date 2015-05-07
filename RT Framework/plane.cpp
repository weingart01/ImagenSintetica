#include "plane.h"

/*-<==>-----------------------------------------------------------------
/ n.x * x + n.y * y + n.z * z = d
/----------------------------------------------------------------------*/
CPlane::CPlane (const VECTOR &normal, SCALAR distance) : norm(normal), dist(distance) {
  // ..

}

bool CPlane::hits (const CLine &line, SCALAR &t_hit) {
	SCALAR t = -(-dist + norm.dot(line.loc))/(line.dir.dot(norm));
    if(t > SMALL_AMOUNT)
    {
        t_hit = t;
        return true;
    }
    return false;
}

VECTOR CPlane::getNormal (const VECTOR &loc) {
  // Pendiente de implementar correctamente
	return norm.normalize();
}

