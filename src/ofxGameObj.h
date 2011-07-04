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
	ofxGameObj(){ 
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		scale = 1;
		file = "none";
	};
	
	void drawBoundingBox(){
		glLineWidth(0);
		ofSetColor(255, 255);
		ofLine(0,0, 0, height);
		ofLine(0,0, width, 0);
		ofLine(width,0, 0, 0);
		ofLine(0,height, 0, 0);
		ofLine(0,height,width,height);
		ofLine(0, 0, width, height);
		ofLine(width,0,0,height);
		ofLine(width,0,width,height);
		ofSetColor(255, 255);
	}
	
	float	getScaledWidth(){return width * scale;};
	float	getScaledHeight(){return height * scale;};
	ofPoint	getPosition(){ return ofPoint(x,y);};
	float	getScale(){return scale;};
	
	void	setDebug(bool * _bDebug){bDebug = _bDebug;};
	void	setPosition(int _x, int _y){x = _x; y = _y; saveXml();};
	void	setScale(float _scale){scale = _scale; saveXml(); };
	void	expand(float _scaleAmount){ scale += _scaleAmount; saveXml(); };
	void	contract(float _scaleAmount){ scale -= _scaleAmount; saveXml(); };
	
	bool	isOver(float _x, float _y){
		bool result = false;
		if ((_x > x - width*0.5) &&
			(_x < x + width*0.5) &&
			(_y > y - height*0.5) &&
			(_y < y + height*0.5))
			result = true;
		return result;
	};
	
protected:	
	void	loadXml(string filePath = "config.xml" ){
		ofxXmlSettings XML;
		cout << "Reading " << objectName << " configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			
			x = XML.getValue(objectName+":x",0);
			y = XML.getValue(objectName+":y",0);
			scale = XML.getValue(objectName+":scale",1.0f);
			width = XML.getValue(objectName+":width",0);
			height = XML.getValue(objectName+":height",0);
			file = XML.getValue(objectName+":file","none");
			
		} else
			cout << " [ FAIL ]" << endl;
	};
	
	void	saveXml(string filePath = "config.xml"){
		ofxXmlSettings XML;
		cout << "Saving " << objectName << " configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			XML.setValue(objectName+":x",x);
			XML.setValue(objectName+":y",y);
			XML.setValue(objectName+":scale",scale);
			XML.setValue(objectName+":width",width);
			XML.setValue(objectName+":height",height);
		} else
			cout << " [ FAIL ]" << endl;
		XML.saveFile();
	};

	string	file, objectName;
	bool	* bDebug;
	int		x,y,width,height;
	float	scale;
	
};
#endif