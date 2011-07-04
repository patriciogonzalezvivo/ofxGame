/*
 *  ofxGroupBoxes.cpp
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxGroupBoxes.h"
ofxGroupBoxes::ofxGroupBoxes(string _objectName){
	objectName = _objectName;
	loadXml();
}

void ofxGroupBoxes::setWorld(b2World * _b2dworld, float _groundY){
	string path = objectName + "/config.boxes";
	ifstream	fs( ofToDataPath(path).c_str());
	
	string line;
	int lineCounter = 0;
	
	cout << "- Loading box: " << path << endl;
	
	while(!(fs >> line).fail()){
		vector <string> values = ofSplitString(line, ",");
		
		string _box	 = objectName + "/" + values[0];
		float _radio = ofToFloat(values[1].c_str());
		float _angle = ofToFloat(values[2].c_str());
	
		float propRadio = _radio * scale;
		
		ofPoint _pos;
		_pos.x = propRadio * cos(_angle) + x;
		_pos.y = propRadio * sin(_angle) + y;
		
		ofxBox * b = new ofxBox();
		b->setPhysics(den, bou, fri);
		b->load(_box).setScale(scale).linkToDebug(bDebug).loadToWorld(_b2dworld, _pos,_groundY);
		boxes.push_back(b);
	}
	
	fs.seekg(0,ios::beg);
	fs.clear();
	fs.close();
}

void ofxGroupBoxes::draw(){ 
	ofSetColor(255, 255);
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw();
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(4);
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(3);
	
	for(int i=0; i < boxes.size(); i++)
		boxes[i]->draw(5);
	
	ofPushMatrix();
	ofTranslate(x-width*0.5,y-height*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxGroupBoxes::loadExtraXml(string filePath){
	ofxXmlSettings XML;
	cout << "Reading " << objectName << " configuration file looking for extra parametters " << filePath;
	
	if (XML.loadFile(filePath)){
		cout << " [ OK ]" << endl;
		
		den = XML.getValue(objectName+":density",0.5);
		bou = XML.getValue(objectName+":bounce",0.5);
		fri = XML.getValue(objectName+":friction",0.5);
		
	} else
		cout << " [ FAIL ]" << endl;
}
