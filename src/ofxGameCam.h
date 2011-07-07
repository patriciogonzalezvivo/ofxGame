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
		
		vel = 0;
		bWidth = false;
		bHeight = false;
		bVertical = false;
		bHorizontal = true;
		
		xOffset = 0.5;
		yOffset = 0.5;
		
		displacement.set(0,0);
	};
	
	ofxGameCam& loadXml(string filePath = "config.xml"){
		ofxXmlSettings XML;
		cout << "Reading camera configuration file " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			
			bVertical = XML.getValue("camera:vertical",0);
			bHorizontal = XML.getValue("camera:horizontal",0);
			xDefaultOffset = XML.getValue("camera:center:x",0.5);
			yDefaultOffset = XML.getValue("camera:center:y",0.5);
			vel = XML.getValue("camera:velocity",0.5f);
			
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
	ofxGameCam& setTarget(ofxBox2dBaseShape * _targetShp){targetShp = _targetShp; targetObj = NULL; setOffset(); return * this; };
	ofxGameCam& setTarget(ofxGameObj * _targetObj){targetObj = _targetObj;targetShp = NULL; setOffset(); return * this; };
	ofxGameCam& setOffset(float _xOffset = -1, float _yOffset = -1){
		if (_xOffset == -1)
			xOffset = xDefaultOffset;
		else 
			xOffset = _xOffset;
		
		if (_yOffset == -1)
			yOffset = yDefaultOffset;
		else 
			yOffset = _yOffset;
		return * this; 
	};
	
	ofxGameCam& apply(){
		if (area != NULL){
			if ((targetObj != NULL)|| (targetShp != NULL)){
				if (targetObj != NULL)
					target = targetObj->getPosition();
				
				if (targetShp != NULL)
					target = targetShp->getPosition();
			
				ofVec2f displacementToTarget(0,0);
				
				if (bHorizontal){
					if (!bWidth)
						width = ofGetWindowSize().x;

					float center = width * xOffset;
						
					if (target.x > area->getScaledWidth() - width*(1-xOffset))
						displacementToTarget.x += -area->getScaledWidth() + width;	
					else if (target.x > center)
						displacementToTarget.x += center - target.x;
					else 
						displacementToTarget.x = 0; 
					
					if ( (vel > 0) && ((int)displacementToTarget.x != (int)displacement.x) )
						displacement.x = displacement.x*(1-vel) + displacementToTarget.x*vel;
					else
						displacement.x = displacementToTarget.x;
				}
				
				if (bVertical){
					if (!bHeight)
						height = ofGetWindowSize().y;
					
					float center = height * yOffset;
					
					if (target.y > area->getScaledHeight() - width*(1-yOffset))
						displacementToTarget.y += -area->getScaledHeight() + height;	
					else if (target.y > center)
						displacementToTarget.y += center - target.y;
					else
						displacementToTarget.y = 0; 
					
					if ( (vel > 0) && ((int)displacementToTarget.y != (int)displacement.y) )
						displacement.y = displacement.y*(1-vel) + displacementToTarget.y*vel;
					else
						displacement.y = displacementToTarget.y;
				}
				
				ofTranslate(displacement.x, displacement.y);
			}
		}
		return * this; 
	};
	
	int		getWidth(){return width;};
	int		getHeight(){return height;};
	
	bool	isOver(ofPoint _loc){return isOver(_loc.x, _loc.y);};
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
	ofVec2f				target,displacement;
	ofxBox2dBaseShape*	targetShp;
	ofxGameObj*			targetObj;
	ofxGameObj*			area;
	
	float		xOffset, yOffset, xDefaultOffset, yDefaultOffset, vel;
	int			x,y,width, height;
	bool		bVertical, bHorizontal, bWidth, bHeight;
};
#endif