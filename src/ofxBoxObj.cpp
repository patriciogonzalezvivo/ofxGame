/*
 *  ofxBoxObj.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxBoxObj.h"

ofxBoxObj::ofxBoxObj(string _objectName){
	objectName = _objectName;//"box"; 
	loadXml();
	loadExtraXml();
}

ofxBoxObj & ofxBoxObj::init(int _x, int _y){
	box = new ofxBox();
	box->setPhysics(den, bou, fri);
	box->load(file).setScale(scale).linkToDebug(bDebug).loadToWorld(gameEng, ofPoint(_x,_y) );
	width = box->getWidth()*2;
	height = box->getHeight()*2;
	saveXml();
	return * this;
}

ofxBoxObj & ofxBoxObj::restart(){
	box->destroy();
	loadXml();
	init(x,y);
	return * this;
}


void ofxBoxObj::update(ofxParticleEmitter * _pEmit){
	x = box->getPosition().x;
	y = box->getPosition().y;
	
	if ((ofRandom(0, 50) < 2) ) 
		_pEmit->addParticle(ofPoint(x,y-getScaledHeight()*0.5));
};

void ofxBoxObj::draw(int _level){ 
	ofSetColor(255, 255);
	
	box->draw(_level);
	
	ofPushMatrix();
	ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxBoxObj::loadExtraXml(string filePath){
	ofxXmlSettings XML;
	//cout << "Reading " << objectName << " configuration file " << filePath;
	
	if (XML.loadFile(filePath)){
		//cout << " [ OK ]" << endl;
		
		den = XML.getValue(objectName+":density",0.5);
		bou = XML.getValue(objectName+":bounce",0.5);
		fri = XML.getValue(objectName+":friction",0.5);
		
	} else
		cout << " [ FAIL ]" << endl;
};
