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
Element[] part;
int       current = 0;

void setup(){
  size(800,600);
  
  f = createFont("Georgia", 12, true);
  textFont(f);
  textAlign(CENTER);
  
  centro = new PVector (width/2,height/2+100);
  
  String[] data = loadStrings("data/config.box");    
  
  if ( data.length > 1 ){                 
    part = new Element[data.length];
    for(int i = 0; i < part.length; i++){ 
      String[] values = split(data[i],",");
      float rad = float(values[1]);
      float ang   = float(values[2]);
      int xI  = int(values[3]);
      int yI   = int(values[4]);
      boolean _mirror = ((int(values[5]))==1)?true:false;
      part[i] = new Element(centro, values[0], rad, ang, xI, yI, _mirror);
    } 
  } else {
      restart();
  }
 
  smooth();
}

void restart(){
  part = new Element[6];
  
  part[0] = new Element(centro,"fastShadow.png");
  part[1] = new Element(centro,"shadow.png");
  part[2] = new Element(centro,"body.png" );
  part[3] = new Element(centro,"top.png" );
  part[4] = new Element(centro,"front.png" );
  part[5] = new Element(centro,"core.png" );
}

void draw(){
  background(200);
  
    for(int i = 0; i< part.length; i++){
      part[i].render();
      noStroke();
      if (i == current)
        fill(0,255,0,100);
      else
        fill(255,0,0,100);
      ellipse(part[i].pos.x,part[i].pos.y,50,50);
      stroke(255);
      line(part[i].pos.x,part[i].pos.y-5,part[i].pos.x,part[i].pos.y+5);
      line(part[i].pos.x-5,part[i].pos.y,part[i].pos.x+5,part[i].pos.y);
      stroke(0);
      fill(255,255);
      text( i,part[i].pos.x+10,part[i].pos.y+15);
    }
  
  stroke(0,255);
  line(centro.x,0,centro.x,height);
  line(0,centro.y,width,centro.y);
  
  if (refLines)
    for(int i = 0; i< part.length; i++){
      stroke(0,50);
      line(part[i].pos.x,0,part[i].pos.x,height);
      line(0,part[i].pos.y,width,part[i].pos.y);
    }
}

// --------------------------------------------------- Mouse Events
void mousePressed(){
  for(int i = 0; i< part.length; i++){
    if ( part[i].isOver(new PVector(mouseX,mouseY))) 
      current = i;
  }
}

void mouseDragged(){
  part[current].moveTo(mouseX,mouseY);
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
    part[current].iCenter.y++;
  if (keyCode == DOWN )
    part[current].iCenter.y--;
   if (keyCode == LEFT )
    part[current].iCenter.x--;
  if (keyCode == RIGHT )
    part[current].iCenter.x++;
  if (key == ',' )
    part[current].north -= 0.01;
  if (key == '.' )
    part[current].north += 0.01;
  if (key == 'm')
    part[current].mirror = !part[current].mirror;
  if (key == 'l')
    refLines = !refLines;
  if (key == 'c' )
    restart();
  if (key == 'r' )
    reverseView = !reverseView;   
}

void saveData() {
  String[] data = new String[part.length];
  for (int i = 0; i < part.length; i++) {
    data[i] = part[i].iPath + "," + part[i].rad + "," + part[i].ang + "," + part[i].iCenter.x + "," + part[i].iCenter.y + "," + (part[i].mirror?1:0);
  }
  saveStrings("data/config.box",data);
}

void close(){
  saveData();    // This could prevent data lost
}
