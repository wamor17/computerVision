#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void edge(Mat img);
void plot(Mat image, Mat newImage);

int main(int argc, char **argv){

	if(argc != 2){
		cout<<"\n Type correctly the picture name and extension"<<endl;
		return -1;
	}

	Mat img, image;
	img = imread(argv[1], 1);
	cvtColor(img, image, CV_BGR2GRAY);

	if (!image.data){
		cout<<"\n Take car how type the picture name\n"<<endl;
		return -1;
	}

	edge(image);

	return 0;
}

void edge(Mat img){
//	GRADIENTE DE PREWITT
 	int PrewittX[3][3] = { {-1,0,1}, {-1,0,1}, {-1,0,1} };
	int PrewittY[3][3] = { {1,1,1}, {0,0,0}, {-1,-1,-1} };
	int Prewitt45[3][3] = { {-2,-1,0}, {-1,0,1}, {0,1,2} };
//	GRADIENTE DE SOBEL
 	int SobelX[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
	int SobelY[3][3] = { {1,2,1}, {0,0,0}, {-1,-2,-1} };
	int Sobel45[3][3] = { {-2,-2,0}, {-2,0,2}, {0,2,2} };
//	GRADIENTE DE ROBERTS
 	int SobelX[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
	int SobelY[3][3] = { {1,2,1}, {0,0,0}, {-1,-2,-1} };
	int Sobel45[3][3] = { {-2,-2,0}, {-2,0,2}, {0,2,2} };

	int imgIn[img.rows][img.cols], imgOutX[img.rows][img.cols], imgOutY[img.rows][img.cols], imgOut45[img.rows][img.cols];
	int n=8;
//	SE PASAN TODOS LOS ELEMENTOS DE UN OBJETO MAT A UN ARREGLO BIDIMENSIONAL
	for (int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			imgIn[i][j] = img.data[i*img.cols + j];
			imgOutX[i][j] = img.data[i*img.cols + j];
			imgOutY[i][j] = img.data[i*img.cols + j];
			imgOut45[i][j] = img.data[i*img.cols + j];
		}
	}

//	CONVOLUCION ENTRE EL ARREGLO BIDIMENSIONAL Y ALGUNA MASCARA
	int sumX, sumY, sum45, mi, mj, factor=765;
	for (int i=1; i<img.rows-1; i++){
	for (int j=1; j<img.cols-1; j++){
		sumX=0; sumY=0; sum45=0; mi=0;
		for (int ni=i-1; ni<=i+1; ni++){
			mj=0;
		for (int nj=j-1; nj<=j+1; nj++){
				sumX += SobelX[mi][mj]*imgIn[ni][nj];
				sumY += SobelY[mi][mj]*imgIn[ni][nj];
				sum45 += Sobel45[mi][mj]*imgIn[ni][nj];
			mj++;
			}
		mi++;
		}
		imgOutX[i][j] = (sumX+factor)/8;
		imgOutY[i][j] = (sumY+factor)/8;
		imgOut45[i][j] = (sum45+factor)/8;		
		}
	}

//	SE PASAN LOS ELEMENTOS DE UNA MATRIZ BIDIMENSIONAL A UN OBJETO DE TIPO MAT PARA MOSTRARLOS CON LA FUNCIÓN SHOW()
	Mat imageOutX = img.clone(), imageOutY = img.clone(), imageOut45 = img.clone();
	for (int i=0; i<imageOutX.rows; i++){
		for(int j=0; j<imageOutX.cols; j++){
			imageOutX.data[i*imageOutX.cols + j] = imgOutX[i][j];
			imageOutY.data[i*imageOutY.cols + j] = imgOutY[i][j];
			imageOut45.data[i*imageOut45.cols + j] = imgOut45[i][j];
		}
	}

//	SE OBTIENE LA MAGNITUD DEL GRADIENTE
	Mat gradient = img.clone(), gradient1 = img.clone();
	int X=0, Y=0, XY=0;
	for (int i=0; i<gradient.rows; i++){
		for(int j=0; j<gradient.cols; j++){
			X = imageOutX.data[i*imageOutX.cols + j];
			Y = imageOutY.data[i*imageOutY.cols + j];
			XY = imageOut45.data[i*imageOut45.cols + j];

			gradient.data[i*gradient.cols + j] = sqrt( pow(X,2) + pow(Y,2) );
			gradient1.data[i*gradient1.cols + j] = sqrt( pow(XY,2) );
		}
	}

//	THRESHOLDING
//	house, castle, fuente, lena, city->175
//	simetry -> 160
	int threshold = 150;
	for (int i=0; i<gradient.rows; i++){
		for(int j=0; j<gradient.cols; j++){
			if( gradient.data[i*gradient.cols + j] > threshold )
				gradient.data[i*gradient.cols + j] = 255;
			else
				gradient.data[i*gradient.cols + j] = 0;

			if( gradient1.data[i*gradient1.cols + j] < threshold )
				gradient1.data[i*gradient1.cols + j] = 255;
			else
				gradient1.data[i*gradient1.cols + j] = 0;
		}
	}

	plot(img, gradient);
}

void plot(Mat image, Mat newImage){

	namedWindow("Imagen de entrada", WINDOW_AUTOSIZE);
	imshow("Imagen de entrada", image);
	waitKey(0);

	namedWindow("Imagen de salida", WINDOW_AUTOSIZE);
	imshow("Imagen de salida", newImage);
	waitKey(0);
}
