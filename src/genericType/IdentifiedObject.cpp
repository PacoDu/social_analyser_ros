/*
 * IdentifiedObject.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#include "IdentifiedObject.h"

// --- CONSTRUCTOR & DESTRUCTOR
IdentifiedObject::IdentifiedObject(unsigned int id): id(id) {
}

IdentifiedObject::~IdentifiedObject() {
}

// --- Getter & Setter
unsigned int IdentifiedObject::getId() const {
	return this->id;
}

void IdentifiedObject::setId(unsigned int id) {
	this->id = id;
}
