#ifndef INC_LINE_H_
#define INC_LINE_H_

#include "geometry.h"
class CRTObject;

/*-<==>-----------------------------------------------------------------
/ 
/----------------------------------------------------------------------*/
class CLine {
  int level;              // Recursion level of the line
public:
  VECTOR loc;
  VECTOR dir;
  COLOR  color;           // Color viewed from the line
  SCALAR t;               // Current t location
  CRTObject *obj;         // Current object the line lies on
 
  // Builds a default empty line
  CLine();
  // Builds a line with specific loc and direction
  CLine (const VECTOR &nloc, const VECTOR &ndir, int nlevel=0);

	// return vector position at current t
  VECTOR getIntersection() const;
	// return current recursion level 
  int 	 getLevel() const;
	// add a color amount to color of this line
  void   addColor(const VECTOR &amount);

  // Returns a new line when 'this' line is reflected in normal at point nloc
  CLine getReflected(const VECTOR &nloc, const VECTOR &normal);
};

#endif
