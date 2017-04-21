/*
 * DrawnObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_DRAWNOBJECT_H_
#define SRC_DRAWNOBJECT_H_

#include "LocalizedObject.h"

class World;

class DrawnObject: public LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	DrawnObject(Vector3d p = Vector3d(), double theta = 0);
	virtual ~DrawnObject();

	// --- METHOD
	Vector3d real_to_pixel(World* world, Vector3d p);
	Vector3d pixel_to_real(World* world, Vector3d p);

	// virtual void draw(World* world) = 0;

};

#endif /* SRC_DRAWNOBJECT_H_ */
