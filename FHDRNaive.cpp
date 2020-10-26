#include<cstring>
#include<iostream>
#include<random>

using namespace std;

class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
    memset(data, 0, 1920*1080*3);  
  }
  
  void
  setPixel(unsigned int x, unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b) {
      if( x >= 1920 || y >= 1080) {
        return;
      }
      data[x][y][0] = r;
      data[x][y][1] = g;
      data[x][y][2] = b;
  }
  
  void
  write(void) {
   int x = 0;
   int y = 0;
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      cout<<data[x][y][0];
      cout<<data[x][y][1];
      cout<<data[x][y][2];
     } 
   }
  }
  
 void drawLine( 
  unsigned int x1, unsigned int y1, 
   unsigned int x2, unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b) {
    
      double m; //slope
      double be;
      double aux;
      double x = 0;
      double y = 0;     
      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);
      
      if(x2>x1 && y2>y1) { // signs check-in because x1,x2,y1,y2 are unsigned so cant be negative
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      } 
      
      if(x1>x2 && y2>y1){
      	 m = (double)(y2-y1)/(double)(x1-x2);
      }
      
      if(x2>x1 && y1>y2){
      	 m = (double)(y1-y2)/(double)(x2-x1);
      }
      
      if(x1>x2 && y1>y2){
      	 m = (double)(y1-y2)/(double)(x1-x2);
      }
      
      aux = m;
      //cout<<aux<<"\n";
      //cout<<m<<"\n";
      
      if(x2>x1 && y2>y1 && aux<=1 && aux>=0) { //1st Octant
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      } 
      
      if(x2>x1 && y2>y1 && aux>1) { //2nd octant
      	 m = (double)(x2-x1)/(double)(y2-y1); 
      	 be = (double)x1 - (m*y1); 
      } 
      
      if(x1>x2 && y2>y1 && aux>1){ //3rd octant
      	 m = (double)(x1-x2)/(double)(y2-y1);
      	 be = (double)x1 + (m*y1); 
      }
      
      if(x1>x2 && y2>y1 && aux<=1 && aux>=0){ //4th octant
      	 m = (double)(y2-y1)/(double)(x1-x2);
      	 be = (double)y1 + (m*x1); 
      }
   
      if(y1>y2 && x2>x1 && aux<=1 && aux>=0){ //5th octant
      	 m = (double)(y1-y2)/(double)(x2-x1); 
      	 be = (double)y1 + (m*x1); 
      }
      
      if(y1>y2 && x2>x1 && aux>1){ //6th octant
      	 m = (double)(x2-x1)/(double)(y1-y2); 
      	 be = (double)x1 + (m*y1); 
      }
      
      if(y1>y2 && x1>x2 && aux>1){ //7th octant
      	 m = (double)(x1-x2)/(double)(y1-y2); 
      	 be = (double)x1 - (m*y1);
      }
      
      if(y1>y2 && x1>x2 && aux<=1 && aux>=0){ //8th octant
      	 m = (double)(y1-y2)/(double)(x1-x2); 
      	 be = (double)y1 - (m*x1);
      }
      
      	//cout<<"m2: "<<m<<"\n";
      	//cout<<"aux2: "<<aux<<"\n";
       //be = (double)y1 - (m*x1); 
 
       if(x2>x1 && y2>y1 && aux<=1 && aux>0){    // 1st octant drawing
      		y = m*x1 + be; 
      		for( x=x1+1 ; x<x2 ; x++) {
      			y = m*x + be;
        		setPixel(x, y, r, g, b); 
   		}	
   	}
   	
   	if(x2>x1 && y2>y1 && aux>1){    // 2nd octant drawing
      		x = m*y1 + be; 
      		for( y=y1+1 ; y<y2 ; y++) {
      			x = m*y + be;
        		setPixel(x, y, r, g, b); 
   		}	
   	}
   	
       
       if(x1>x2 && y2>y1 && aux>1) {	// 3rd octant drawing 
       	x = m*y1 + be; 
      		for( y=y2-1 ; y>y1 ; y--) {
        		x = ((-1)*(m*y)) + be;
        		setPixel(x, y, r, g, b); 
   		}	
      }
      
       if(x1>x2 && y2>y1 && aux<=1 && aux>=0) {	// 4th octant drawing 
       	y = m*x1 + be; 
      		for( x=x1-1 ; x>x2 ; x--) {
        		y = ((-1)*(m*x)) + be;
        		setPixel(x, y, r, g, b); 
   		}	
      }
      
      if(y1>y2 && x2>x1 && aux<=1 && aux>=0) {  //5th octant drawing  
       	y = (m*x1) + be;
      		for( x=x1+1 ; x<x2 ; x++) {
        		y = ((-1)*(m*x)) + be;
        		setPixel(x, y, r, g, b); 
   		}	
      }
      
      if(y1>y2 && x2>x1 && aux>1) { //6th octant drawing   
       	x = (m*y2) + be;
      		for( y=y2+1 ; y<y1 ; y++) {
        		x = ((-1)*(m*y)) + be;
        		setPixel(x, y, r, g, b); 
   		}	
      }
      
      if(x1>x2 && y1>y2 && aux>1){  //7th octant drawing  
      		x = m*y1 + be; 
      		for( y=y2+1 ; y<y1 ; y++) {
      			x = m*y + be;
        		setPixel(x, y, r, g, b); 
   		}
   	}
   	
   	if(x1>x2 && y1>y2 && aux<=1 && aux>=0){  //8th octant drawing    
      		y = m*x1 + be; 
      		for( x=x2+1 ; x<x1 ; x++) {
      			y = m*x + be;
        		setPixel(x, y, r, g, b); 
   		}
   	}
      

 }  	
};

/* testing */
int main(void) {
 FHDRaster * raster = new FHDRaster();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;
 
 raster->drawLine(0,0, 1000,  500, 255, 255, 255);
 raster->drawLine(1000, 0, 0, 500, 255, 255, 255);
 raster->drawLine(0, 0, 100, 1000, 255, 255, 255);
 raster->drawLine(0, 0, 100, 1000, 255, 255, 255);
 raster->drawLine(1919, 0, 1819, 1000, 255, 255, 255);
 raster->drawLine(0, 1000, 100, 0, 255, 255, 255);
 raster->drawLine(1919, 1000, 1819, 0, 255, 255, 255);
 raster->write();
 
 return 0;
}
