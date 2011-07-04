/*
 *  ofxUser.h
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *  Kinect User masking GameObject
 *
 */

#ifndef OFXUSR
#define OFXUSR

#include "ofxGameObj.h"

class ofxUser : public ofxGameObj {
public:
	ofxUser();
		
	void update(unsigned char * mskPixels, unsigned char * imagePixels, int blurAmount);
	
	void draw(){ draw(x,y); };
	void draw(int _x, int _y);
	
private:
	void superFastBlur(unsigned char *pix, int radius); // Grayscale Blur for tha masking the user
	
	ofImage				usersMasked;
};
#endif
