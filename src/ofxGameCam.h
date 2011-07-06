/*
 *  ofxGameCamera.h
 *
 *  Created by Patricio González Vivo on 05/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#ifndef OFXGAMECAM
#define OFXGAMECAM

#include "ofMain.h"
#include "ofxBox2d.h"

#include "ofxGameObj.h"

class ofxGameCam{
public:
	ofxGameCam(){
		area = NULL;
		targetShp = NULL;
		targetObj = NULL;
		
		bWidth = false;
		bHeight = false;
		bVertical = false;
		bHorizontal = true;
		
		xOffset = 0.5;
		yOffset = 0.5;
	};
	
	ofxGameCam& loadXml(string filePath = "config.xml"){
		ofxXmlSettings XML;
		cout << "Reading camera configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			
			bVertical = XML.getValue("camera:vertical",0);
			bHorizontal = XML.getValue("camera:horizontal",0);
			xOffset = XML.getValue("camera:center:x",0.5);
			yOffset = XML.getValue("camera:center:y",0.5);
			
			x = XML.getValue("camera:x",0);
			y = XML.getValue("camera:y",0);
			
			if ( XML.tagExists("camera:width")){
				bWidth = true;
				width = XML.getValue("camera:width",0);
			}
			
			if ( XML.tagExists("camera:height")){
				bHeight = true;
				height = XML.getValue("camera:height",0);
			}
			
		} else
			cout << " [ FAIL ]" << endl;
		return * this; 
	}
	
	ofxGameCam& setArea(ofxGameObj * _area){area = _area; return * this; };
	ofxGameCam& setTarget(ofxBox2dBaseShape * _targetShp){targetShp = _targetShp; targetObj = NULL ; return * this; };
	ofxGameCam& setTarget(ofxGameObj * _targetObj){targetObj = _targetObj;targetShp = NULL ;return * this; };
	
	ofxGameCam& apply(){
		if (area != NULL){
			if ((targetObj != NULL)|| (targetShp != NULL)){
				if (targetObj != NULL)
					target = targetObj->getPosition();
				
				if (targetShp != NULL)
					target = targetShp->getPosition();
			
		
				if (bHorizontal){
					if (!bWidth)
						width = ofGetWindowSize().x;
						
					float center = width * xOffset;
						
					if (target.x > area->getScaledWidth() - width*(1-xOffset))
						ofTranslate(-area->getScaledWidth() + width, 0);	
					else if (target.x > center)
						ofTranslate(center - target.x, 0);
				}
				
				if (bVertical){
					if (!bHeight)
						height = ofGetWindowSize().y;
					
					float center = height * yOffset;
					
					if (target.y > area->getScaledHeight() - width*(1-yOffset))
						ofTranslate(-area->getScaledHeight() + height, 0);	
					else if (target.y > center)
						ofTranslate(center - target.y, 0);
				}
			}
		}
		return * this; 
	};
	
	int		getWidth(){return width;};
	int		getHeight(){return height;};
	
	bool	isOver(ofPoint _loc){return isOver(_loc.x, _loc.y);};
	bool	isOver(float _x, float _y);
	
protected:	
	ofVec2f				target;
	ofxBox2dBaseShape*	targetShp;
	ofxGameObj*			targetObj;
	ofxGameObj*			area;
	
	float		xOffset, yOffset;
	int			x,y,width, height;
	bool		bVertical, bHorizontal, bWidth, bHeight;
};
#endif