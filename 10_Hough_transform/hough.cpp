#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>
#define pi 3.14159265

using namespace std;
using namespace cv;

Mat img, imageOut;
Mat filledImage;

void hough_lines();
void hough_circles();
void plot(Mat in);
void plot2(Mat in, Mat out);
void plot3(Mat in1, Mat in2, Mat in3);

int main(int argc, char **argv){

	img = imread(argv[1], 0 );

	if (!img.data){
		cout<<"\n Take care how typing the picture name \n"<<endl;
		return -1;
	}

	img.copyTo(imageOut);

	hough_lines();

	return 0;
}

void hough_circles(){
//	VARIABLES A UTILIZAR
	int rows = img.rows, cols = img.cols, distMax = round(sqrt( pow(rows,2) + pow(cols,2) ));
	int radio = 80, pixel = 0, Cx = 0, Cy = 0, mayor=0, radius=0;
	int imgIn[rows][cols]={0}, imgOut[rows][cols]={0}, collector[rows][cols][radio];
/*
	for (int i=0; i<rows; i++){
	for (int j=0; j<cols; j++){
		pixel = img.data[i*cols + j];

		cout<<" pixel = "<<pixel;
		if( pixel == 0 )
			for(int r=5; i<radio; i++)
			for(int theta=0; theta<360; theta++){
				Cx = i + cos((theta*pi)/180)*r;
				Cy = j + sin((theta*pi)/180)*r;

				cout<<" Cx = "<<Cx<<"\n Cy = "<<Cy<<endl;

				if( Cx >= 0 && Cy >= 0 ){
					collector[Cx][Cy][r]++;

					if( collector[Cx][Cy][r] > mayor ){
						mayor = collector[Cx][Cy][r];

						Cx = i; Cy = j; radius = r;
					}
				}

			}

//		imgIn[i][j] = img.data[i*cols + j];
	}
	}
*/
//	cout<<endl<<" Valor mayor = "<<mayor<<"\n Con coordenadas (Cx,Cy,r) ("<<Cx<<","<<Cy<<","<<radius<<")  "<<endl<<endl;
}

void hough_lines(){
//	VARIABLE A UTILIZAR
	int rows = img.rows, cols = img.cols, dMaxima = round(sqrt( pow(rows,2) + pow(cols,2) )), grados=360;
	int rowsCollector = dMaxima, collector[rowsCollector][grados] = {0};
	int imgIn[rows][cols], imgOut[rows][cols];

//	SE BUSCA EN LA IMAGEN UN PUNTO NEGRO, QUE REPRESENTA UN BORDE, AL ENCONTRARLO SE CREAN LAS CURVAS SINUSOIDALES EN EL PLANO POLAR
//	Y SE VAN AGREGANDO EN FORMA DE INCREMENTO A LOS ARREGLOS, CONSIDERANDO LOS VALORES NEGATIVOS Y POSITIVOS QUE PUEDEN RESULTAR
//	DE APLICAR LA EXTRAPOLACION A COORDENADAS POLARES CON UN INTERVALO DE [0, 180)
//	SE OBTIENE EL VALOR MAYOR QUE INDICA EL CRUCE DE VARIAS CURVAS POR EL MISMO PUNTO DEL PLANO POLAR, ESTO NOS DA UN PUNTO EN COMUN Y,
//	UN PUNTO EN EL PLANO POLAR ES IGUAL A UNA RECTA EN EL PLANO CARTESIANO
	int mayor=0, x=0, y=0, p=0, pixel=0;
	for (int i=0; i<rows; i++)
	for (int j=0; j<cols; j++){

		imgIn[i][j] = 0;
		imgOut[i][j] = 0;
		pixel = img.data[i*cols + j];

		if ( pixel > 0 ){
			for (int theta=0; theta<grados; theta++){
				p = i*cos((theta*pi)/180) + j*sin((theta*pi)/180);

				if ( p >= 0 ){
					collector[p][theta]++;

					if( collector[p][theta] > mayor ){
						mayor = collector[p][theta];

						x = i; y = j;
					}
				}

			}
		}
		imgIn[i][j] = img.data[i*cols + j];
	}

	cout<<endl<<" Valor mayor = "<<mayor<<"\n Con coordenadas x-y ("<<x<<","<<y<<")  "<<endl<<endl;

//	OBTENEMOS SOLO LOS PUNTOS QUE ESTAN POR ENCIMA DEL 80% DEL VALOR PARA EL PUNTO MAXIMO EN EL ACUMULADOR
	int umbral = 100;//0.7*mayor;
	cout<<" RECTAS MAXIMAS EN COORDENADAS (ro,theta) \n"<<endl;
	cout<<" Umbral = "<<umbral<<endl<<endl;

	for (int i=0; i<rowsCollector; i++){
		for (int j=0; j<grados; j++){
			if ( collector[i][j] >= umbral ){
				collector[i][j] = 255;
				cout<<" ("<<i<<","<<j<<")"<<endl;
			}else
				collector[i][j] = 0;
		}
	}
	cout<<endl<<endl;

//	OBTENEMOS RECTAS EN EL PLANO X-Y, A PARTIR DE PUNTOS EN EL PLANO RO-THETA
	int Y=0;
	for (int ro=0; ro<rowsCollector; ro++)
	for (int theta=0; theta<grados; theta++){
		if( collector[ro][theta] == 255 ){
			for (int x=0; x<rows; x++)
				if ( sin((theta*pi)/180) > 0 ){
					Y = ( ro - x*cos((theta*pi)/180) )/sin((theta*pi)/180);

					if( Y >= 0 && Y < cols )
						imgIn[x][Y] = 255;
				}
		}
	}

//	SE PASAN LOS DATOS DEL ACUMULADOR A UNA IMAGEN
	Mat Collector(rowsCollector, grados, CV_8UC1, Scalar(255));

	for (int i=0; i<rowsCollector; i++)
		for (int j=0; j<grados; j++){
			Collector.data[i*grados + j] -= collector[i][j];
		}

	Mat lineas(rows, cols, CV_8UC1, Scalar(0));
	for (int i=0; i<rows; i++)
		for(int j=0; j<cols; j++){
			lineas.data[i*cols + j] = imgIn[i][j];
		}

//	SE MUESTRA TANTO LA IMAGEN DE PUNTOS EN UN PLANO CARTESIANO COMO SU SIMILAR EN EL PLANO POLAR
	plot(lineas);
}

void plot(Mat in){
	namedWindow("Solo una imagen de salida", 0);
	imshow("Solo una imagen de salida", in);
	waitKey(0);
}

void plot2(Mat in, Mat out){
	namedWindow("IMAGEN DE ENTRADA", 0);
	imshow("IMAGEN DE ENTRADA", in);
	waitKey(0);

	namedWindow("IMAGEN DE SALIDA CON LA RECTA PREDOMINANTE", 0);
	imshow("IMAGEN DE SALIDA CON LA RECTA PREDOMINANTE", out);
	waitKey(0);
}

void plot3(Mat in1, Mat in2, Mat in3){
	namedWindow("IMAGEN DE ENTRADA", WINDOW_AUTOSIZE);
	imshow("IMAGEN DE ENTRADA", in1);
	waitKey(0);

	namedWindow("CURVAS SINUSOIDALES DE CADA PUNTO DE LA IMAGEN DE ENTRADA", WINDOW_AUTOSIZE);
	imshow("CURVAS SINUSOIDALES DE CADA PUNTO DE LA IMAGEN DE ENTRADA", in2);
	waitKey(0);

	namedWindow("IMAGEN DE SALIDA, RECTA PREDOMINANTE", WINDOW_AUTOSIZE);
	imshow("IMAGEN DE SALIDA, RECTA PREDOMINANTE", in3);
	waitKey(0);
}

