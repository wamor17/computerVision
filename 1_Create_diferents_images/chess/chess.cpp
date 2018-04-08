#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	
  Mat image(512, 512, CV_8UC1, Scalar(0));
  
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
  waitKey(0);

  return 0;
}
