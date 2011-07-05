/*
 *  ofxBoxProxy.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxBoxProxy.h"

ofxBoxProxy::ofxBoxProxy(string _objectName){
	objectName = _objectName;//"box"; 
	loadXml();
	loadExtraXml();
}

ofxBoxProxy & ofxBoxProxy::setWorld(b2World * _b2dworld, float _groundY, int _x, int _y){
	groundY = _groundY;
	b2dworld = _b2dworld;
	init(_x,_y);
	width = box->getWidth()*2;
	height = box->getHeight()*2;
	saveXml();
	return * this;
}

ofxBoxProxy & ofxBoxProxy::init(int _x, int _y){
	box = new ofxBox();
	box->setPhysics(den, bou, fri);
	box->load(file).setScale(scale).linkToDebug(bDebug).loadToWorld(b2dworld, ofPoint(_x,_y),groundY);
	return * this;
}

ofxBoxProxy & ofxBoxProxy::restart(){
	box->destroy();
	loadXml();
	init(x,y);
	return * this;
}


void ofxBoxProxy::update(ofxParticleEmitter * _pEmit){
	x = box->getPosition().x;
	y = box->getPosition().y;
	
	if ((ofRandom(0, 50) < 2) ) 
		_pEmit->addParticle(ofPoint(x,y-getScaledHeight()*0.5));
};

void ofxBoxProxy::draw(int _level){ 
	ofSetColor(255, 255);
	
	box->draw(_level);
	
	ofPushMatrix();
	ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxBoxProxy::loadExtraXml(string filePath){
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
