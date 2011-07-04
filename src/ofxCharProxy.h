/*
 *  ofxCharProxy.h
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXCHARPROXY
#define OFXCHARPROXY

#include "ofxGameObj.h"
#include "ofxCharacter.h"

class ofxCharProxy : public ofxGameObj {
public:
	ofxCharProxy(){
	}
	
	ofxCharProxy(string _charName){
		objectName = _charName;//"character"; 
		loadXml();
		loadExtraXml();
		character.load(file);
		reset();
		saveXml();
	};
	
	void reset(){
		character.setOrientation(ori);
		character.setPhysics(den, bou, fri);
		width = character.getWidth()*2;
		height = character.getHeight()*2;
		character.setScale(scale);
		character.pos.set(x, y);
	};
	
	void update(ofxParticleEmitter * _pEmit){
		character.update(_pEmit);
	};

	void draw(){ 
		character.setScale(scale);
		character.pos.set(x, y);
		draw(x,y);
	};	
	
	void draw(int _x, int _y){
		ofSetColor(255, 255);
		character.draw(*bDebug);
		
		ofPushMatrix();
		ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
		ofScale(scale, scale);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};
	
	ofxCharacter * getCharacter(){return & character;};
	
private:
	void loadExtraXml(string filePath = "config.xml" ){
		ofxXmlSettings XML;
		cout << "Reading " << objectName << " configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			
			ori = XML.getValue(objectName+":orientation","LEFT");
			den = XML.getValue(objectName+":density",0.5);
			bou = XML.getValue(objectName+":bounce",0.5);
			fri = XML.getValue(objectName+":friction",0.5);
			
		} else
			cout << " [ FAIL ]" << endl;
	};
	
	ofxCharacter	character;
	string			ori;
	float			den, bou, fri;
};
#endif