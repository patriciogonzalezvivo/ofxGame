/*
 *  ofxBoxEmitter.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxBoxEmitter.h"

ofxBoxEmitter::ofxBoxEmitter(string _objectName){
	objectName = _objectName;//"emitter"; 
	initForce.set(0,0);
	loadXml();
	loadExtraXml();
}

ofxBoxEmitter & ofxBoxEmitter::setWorld(b2World * _b2dworld, float _groundY){
	b2dworld = _b2dworld;
	groundY = _groundY;
	return * this;
}

void ofxBoxEmitter::clear(){
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->destroy();
	boxes.clear();
}

void ofxBoxEmitter::draw(){ 
	ofSetColor(255, 255);
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw();
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(4);
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(3);
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(5);
	
	ofPushMatrix();
	ofTranslate(x-width*0.5,y-height*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxBoxEmitter::addBox(){
	ofxBox * b = new ofxBox();
	b->setPhysics(den, bou, fri);
	b->load(file).setScale(scale).linkToDebug(bDebug).loadToWorld(b2dworld, ofPoint(x,y),groundY);
	b->addForce(initForce, forceScale);
	boxes.push_back(b);
}

void ofxBoxEmitter::loadExtraXml(string filePath){
	ofxXmlSettings XML;
	cout << "Reading " << objectName << " configuration file looking for extra parametters " << filePath;
	
	if (XML.loadFile(filePath)){
		cout << " [ OK ]" << endl;
		
		initForce.x = XML.getValue(objectName+":xForce",0);
		initForce.y = XML.getValue(objectName+":yForce",0);
		forceScale = XML.getValue(objectName+":scaleForce",10);
		den = XML.getValue(objectName+":density",0.5);
		bou = XML.getValue(objectName+":bounce",0.5);
		fri = XML.getValue(objectName+":friction",0.5);
		
	} else
		cout << " [ FAIL ]" << endl;
}

void ofxBoxEmitter::loadGroup(const string& path, ofPoint _loc){
	ifstream	fs( ofToDataPath(path+".boxes").c_str());
	
	string line;
	int lineCounter = 0;
	
	cout << "- Loading box: " << path << endl;
	
	while(!(fs >> line).fail()){
		vector <string> values = ofSplitString(line, ",");
		
		string _box	 = values[0];
		float _radio = ofToFloat(values[1].c_str());
		float _angle = ofToFloat(values[2].c_str());
		
		float propRadio = _radio * scale;
		
		ofPoint _pos;
		_pos.x = propRadio * cos(_angle) + _loc.x;
		_pos.y = propRadio * sin(_angle) + _loc.y;
		
		ofxBox * b = new ofxBox();
		b->setPhysics(den, bou, fri);
		b->load(_box).setScale(scale).linkToDebug(bDebug).loadToWorld(b2dworld, _pos,groundY);
		boxes.push_back(b);
	}
	
	fs.seekg(0,ios::beg);
	fs.clear();
	fs.close();
}
