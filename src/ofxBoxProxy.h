/*
 *  ofxBoxProxy.h
 *
 *  Created by Patricio González Vivo on 02/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXBOXPROXY
#define OFXBOXPROXY

#include "ofxGameObj.h"
#include "ofxBox.h"
#include "ofxParticleEmitter.h"

class ofxBoxProxy : public ofxGameObj {
public:
	ofxBoxProxy(string _objectName){
		objectName = _objectName;//"box"; 
		loadXml();
		loadExtraXml();
	}
	~ofxBoxProxy(){
		clear();
	}
	
	ofxBoxProxy & setWorld(b2World * _b2dworld, float _groundY){
		groundY = _groundY;
		
		box = new ofxBox();
		box->setPhysics(den, bou, fri);
		box->load(file).setScale(scale).linkToDebug(bDebug).loadToWorld(_b2dworld, ofPoint(x,y),groundY);
		width = box->getWidth()*2;
		height = box->getHeight()*2;
		saveXml();
		return * this;
	}
	
	void update(ofxParticleEmitter * _pEmit){
		x = box->getPosition().x;
		y = box->getPosition().y;
		
		if ((ofRandom(0, 50) < 2) ) 
			_pEmit->addParticle(ofPoint(x,y-getScaledHeight()*0.5));
	};
	
	void clear(){
		box->destroy();
	}
	
	void draw(){ 
		ofSetColor(255, 255);
		
		box->draw();
		
		ofPushMatrix();
		ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
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
	
	ofxBox*				box;			
	float				den, bou, fri,groundY;				
};
#endif
