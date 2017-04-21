///*
// * PopulationFactory.h
// *
// *  Created on: Mar 28, 2017
// *      Author: paco
// */
//
//#ifndef SRC_POPULATIONMANAGER_H_
//#define SRC_POPULATIONMANAGER_H_
//
//#include "ofxJSON.h"
//
//#include "DrawnObject.h"
//#include "Population.h"
//#include "Agent.h"
//#include "Formation.h"
//#include "GaussianSpace.h"
//
//class PopulationManager: public DrawnObject {
//public:
//	// --- CONSTRUCTOR & DESTRUCTOR
//	PopulationManager(World* world);
//	PopulationManager(World* world, std::string feature_file, Point p = Point());
//	PopulationManager(World* world, std::string feature_file, std::string gt_file, Point p = Point());
//
//	~PopulationManager();
//
//	// --- METHOD
//	int loadFrame(unsigned int fIndex);
//	int loadJson();
//	int loadFeatureJson();
//	int loadGroundTruthJson();
//	void findDataBounds();
//
//	int nextFrame();
//	int previousFrame();
//
//	void draw(World* world);
//	void update(World* world);
//
//	// --- Getter & Setter
//	Population* getPopulation() const;
//	void setPopulation(Population* population);
//	const std::string& getFeatureFile() const;
//	void setFeatureFile(const std::string& featureFile);
//	const ofxJSONElement& getFeatures() const;
//	void setFeatures(const ofxJSONElement& features);
//	unsigned int getFrameIndex() const;
//	void setFrameIndex(unsigned int frameIndex);
//	const ofxJSONElement& getGroundTruth() const;
//	void setGroundTruth(const ofxJSONElement& groundTruth);
//	bool isGtEnabled() const;
//	void setGtEnabled(bool gtEnabled);
//	const std::string& getGtFile() const;
//	void setGtFile(const std::string& gtFile);
//	bool isLoaded() const;
//	void setLoaded(bool loaded);
//
//protected:
//	Population* _population;
//
//	ofxJSONElement features;
//	ofxJSONElement groundTruth;
//	std::string feature_file;
//	std::string gt_file;
//	World* world;
//
//	double min_x, min_y, max_x, max_y;
//
//	bool loaded = 0;
//	bool gt_enabled = 0;
//	unsigned int frameIndex = 0;
//};
//
//#endif /* SRC_POPULATIONMANAGER_H_ */
