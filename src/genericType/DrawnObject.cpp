/*
 * DrawnObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "DrawnObject.h"
#include "../worldRepresentation/World.h"
#include "../utils.h"

// --- CONSTRUCTOR & DESTRUCTOR
DrawnObject::DrawnObject(Vector3d p, double theta):
		LocalizedObject(p,theta) {
}

DrawnObject::~DrawnObject() {
}

// --- METHOD
Vector3d DrawnObject::real_to_pixel(World* world, Vector3d p) {
	Vector3d p_pixel;
	p_pixel.x() = vProjection(p.x(), 0, world->width, 0, world->widthView) + world->getX();
	p_pixel.y() = vProjection(p.y(), 0, world->height, 0, world->heightView) + world->getY();

	return p_pixel;
}

Vector3d DrawnObject::pixel_to_real(World* world, Vector3d p) {
	Vector3d p_real;
	p_real.x() = vProjection(p.x() - world->getX(), 0, world->widthView, 0, world->width);
	p_real.y() = vProjection(p.y() - world->getY(), 0, world->heightView, 0, world->height);

	return p_real;
}
