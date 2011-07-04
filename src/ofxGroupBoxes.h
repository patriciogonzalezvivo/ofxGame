/*
 *  ofxGroupBoxes.h
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXGROUPBOXES
#define OFXGROUPBOXES

#include "ofxGameObj.h"
#include "ofxBox.h"

class ofxGroupBoxes : public ofxGameObj {
public:
	ofxGroupBoxes(string _objectName);
	~ofxGroupBoxes(){ clear(); };
	
	void setWorld(b2World * _b2dworld, float _groundY);
	
	void clear(){boxes.clear();};

	void draw();
	
private:
	void loadExtraXml(string filePath = "config.xml");
	vector<ofxBox*>	boxes;
	float den, bou, fri;
};
#endif