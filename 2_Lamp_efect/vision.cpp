#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

void enfoque(int filas, int columnas, Mat image);

int main( int argc, char** argv ){
	
  if( argc != 2) {
    cout <<" Usage: mostrar_imagen <archivo de imagen>" << endl;
    return -1;
  }

  Mat im;
  im = imread(argv[1], 1);

  if( !im.data ) {
    cout <<  "Could not open or find the image" <<endl ;
    return -1;
  }
  
  int filas = 768;
  int columnas = 574;
  enfoque(filas/2,columnas/2,im); 
   
  return 0;
}

void enfoque(int filas, int columnas, Mat image){
//  im.data[i*512 + j] = 255;

  circle( image, Point(filas,columnas), 50, Scalar(255,255,255 ), 1, LINE_8 );
  
  namedWindow("Display image", WINDOW_AUTOSIZE);
  imshow("Display image", image);
  waitKey(0);	
}

