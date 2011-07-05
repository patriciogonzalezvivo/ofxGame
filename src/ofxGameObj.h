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
	
	void	setDebug(bool * _bDebug){bDebug = _bDebug;};
	void	setPosition(int _x, int _y){x = _x; y = _y; saveXml();};
	void	setScale(float _scale){scale = _scale; saveXml(); };
	void	expand(float _scaleAmount){ scale += _scaleAmount; saveXml(); };
	void	contract(float _scaleAmount){ scale -= _scaleAmount; saveXml(); };
	
	float	getScaledWidth(){return width * scale;};
	float	getScaledHeight(){return height * scale;};
	ofPoint	getPosition(){ return ofPoint(x,y);};
	float	getScale(){return scale;};
	
	bool	isOver(ofPoint _loc){return isOver(_loc.x, _loc.y);};
	bool	isOver(float _x, float _y);
	
protected:	
	void	loadXml(string filePath = "config.xml");
	void	saveXml(string filePath = "config.xml");

	string	file, objectName;
	bool	* bDebug;
	int		x,y,width,height;
	float	scale;
	
};
#endif