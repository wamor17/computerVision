#include <iostream>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat im;

void histograma(Mat image);
void plot(float H[]);

int main( int argc, char** argv ){

  im = imread(argv[1], CV_LOAD_IMAGE_COLOR);
//  im = imread("build/images/f14.png", CV_LOAD_IMAGE_COLOR);

  if( !im.data ) {
    cout <<" Take care how type the picture name" <<endl ;
    return -1;
  }

  histograma(im);
  return 0;
}

void histograma(Mat image){

	int channel;
	cout<<"\n Channel: ";cin>>channel;

//  Vector del histograma inicializado en cero
	int h[256];
	for(int i=0; i<256; i++)
		h[i] = 0;

//	Se obtienen la ocurrencia de cada nivel de gris
	int num=0;
	for(int j=0; j<image.rows; j++){
		for(int i=0; i<image.cols; i++){
			num = image.at<Vec3b>(j,i)[channel];
			h[num]++;
		}
	}

//  Se normaliza y redondea el histograma
	float n = (image.rows)*(image.cols), Hn[256];
	int porc=255*10;

	for(int i=0; i<256; i++){
		Hn[i] = round((h[i]/n)*porc);
	}

/*
//  Se imprime el histograma normalizado con cada uno de sus valores
	int cont=0;
	cout<<"\n";
	for(int i=0; i<256; i++){
		cont++;
		cout<<i<<"- "<<Hn[i]<<"  \t  ";

		if( cont==10){
		   cout<<"\n";
		   cont=0;
		}
	}
	cout<<"\n\n";
	cout<<" Dimensiones: "<<image.rows<<"x"<<image.cols<<"\n";
	cout<<" Pixeles: "<<image.rows*image.cols<<"\n";*/

	plot(Hn);
}

void plot(float H[]){
	Mat image(280, 256, CV_8UC1, Scalar(255));
	int dif=0;

	for(int j=0; j<image.cols; j++){
		dif = 256 - H[j];
		for(int i=0; i<image.rows; i++){
			if(i >= dif && i <= image.rows-25){
				image.data[i*image.cols + j] = 0;
			} else{
				if(i > image.rows-25 && i <= image.rows-20 )
				   image.data[i*image.cols + j] = 220;
				else if(i > image.rows-20 )
					image.data[i*image.cols + j] = j;
			}
		}
		dif=0;
	}

	cout<<"\n\n";
	namedWindow("Histograma de la imagen", WINDOW_AUTOSIZE);
	imshow("Histograma de la imagen", image);
	waitKey(0);
}

