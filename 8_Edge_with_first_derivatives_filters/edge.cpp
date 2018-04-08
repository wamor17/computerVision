#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void edge(Mat img);
void plot(Mat image, Mat newImage);
void histograma(Mat image);
void plotH(float H[]);

int main(int argc, char **argv){

	if(argc != 2){
		cout<<"\n Type correctly the picture name and extension"<<endl;
		return -1;
	}

	Mat img;
	clock_t time = clock();;
	img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );

	if (!img.data){
		cout<<"\n Take care how type the picture name\n"<<endl;
		return -1;
	}

	edge(img);

	time = (clock()-time)/1000;
	cout<<" Tiempo de ejecucion: "<<time<<" s"<<endl;

	return 0;
}

void edge(Mat img){
//	GRADIENTE DE PREWITT
 	int PrewittX[3][3] = { {-1,0,1}, {-1,0,1}, {-1,0,1} };
	int PrewittY[3][3] = { {-1,-1,-1}, {0,0,0}, {1,1,1} };
	int Prewitt45[3][3] = { {-2,-1,0}, {-1,0,1}, {0,1,2} };

//	GRADIENTE DE SOBEL
 	int SobelX[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
	int SobelY[3][3] = { {1,2,1}, {0,0,0}, {-1,-2,-1} };
	int Sobel45[3][3] = { {-2,-2,0}, {-2,0,2}, {0,2,2} };

//	GRADIENTE DE ROBERTS
 	int RobertsX[3][3] = { {0,-1,0}, {0,1,0}, {0,0,0} };
	int RobertsY[3][3] = { {-1,0,0}, {0,1,0}, {0,0,0} };
	int Roberts45[3][3] = { {-1,1,0}, {0,1,0}, {0,0,0} };

//	GRADIENTE DE FRI-CHEN
 	int FriChenX[3][3] = { {-1,0,1}, {-sqrt(2),0,sqrt(2)}, {-1,0,1} };
	int FriChenY[3][3] = { {-1,-sqrt(2),-1}, {0,0,0}, {1,sqrt(2),1} };

//	SE PASAN TODOS LOS ELEMENTOS DE UN OBJETO MAT A UN ARREGLO BIDIMENSIONAL
	float imgIn[img.rows][img.cols], imgOutX[img.rows][img.cols], imgOutY[img.rows][img.cols], imgOut45[img.rows][img.cols];
	float gradient[img.rows][img.cols], gradientXY[img.rows][img.cols];

	for (int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			imgIn[i][j] = img.data[i*img.cols + j];
			imgOutX[i][j] = 0;
			imgOutY[i][j] = 0;
			imgOut45[i][j] = 0;
			gradient[i][j] = 0;
			gradientXY[i][j] = 0;
		}
	}

//	CONVOLUCION ENTRE EL FILTRO BIDIMENSIONAL Y DIFERENTES MASCARAS
	long int sumX, sumY, sum45, mi, mj, factor=765, N=6;
	for (int i=0; i<img.rows; i++){
	for (int j=0; j<img.cols; j++){
		sumX=0; sumY=0; sum45=0; mi=0;
		for (int ni=i-1; ni<=i+1; ni++){
			mj=0;
		for (int nj=j-1; nj<=j+1; nj++){
			if ( ni-1 >= 0 && nj-1 >= 0 && ni+1 < img.rows && nj+1 < img.cols ){
				sumX += SobelX[mi][mj]*imgIn[ni][nj];
				sumY += SobelY[mi][mj]*imgIn[ni][nj];
				sum45 += Sobel45[mi][mj]*imgIn[ni][nj];
			} else{
				sumX += 0;
				sumY += 0;
				sum45 += 0;
			}

			mj++;
			}
		mi++;
		}
		
		if ( sumX <= 0 ){
			imgOutX[i][j] = 0;
		}else if ( sumX >= 255){
			imgOutX[i][j] = 255;
		}else
			imgOutX[i][j] = sumX;

		if ( sumY <= 0 ){
			imgOutY[i][j] = 0;
		}else if ( sumY >= 255){
			imgOutY[i][j] = 255;
		}else
			imgOutY[i][j] = sumY;

		if ( sum45 <= 0 ){
			imgOut45[i][j] = 0;
		}else if ( sum45 >= 255){
			imgOut45[i][j] = 255;
		}else
			imgOut45[i][j] = sum45;
	}
	}

//	SE OBTIENE LA MAGNITUD DEL GRADIENTE
	float X=0, Y=0, XY=0, raiz=0, raiz2=0;
	for (int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			X = imgOutX[i][j];
			Y = imgOutY[i][j];
			XY = imgOut45[i][j];
			raiz = sqrt( pow(X,2) + pow(Y,2) );
			raiz2 = sqrt( pow(XY,2) );

			if ( raiz >= 255 ){
				gradient[i][j] = 255;				
			}else if( raiz <= 0 ){
				gradient[i][j] = 0;
			}else{
				gradient[i][j] = raiz;
			}

			if ( raiz2 >= 255 ){
				gradientXY[i][j] = 255;				
			}else if( raiz2 <= 0 ){
				gradientXY[i][j] = 0;
			}else{
				gradientXY[i][j] = raiz;
			}
		}
	}

//	SE PASAN LOS ELEMENTOS DE UNA MATRIZ BIDIMENSIONAL A UN OBJETO DE TIPO MAT PARA MOSTRARLOS CON LA FUNCIÓN SHOW()
	Mat GRADIENTE = img.clone(), GRADIENTE2 = img.clone();
	for (int i=0; i<GRADIENTE.rows; i++){
		for(int j=0; j<GRADIENTE.cols; j++){
			GRADIENTE.data[i*GRADIENTE.cols + j] = gradient[i][j];
			GRADIENTE2.data[i*GRADIENTE.cols + j] = gradientXY[i][j];
		}
	}

//	THRESHOLDING
/*  int threshold = 90;
	for (int i=0; i<GRADIENTE.rows; i++){
		for(int j=0; j<GRADIENTE.cols; j++){
			if( GRADIENTE.data[i*GRADIENTE.cols + j] <= threshold )
				GRADIENTE.data[i*GRADIENTE.cols + j] = 0;
			else
				GRADIENTE.data[i*GRADIENTE.cols + j] = 255;
		
			if( GRADIENTE2.data[i*GRADIENTE2.cols + j] <= threshold )
				GRADIENTE2.data[i*GRADIENTE2.cols + j] = 0;
			else
				GRADIENTE2.data[i*GRADIENTE2.cols + j] = 255;
		}
	}
*/
	Mat m = img.clone(), om = img.clone();
	Mat mask = (Mat_<double>(3,3) << -2,-1,0, -1,0,1, 0,1,2 );

	filter2D( m, om, m.depth(), mask );
	plot(img, GRADIENTE);
}

void plot(Mat image, Mat newImage){

	namedWindow("Imagen de entrada", WINDOW_AUTOSIZE);
	imshow("Imagen de entrada", image);
	waitKey(0);

	namedWindow("Imagen de salida", WINDOW_AUTOSIZE);
	imshow("Imagen de salida", newImage);
	waitKey(0);
}



