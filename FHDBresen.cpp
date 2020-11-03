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
      unsigned int x = 0;
      unsigned int y = 0;
      int dx,dy,p,updateUp,updateRight;
        
      if(x2>x1 && y2>y1) { // signs check-in because x1,x2,y1,y2 are unsigned so can't be negative
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
      
      if(x1==x2 || y1==y2 ){
      	 m = 0;
      }
      
      
      
      aux = m;
      
      if(x2>x1 && y2>y1 && aux<1 && aux>=0) { //1st Octant 
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx;     
      } 
      
      if(x2>x1 && y2>y1 && aux>=1) { //2nd Octant
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy; 
      }  
      
      if(x1>x2 && y2>y1 && aux>1){ //3th octant
      	 m = (double)(x1-x2)/(double)(y2-y1);
      	 be = (double)x1 - (m*y1); 
      	 dx = x1 - x2;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy; 
      }
      
      if(x1>x2 && y2>y1 && aux<=1 && aux>=0){ //4rd octant
      	 m = (double)(y2-y1)/(double)(x1-x2);
      	 be = (double)y1 - (m*x1); 
      	 dx = x1 - x2;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx; 
      }
      
      if(x2>x1 && y1>y2 && aux<=1 && aux>=0){ //5th octant
      	 m = (double)(y1-y2)/(double)(x2-x1);
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx; 
      }
       if(x2>x1 && y1>y2 && aux>1){ //6th octant
      	 m = (double)(x2-x1)/(double)(y1-y2);
      	 be = (double)x1 - (m*y1);
      	 dx = x2 - x1;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy;  
      }
      
      if(x1>x2 && y1>y2 && aux>=1){ //7th Octant
      	 m = (double)(x1-x2)/(double)(y1-y2);
      	 be = (double)x1 - (m*y1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy;  
      }
      
      if(x1>x2 && y1>y2 && aux<1 && aux>=0){ //8th Octant
      	 m = (double)(y1-y2)/(double)(x1-x2);
      	 be = (double)y1 - (m*x1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx;  
      }
      if(y1==y2 && aux==0 ){
      	 m = 0;
      	 be = (double)x1 - (m*y1); 
      }
      
      if(x1==x2 && aux==0){
      	 m = 0;
      	 be = (double)y1 - (m*x1);
      }
         

      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);     
                                   
      
      if(x2>x1 && y2>y1 && aux>=0 && aux<1){    //1st Octant Drawing
      	 y = m*x1 + be;               
      	for( x = x1 + 1 ; x < x2 ; x++ ) {   
        	if( p < 0 ) { 
          		y++;
          		p += updateUp;    
        	} else {
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		} 	
   	}
   	
   	if(x2>x1 && y2>y1 && aux>=1){    //2nd Octant drawing
      	 x = m*y1 - be;               
      	for( y = y1 + 1 ; y < y2 ; y++ ) {   
        	if( p < 0 ) { 
        		
          		p += updateUp;    
        	} else {
        		x++;
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		}  	
   	}
   	
       
       if(x1>x2 && y2>y1 && aux>1) {    //3rd Octant drawing
         x = m*y1 + be;               
      	for( y = y1 + 1 ; y < y2 ; y++ ) {   
        	if( p < 0 ) { 
        		
          		p += updateUp;    
        	} else {
        		x--;
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		}  
   	}	
      
      
      if(x1>x2 && y2>y1 && aux>=0 && aux<=1) {    //4th Octant drawing
         y = m*x1 + be; 
      	 for( x=x1-1 ; x>x2 ; x--) {
        	if( p < 0 ) { 
          		y++;
          		p += updateUp;    
        	} else {
          		p += updateRight;
        	} 
        	setPixel(x, y, r, g, b); 
      		} 
   	}	
       
       if(x2>x1 && y1>y2 && aux>=0 && aux<=1) {    //5th octant drawing
       	y = m*x1 + be;
      		for( x=x1+1 ; x<x2 ; x++) {
        	 if( p < 0 ) { 
          		y--;
          		p += updateUp;    
        	 } else {
          		p += updateRight;
        	  } 
        	  setPixel(x, y, r, g, b); 
      			}	 
   		}	
      
      if(x2>x1 && y1>y2 && aux>1) {    //6th octant drawing
       	x = m*y1 + be;               
      	 	for( y = y1-1; y>y2 ; y-- ) {   
        		if( p < 0 ) { 
          			p += updateUp;    
        		} else {
        			x++;
          			p += updateRight;
        		} 
        		setPixel(x, y, r, g, b); 
      		}	
      }
      
      if(x1>x2 && y1>y2 && aux>=1) {    //7th Octant Drawing
       	x = m*y1 + be;               
      	 	for( y = y1-1; y>y2 ; y-- ) {   
        		if( p < 0 ) { 
          			p += updateUp;    
        		} else {
        			x--;
          			p += updateRight;
        		} 
        		setPixel(x, y, r, g, b); 
      		}	
      }
      	
      if(x1>x2 && y1>y2 && aux>=0 && aux<1) {    //8th Octant drawing
       	y = m*x1 - be;
      		for( x=x1-1 ; x>x2 ; x--) {
        		if( p < 0 ) { 
          		y--;
          		p += updateUp;    
        	 } else {
          		p += updateRight;
        	  } 
        	  setPixel(x, y, r, g, b);
   		}	 
   	}
   	
   	if(y1==y2 && aux==0) {    
       	x = m*y1 + be;
       	if(x1>x2){
      		for( x=x2+1 ; x<x1 ; x++) {
        	  setPixel(x, y1, r, g, b);
   		}
   		}
   		if(x2>x1){
      		for( x=x1+1 ; x<x2 ; x++) {
        	  setPixel(x, y1, r, g, b);
   		}
   		}	 
   	}
   	
   	if(x1==x2 && aux==0) {  
       	y = m*x1 + be;
       	if(y1>y2){
      		for( y=y2+1 ; y<y1 ; y++) {
        	  setPixel(x1, y, r, g, b);
   		}
   		}
   		if(y2>y1){
      		for( y=y1+1 ; y<y2 ; y++) {
         		  setPixel(x1, y, r, g, b);
   		}
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
 /*raster->drawLine(0,0, 1000,  500, 255, 255, 255);
 raster->drawLine(1000, 0, 0, 500, 255, 255, 255);
 raster->drawLine(0, 0, 100, 1000, 255, 255, 255);
 raster->drawLine(0, 0, 100, 1000, 255, 255, 255);
 raster->drawLine(1919, 0, 1819, 1000, 255, 255, 255);
 raster->drawLine(0, 1000, 100, 0, 255, 255, 255);
 raster->drawLine(1919, 1000, 1819, 0, 255, 255, 255);*/
 raster -> drawLine(300,0,600,300,255,255,255);
 raster->write();

 return 0;
}
