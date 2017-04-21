///*
// * PopulationFactory.cpp
// *
// *  Created on: Mar 28, 2017
// *      Author: paco
// */
//
//#include "PopulationManager.h"
//
//// --- CONSTRUCTOR & DESTRUCTOR
//PopulationManager::PopulationManager(World* world): DrawnObject(), world(world) {
//	this->_population = new Population();
//}
//
//PopulationManager::PopulationManager(World* world, std::string feature_file, Point p):
//		DrawnObject(p), feature_file(feature_file), world(world) {
//	this->_population = new Population();
//	if(!this->loadFeatureJson()) this->loadFrame(frameIndex);
//
//	else throw std::string("Error while loading json file.");
//
//	this->findDataBounds();
//}
//
//PopulationManager::PopulationManager(World* world, std::string feature_file,
//		std::string gt_file, Point p): DrawnObject(p), feature_file(feature_file), gt_file(gt_file), world(world) {
//
//	this->_population = new Population();
//	this->setGtEnabled(1);
//
//	int err = this->loadJson();
//	if(!err) this->loadFrame(frameIndex);
//	else ofLogError("PopulationManager::PopulationManager") << "Failed to load json";
//
//	this->findDataBounds();
//
//}
//
//PopulationManager::~PopulationManager() {
//	this->_population->clear();
//	delete this->_population;
//}
//
//
//// --- METHOD
//int PopulationManager::loadFrame(unsigned int fIndex) {
//	int err;
//	if(!this->loaded) err = loadJson();
//	if(err) return err;
//
//	this->_population->clear();
//
//	ofLogNotice("PopulationManager::loadFrame") << "Parsing features for frame #" << frameIndex;
//
//	for (Json::ArrayIndex i = 0; i < features["features"][frameIndex].size(); ++i)
//	{
////		Point pos;
////		if(min < 0){
////			pos.x = features["features"][frameIndex][i][1].asDouble() - min,
////
////		}
//		Agent* a = new Agent(
//						this->world,
//						Point(
//								features["features"][frameIndex][i][1].asDouble()/100,
//								features["features"][frameIndex][i][2].asDouble()/100
//							),
//						features["features"][frameIndex][i][3].asDouble(),
//						features["features"][frameIndex][i][0].asInt()
//						);
////		GaussianSpace * g = new GaussianSpace(a);
//		this->_population->pushAgent(a);
//	}
//
//	if(this->isGtEnabled()){
//		ofLogNotice("PopulationManager::loadFrame") << "Parsing ground truth for frame #" << frameIndex;
//		ofLogNotice("PopulationManager::loadFrame") << "GT size " << groundTruth["GTgroups"][frameIndex].size();
//		for (Json::ArrayIndex i = 0; i < groundTruth["GTgroups"][frameIndex].size(); ++i)
//		{
//			ofLogNotice("PopulationManager::loadFrame") << "Computing formation #" << i;
//			std::vector<Agent*> group;
//			for(Json::ArrayIndex j = 0; j < groundTruth["GTgroups"][frameIndex][i].size(); j++){
//				group.push_back(this->_population->getAgent(groundTruth["GTgroups"][frameIndex][i][j].asInt()));
//			}
//
//			// TODO
//			Formation* fformation = new Formation(group);
//			fformation->computeSocialSpace(world);
////
//			this->_population->pushFormation(fformation);
//		}
//	}
//
//	return 0;
//}
//
//void PopulationManager::update(World * world){
//	this->_population->update(world);
//}
//
//int PopulationManager::loadJson() {
//	int err = loadFeatureJson();
//	if(!err && this->isGtEnabled()) err = loadGroundTruthJson();
//	if(!err) this->loaded = 1;
//	return err;
//}
//
//int PopulationManager::loadFeatureJson() {
//	if(feature_file.length() > 0){
//		bool parsingSuccessful = this->features.open(this->feature_file);
//		if (parsingSuccessful) return 0;
//		else{
//			ofLogError("PopulationManager::loadFeatureJson")  << "Failed to parse features JSON" << std::endl;
//		}
//	}
//
//	return -1;
//}
//
//int PopulationManager::loadGroundTruthJson() {
//	if(gt_file.length() > 0){
//		bool parsingSuccessful = this->groundTruth.open(this->gt_file);
//		if (parsingSuccessful) return 0;
//		else{
//			ofLogError("PopulationManager::loadFeatureJson")  << "Failed to parse ground truth JSON" << std::endl;
//		}
//	}
//
//	return -1;
//}
//
//
//void PopulationManager::findDataBounds() {
//	min_x = INFINITY;
//	max_x = -INFINITY;
//
//	for (Json::ArrayIndex i = 0; i < features["features"].size(); ++i){
//		for (Json::ArrayIndex j = 0; j < features["features"][i].size(); ++j){
////			for (Json::ArrayIndex k = 0; k < features["features"][i][j].size(); ++k){
//				if(features["features"][i][j][1].asDouble() > max_x) max_x = features["features"][i][j][1].asDouble();
//				if(features["features"][i][j][1].asDouble() < min_x) min_x = features["features"][i][j][1].asDouble();
////			}
//		}
//	}
//}
//
//
//int PopulationManager::nextFrame() {
//	if(frameIndex < features["features"].size()) frameIndex++;
//	return this->loadFrame(frameIndex);
//}
//
//int PopulationManager::previousFrame() {
//	if(frameIndex > 0) frameIndex--;
//	return this->loadFrame(frameIndex);
//}
//
//void PopulationManager::draw(World* world) {
//	this->_population->draw(world);
//}
//
//// --- Getter & Setter
//Population* PopulationManager::getPopulation() const {
//	return _population;
//}
//
//void PopulationManager::setPopulation(Population* population) {
//	_population = population;
//}
//
//const std::string& PopulationManager::getFeatureFile() const {
//	return feature_file;
//}
//
//void PopulationManager::setFeatureFile(const std::string& featureFile) {
//	feature_file = featureFile;
//}
//
//const ofxJSONElement& PopulationManager::getFeatures() const {
//	return features;
//}
//
//void PopulationManager::setFeatures(const ofxJSONElement& features) {
//	this->features = features;
//}
//
//unsigned int PopulationManager::getFrameIndex() const {
//	return frameIndex;
//}
//
//void PopulationManager::setFrameIndex(unsigned int frameIndex) {
//	this->frameIndex = frameIndex;
//}
//
//const ofxJSONElement& PopulationManager::getGroundTruth() const {
//	return groundTruth;
//}
//
//void PopulationManager::setGroundTruth(const ofxJSONElement& groundTruth) {
//	this->groundTruth = groundTruth;
//}
//
//bool PopulationManager::isGtEnabled() const {
//	return gt_enabled;
//}
//
//void PopulationManager::setGtEnabled(bool gtEnabled) {
//	gt_enabled = gtEnabled;
//}
//
//const std::string& PopulationManager::getGtFile() const {
//	return gt_file;
//}
//
//void PopulationManager::setGtFile(const std::string& gtFile) {
//	gt_file = gtFile;
//}
//
//bool PopulationManager::isLoaded() const {
//	return loaded;
//}
//
//void PopulationManager::setLoaded(bool loaded) {
//	this->loaded = loaded;
//}
