// Make by Patricio Gonzalez Vivo
// This is a handy app that let you arrange the parts of the character body. 
// After making it you only have to move and rename the "data/" to oF proyect dataPath with the character name.
// Then just load it with the ofxCharacter
//
// Keys:
//        [ 0,1,2,3,4,... ]  Select a bodyPart or Click over it
//        Drag the body part with the mouse
//        Use the ARROY KEYS to move the joint point of the bodyPart
//        Use "m" to mirror the bodyPart
//        Use "r" to reload the model
//        Use "l" to toagle the view of the reference lines

boolean   refLines = true; 
boolean   reverseView = false;
PVector   centro;
PFont     f;
Element[] bPart;
int       current = 0;

void setup(){
  size(800,600);
  
  f = createFont("Georgia", 12, true);
  textFont(f);
  textAlign(CENTER);
  
  centro = new PVector (width/2,height/2+100);
  
  String[] data = loadStrings("data/config.character");    
  
  if ( data.length > 1 ){                 
    bPart = new Element[data.length];
    for(int i = 0; i < bPart.length; i++){ 
      String[] values = split(data[i],",");
      float rad = float(values[1]);
      float ang   = float(values[2]);
      int xI  = int(values[3]);
      int yI   = int(values[4]);
      boolean _mirror = ((int(values[5]))==1)?true:false;
      bPart[i] = new Element(centro, values[0], rad, ang, xI, yI, _mirror);
    } 
  } else {
      restart();
  }
 
  smooth();
}

void restart(){
  bPart = new Element[6];
  
  bPart[0] = new Element(centro,"shadow.png");
  bPart[1] = new Element(centro,"arm.png");
  bPart[2] = new Element(centro,"leg.png" );
  bPart[3] = new Element(centro,"leg.png");
  bPart[4] = new Element(centro,"body.png");
  bPart[5] = new Element(centro,"arm.png");
}

void draw(){
  background(200);
  
  if (!reverseView)
    for(int i = 0; i< bPart.length; i++){
      bPart[i].render();
      noStroke();
      if (i == current)
        fill(0,255,0,100);
      else
        fill(255,0,0,100);
      ellipse(bPart[i].pos.x,bPart[i].pos.y,50,50);
      stroke(255);
      line(bPart[i].pos.x,bPart[i].pos.y-5,bPart[i].pos.x,bPart[i].pos.y+5);
      line(bPart[i].pos.x-5,bPart[i].pos.y,bPart[i].pos.x+5,bPart[i].pos.y);
      stroke(0);
      fill(255,255);
      text( i,bPart[i].pos.x+10,bPart[i].pos.y+15);
    }
  else {
    bPart[0].render();
    bPart[5].render();
    bPart[2].render();
    bPart[3].render();
    bPart[4].render();
    bPart[1].render();
  }
  
  stroke(0,255);
  line(centro.x,0,centro.x,height);
  line(0,centro.y,width,centro.y);
  
  if (refLines)
    for(int i = 0; i< bPart.length; i++){
      stroke(0,50);
      line(bPart[i].pos.x,0,bPart[i].pos.x,height);
      line(0,bPart[i].pos.y,width,bPart[i].pos.y);
    }
}

// --------------------------------------------------- Mouse Events
void mousePressed(){
  for(int i = 0; i< bPart.length; i++){
    if ( bPart[i].isOver(new PVector(mouseX,mouseY))) 
      current = i;
  }
}

void mouseDragged(){
  bPart[current].moveTo(mouseX,mouseY);
}

void mouseReleased(){
  saveData();
}

// --------------------------------------------------- Keyboard Event
void keyPressed(){   
  if (key == '0')
    current = 0;
  if (key == '1')
    current = 1;
  if (key == '2')
    current = 2;
  if (key == '3')
    current = 3;
  if (key == '4')
    current = 4;
  if (key == '5')
    current = 5;
  if (keyCode == UP )
    bPart[current].iCenter.y++;
  if (keyCode == DOWN )
    bPart[current].iCenter.y--;
   if (keyCode == LEFT )
    bPart[current].iCenter.x--;
  if (keyCode == RIGHT )
    bPart[current].iCenter.x++;
  if (key == ',' )
    bPart[current].north -= 0.01;
  if (key == '.' )
    bPart[current].north += 0.01;
  if (key == 'm')
    bPart[current].mirror = !bPart[current].mirror;
  if (key == 'l')
    refLines = !refLines;
  if (key == 'c' )
    restart();
  if (key == 'r' )
    reverseView = !reverseView;   
}

void saveData() {
  String[] data = new String[bPart.length];
  for (int i = 0; i < bPart.length; i++) {
    data[i] = bPart[i].iPath + "," + bPart[i].rad + "," + bPart[i].ang + "," + bPart[i].iCenter.x + "," + bPart[i].iCenter.y + "," + (bPart[i].mirror?1:0);
  }
  saveStrings("data/config.character",data);
}

void close(){
  saveData();    // This could prevent data lost
}
