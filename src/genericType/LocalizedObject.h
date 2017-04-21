/*
 * LocalizedObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_LOCALIZEDOBJECT_H_
#define SRC_LOCALIZEDOBJECT_H_

#include <Eigen/Dense>

using namespace Eigen;

class LocalizedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	LocalizedObject(Vector3d p = Vector3d(), double theta = 0);
	virtual ~LocalizedObject();

	// METHOD
	Vector3d getDirection();
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);

	// --- Getter & Setter
	Vector3d getPosition() const;
	void setPosition(Vector3d position);
	double getTheta() const;
	void setTheta(double theta);

protected:
	Vector3d position;
	double theta;
};

#endif /* SRC_LOCALIZEDOBJECT_H_ */
