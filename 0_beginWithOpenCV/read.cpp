#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv ){
	
  if( argc != 2) {
    cout <<" Usage: mostrar_imagen <archivo de imagen>" << endl;
    return -1;
  }

  Mat image;
  image = imread(argv[1], 1);

  if(! image.data ) {
    cout <<  "Could not open or find the image" << std::endl ;
    return -1;
  }
  
  namedWindow("Display image", WINDOW_AUTOSIZE);
  imshow("Display image", image);
  waitKey(0);
	
  return 0;
}
