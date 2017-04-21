/*
 * utils.c
 *
 *  Created on: Apr 12, 2017
 *      Author: paco
 */
#include "utils.h"

float vProjection(float value, float inputMin, float inputMax, float outputMin, float outputMax, bool clamp) {

	if (fabs(inputMin - inputMax) < FLT_EPSILON){
		return outputMin;
	} else {
		float outVal = ((value - inputMin) / (inputMax - inputMin) * (outputMax - outputMin) + outputMin);

		if( clamp ){
			if(outputMax < outputMin){
				if( outVal < outputMax )outVal = outputMax;
				else if( outVal > outputMin )outVal = outputMin;
			}else{
				if( outVal > outputMax )outVal = outputMax;
				else if( outVal < outputMin )outVal = outputMin;
			}
		}
		return outVal;
	}

}

double distance(Vector3d a, Vector3d b) {
	return sqrt((a.x()-b.x())*(a.x()-b.x()) + (a.y()-b.y())*(a.y()-b.y()));
}

int planSide(Vector3d testedPoint, Vector3d planeNormalA, Vector3d a){
	Vector3d AB = testedPoint - a;
	double dot = AB.dot(planeNormalA);
	return (dot > 0 ? 1 : -1);
}

Vector3d lineIntersectionPoint(Vector3d ps1, Vector3d pe1, Vector3d ps2, Vector3d pe2)
{
  // Get A,B,C of first line - points : ps1 to pe1
  double A1 = pe1.y()-ps1.y();
  double B1 = ps1.x()-pe1.x();
  double C1 = A1*ps1.x()+B1*ps1.y();

  // Get A,B,C of second line - points : ps2 to pe2
  double A2 = pe2.y()-ps2.y();
  double B2 = ps2.x()-pe2.x();
  double C2 = A2*ps2.x()+B2*ps2.y();

  // Get delta and check if the lines are parallel
  double delta = A1*B2 - A2*B1;
  if(delta == 0) return Vector3d(0,0); // TODO Fix incorrect result
//     throw new std::logic_error( "Lines are parallel");

  double a = (B2*C1 - B1*C2)/delta;
  double b = (A1*C2 - A2*C1)/delta;

  // return the Vector3d intersection point
  return Vector3d(a,b,0);
}

Vector3d* rayIntersectionPoint(Vector3d as, Vector3d ad, Vector3d bs, Vector3d bd)
{
// Return intersection point if ray intersect, return NULL otherwise
	// as : starting point, ad: direction vector
	double dx = bs.x() - as.x();
	double dy = bs.y() - as.y();
	double det = bd.x() * ad.y() - bd.y() * ad.x();

	if(det != 0){
		double u = (dy * bd.x() - dx * bd.y()) / det;
		double v = (dy * ad.x() - dx * ad.y()) / det;
		if(u > 0 && v > 0){
			// Rays intersect
			Vector3d * outV = new Vector3d(as.x() + u * ad.x(), as.y() + u * ad.y(), 0);
			return outV;
		}
	}
	// Rays are parallels or do not intersect
	return NULL;
}

double radToDeg(double rad) {
	return rad*180/M_PI;
}
