/*
 * IdentifiedObject.h
 *
 *  Created on: Mar 27, 2017
 *      Author: paco
 */

#ifndef SRC_IDENTIFIEDOBJECT_H_
#define SRC_IDENTIFIEDOBJECT_H_

class IdentifiedObject {
public:
	// --- CONSTRUCTOR & DESTRUCTOR
	IdentifiedObject(unsigned int id=0);
	virtual ~IdentifiedObject();

	// --- Getter & Setter
	unsigned int getId() const;
	void setId(unsigned int id);

protected:
	unsigned int id;
};

#endif /* SRC_IDENTIFIEDOBJECT_H_ */
