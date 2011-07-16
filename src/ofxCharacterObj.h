/*
 *  ofxCharacterObj.h
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */
#ifndef OFXCHARPROXY
#define OFXCHARPROXY

#include "ofxGameObj.h"
#include "ofxCharacter.h"

class ofxCharacterObj : public ofxGameObj {
public:
	ofxCharacterObj(string _charName);
	
	void reset();

	void draw(){ 
		character.setScale(scale);
		character.setPosition(x, y);
		draw(x,y);
	};	
	
	void draw(int _x, int _y);
	
	ofxCharacter * getCharacter(){return & character;};
	
protected:
	void loadExtraXml(string filePath = "config.xml" );
	
	ofxCharacter	character;
	string			ori;
	float			den, bou, fri;
};
#endif