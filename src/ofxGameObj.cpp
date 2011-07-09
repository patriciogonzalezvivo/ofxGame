/*
 *  ofxGameObj.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

#include "ofxGameObj.h"

ofxGameObj::ofxGameObj(){ 
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	scale = 1;
	file = "none";
	objColor.setHex(0xeeeeee);
}

void ofxGameObj::drawBoundingBox(){
	glLineWidth(0);
	ofSetColor(objColor);
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

bool ofxGameObj::isOver(float _x, float _y){
	bool result = false;
	if ((_x > x - getScaledWidth()*0.5) &&
		(_x < x + getScaledWidth()*0.5) &&
		(_y > y - getScaledHeight()*0.5) &&
		(_y < y + getScaledHeight()*0.5))
		result = true;
	return result;
}
	
void ofxGameObj::loadXml(string filePath){
	ofxXmlSettings XML;
	//cout << "Reading " << objectName << " configuration file " << filePath;
	
	if (XML.loadFile(filePath)){
		//cout << " [ OK ]" << endl;
		
		x = XML.getValue(objectName+":x",0);
		y = XML.getValue(objectName+":y",0);
		scale = XML.getValue(objectName+":scale",1.0f);
		width = XML.getValue(objectName+":width",0);
		height = XML.getValue(objectName+":height",0);
		file = XML.getValue(objectName+":file","none");
		
	} else
		cout << " [ FAIL ]" << endl;
}

void ofxGameObj::saveXml(string filePath){
	ofxXmlSettings XML;
	//cout << "Saving " << objectName << " configuration file " << filePath;
	
	if (XML.loadFile(filePath)){
		//cout << " [ OK ]" << endl;
		XML.setValue(objectName+":x",x);
		XML.setValue(objectName+":y",y);
		XML.setValue(objectName+":scale",scale);
		XML.setValue(objectName+":width",width);
		XML.setValue(objectName+":height",height);
	} else
		cout << " [ FAIL ]" << endl;
	XML.saveFile();
}