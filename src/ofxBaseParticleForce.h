#ifndef OFXBASEPARTICLEFORCE
#define OFXBASEPARTICLEFORCE

#include "ofMain.h"
#include "ofxBaseParticle.h"

class ofxBaseParticleForce : public ofxGameObj {
public:
	ofxBaseParticleForce(){
		objectName = "ParticleEmitter";
		objColor.set(0,0,255);
		loadXml();
		loadForce();
	};
	
	ofxBaseParticleForce(string _objectName){
		objectName = _objectName;
		objColor.set(0,0,255);
		loadXml();
		loadForce();
	};
	
	~ofxBaseParticleForce(){};

	virtual void update(){};
	virtual void draw(){
		ofPushMatrix();
		ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
		ofScale(scale, scale);
		
		if (*bDebug)
			drawBoundingBox();
		
		ofPopMatrix();
	};

	
	void apply(ofxBaseParticle * p){
		float xMin = x - getScaledWidth()*0.5;
		float xMax = x + getScaledWidth()*0.5;
		float yMin = y - getScaledHeight()*0.5;
		float yMax = y + getScaledHeight()*0.5;
		
		if (p->position.x >= xMin && p->position.x <= xMax && p->position.y >= yMin && p->position.y <= yMax){
			p->movement += getForce(p);
			if (noise)
				p->movement += getNoise(p);
		}
    };

	virtual ofPoint getForce(ofxBaseParticle * p){return force;};
	virtual ofPoint getNoise(ofxBaseParticle * p){
		float rAngl = ofSignedNoise(p->position.x * 0.005f, p->position.y *0.005f) * noiseAngle;
		ofVec2f noiseVector( cos( rAngl ), sin( rAngl ) );
		return noiseVector * noiseTurbulence;// * (1.0 - ofNormalize(p->life, 0, p->initLife));
	}

protected:
	void loadForce(string filePath = "config.xml"){
		ofxXmlSettings XML;
		cout << "Reading " << objectName << " configuration file looking Force Extra parametters " << filePath;
		
		if (XML.loadFile(filePath)){
			cout << " [ OK ]" << endl;
			force.x = XML.getValue(objectName+":xForce",0.0f);
			force.y = XML.getValue(objectName+":yForce",0.0f);
			
			 den			= XML.getValue(objectName+":density",0);
			 spe			= XML.getValue(objectName+":speedLimit",0);
			 
			 noise	= XML.tagExists(objectName+":noise");
			 
			 if (noise){
			 noiseAngle= XML.getValue(objectName+":noise:angle",12);
			 noiseTurbulence = XML.getValue(objectName+":noise:turbulence",0.01);
			 }
			
		} else
			cout << " [ FAIL ]" << endl;
	};
	
	ofVec2f force;
protected:
	//int		fade, melt; 
	float	noiseAngle,noiseTurbulence,den,spe;
	bool	noise, density;	
};

#endif

