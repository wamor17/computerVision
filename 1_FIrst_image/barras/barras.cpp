#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/*			R G B
Negro		0 0 0
Azul		0 0 1
Verde		0 1 0
Cyan		0 1 1
Rojo		1 0 0
Amarillo 	1 0 1
Rosa		1 1 0
Blanco		1 1 1
*/

int main(int argc, char** argv){
	
  Mat image(512, 512, CV_8UC3, Scalar(0,0,0));
  
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
  waitKey(0);

  return 0;
}
