/*
 *  ofxGame.h
 *
 *  Created by Patricio González Vivo on 03/07/11.
 *  Copyright 2011 PatricioGonzalezVivo.com. All rights reserved.
 *
 *
 *  This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 
 *	Unported License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ 
 *	or send a letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.
 *
 */

// BOX2D Engine Related Classes
#ifdef BOX2D		
#include "ofxBox2d.h"		// github.com/vanderlin/ofxBox2d -> addon/ofxBox2d
// Enginer ( BOX2D WORLD)
#include "ofxGameEng.h"	
// BOX2D Rectangules
#include "ofxCharacterObj.h"	
#include "ofxCharacter.h"	// made from ofxElement.h
#include "ofxBoxEmitter.h"
#include "ofxBoxObj.h"		// made from ofxElement.h
#endif

// Camera
#include "ofxGameCam.h"		
// Objects
#include "ofxGameObj.h"		
// Objects childs
#include "ofxMask.h"
#include "ofxClock.h"
#include "ofxPlace.h"
#include "ofxPicture.h"
#include "ofxVideo.h"

// Particles Systems
#include "ofxParticleEmitter.h"		// OLD soon replaced
#include "ofxParticle.h"			// OLD soon replaced

#include "ofxBaseParticleEmitter.h"
#include "ofxBaseParticleForce.h"
#include "ofxBaseParticleSpring.h"
#include "ofxBaseParticle.h"






