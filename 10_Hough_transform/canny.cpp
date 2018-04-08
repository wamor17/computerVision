#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#define pi 3.14159265

using namespace std;
using namespace cv;

Mat img, imageOut;

void canny();
void gaussianBlur();
void gradient();
void histeresis();
void plot(Mat image, Mat newImage);
void hough();
int otsu(Mat image);

int main(int argc, char **argv){

	img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );

	if (!img.data){
		cout<<"\n Take care how typing the picture name \n"<<endl;
		return -1;
	}

	img.copyTo(imageOut);
	canny();

	return 0;
}

void canny(){
	gaussianBlur();
	gradient();
	histeresis();
	plot(img, imageOut);
}

void gaussianBlur(){
//	SE PASAN TODOS LOS ELEMENTOS DE UN OBJETO MAT A UN ARREGLO BIDIMENSIONAL
	int rows = imageOut.rows, cols = imageOut.cols;
	float imgIn[rows][cols], imgOut[rows][cols];

	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			imgIn[i][j] = imageOut.data[i*cols + j];
			imgOut[i][j] = 0;
		}
	}
//	FILTRO GAUSSIANO PARA SUAVIZAR LA IMAGEN
	int gaussian[5][5] = { {2,4,5,4,2}, {4,9,12,9,4}, {5,12,15,12,5}, {4,9,12,9,4}, {2,4,5,4,2} };
//	CONVOLUCION ENTRE LA IMAGEN Y UN FILTRO GAUSSIANO, ESTO ATENUA EL RUIDO DE LA IMAGEN
	int sum, mi, mj, factor=159, rango=2, rn=rango+1;

	for (int i=0; i<rows; i++){
	for (int j=0; j<cols; j++){
		sum=0; mi=0;
		for (int ni=i-rango; ni<=i+rango; ni++){
			mj=0;
		for (int nj=j-rango; nj<=j+rango; nj++){
			if ( (ni >= 0 && nj >= 0) && (ni < rows && nj < cols) ){
				sum += gaussian[mi][mj]*imgIn[ni][nj];
			} else{
				sum += 0;
			}

			mj++;
			}
		mi++;
		}
		imgOut[i][j] = sum/factor;
	}
	}
//	SE PASAN LOS ELEMENTOS DE UNA MATRIZ BIDIMENSIONAL A UN OBJETO DE TIPO MAT
	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			imageOut.data[i*cols + j] = imgOut[i][j];
		}
	}
}

void gradient(){
//	SE PASAN TODOS LOS ELEMENTOS DE UN OBJETO MAT A UN ARREGLO BIDIMENSIONAL
	int rows = imageOut.rows, cols = imageOut.cols;
	float lengthGradient[rows][cols], direction[rows][cols];
	float imgIn[rows][cols], imgOutX[rows][cols], imgOutY[rows][cols];

	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			imgIn[i][j] = imageOut.data[i*cols + j];
			imgOutX[i][j] = 0;
			imgOutY[i][j] = 0;
			lengthGradient[i][j] = 0;
			direction[i][j] = 0;
		}
	}
//	GRADIENTE DE SOBEL
 	int SobelX[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
	int SobelY[3][3] = { {-1,-2,-1}, {0,0,0}, {1,2,1} };
//	OBTENCION DE BORDES APLICANDO LA CONVOLUCION DE UNA IMAGEN CON UNA MATRIZ DE PRIMERA DERIVADA
//	SE OBTIENE LA MAGNITUD Y EL ANGULO DEL GRADIENTE PARA CADA PIXEL
	float X=0, Y=0, raiz=0, theta=0, mayor=0;
	int sumX, sumY, mi, mj;
	int count[136], p=0;

	for (int i=0; i<136; i++)
		count[i] = 0;

	for (int i=0; i<rows; i++){
	for (int j=0; j<cols; j++){
		sumX=0; sumY=0; mi=0;
		for (int ni=i-1; ni<=i+1; ni++){
			mj=0;
		for (int nj=j-1; nj<=j+1; nj++){
			if ( ni >= 0 && nj >= 0 && ni < img.rows && nj < img.cols ){
				sumX += SobelX[mi][mj]*imgIn[ni][nj];
				sumY += SobelY[mi][mj]*imgIn[ni][nj];
			} else{
				sumX += 0;
				sumY += 0;
			}
			mj++;
			}
		mi++;
		}
		
		X = round(sumX);
		Y = round(sumY);

		lengthGradient[i][j] = round( sqrt( pow(X,2) + pow(Y,2) ) );
		theta = (atan2(Y,X)*180)/pi;

		if ( theta >= 0 && theta < 22.5 )
			direction[i][j] = 0;
		else if ( theta >= 22.5 && theta < 67.5 )
			direction[i][j] = 45;
		else if ( theta >= 67.5 && theta < 112.5  )
			direction[i][j] = 90;
		else if ( theta >= 112.5 && theta < 157.5 )
			direction[i][j] = 135;
		else if ( theta >= 157.5 && theta <= 180 )
			direction[i][j] = 0;

		p = direction[i][j];
		count[ p ]++;
		p = 0;
	}
	}

	cout<<"\n 0° = "<<count[0]<<"\n 45° = "<<count[45]<<"\n 90° = "<<count[90]<<"\n 135° = "<<count[135]<<endl<<endl;

	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
			imageOut.data[i*cols + j] = lengthGradient[i][j];
		}
	}
//	NO-MAXIMUM SUPPRESSION
	int ni=0, nj=0, angulo, value=0;
	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			ni = i-1;
			nj = j-1;

			if ( (ni > 0 && nj > 0) && (ni < rows && nj < cols) ){
				angulo = direction[ni][nj];
				value = lengthGradient[ni][nj];

				switch( angulo ){
					case 0:
						if ( value > lengthGradient[ni][nj-1] && value > lengthGradient[ni][nj+1] ){
							imageOut.data[ni*cols + nj] = value;
						}else
							imageOut.data[ni*cols + nj] = 0;
					break;
					case 45:
						if ( value > lengthGradient[ni+1][nj-1] && value > lengthGradient[ni-1][nj+1] ){
							imageOut.data[ni*cols + nj] = value;
						}else
							imageOut.data[ni*cols + nj] = 0;
					break;
					case 90:
						if ( value > lengthGradient[ni-1][nj] && value > lengthGradient[ni+1][nj] ){
							imageOut.data[ni*cols + nj] = value;
						}else
							imageOut.data[ni*cols + nj] = 0;	
					break;
					case 135:
						if ( value > lengthGradient[ni-1][nj-1] && value > lengthGradient[ni+1][nj+1] ){
							imageOut.data[ni*cols + nj] = value;
						}else
							imageOut.data[ni*cols + nj] = 0;					
					break;
				}
			}
		}
	}
}

void histeresis(){
//	DIMENSIONES DE LA IMAGEN
	int rows = imageOut.rows, cols = imageOut.cols;
//	Umbral bajo y ratio para umbral alto
	int lowThreshold = 20, ratio=3, highThreshold = lowThreshold*ratio;
//	Otras variables
	float pixel, data=0, cont=0;
//	Copia de los elementos de un objeto Mat a un arreglo bidimensional
	float edges[rows][cols];
	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
			edges[i][j] = imageOut.data[i*cols + j];
		}
	}
//	SEGUIMIENTO A LAS LINEAS CON PIXELES FUERTES ALREDEDOR Y PURGA DE PIXELES DEBILES
	for (int i=0; i<rows; i++){
	for (int j=0; j<cols; j++){
		pixel = edges[i][j];

		if( pixel < highThreshold && pixel > lowThreshold ){
			cont = 0;

			for (int vi=i-1; vi<i+1; vi++){
			for (int vj=j-1; vj<j+1; vj++){
				data = edges[i][j];
				if ( data >= highThreshold )
					cont++;
			}
			}

			if ( cont > 0 )
				edges[i][j] = 255;
			else
				edges[i][j] = 0;

		}else if( pixel >= highThreshold )
			edges[i][j] = 255;
		else if( pixel <= lowThreshold )
			edges[i][j] = 0;
	
	}
	}

	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
			imageOut.data[i*cols + j] = edges[i][j];
		}
	}
}

int otsu(Mat image){
//  Variables a utilizar
	float h[256], N=(image.rows)*(image.cols), w0=0, w1=0, u0=0, u1=0, sigmaB=0, mayor=0;
	int umbral=0, L = 255, aux=0, aux1=0;

	for(int i=0; i<L; i++){
		h[i] = 0;
	}
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

void plot(Mat image, Mat newImage){
	namedWindow("Imagen de entrada en escala de grises", WINDOW_AUTOSIZE);
	imshow("Imagen de entrada en escala de grises", image);
	waitKey(0);

	namedWindow("Bordes de la imagen utilizando el método de Canny", WINDOW_AUTOSIZE);
	imshow("Bordes de la imagen utilizando el método de Canny", newImage);
	waitKey(0);
}

