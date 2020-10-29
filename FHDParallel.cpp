#include<cstring>
#include<iostream>
#include <thread> 
#include<random>
#include <functional>

using namespace std;
unsigned int ix [6];
unsigned int iy [6];

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
      
      aux = m;
      
      if(x2>x1 && y2>y1 && aux<=1 && aux>=0) { //1st Octant 
      	 m = (double)(y2-y1)/(double)(x2-x1); 
      	 be = (double)y1 - (m*x1); 
      	 dx = x2 - x1;
      	 dy = y2 - y1;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx;     
      } 
      
      if(x2>x1 && y2>y1 && aux>1) { //2nd Octant
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
      
      if(x1>x2 && y1>y2 && aux>1){ //7th Octant
      	 m = (double)(x1-x2)/(double)(y1-y2);
      	 be = (double)x1 - (m*y1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dx;          
      	 updateRight = 2*dx-2*dy;  
      }
      
      if(x1>x2 && y1>y2 && aux<=1 && aux>=0){ //8th Octant
      	 m = (double)(y1-y2)/(double)(x1-x2);
      	 be = (double)y1 - (m*x1);
      	 dx = x1 - x2;
      	 dy = y1 - y2;  
      	 p = 2*dy-dx; 
      	 updateUp    = 2*dy;          
      	 updateRight = 2*dy-2*dx;  
      }
         

      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);     
                                   
      
      if(x2>x1 && y2>y1 && aux>=0 && aux<=1){    //1st Octant Drawing
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
   	
   	if(x2>x1 && y2>y1 && aux>1){    //2nd Octant drawing
      	 x = m*y1 + be;               
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
      
      if(x1>x2 && y1>y2 && aux>1) {    //7th Octant Drawing
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
      	
      if(x1>x2 && y1>y2 && aux>=0 && aux<=1) {    //8th Octant drawing
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
   }
};

class divideThreads {
 public:
  divideThreads(void) {
    //memset(data, 0, 1920*1080*3);  
  }
 
  void divide(unsigned int x1, 
  	     unsigned int y1,
  	     unsigned int x2,
  	     unsigned int y2){
  	     
  	     	 double m, be;
  		 if(x2>x1 && y2>y1) { 
      	 		m = (double)(y2-y1)/(double)(x2-x1);
      	 		be = (double)y1 - (m*x1); 
      	 		ix[2] =  round((x2+x1)/2);
      	 		ix[0] =  round((x1+ix[2])/2);
      	 		ix[4] =  round((x2+ix[2])/2);
      	 		ix[1] =  ix[0]+1;
      	 		ix[3] =  ix[2]+1;
      	 		ix[5] =  ix[4]+1;
      	 		
      	 		for (int i=0; i<6; i++){
      	 			iy[i] = m*ix[i] + be;		
      	 		}
      	 		
      		} 
      
      		if(x1>x2 && y2>y1){
      	 		m = (double)(y2-y1)/(double)(x1-x2);
      	 		be = (double)y1 - (m*x1);
      	 		ix[2] =  round((x2+x1)/2);
      	 		ix[0] =  round((x1+ix[2])/2);
      	 		ix[4] =  round((x2+ix[2])/2);
      	 		ix[1] =  ix[0]+1;
      	 		ix[3] =  ix[2]+1;
      	 		ix[5] =  ix[4]+1;
      	 		
      	 		for (int i=0; i<6; i++){
      	 			iy[i] = m*ix[i] + be;		
      	 		}
      		}
      
      		if(x2>x1 && y1>y2){
      	 		m = (double)(y1-y2)/(double)(x2-x1);
      	 		be = (double)y1 - (m*x1);
      	 		ix[2] =  round((x2+x1)/2);
      	 		ix[0] =  round((x1+ix[2])/2);
      	 		ix[4] =  round((x2+ix[2])/2);
      	 		ix[1] =  ix[0]+1;
      	 		ix[3] =  ix[2]+1;
      	 		ix[5] =  ix[4]+1;
      	 		
      	 		for (int i=0; i<6; i++){
      	 			iy[i] = m*ix[i] + be;		
      	 		}
      		}
      
      		if(x1>x2 && y1>y2){
      	 		m = (double)(y1-y2)/(double)(x1-x2);
      	 		be = (double)y1 - (m*x1);
      	 		ix[2] =  round((x2+x1)/2);
      	 		ix[0] =  round((x1+ix[2])/2);
      	 		ix[4] =  round((x2+ix[2])/2);
      	 		ix[1] =  ix[0]+1;
      	 		ix[3] =  ix[2]+1;
      	 		ix[5] =  ix[4]+1;
      	 		
      	 		for (int i=0; i<6; i++){
      	 			iy[i] = m*ix[i] + be;		
      	 		}
      		}     
  	     
	}
};

/* testing */
int main(void) {
 FHDRaster * raster = new FHDRaster();
 divideThreads * divisor = new divideThreads();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned int x1 = 0;
 unsigned int y1 = 0;
 unsigned int x2 = 1000;
 unsigned int y2 = 500;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;

 divisor -> divide(x1,y1,x2,y2);
 
 std::thread t1(&FHDRaster::drawLine,raster,x1,y1,ix[0],iy[0],255,255,255);
 std::thread t2(&FHDRaster::drawLine,raster,ix[1],iy[1],ix[2],iy[2],255,255,255);
 std::thread t3(&FHDRaster::drawLine,raster,ix[3],iy[3],ix[4],iy[4],255,255,255);
 std::thread t4(&FHDRaster::drawLine,raster,ix[5],iy[5],x2,y2,255,255,255);
 
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 
 raster->write();

 return 0;
}
