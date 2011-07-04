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
	
	ofxCharProxy(string _charName);
	
	void reset();
	
	void update(ofxParticleEmitter * _pEmit){character.update(_pEmit);};

	void draw(){ 
		character.setScale(scale);
		character.pos.set(x, y);
		draw(x,y);
	};	
	
	void draw(int _x, int _y);
	
	ofxCharacter * getCharacter(){return & character;};
	
private:
	void loadExtraXml(string filePath = "config.xml" );
	
	ofxCharacter	character;
	string			ori;
	float			den, bou, fri;
};
#endif