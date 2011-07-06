/*
 *  ofxGameEng.cpp
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 05/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxGameEng.h"

ofxGameEng::ofxGameEng(){
	boundingObj = NULL;

	groundX	= -1;
	groundY	= -1;
}

ofxGameEng& ofxGameEng::loadXml(string filePath = "config.xml"){
	ofxXmlSettings XML;
	if (XML.loadFile(filePath)){
		cout << " [ OK ]" << endl;
		
		init();
		
		if ( XML.tagExists("world:gravity"))
			setGravity(XML.getValue("world:gravity:x",0), 
					   XML.getValue("world:gravity:y",10) );
		
		setFPS(XML.getValue("world:fps",30));
		
		bool bGrabbing = XML.getValue("world:grabbing",0);
		if (bGrabbing)
			registerGrabbing();
		
		if ( XML.tagExists("world:ground:x"))
			groundX = XML.getValue("world:ground:x",0);
		
		if ( XML.tagExists("world:ground:y"))
			groundY = XML.getValue("world:ground:y",10);
	
		if( boundingObj != NULL ){
			createGround(ofPoint(	(groundX!=-1)?groundX:0,
									(groundY!=-1)?groundY:0),
							ofPoint((groundX!=-1)?groundX:boundingObj->getScaledWidth(), 
									(groundY!=-1)?groundY:boundingObj->getScaledHeight()));
			createBounds(0, 0, boundingObj->getScaledWidth(),boundingObj->getScaledHeight());
		}
		
		// TODO:
		//		This need some love
		
	} else
		cout << " [ FAIL ]" << endl;
		
	return * this;
}