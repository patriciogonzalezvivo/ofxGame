/*
 *  ofxEmitter.h
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXEMITTER
#define OFXEMITTER

#include "ofxObject.h"
#include "ofxBox.h"

class ofxEmitter : public ofxGameObj {
public:
	ofxEmitter(string _objectName){
		objectName = _objectName;//"emitter"; 
		initForce.set(0,0);
		loadXml();
		loadExtraXml();
	}
	
	ofxEmitter & setWorld(b2World * _b2dworld, float _groundY){
		b2dworld = _b2dworld;
		groundY = _groundY;
		return * this;
	}
	
	void clear(){
		for(int i=0; i < boxes.size(); i++)
			boxes[i]->destroy();
		boxes.clear();
	}
	
	void draw(){ 
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
	};
	
	void addBox(){
		ofxBox * b = new ofxBox();
		b->setPhysics(den, bou, fri);
		b->load(file).setScale(scale).linkToDebug(bDebug).loadToWorld(b2dworld, ofPoint(x,y),groundY);
		b->addForce(initForce, forceScale);
		boxes.push_back(b);
	}
	
	
private:
	void loadExtraXml(string filePath = "config.xml" ){
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
	};
	
	float				den, bou, fri, forceScale;
	ofVec2f				initForce;
	vector<ofxBox*>		boxes;
	b2World *			b2dworld;
	float				groundY;
	
};
#endif