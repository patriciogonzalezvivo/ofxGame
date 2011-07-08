/*
 *  ofxUser.h
 *
 *  Created by Patricio González Vivo on 30/06/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *  Kinect User masking GameObject
 *
 */

#ifndef OFXMASK
#define OFXMASK

#include "ofxGameObj.h"

class ofxMask : public ofxGameObj {
public:
	ofxMask(string _objName = "mask"){
		objectName = _objName; 
		loadXml();
		if ( !(width > 0) )
			width = 640;
		if ( !(height > 0) )
			height = 480;
		
		usersMasked.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	};
		
	void update(unsigned char * mskPixels, unsigned char * imagePixels, int blurAmount = 0){
		if (blurAmount > 0)
			superFastBlur(mskPixels, blurAmount);
		
		unsigned char * fPixels = usersMasked.getPixels();
		
		for( int i=0; i < width; i++ ){
			for( int j=0; j < height; j++ ){
				int p = j * width + i;	
				fPixels[p * 4 + 0] = imagePixels[p * 3 + 0];
				fPixels[p * 4 + 1] = imagePixels[p * 3 + 1];
				fPixels[p * 4 + 2] = imagePixels[p * 3 + 2];
				fPixels[p * 4 + 3] = mskPixels[p];				
			}
		}
		usersMasked.setFromPixels( fPixels , width, height, OF_IMAGE_COLOR_ALPHA);
	};
	
	void draw(){ draw(x,y); };
	void draw(int _x, int _y){
		ofPushMatrix();
		ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
		ofScale(scale, scale);
		
		ofSetColor(255, 255);
		usersMasked.draw(0, 0);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};
	
	int getMaskWidth(){return usersMasked.getWidth();};
	int getMaskHeight(){return usersMasked.getHeight();};
	unsigned char * getPixels(){return usersMasked.getPixels();};
	
private:
	void superFastBlur(unsigned char *pix, int radius){  
		int w = width;
		int h = height;
		
		if (radius<1) return;  
		int wm=w-1;  
		int hm=h-1;  
		int wh=w*h;  
		int div=radius+radius+1;  
		unsigned char *a=new unsigned char[wh]; 
		int asum,x,y,i,p,p1,p2,yp,yi,yw;  
		int *vMIN = new int[MAX(w,h)];  
		int *vMAX = new int[MAX(w,h)];  
		
		unsigned char *dv=new unsigned char[256*div];  
		for (i=0;i<256*div;i++) dv[i]=(i/div);  
		
		yw=yi=0;  
		
		for (y=0;y<h;y++){
			asum = 0;
			for(i=-radius;i<=radius;i++){  
				p = (yi + MIN(wm, MAX(i,0))); 
				asum += pix[p];
			}  
			for (x=0;x<w;x++){   
				a[yi]=dv[asum];
				
				if(y==0){  
					vMIN[x]=MIN(x+radius+1,wm);  
					vMAX[x]=MAX(x-radius,0);  
				}   
				p1 = (yw+vMIN[x]); 
				p2 = (yw+vMAX[x]); 
				asum += pix[p1]     - pix[p2];  
				
				yi++;  
			}  
			yw+=w;  
		}  
		
		for (x=0;x<w;x++){
			asum=0;
			yp=-radius*w;  
			for(i=-radius;i<=radius;i++){  
				yi=MAX(0,yp)+x;   
				asum+=a[yi];
				yp+=w;  
			}  
			yi=x;  
			for (y=0;y<h;y++){  
				pix[yi]       = dv[asum];
				
				if(x==0){  
					vMIN[y]=MIN(y+radius+1,hm)*w;  
					vMAX[y]=MAX(y-radius,0)*w;  
				}   
				p1=x+vMIN[y];  
				p2=x+vMAX[y];
				asum+=a[p1]-a[p2];
				
				yi+=w;  
			}  
		}  
		
		delete a;
		delete vMIN;  
		delete vMAX;  
		delete dv;  
	};

	ofImage				usersMasked;
};
#endif
