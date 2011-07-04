class Element{
  PVector oCenter;
  PVector iCenter;
  
  float rad = 0;
  float ang = 0; 
  PVector pos;
  
  float north = 0;
    
  int w,h;
  PImage iPart;
  String iPath;
  boolean mirror;
  
  Element(PVector _center, String _imagePath){
    iPath = _imagePath;
    iPart = loadImage(iPath);
    w = iPart.width;
    h = iPart.height;
    iCenter = new PVector(-w/2,-h/2);
    calcPos(_center,0);
    mirror = false;
  }
  
  Element(PVector _center, String _s,float _rad, float _ang, int _iX, int _iY, boolean _mirror){
    rad = _rad;
    ang = _ang;
    iPath = _s;
    println("Loading " + iPath);
    iPart = loadImage(iPath);
    w = iPart.width;///2;
    h = iPart.height;///2;
    mirror = _mirror;
    iCenter = new PVector(_iX,_iY);
    calcPos(_center,0);
  }
  
  void calcPos(PVector _center,float _north){
    north = _north;
    oCenter = _center;
    
    pos = new PVector(calcX(),calcY());
    pos.add(oCenter);
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
    calcPos(oCenter,north);
  }
  
  float calcRad(PVector _pos){
    float distance = _pos.dist(oCenter);
    return distance;
  }
  
  float calcAng(PVector _pos){
    _pos.sub(oCenter);
    return _pos.heading2D();
  }
  
  void render(){
    pushMatrix();
      translate(pos.x, pos.y);
      rotate(north);
      
      if (!mirror){
        image(iPart,iCenter.x,iCenter.y,w,h);
      } else {
        scale(-1,1);
        image(iPart,iCenter.x+w,iCenter.y,-w,h);
      }  
    popMatrix();
  }

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

