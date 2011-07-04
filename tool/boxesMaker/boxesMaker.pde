// Make by Patricio Gonzalez Vivo
boolean   refLines = true; 
PVector   centro;
PFont     f;
ArrayList gObjects;
String objects[] = {"jabon"};
int       current = 0;

void setup(){
  size(800,600);
  
  f = createFont("Georgia", 12, true);
  textFont(f);
  textAlign(CENTER);
  
  centro = new PVector (width/2,height/2+100);
  
  String[] data = loadStrings("data/config.boxes"); 
  
  gObjects = new ArrayList();
  
  if ( data.length > 0 ){         
    for(int i = 0; i < data.length; i++){ 
      String[] values = split(data[i],",");
      gObjects.add(new GameObject(centro, values[0], float(values[1]), float(values[2])));
    } 
  }
 
  smooth();
}

void draw(){
  background(200);

    for(int i = 0; i < gObjects.size(); i++){
      GameObject gObj = (GameObject) gObjects.get(i);
      
      gObj.render();
      noStroke();
      if (i == current)
        fill(0,255,0,100);
      else
        fill(255,0,0,100);
      ellipse(gObj.pos.x,gObj.pos.y,50,50);
      stroke(255);
      line(gObj.pos.x,gObj.pos.y-5,gObj.pos.x,gObj.pos.y+5);
      line(gObj.pos.x-5,gObj.pos.y,gObj.pos.x+5,gObj.pos.y);
      stroke(0);
      fill(255,255);
      text( i,gObj.pos.x+10,gObj.pos.y+15);
      
      if (refLines){
        stroke(0,50);
        line(gObj.pos.x,0,gObj.pos.x,height);
        line(0,gObj.pos.y,width,gObj.pos.y);
      }
    }
  
  stroke(0,255);
  line(centro.x,0,centro.x,height);
  line(0,centro.y,width,centro.y);
}

// --------------------------------------------------- Mouse Events
void mousePressed(){
  for(int i = 0; i < gObjects.size(); i++){
    GameObject gObj = (GameObject) gObjects.get(i);
    if ( gObj.isOver(mouseX,mouseY) ) 
      current = i;
  }
  println(current + " selected");
}

void mouseDragged(){
  //if ((current < gObjects.size()) && (current >= 0) ){
    GameObject gObj = (GameObject) gObjects.get(current);
    gObj.moveTo(mouseX,mouseY);
    
  //}
}

void mouseReleased(){
  saveData();
}

// --------------------------------------------------- Keyboard Event
void keyPressed(){   
  if (key == '0')
    gObjects.add(new GameObject(centro, objects[0], new PVector(mouseX,mouseY)));
    
  if (keyCode == UP){
    GameObject gObj = (GameObject) gObjects.get(current);
    gObj.moveTo((int)gObj.pos.x,(int)gObj.pos.y-1);
  }
   if (keyCode == DOWN){
    GameObject gObj = (GameObject) gObjects.get(current);
    gObj.moveTo((int)gObj.pos.x,(int)gObj.pos.y+1);
  }
  if (keyCode == LEFT){
    GameObject gObj = (GameObject) gObjects.get(current);
    gObj.moveTo((int)gObj.pos.x-1,(int)gObj.pos.y);
  } 
  if (keyCode == RIGHT){
    GameObject gObj = (GameObject) gObjects.get(current);
    gObj.moveTo((int)gObj.pos.x+1,(int)gObj.pos.y);
  } 
  
  if (key == 'l')
    refLines = !refLines; 
}

void saveData() {
  String[] data = new String[gObjects.size()];
  for (int i = 0; i < gObjects.size(); i++) {
    GameObject gObj = (GameObject) gObjects.get(i);
    data[i] = gObj.objPath + "," + gObj.rad + "," + gObj.ang;
  }
  saveStrings("data/config.boxes",data);
}

void close(){
  saveData();    // This could prevent data lost
}
