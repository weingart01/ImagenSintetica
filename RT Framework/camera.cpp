#include "raytracer.h"
#include <math.h>

/*-<==>-----------------------------------------------------------------
/ 
/---------------------------------------------------------------------*/
CCamera::CCamera() {
  // Initialize with some default parameters
  setRenderParameters(320, 240, 60.0f);
  lookAt(VECTOR(0,0,0), VECTOR(0,0,1));
}

CCamera::~CCamera() {
}

/*-<==>-----------------------------------------------------------------
/ Save render parameters for later use
/ fov is in degrees
/---------------------------------------------------------------------*/
void CCamera::setRenderParameters (int axres, int ayres, SCALAR afov_in_deg) {
  // Pendiente de implementar correctamente
  // ...
	xres = axres;
	yres = ayres;
	fov=afov_in_deg;
  // Compute view_d from afov_in_deg
  // ...
	SCALAR tan_formula = tan((afov_in_deg*M_PI/180)/2);
	viewd = (ayres/2)/tan_formula;
	//REVISADO OK
}

/*-<==>-----------------------------------------------------------------
/ Save the new camera position and target point. 
/ Define the axis of the camera (front, up, left) in world coordinates 
/ based on the current values of the vectors target & loc 
/---------------------------------------------------------------------*/
void CCamera::lookAt(const VECTOR &src_point, const VECTOR &dst_point) {
  loc = src_point;//position
  target = dst_point;//target
  // Pendiente de implementar correctamente
  // ...
	front = target-loc;
	  front.normalize();
	  VECTOR aux_up = VECTOR(0,1,0);
	  left=aux_up.cross(front);
	  left.normalize();
	  aux_up.normalize();
	  up = front.cross(left);
	  up.normalize();
 
  // REVISADA
}

/*-<==>-----------------------------------------------------------------
/ return a line which starts on camera position and goes through the pixel
/ (x,y) from the screen
/---------------------------------------------------------------------*/
CLine CCamera::getLineAt (SCALAR x, SCALAR y) const {
  // Pendiente de implementar correctamente
  // ...

  VECTOR po = loc;
  SCALAR tmp_xres = xres / 2 - x - 0.5;
  SCALAR tmp_yres = yres / 2 - y - 0.5;
  VECTOR temp_xy = viewd*front + up * tmp_yres + left * tmp_xres ;
  return CLine(loc, temp_xy, 5);
}

