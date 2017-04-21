/*
 * World.h
 *
 *  Created on: Mar 29, 2017
 *      Author: paco
 */

#ifndef SRC_WORLD_H_
#define SRC_WORLD_H_

#include "../genericType/DrawnObject.h"

class World: public DrawnObject {
public:
	World(double w, double h, int wv, int hv, Vector3d position = Vector3d(), double theta = 0);
	virtual ~World();

	void draw(World* world);
	void draw();

	double width;
	double height;
	double widthView;
	double heightView;

};

#endif /* SRC_WORLD_H_ */
