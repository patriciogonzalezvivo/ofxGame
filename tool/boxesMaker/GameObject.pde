class GameObject{
  PVector center;
  Element[] part;
  
  String objPath;
  float rad = 0;
  float ang = 0; 
  float north = 0;
  PVector pos = new PVector(0,0);
  
   GameObject(PVector _center, String _objPath){
    center = _center;
    loadObject(_objPath);
   }
   
   GameObject(PVector _center, String _objPath,float _rad, float _ang ){
    rad = _rad;
    ang = _ang;
    center = _center;
    loadObject(_objPath);
    calcPos(_center,0);
  }
  
  GameObject(PVector _center, String _objPath, PVector _pos){
    rad = 0;
    ang = 0;
    center = _center;
    loadObject(_objPath);
    calcPos(_center,0);
    moveTo((int)_pos.x,(int)_pos.y);
  }
  
   void loadObject(String _objPath){
      objPath = _objPath;
      String[] data = loadStrings("data/"+ objPath +"/config.box");    
  
      if ( data.length > 1 ){                 
        part = new Element[data.length];
        for(int i = 0; i < part.length; i++){ 
          String[] values = split(data[i],",");
          float rad = float(values[1]);
          float ang   = float(values[2]);
          int xI  = int(values[3]);
          int yI   = int(values[4]);
          boolean _mirror = ((int(values[5]))==1)?true:false;
          part[i] = new Element(pos, "data/"+ objPath + "/" + values[0], rad, ang, xI, yI, _mirror);
        } 
      }
   }
   
   void calcPos(PVector _center,float _north){
    north = _north;
    center = _center;
    
    pos = new PVector(calcX(),calcY());
    pos.add(center);
  }
  
  
  float calcX(){
    float posX = rad * cos(ang + north);
    return posX;
  }

  float calcY(){
    float posY = rad * sin(ang + north);
    return posY;
  }    
  
  void moveTo(int _x, int _y){
    PVector place = new PVector(_x,_y);
    rad = calcRad(place);
    ang = calcAng(place);
    calcPos(center,north);
  }
  
  float calcRad(PVector _pos){
    float distance = _pos.dist(center);
    return distance;
  }
  
  float calcAng(PVector _pos){
    _pos.sub(center);
    return _pos.heading2D();
  }
  
  void render(){
    pushMatrix();
      fill(255,255);
      translate(pos.x, pos.y);
      //scale(0.5,0.5);
      for(int i = 0; i< part.length; i++)
        part[i].render();
      
    popMatrix();
  }
  /*
  boolean isOver(PVector _loc){
    boolean over = false;
    
    for(int i = 0; i < part.length; i++)
      if ( part[i].isOver(_loc) )
         over = true;
      
    return over;
  }

  boolean isOver(int _x, int _y){
    return isOver(new PVector(_x,_y));
  }*/
  boolean isOver(PVector _loc){
    if (pos.dist(_loc) <= 25) return true;
    else return false;
  }

  boolean isOver(int _x, int _y){
    PVector _loc = new PVector(_x,_y);
    if (pos.dist(_loc) <= 25) return true;
    else return false;
  }  
}
