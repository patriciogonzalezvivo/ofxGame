/*
 *  ofxUser.cpp
 *  jaboneria
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxUser.h"

ofxUser::ofxUser(){
	objectName = "user"; 
	loadXml();
	width = 640;
	height = 480;
	usersMasked.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
	width = usersMasked.getWidth();
	height = usersMasked.getHeight();
	saveXml();
}

void ofxUser::update(unsigned char * mskPixels, unsigned char * imagePixels, int blurAmount){
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

void ofxUser::draw(int _x, int _y){
	ofPushMatrix();
	ofTranslate(_x-getScaledWidth()*0.5,_y-getScaledHeight()*0.5);
	ofScale(scale, scale);
	
	ofSetColor(255, 255);
	usersMasked.draw(0, 0);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
};

void ofxUser::superFastBlur(unsigned char *pix, int radius) {  
	int w = width;
	int h = height;
	
	if (radius<1) return;  
	int wm=w-1;  
	int hm=h-1;  
	int wh=w*h;  
	int div=radius+radius+1;  
	//unsigned char *r=new unsigned char[wh];  
	//unsigned char *g=new unsigned char[wh];  
	//unsigned char *b=new unsigned char[wh]; 
	unsigned char *a=new unsigned char[wh]; 
	//int rsum,gsum,bsum,x,y,i,p,p1,p2,yp,yi,yw;  
	int asum,x,y,i,p,p1,p2,yp,yi,yw;  
	int *vMIN = new int[MAX(w,h)];  
	int *vMAX = new int[MAX(w,h)];  
	
	unsigned char *dv=new unsigned char[256*div];  
	for (i=0;i<256*div;i++) dv[i]=(i/div);  
	
	yw=yi=0;  
	
	for (y=0;y<h;y++){  
		//rsum=gsum=bsum=0;  
		asum = 0;
		for(i=-radius;i<=radius;i++){  
			p = (yi + MIN(wm, MAX(i,0)));// * 3;  
			//rsum += pix[p];  
			//gsum += pix[p+1];  
			//bsum += pix[p+2];  
			asum += pix[p];
		}  
		for (x=0;x<w;x++){  
			//r[yi]=dv[rsum];  
			//g[yi]=dv[gsum];  
			//b[yi]=dv[bsum];  
			a[yi]=dv[asum];
			
			if(y==0){  
				vMIN[x]=MIN(x+radius+1,wm);  
				vMAX[x]=MAX(x-radius,0);  
			}   
			p1 = (yw+vMIN[x]);//*3;  
			p2 = (yw+vMAX[x]);//*3;  
			
			//rsum += pix[p1]     - pix[p2];  
			//gsum += pix[p1+1]   - pix[p2+1];  
			//bsum += pix[p1+2]   - pix[p2+2];  
			asum += pix[p1]     - pix[p2];  
			
			yi++;  
		}  
		yw+=w;  
	}  
	
	for (x=0;x<w;x++){  
		//rsum=gsum=bsum=0;
		asum=0;
		yp=-radius*w;  
		for(i=-radius;i<=radius;i++){  
			yi=MAX(0,yp)+x;  
			//rsum+=r[yi];  
			//gsum+=g[yi];  
			//bsum+=b[yi];  
			asum+=a[yi];
			yp+=w;  
		}  
		yi=x;  
		for (y=0;y<h;y++){  
			//pix[yi*3]       = dv[rsum];  
			//pix[yi*3 + 1]   = dv[gsum];  
			//pix[yi*3 + 2]   = dv[bsum];  
			pix[yi]       = dv[asum];
			
			if(x==0){  
				vMIN[y]=MIN(y+radius+1,hm)*w;  
				vMAX[y]=MAX(y-radius,0)*w;  
			}   
			p1=x+vMIN[y];  
			p2=x+vMAX[y];  
			
			//rsum+=r[p1]-r[p2];  
			//gsum+=g[p1]-g[p2];  
			//bsum+=b[p1]-b[p2];  
			
			asum+=a[p1]-a[p2];
			
			yi+=w;  
		}  
	}  
	
	delete a;
	//delete r;  
	//delete g;  
	//delete b;  
	
	delete vMIN;  
	delete vMAX;  
	delete dv;  
} 