/*
 *  ofxBoxProxy.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */
/*
#ifndef OFXBOXPROXY
#define OFXBOXPROXY

#include "ofxObject.h"
#include "ofxBox.h"

class ofxBoxProxy : public ofxGameObj {
public:
	ofxBoxProxy(string _objectName){
		objectName = _objectName;//"box"; 
		loadXml();
		loadExtraXml();
	}
	
	ofxBoxProxy & setWorld(b2World * _b2dworld, float _groundY){
		groundY = _groundY;
		
		box = new ofxBox();
		box->setPhysics(den, bou, fri);
		box->load(file).linkToDebug(bDebug).setScale(scale).loadToWorld(_b2dworld, ofPoint(x,y),groundY);
		return * this;
	}
	
	void clear(){
		box->destroy();
	}
	
	void draw(){ 
		ofSetColor(255, 255);
		
		box->draw();
		
		ofPushMatrix();
		ofTranslate(x-width*0.5,y-height*0.5);
		ofScale(scale, scale);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};
	
private:
	void loadExtraXml(string filePath = "config.xml" ){
		ofxXmlSettings XML;
		cout << "Reading " << objectName << " configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			
			den = XML.getValue(objectName+":density",0.5);
			bou = XML.getValue(objectName+":bounce",0.5);
			fri = XML.getValue(objectName+":friction",0.5);
			
		} else
			cout << " [ FAIL ]" << endl;
	};
	
	float				den, bou, fri;
	ofxBox*				box;
	float				groundY;
	
};
#endif*/
