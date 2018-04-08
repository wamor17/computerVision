#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void barras(Mat image);
void blackImage();
void chess();

int main(int argc, char** argv){
	
  Mat im(512, 512, CV_8UC3, Scalar(0,0,0));

//  chess();
//  barras(im);
  blackImage();
  
  waitKey(0);    
  return 0;
}

void blackImage(){
  Mat image(512, 512, CV_8UC3, Scalar(255,255,255));

  namedWindow("Imagen con todos los pixeles en bajo", WINDOW_AUTOSIZE);
  imshow("Imagen con todos los pixeles en bajo", image);	
}


void barras(Mat image){

  for(int k=0; k<3; k++){
	  for(int i=0; i<512; i++){
			for(int j=0; j<512; j++){
					// Azul
					if(k == 0){
						if( j > 64 && j <= 128 )
							image.data[i*512*3 + j*3 + k] = 255;
					}
					// Cyan
					if(k == 0 || k == 1){
						if( j > 128	 && j < 192 )
							image.data[i*512*3 + j*3 + k] = 255;
					}
					// Verde
					if(k == 1){
						if( j >= 192 && j < 256 )
							image.data[i*512*3 + j*3 + k] = 255;
					}
					// Amarillo
					if(k == 1 || k == 2){
						if( j >= 256	 && j < 320 )
						image.data[i*512*3 + j*3 + k] = 255;
					}
					// Rojo
					if(k == 2){
						if( j >= 320	 && j < 384  )
						image.data[i*512*3 + j*3 + k] = 255;
					}
					// Rosa
					if(k == 0 || k == 2){
						if( j >= 384	 && j < 448  )
						image.data[i*512*3 + j*3 + k] = 255;
					}
					// Blanco
					if( j >= 448 && j <= 511 )
						image.data[i*512*3 + j*3 + k] = 255;
			}
		}
  }
  
  namedWindow("Barras de todos los colores con 8 bits", WINDOW_AUTOSIZE);
  imshow("Barras de todos los colores con 8 bits", image);
}

void chess(){
  Mat image(512,512,CV_8UC1,Scalar(0));

  for (int i=0; i<512; i++){
        for (int j=0; j<512; j++){
			if( i > 0 && i < 64  || i > 128 && i < 192 || i > 256 && i < 320 || i > 384 && i < 448 )
				if ( j > 0 && j < 64 || j > 128 && j < 192 || j > 256 && j < 320 || j > 384 && j < 448 ){
					image.data[i*512 + j] = 255;
				}
			
			if( i > 64 && i < 128  || i > 192 && i < 256 || i > 320 && i < 384 || i > 448 && i < 512 )
				if ( j > 64 && j < 128 || j > 192 && j < 256 || j > 320 && j < 384 || j > 448 && j < 512 ){
					image.data[i*512 + j] = 255;
				}
        }
  }
	
  namedWindow("Tablero de ajedrez", WINDOW_AUTOSIZE);
  imshow("Tablero de ajedrez", image);
}


