/*
 *  ofxGameObj.h
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXGAMEOBJ
#define OFXGAMEOBJ

#include "ofMain.h"
#include "ofxXmlSettings.h"

class ofxGameObj{
public:
	ofxGameObj();
	
	void drawBoundingBox();
	
	ofxGameObj&	setDebug(bool * _bDebug){bDebug = _bDebug;return * this;};
	ofxGameObj&	setPosition(int _x, int _y){x = _x; y = _y; saveXml();return * this;};
	ofxGameObj&	setScale(float _scale){scale = _scale; saveXml();return * this; };
	ofxGameObj&	expand(float _scaleAmount){ scale += _scaleAmount; saveXml();return * this; };
	ofxGameObj&	contract(float _scaleAmount){ scale -= _scaleAmount; saveXml();return * this; };
	
	float	getScaledWidth(){return width * scale;};
	float	getScaledHeight(){return height * scale;};
	ofPoint	getPosition(){ return ofPoint(x,y);};
	float	getScale(){return scale;};
	
	virtual void update(){};
	virtual void draw(){};
	
	bool	isOver(ofPoint _loc){return isOver(_loc.x, _loc.y);};
	bool	isOver(float _x, float _y);
	
protected:	
	void	loadXml(string filePath = "config.xml");
	void	saveXml(string filePath = "config.xml");
	
	ofColor	objColor;
	string	file, objectName;
	bool	* bDebug;
	int		x,y,width,height;
	float	scale;
	
};
#endif