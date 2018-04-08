#include <iostream>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void histograma(Mat im);
void ajuste_lineal(Mat image);
void plot(float H[]);

int main( int argc, char** argv ){

	if( argc != 2) {
	cout <<" Type currently the picture name and extension " << endl;
	return -1;
	}

	Mat im;
	im = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if( !im.data ) {
	cout <<" Take care how type the picture name" <<endl ;
	return -1;
	}

	histograma(im);
	ajuste_lineal(im);

	return 0;
}

void histograma(Mat im){
	
	Mat image;
	cvtColor(im,image,CV_BGR2GRAY);
	
//  Vector del histograma inicializado en cero
	int h[256];
	for(int i=0; i<256; i++)
		h[i] = 0;

//	Se obtienen la ocurrencia de cada nivel de gris
	int num=0;
	for(int j=0; j<image.cols; j++){
		for(int i=0; i<image.rows; i++){
			num = image.data[i*image.cols + j];
			h[num]++;
		}
	}
	
//  Se normaliza y redondea el histograma 
	float n = (image.rows)*(image.cols), Hn[256];
	int porc=255*50;
	
	for(int i=0; i<256; i++){
		if( ((h[i]/n)*porc)-floor((h[i]/n)*porc) < ceil((h[i]/n)*porc)-((h[i]/n)*porc) )
			Hn[i] = floor((h[i]/n)*porc);
		  else
		    Hn[i] = ceil((h[i]/n)*porc);
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

void ajuste_lineal(Mat image){
	
	int Inmin, Inmax, factor, rows=image.rows, cols=image.cols;
	Mat newImage = image.clone();
	
	cout<<"\n Valor mínimo = ";cin>>Inmin;
	cout<<" Valor máximo = ";cin>>Inmax;
	factor = 255/(Inmax-Inmin);
	
	for(int j=0; j<rows; j++){
		for(int i=0; i<cols; i++){
			for(int c=0; c<3; c++)
				if( (image.at<Vec3b>(j,i)[c]-Inmin)*factor > 255 )
					newImage.at<Vec3b>(j,i)[c] = 255;
					else if( (image.at<Vec3b>(j,i)[c]-Inmin)*factor < 0 )
						newImage.at<Vec3b>(j,i)[c] = 0;
					else
						newImage.at<Vec3b>(j,i)[c] = (image.at<Vec3b>(j,i)[c]-Inmin)*factor;
		}
	}
	
	namedWindow("Imagen corregida", WINDOW_AUTOSIZE);	
	imshow("Imagen corregida", newImage);
	waitKey(0);
	histograma(newImage);
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

