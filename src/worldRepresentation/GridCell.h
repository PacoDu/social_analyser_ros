/*
 * GridCell.h
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#ifndef SRC_GRIDCELL_H_
#define SRC_GRIDCELL_H_

#include "World.h"
#include "../genericType/IdentifiedObject.h"
#include "../genericType/DrawnObject.h"

class GridCell: public IdentifiedObject, public DrawnObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GridCell(double size, double value = 0, Vector3d p = Vector3d(), int id = 0);
	virtual ~GridCell();

	// --- METHOD
	void draw(World* world);

	// --- Getter & Setter
	double getValue() const;
	void setValue(double value);
	double getSize() const;
	void setSize(double size);

protected:
	double _value;
	double _size;
};

#endif /* SRC_GRIDCELL_H_ */
