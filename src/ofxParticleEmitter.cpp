/*
 *  ofxParticleEmitter.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxParticleEmitter.h"

ofxParticleEmitter::ofxParticleEmitter(string _objectName){
	objectName = _objectName;
	fade = -1;
	melt = -1;
	objColor.setHex(0xffcc33);
	loadXml();
	loadExtraXml();
	if (file != "none")
		pImage.loadImage(file);
}

void ofxParticleEmitter::update(){
	for(int i = 0; i < particles.size(); i++){
		if (noise)
			particles[i].applyNoiseForce(noiseAngle,noiseTurbulence);
		
		if (den != 0)
			particles[i].applyViscosityForce(den);
		
		if (spe != 0)
			particles[i].update(spe);
		else
			particles[i].update();
		
		if (fade != -1)
			particles[i].applyAlphaFade((fade==0)?false:true);
		
		if (melt != -1)
			particles[i].applySizeFade((melt==0)?false:true);
		
		particles[i].life--;
	}
	
	for(int i = 0; i < particles.size(); i++)
		if ( particles[i].life <= 0 )
			particles.erase(particles.begin()+i);
}

void ofxParticleEmitter::draw(){ 
	ofSetColor(255, 255);
	for(int i=0; i < particles.size(); i++)
		particles[i].draw();
	
	ofPushMatrix();
	ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxParticleEmitter::addParticle(ofPoint _loc){
	if ((randomMax != 1) || (randomMin != 1)){
		addParticle(ofVec2f(ofRandom(_loc.x-getScaledWidth()*0.5 ,_loc.x+getScaledWidth()*0.5),
							ofRandom(_loc.y-getScaledHeight()*0.5,_loc.y+getScaledHeight()*0.5)),
					ofVec2f(initForce.x*ofNoise(ofGetFrameNum()/25)*ofRandom(randomMin,randomMax),
							initForce.y*ofNoise(ofGetFrameNum()/25)*ofRandom(randomMin,randomMax)));
	} else {
		addParticle(ofVec2f(ofRandom(_loc.x-getScaledWidth()*0.5 ,_loc.x+getScaledWidth()*0.5),
							ofRandom(_loc.y-getScaledHeight()*0.5 ,_loc.y+getScaledHeight()*0.5)),
					ofVec2f(initForce.x,initForce.y));
	}
}

void ofxParticleEmitter::addParticle(ofVec2f _loc, ofVec2f _vel, int _life, float _scale){
	ofxParticle p;
	
	p.setPosition(_loc).setVelocity(_vel).setScale(_scale).setLife(_life).setImage(&pImage);
	
	particles.push_back(p);
}

void ofxParticleEmitter::loadExtraXml(string filePath){
	ofxXmlSettings XML;
	//cout << "Reading " << objectName << " configuration file looking for extra parametters " << filePath;
	
	if (XML.loadFile(filePath)){
		//cout << " [ OK ]" << endl;
		initForce.x = XML.getValue(objectName+":xForce",0);
		initForce.y = XML.getValue(objectName+":yForce",0);
		randomMax	= XML.getValue(objectName+":randomMax",1);
		randomMin	= XML.getValue(objectName+":randomMin",1);
		life		= XML.getValue(objectName+":life",ofGetFrameRate()); 
		den			= XML.getValue(objectName+":density",0);
		spe			= XML.getValue(objectName+":speedLimit",0);
		
		noise	= XML.tagExists(objectName+":noise");
		fade	= XML.getValue(objectName+":alfafade",-1);
		melt	= XML.getValue(objectName+":sizefade",-1);
		
		if (noise){
			noiseAngle= XML.getValue(objectName+":noise:angle",12);
			noiseTurbulence = XML.getValue(objectName+":noise:turbulence",0.01);
		}
	} else
		cout << " [ FAIL ]" << endl;
}