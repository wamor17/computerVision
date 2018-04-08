#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

int otsu(Mat image);

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector 50
  lowThreshold = 30;
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  src.copyTo( dst, detected_edges);
  imshow( window_name, detected_edges );
 }


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( argv[1] );

  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
  }

int otsu(Mat image){
//  Variables a utilizar
  float h[256], N=(image.rows)*(image.cols), w0=0, w1=0, u0=0, u1=0, sigmaB=0, mayor=0;
  int umbral=0, L = 255, aux=0, aux1=0;

  for(int i=0; i<L; i++){
    h[i] = 0;
  }
//  Se obtienen la ocurrencia de cada nivel de gris
  for(int i=0; i<image.rows; i++){
    for(int j=0; j<image.cols; j++){
      h[ image.data[i*image.cols + j] ]++;
    }
  }
//  Suma auxiliar para obtener el valor de u1
  for(int i=1; i<L; i++)
    aux1 += i*h[i];
//  Obtenemos el valor de sigmaB para cada valor de k
  for (int k=1; k<L; k++){
    w0 += h[k];
    w1 = N-w0;

    aux += k*h[k];
    u0 = aux/w0;
    u1 = (aux1-aux)/w1;

    sigmaB = (w0*w1)*pow((u1-u0),2);
    if(sigmaB > mayor){
      mayor = sigmaB;
      umbral = k;
    }
  }

  return umbral;
}
