#include <iostream>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat image, img;

void thresholding(Mat image, int umbral);
int otsu(Mat image);

int main( int argc, char **argv){

	image = imread(argv[1], 1);
    cvtColor( image, img, CV_BGR2GRAY );

	if(!img.data){
		cout<<"Take care how type the picture name"<<endl;
		return -1;
	}

	cout<<"\n\n Umbral -> "<<otsu(img)<<endl<<endl;
	thresholding(img, otsu(img) );

	return 0;
}

int otsu(Mat image){
//  Variables a utilizar
	float h[256]={0}, N=(image.rows)*(image.cols), w0=0, w1=0, u0=0, u1=0, sigmaB=0, mayor=0;
	int umbral=0, L=255, aux=0, aux1=0;

//	Se obtienen la ocurrencia de cada nivel de gris
	for(int i=0; i<image.rows; i++){
		for(int j=0; j<image.cols; j++){
			h[ image.data[i*image.cols + j] ]++;
		}
	}

//	Suma auxiliar para obtener el valor de u1
	for(int i=1; i<L; i++)
		aux1 += i*h[i];

//	Obtenemos el valor de sigmaB para cada valor de k
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

void thresholding(Mat image, int umbral){
	Mat newImage = image.clone();
	int rows = newImage.rows, cols = newImage.cols;

	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			if(newImage.data[i*cols + j] < umbral)
				newImage.data[i*cols + j] = 0;
			else
				newImage.data[i*cols + j] = 255;
		}
	}

	namedWindow("Imagen original",WINDOW_AUTOSIZE);
	imshow("Imagen original",image);
	namedWindow("Humbralización de una imagen");
	imshow("Humbralización de una imagen",newImage);
	waitKey(0);
}
