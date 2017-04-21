/*
 * GridMap.h
 *
 *  Created on: Apr 6, 2017
 *      Author: paco
 */

#ifndef SRC_GRIDMAP_H_
#define SRC_GRIDMAP_H_

#include "GridCell.h"
#include "World.h"
#include "../agentManagement/Population.h"

class GridMap: public IdentifiedObject, public DrawnObject{
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	GridMap(World* world, Population* pop, double resolution = 0.1);
	virtual ~GridMap();

	// --- METHOD
	void draw(World* world);
	void compute();
	void normalize();
	void update();

	// --- Getter & Setter
	bool isGroupSpaceEnabled() const;
	void setGroupSpaceEnabled(bool groupSpaceEnabled = true);
	bool isPersonalSpaceEnabled() const;
	void setPersonalSpaceEnabled(bool personalSpaceEnabled = true);

protected:
	double width;
	double height;
	double resolution;
	Population* _population;
	bool personalSpaceEnabled = true;
	bool groupSpaceEnabled = true;

private:
	std::vector<std::vector<GridCell*>> _map;
};

#endif /* SRC_GRIDMAP_H_ */
