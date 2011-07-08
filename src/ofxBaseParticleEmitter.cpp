/*
 *  ofxBaseParticleEmitter.cpp
 *
 *  Created by Patricio González Vivo on 04/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 */

#include "ofxBaseParticleEmitter.h"
ofxBaseParticleEmitter::ofxBaseParticleEmitter(){
	objectName = "ParticleEmitter";
	objColor.setHex(0xffcc33);
	loadXml();
	loadExtraXml();

	if (file != "none")
		pImage.loadImage(file);
	
	bbox = NULL;
}

ofxBaseParticleEmitter::ofxBaseParticleEmitter(string _objectName){
	objectName = _objectName;
		
	objColor.setHex(0xffcc33);
	loadXml();
	loadExtraXml();
	
	if (file != "none")
		pImage.loadImage(file);
	
	bbox = NULL;
}

void ofxBaseParticleEmitter::addDefault(){
	ofxBaseParticle * p = new ofxBaseParticle();
	addDefault(p);
};

void ofxBaseParticleEmitter::addDefault(ofxBaseParticle * p){
	p->setPosition(ofPoint(ofRandom(x-getScaledWidth()*0.5,x+getScaledWidth()*0.5), 
						   ofRandom(y-getScaledHeight()*0.5,y+getScaledHeight()*0.5)));
	
	p->setMovement(initForce);
	
	if ( (sizeMin != 0) || (sizeMax != 0) )
		p->setScale(scale*ofRandom(sizeMin, sizeMax));
	else 
		p->setScale(scale);
	
	if (life > 0)
		p->setLife(life);
	
	p->collisionDamp = colDamp;
	
	if (file != "none")
		p->setImage(&pImage);
	
	particles.push_back(p);
};

void ofxBaseParticleEmitter::update(){
    for (int iter = 0; iter < iteration; iter++){
        for (vector<ofxBaseParticleSpring*>::iterator i = springs.begin(); i != springs.end(); i++)
			(*i)->update();
		
        for (vector<ofxBaseParticleForce*>::iterator f = forces.begin(); f != forces.end(); f++)
            (*f)->update();
		
        for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end();){
            if ((*i)->live){
                (*i)->baseUpdate();			
                if (!(*i)->fixed) {
                    for (vector<ofxBaseParticleForce*>::iterator f = forces.begin(); f != forces.end(); f++)
						(*f)->apply(*i);
					
                    (*i)->position += (*i)->movement;
					
                    clampVelocity(*i);
                    (*i)->movement *= (*i)->friction;
                }
                i++;
            } else {
                deleteSpring(*i);
                delete (*i);
                i = particles.erase(i);
            }
        }
		
        if (hasCollision) collision();
        if (hasBbox) borders();
    }
}

void ofxBaseParticleEmitter::clear(){ 
	for (vector<ofxBaseParticle*>::iterator p = particles.begin(); p != particles.end(); p++) 
		delete (*p); 
	particles.clear();
}

void ofxBaseParticleEmitter::clampVelocity(ofxBaseParticle * p){
    p->movement.x = ofClamp(p->movement.x, -maxVelocity, maxVelocity);
    p->movement.y = ofClamp(p->movement.y, -maxVelocity, maxVelocity);
}

void ofxBaseParticleEmitter::deleteSpring(ofxBaseParticle * p){
    for (vector<ofxBaseParticleSpring*>::iterator i = springs.begin(); i != springs.end();){
        if ((*i)->p1 == p || (*i)->p2 == p) {
            delete (*i);
            i = springs.erase(i);
        } else 
			i++;
    }
}

ofxBaseParticle * ofxBaseParticleEmitter::getParticle(float p){
    if (particles.size() == 0) return NULL;
    p = ofClamp(p, 0, 1);
    int n = (int)(p * (particles.size() - 1));
    vector<ofxBaseParticle*>::iterator i = particles.begin() + n;
    return (*i);
}

ofxBaseParticle * ofxBaseParticleEmitter::getParticleAt(int n){
    if (particles.size() == 0) return NULL;
    n = (int)ofClamp(n, 0, particles.size() - 1);
    vector<ofxBaseParticle*>::iterator i = particles.begin() + n;
    return (*i);
}

void ofxBaseParticleEmitter::borders(){
	float xMin,xMax,yMin, yMax;
	
	if (bbox != NULL){
		xMin = (bbox->getPosition().x - bbox->getScaledWidth()*0.5);
		xMax = (bbox->getPosition().x + bbox->getScaledWidth()*0.5);
		yMin = (bbox->getPosition().y - bbox->getScaledHeight()*0.5);
		yMax = (bbox->getPosition().y + bbox->getScaledHeight()*0.5);
	} else {
		xMin = x - getScaledWidth()*0.5;
		xMax = x + getScaledWidth()*0.5;
		yMin = y - getScaledHeight()*0.5;
		yMax = y + getScaledHeight()*0.5;
	}
	
    if (borderEvent == PARTICLE_BORDER_DIE){
        for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end();i++) {
            if ((*i)->position.x < xMin - (*i)->size || (*i)->position.x > xMax + (*i)->size || (*i)->position.y < yMin - (*i)->size || (*i)->position.y > yMax + (*i)->size)
				(*i)->kill();
        }
    } else if (borderEvent == PARTICLE_BORDER_BOUNCE){
        for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end();i++){
            if ((*i)->position.x < xMin - (*i)->size){
				(*i)->position.x = xMin - (*i)->size;
                (*i)->movement.x *= -1;
            }
            else if ((*i)->position.x > xMax + (*i)->size){
                (*i)->position.x = xMax + (*i)->size;
                (*i)->movement.x *= -1;
            }
            if ((*i)->position.y < yMin - (*i)->size) {
                (*i)->position.y = yMin - (*i)->size;
                (*i)->movement.y *= -1;
            }
            else if ((*i)->position.y > yMax + (*i)->size){
                (*i)->position.y = yMax + (*i)->size;
                (*i)->movement.y *= -1;
            }
        }
    }
    else if (borderEvent == PARTICLE_BORDER_JUMP_TO_OPPOSITE){
        for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end();i++){
            if ((*i)->position.x < xMin - (*i)->size)
                (*i)->position.x = xMax + (*i)->size;
            else if ((*i)->position.x > xMax + (*i)->size)
                (*i)->position.x = xMin- (*i)->size;
            else if ((*i)->position.y < yMin - (*i)->size)
                (*i)->position.y = yMax + (*i)->size;
            else if ((*i)->position.y > yMax + (*i)->size)
                (*i)->position.y = yMin - (*i)->size;
        }
    }
	
}

void ofxBaseParticleEmitter::collision(){
    for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end();i++)
        for (vector<ofxBaseParticle*>::iterator j = particles.begin(); j != particles.end();j++)
            (*i)->collide(*j);
}

void ofxBaseParticleEmitter::draw(){
	
    for (vector<ofxBaseParticleSpring*>::iterator i = springs.begin(); i != springs.end(); i++)
        (*i)->baseDraw();
	
    for (vector<ofxBaseParticle*>::iterator i = particles.begin(); i != particles.end(); i++)
        (*i)->draw();
	
	ofPushMatrix();
	ofTranslate(x-getScaledWidth()*0.5,y-getScaledHeight()*0.5);
	ofScale(scale, scale);
	
	if (*bDebug)
		drawBoundingBox();
	
	ofPopMatrix();
}

void ofxBaseParticleEmitter::loadExtraXml(string filePath){
	ofxXmlSettings XML;
	cout << "Reading " << objectName << " extra configuration file " << filePath;
	
	if (XML.loadFile(filePath)){
		cout << " [ OK ]" << endl;
		
		initForce.x = XML.getValue(objectName+":xInitForce",0.0f);
		initForce.y = XML.getValue(objectName+":yInitForce",0.0f);
		
		sizeMax	= XML.getValue(objectName+":sizeMax",0.0f);
		sizeMin	= XML.getValue(objectName+":sizeMin",0.0f);
		
		cout << "Reading sizeMax " << sizeMax << " and sizeMin " << sizeMin << endl; 
		
		colDamp = XML.getValue(objectName+":damp",20.0f);
		
		iteration = XML.getValue(objectName+":iteration",2);
		maxVelocity = XML.getValue(objectName+":maxvel",20);
		
		hasBbox = XML.getValue(objectName+":bounds",0);
		hasCollision = XML.getValue(objectName+":collision",0);
		
		borderEvent = XML.getValue(objectName+":borderEvent",0);
		life		= XML.getValue(objectName+":life",0); 
		
		//fade	= XML.getValue(objectName+":alfafade",-1);
		//melt	= XML.getValue(objectName+":sizefade",-1);
	} else
		cout << " [ FAIL ]" << endl;
}

#ifdef MASKINTERACTION
void ofxBaseParticleEmitter::pixelCollision(ofxMask * _mask, float _force){
	ofPoint bounce;
	int id = 0;
	int maskWidth = _mask->getMaskWidth();
	int maskHeight = _mask->getMaskHeight();
	unsigned char * pixels = _mask->getPixels();
	ofPoint maskUpLeftCorner = ofPoint(_mask->getPosition().x - maskWidth*0.5, _mask->getPosition().y - maskHeight*0.5);
	
	for (int i = 0; i < particles.size(); i++){
		if (_mask->isOver(particles[i]->position)){
			
			id = imageCollision((particles[i]->position - maskUpLeftCorner), particles[i]->size, _force, pixels,  maskWidth, maskHeight, bounce);
			if (id > 0){
				particles[i]->movement += bounce;
				particles[i]->otherCollisionEvent();
				particles[i]->intUserData = id - 1;
				if (particles[i]->free)
					particles[i]->free = false;
			}
		}
	}
}

int ofxBaseParticleEmitter::imageCollision(ofPoint p, float radius, float _force, unsigned char * pixels, int _width, int _height, ofPoint & bounce){
	bounce.set(0, 0);
	
	float o = ofRandom(0, 360);
	int step = 20;
	int X, Y;
	float inc = 360 / (float)step;
	float dx, dy;
	int colorId = 0;
	
	for (int u = 0; u < step; u++){
		o = fmodf(o + inc, 360);
		
		dx = cosf(o * PI / 180.f);
		dy = sinf(o * PI / 180.f);
		
		X = (int)((p.x + dx * radius));
		Y = (int)((p.y + dy * radius));
		
		if (X >= 0 && X < _width && Y >= 0 && Y < _height && pixels[(X + Y * _width) * 4 + 3] > 0){
			bounce.x -= dx * _force;
			bounce.y -= dy * _force;
			colorId = pixels[(X + Y * _width) * 4 + 3];
		}
	}
	return colorId;
}
#endif