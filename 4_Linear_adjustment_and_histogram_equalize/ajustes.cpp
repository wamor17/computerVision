#include <iostream>
#include <stdio.h>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat im;

void histogramaIn(Mat image);
void histogramaOut(Mat image);
void ajuste_lineal(Mat image);
void ecualizacion(Mat image, float H[][256]);
void plotR(float H[][256]);
void plotG(float H[][256]);
void plotB(float H[][256]);
void plotGray(float H[][256]);

int main( int argc, char** argv ){

	im = imread(argv[1], 1);
//    im = imread("build/images/fuente.png", 1);

	if( !im.data ) {
	cout <<" Take care how type the picture name" <<endl ;
	return -1;
	}

	histogramaIn(im);
//	ajuste_lineal(im);

	return 0;
}

void histogramaIn(Mat image){
	int channels=image.channels();

//  Vector del histograma inicializado en cero y los vectores para los valores máximo y mínimo
	float h[3][256];
	for(int c=0; c<channels; c++){
		for(int i=0; i<256; i++){
			h[c][i] = 0;
		}
	}

//	Se obtienen la ocurrencia de cada nivel de gris de los tres canales y los valores máximo y mínimo para cada histograma
	for(int c=0; c<channels; c++){
		for(int j=0; j<image.cols; j++){
			for(int i=0; i<image.rows; i++){
				h[c][image.at<Vec3b>(j,i)[c]]++;
			}
		}
	}

//  Se procede a normalizar el histograma
	float n = (image.rows)*(image.cols), Hm[3][256];
	int porc=255*5;

	for(int c=0; c<channels; c++)
		for(int i=0; i<256; i++){
			Hm[c][i] = round((h[c][i]/n)*porc);
	}

/*	if(channels > 2){
		plotR(Hm);
		plotG(Hm);
		plotB(Hm);
	}else if( channels == 0)
		plotGray(Hm);*/

	ecualizacion(image, h);
}

void histogramaOut(Mat image){
//  Vector del histograma inicializado en cero
	float h[3][256];
	for(int c=0; c<3; c++){
		for(int i=0; i<256; i++)
				h[c][i] = 0;
	}

//	Se obtienen la ocurrencia de cada nivel de gris de los tres canales
	for(int c=0; c<3; c++){
		for(int j=0; j<image.cols; j++){
			for(int i=0; i<image.rows; i++){
				h[c][image.at<Vec3b>(j,i)[c]]++;
			}
		}
	}

//  Se procede a normalizar el histograma
	float n = (image.rows)*(image.cols), Hm[3][256], Hn[3][256];
	int porc=255*5;

	for(int c=0; c<3; c++)
		for(int i=0; i<256; i++){
			Hm[c][i] = round((h[c][i]/n)*porc);
			Hn[c][i] = round(h[c][i]/n);
	}

	plotR(Hm);
	plotG(Hm);
	plotB(Hm);
}

void ajuste_lineal(Mat image){
	int Inmin, Inmax, factor, rows=image.rows, cols=image.cols, channels=image.channels();
	Mat newImage = image.clone();

	cout<<"\n Valor mínimo = ";cin>>Inmin;
	cout<<" Valor máximo = ";cin>>Inmax;
	factor = 255/(Inmax-Inmin);

	for(int j=0; j<rows; j++){
		for(int i=0; i<cols; i++){
			if( (newImage.data[j*cols+i]-Inmin)*factor > 255 )
				newImage.data[j*cols+i] = 255;
				else if( (image.data[j*cols+i]-Inmin)*factor < 0 )
					newImage.data[j*cols+i] = 0;
				else
					newImage.data[j*cols+i] = (newImage.data[j*cols+i]-Inmin)*factor;
		}
	}

	namedWindow("Imagen original", WINDOW_AUTOSIZE);
	imshow("Imagen original", image);
	waitKey(0);
	namedWindow("Imagen corregida", WINDOW_AUTOSIZE);
	imshow("Imagen corregida", newImage);
	waitKey(0);
}

void ecualizacion(Mat image, float H[][256]){
	Mat newImage = image.clone();
	float dimension=newImage.rows*newImage.cols, Ha[3][256];
	int rows=newImage.rows, cols=newImage.cols, channels=newImage.channels();

//	Copia del histograma normalizado
	for(int c=0; c<3; c++)
		for(int i=0; i<256; i++){
			Ha[c][i] = H[c][i];
	}

	cout<<"\n\n\n";
//	Histograma acumulado
	for(int c=0; c<channels; c++){
		for(int i=1; i<256; i++){
			Ha[c][i] = (Ha[c][i-1] + Ha[c][i]);
		}
	}

//	Modificación de la imagen a partir a la funcion de transformación
	for(int j=0; j<rows; j++){
		for(int i=0; i<cols; i++)
			for(int c=0; c<channels; c++){
			newImage.at<Vec3b>(j,i)[c] = round((255/dimension)*Ha[c][ image.at<Vec3b>(j,i)[c] ]);
		}
	}

	namedWindow("Imagen original", WINDOW_AUTOSIZE);
	imshow("Imagen original", image);
	namedWindow("Imagen aplicando la ecualización del histograma", WINDOW_AUTOSIZE);
	imshow("Imagen aplicando la ecualización del histograma", newImage);
	waitKey(0);
}

void plotR(float H[][256]){
	Mat image(280, 256, CV_8UC1, Scalar(255));
	int dif=0;

	for(int j=0; j<image.cols; j++){
		dif = 256 - H[0][j];
		for(int i=0; i<image.rows; i++){
			if(i >= dif && i <= image.rows-25){
				image.data[i*image.cols + j] = 0;
			  }else{
				 if(i > image.rows-25 && i <= image.rows-20 )
				    image.data[i*image.cols + j] = 220;
				 else if(i > image.rows-20 )
					image.data[i*image.cols + j] = j;
			}
		}
		dif=0;
	}

	cout<<"\n\n";
	namedWindow("Histograma del canal Rojo", WINDOW_AUTOSIZE);
	imshow("Histograma del canal Rojo", image);
	waitKey(0);
}

void plotG(float H[][256]){
	Mat image(280, 256, CV_8UC1, Scalar(255));
	int dif=0;

	for(int j=0; j<image.cols; j++){
		dif = 256 - H[1][j];
		for(int i=0; i<image.rows; i++){
			if(i >= dif && i <= image.rows-25){
				image.data[i*image.cols + j] = 0;
			  }else{
				 if(i > image.rows-25 && i <= image.rows-20 )
				    image.data[i*image.cols + j] = 220;
				 else if(i > image.rows-20 )
					image.data[i*image.cols + j] = j;
			}
		}
		dif=0;
	}

	cout<<"\n\n";
	namedWindow("Histograma del canal Verde", WINDOW_AUTOSIZE);
	imshow("Histograma del canal Verde", image);
	waitKey(0);
}

void plotB(float H[][256]){
	Mat image(280, 256, CV_8UC1, Scalar(255));
	int dif=0;

	for(int j=0; j<image.cols; j++){
		dif = 256 - H[2][j];
		for(int i=0; i<image.rows; i++){
			if(i >= dif && i <= image.rows-25){
				image.data[i*image.cols + j] = 0;
			  }else{
				 if(i > image.rows-25 && i <= image.rows-20 )
				    image.data[i*image.cols + j] = 220;
				 else if(i > image.rows-20 )
					image.data[i*image.cols + j] = j;
			}
		}
		dif=0;
	}

	cout<<"\n\n";
	namedWindow("Histograma del canal Azul", WINDOW_AUTOSIZE);
	imshow("Histograma del canal Azul", image);
	waitKey(0);
}

void plotGray(float H[][256]){

	Mat image(280, 256, CV_8UC1, Scalar(255));
	float dif=0;

	for(int j=0; j<image.cols; j++){
		dif = 255 - H[0][j];
		for(int i=0; i<image.rows; i++){
			if(i >= dif && i <= image.rows-25){
				image.data[i*image.cols + j] = 0;
			  }else{
				 if(i > image.rows-25 && i <= image.rows-20 )
				    image.data[i*image.cols + j] = 220;
				 else if(i > image.rows-20 )
					image.data[i*image.cols + j] = j;
			}
		}
		dif=0;
	}

	cout<<"\n\n";
	namedWindow("Histograma de la imagen en escala de grises", WINDOW_AUTOSIZE);
	imshow("Histograma de la imagen en escala de grises", image);
	waitKey(0);
}

