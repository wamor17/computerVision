#include <iostream>
#include <SerialStream.h>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#define windowLength 11
#define pi 3.14159265

using namespace std;
using namespace LibSerial;
using namespace cv;

Mat imageIn, imageOut, img;
Mat Mean, Variance, Homogeneity, Energy, Entropy, Contrast;
SerialStream Arduino;
unsigned t0, t1;

void conect2Arduino();
void fill_Image();
void inspectorWindow();
void segmentacion();
void sum_diff_histograms(float P_sum[], float P_diff[], int imgIn[][windowLength]);
void texture_Features(float P_sum[], float P_diff[], float textureFeatures[]);
void plot(Mat in);
void plot(Mat in, Mat out);
void plot(Mat in, Mat out, Mat aux);

int main(int argc, char** argv){
//	img = imread(argv[1], 0 );

/*	if (!img.data){
		cout<<"\n Take care how typing the picture name \n"<<endl;
		return -1;
	}
*/
//	system("wget http://192.168.43.1:8080/photo.jpg -O images/p1.jpg");
    img = imread("images/p1.jpg");

	imageIn.copyTo(imageOut);
	imageIn.copyTo(Mean);
	imageIn.copyTo(Variance);
	imageIn.copyTo(Homogeneity);
	imageIn.copyTo(Energy);
	imageIn.copyTo(Entropy);
	imageIn.copyTo(Contrast);

    cvtColor( img, image, CV_BGR2GRAY );
	t0 = clock();

	cout<<"\n Please wait... \n\n";
// ------------------------------------------------------------------------------------------------------------------------------
//	segmentacion();
	inspectorWindow();
// ------------------------------------------------------------------------------------------------------------------------------
	cout<<"\n Finish!!!"<<endl<<endl;

	t1 = clock();
	double time = (double(t1-t0)/CLOCKS_PER_SEC);
	cout<<" Execution time: "<<time<<" segundos"<<endl<<endl;

	return 0;
}

void segmentacion(){
//	SE OBTIENEN LAS IMAGENES DE CARACTERISTICAS
	inspectorWindow();

//	UTILIZO UN UMBRAL DE 40 PARA DEJAR SOLO LA LIBRETA QUE ES LO QUE NOS INTERESA
/*	cout<<" Umbralizando... "<<endl;

	int threshold = 120, rows = imageIn.rows, cols = imageIn.cols, pixel=0;
	Mat thresholdImage(rows, cols, CV_8UC1, Scalar(255));

	for( int i=0; i<rows; i++ ){
		for( int j=0; j<cols; j++){
			pixel = gray.data[i*cols + j];

			if( pixel >= threshold )
				thresholdImage.data[i*cols + j] = 255;
			else
				thresholdImage.data[i*cols + j] = 0;
		}
	}

	imwrite("images/2umbralizacion.png", thresholdImage);
*/
// EROSIONO LA IMAGEN CON UN ELEMENTO ESTRUCTURANTE DE DIMENSIONES 3x3
/*	cout<<" Eroding... "<<endl;

	Mat erode = thresholdImage.clone(), dilate;
	erode = erosion(erosion(erosion(erosion(erosion(erosion(thresholdImage, element(3)), element(3)), element(3)), element(3)), element(3)), element(3));
	dilate = dilatation(dilatation(dilatation(dilatation(dilatation(dilatation(dilatation(dilatation(erode, element(3)), element(3)), element(3)), element(3)), element(3)), element(3)), element(3)), element(3));

	imwrite("images/3erosion.png",dilate);
*/
//	SE REALIZA LA SEPARACION DE LA IMAGEN TOMANDO COMO REFERENCIA LA SALIDA DE LA MORFOLOGIA MATEMATICA
/*	cout<<" Segmentation... "<<endl;

	imageOut = imread("images/p1.jpg", 1);
	pixel=0;

	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			pixel = thresholdImage.data[i*cols + j];

			if( pixel != 255 ){
				imageOut.data[i*3*cols + j*3 + 0] = 0;
				imageOut.data[i*3*cols + j*3 + 1] = 0;
				imageOut.data[i*3*cols + j*3 + 2] = 0;
			}
		}
	}

	imwrite("images/4segmentacion.png", imageOut);

	plot(imageIn, imageOut);
*/
}

void inspectorWindow(){
	int rows = imageIn.rows, cols = imageIn.cols, rango = round(windowLength/2), mi=0, mj=0;
	int subImage[windowLength][windowLength] = {0};

	float P_sum[511]={0}, P_diff[511]={0}, textureFeatures[6]={0};
	float meanFeatures[rows][cols]={0}, varianceFeatures[rows][cols]={0}, homogeneityFeature[rows][cols]={0};
	float energyFeatures[rows][cols]={0}, entropyFeatures[rows][cols]={0}, contrastFeatures[rows][cols]={0};

	for (int i=0; i<rows; i++){
	for (int j=0; j<cols; j++){
		mi=0;
		for (int ni=i-rango; ni<=i+rango; ni++){
			mj=0;
		for (int nj=j-rango; nj<=j+rango; nj++){
//			NECESITO CREAR UNA SUB IMAGEN PARA CALCULAR SUS CARACTERISTICAS DE TEXTURA
			if ( ni >= 0 && ni <rows && nj >= 0 && nj <cols )
				subImage[mi][mj] = imageIn.data[ni*cols + nj];
			else
				subImage[mi][mj] = 0;

			mj++;
			}
		mi++;
		}
//		SE OBTIENEN LOS HISTOGRAMAS NORMALIZADOS PARA CADA SUB IMAGEN
		sum_diff_histograms(P_sum, P_diff, subImage);

//		A PARTIR DE LOS HISTOGRAMAS NORMALIZADOS, SE OBTIENEN LAS CARACTERISTICAS DE TEXTURA
		texture_Features(P_sum, P_diff, textureFeatures);

//		FEATURE -> MATRIX
		meanFeatures[i][j] = textureFeatures[0];
		varianceFeatures[i][j] = textureFeatures[1];
		homogeneityFeature[i][j] = textureFeatures[2];
		energyFeatures[i][j] = textureFeatures[3];
		entropyFeatures[i][j] = textureFeatures[4];
		contrastFeatures[i][j] = textureFeatures[5];
	}
	}

//	PARA CADA MATRIZ DE CARACTERISTICAS ES NECESARIO HACER UN AJUSTE LINEAL
//	PRIMERO SE OBTIENE EL MAYOR DE CADA MATRIZ DE CARACTERISTICAS
	float MMean=0, MVariance=0, MHomogeneity=0, MEnergy=0, MEntropy=0, MContrast=0;
	float mMean=255, mVariance=260100, mHomogeneity=1, mEnergy=1, mEntropy=255, mContrast=260100;

	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
//			MAYOR Y MENOR DE LA MEDIA
			if ( meanFeatures[i][j] > MMean )
				MMean = meanFeatures[i][j];				

			if ( meanFeatures[i][j] < mMean )
				mMean = meanFeatures[i][j];

//			MAYOR Y MENOR DE LA VARIANZA
			if ( varianceFeatures[i][j] > MVariance )
				MVariance = varianceFeatures[i][j];

			if ( varianceFeatures[i][j] < mVariance )
				mVariance = varianceFeatures[i][j];

//			MAYOR Y MENOR DE LA HOMOGENEIDAD
			if ( homogeneityFeature[i][j] > MHomogeneity )
				MHomogeneity = homogeneityFeature[i][j];

			if ( homogeneityFeature[i][j] < mHomogeneity )
				mHomogeneity = homogeneityFeature[i][j];

//			MAYOR Y MENOR DE LA ENERGIA
			if ( energyFeatures[i][j] > MEnergy )
				MEnergy = energyFeatures[i][j];

			if ( energyFeatures[i][j] < mEnergy )
				mEnergy = energyFeatures[i][j];

//			MAYOR Y MENOR DE LA ENTROPIA
			if ( entropyFeatures[i][j] > MEntropy )
				MEntropy = entropyFeatures[i][j];

			if ( entropyFeatures[i][j] < mEntropy )
				mEntropy = entropyFeatures[i][j];

//			MAYOR Y MENOR DEL CONTRASTE
			if ( contrastFeatures[i][j] > MContrast )
				MContrast = contrastFeatures[i][j];

			if ( contrastFeatures[i][j] < mContrast )
				mContrast = contrastFeatures[i][j];
		}
	}

	cout<<" Ajuste lineal... \n";
	float value=0;
	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){

			value = meanFeatures[i][j];
			Mean.data[i*cols + j] = int( 255*( (value - mMean)/(MMean - mMean) ) );

			value = varianceFeatures[i][j];
			Variance.data[i*cols + j] = int( 255*( (value - mVariance)/(MVariance - mVariance) ) );

			value = homogeneityFeature[i][j];
			Homogeneity.data[i*cols + j] = int(value*255);


			value = energyFeatures[i][j];
			Energy.data[i*cols + j] = int(value*255);

			value = entropyFeatures[i][j];
			Entropy.data[i*cols + j] = int( 255*( (value - mEntropy)/(MEntropy - mEntropy) ) );

			value = contrastFeatures[i][j];
			Contrast.data[i*cols + j] = int( 255*( (value - mContrast)/(MContrast - mContrast) ) );

		}
	}

//	GUARDAMOS EN UN ARCHIVO .png LA IMAGEN DE SALIDA DEL AJUSTE LINEAL CON CADA UNA DE LAS CARACTERISTICAS
	cout<<" Exit files... \n";
	imwrite("images/imagenes_textura/1mean.png",Mean);
	imwrite("images/imagenes_textura/2variance.png", Variance);
	imwrite("images/imagenes_textura/3homogeneity.png", Homogeneity);
	imwrite("images/imagenes_textura/4energy.png", Energy);
	imwrite("images/imagenes_textura/5entropy.png", Entropy);
	imwrite("images/imagenes_textura/6contrast.png", Contrast);

//	LA IMAGEN A UTILIZAR SE ALMACENA AL MISMO NIVEL QUE LAS IMAGENES DE SALIDA DEL ALGORITMO
	imwrite("images/1textura_homogeneidad.png", Homogeneity);
}

void sum_diff_histograms(float P_sum[], float P_diff[], int imgIn[][windowLength]){
//	HITOGRAMAS DE SUMAS Y DIFERENCIAS
	float histSum[511]={0}, histDiff[511]={0};
//	DIMENSIONES DE LA IMAGEN
	int rows = windowLength, cols = windowLength;
//	VARIABLE DE CONTROL PARA NORMALIZACION Y ANALISIS DE INTENSIDADES
	int vSum=0, vDiff=0, d=1;
//	CONTADORES PARA LOS HISTOGRAMAS
	float countSum=0, countDiff=0;

//	ANALISIS EN CUATRO ANGULOS: 0°, 45°, 90° Y 135°
	for (int i=0; i<rows; i++){
		for (int j=0; j<cols; j++){
			vSum = 0; vDiff = 0;

//		ANALISIS DE PIXELES PARA OBTENER LAS OCURRENCIAS DE TONOS DE GRIS Y ALMACENARLAS EN UN ARREGLO DE HISTOGRAMA
		if( i-(d+1) >= 0 && i+(d+1) < rows && j-(d+1) >= 0 && j+(d+1) < cols ){
//			SUMAS Y DIFERENCIAS EN 0°
			vSum = imgIn[i][j] + imgIn[i][j+d];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i][j+d])+255;
			histDiff[vDiff]++;
			countDiff++;

			vSum = imgIn[i][j] + imgIn[i][j+(d+1)];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i][j+(d+1)])+255;
			histDiff[vDiff]++;
			countDiff++;

//			SUMAS Y DIFERENCIAS ANALIZANDO EN 45°
			vSum = imgIn[i][j] + imgIn[i-d][j+d];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-d][j+d])+255;
			histDiff[vDiff]++;
			countDiff++;

			vSum = imgIn[i][j] + imgIn[i-(d+1)][j+(d+1)];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-(d+1)][j+(d+1)])+255;
			histDiff[vDiff]++;
			countDiff++;

//			SUMAS Y DIFERENCIAS ANALIZANDO EN 90°
			vSum = imgIn[i][j] + imgIn[i-d][j];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-d][j])+255;
			histDiff[vDiff]++;
			countDiff++;

			vSum = imgIn[i][j] + imgIn[i-(d+1)][j];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-(d+1)][j])+255;
			histDiff[vDiff]++;
			countDiff++;

//			SUMAS Y DIFERENCIAS ANALIZANDO EN 135°
			vSum = imgIn[i][j] + imgIn[i-d][j-d];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-d][j-d])+255;
			histDiff[vDiff]++;
			countDiff++;

			vSum = imgIn[i][j] + imgIn[i-(d+1)][j-(d+1)];
			histSum[vSum]++;
			countSum++;

			vDiff = (imgIn[i][j] - imgIn[i-(d+1)][j-(d+1)])+255;
			histDiff[vDiff]++;
			countDiff++;
		}
	}
	}

//	NORMALIZACION DE LOS HISTOGRAMAS
	for (int i=0; i<511; i++){
		P_sum[i] = histSum[i]/countSum;
		P_diff[i] = histDiff[i]/countDiff;
	}


}

void texture_Features(float P_sum[], float P_diff[], float textureFeatures[]){
	float Psum_i=0, Pdiff_j=0, pow1, mean=0, variance=0, homogeneity=0, energy=0, entropy=0, contrast=0;
	int length = 511;

//	SE OBTIENE LA MEDIA DE LOS DATOS
	for (int i=0; i<length; i++){
		mean += P_sum[i]*i;
	}
	mean *= 0.5;

	float p1=0, p2=0;
	for (int i=0; i<length; i++){
		Psum_i = P_sum[i];
		Pdiff_j = P_diff[i];

//		VARIANZA DE LOS DATOS
		variance += pow((i-2*mean),2)*Psum_i + pow((i-255),2)*Pdiff_j;

//		HOMEGENEIDAD DE LOS DATOS
		homogeneity += (1/(pow((i-255),2)+1))*Pdiff_j;

//		ENERGIA DEL SISTEMA
		p1 += pow(Psum_i,2);
		p2 += pow(Pdiff_j,2);

//		ENTROPIA DEL SISTEMA
		if ( Psum_i > 0 && Pdiff_j > 0 )
			entropy += (-1)*Psum_i*log(Psum_i) - Pdiff_j*log(Pdiff_j);

//		CONTRASTE
		contrast += pow((i-255), 2)*Pdiff_j;

		pow1 = 0;
	}

//	ENERGIA
	energy = p1*p2;
	variance *= 0.5;

	textureFeatures[0] = mean;
	textureFeatures[1] = variance;
	textureFeatures[2] = homogeneity;
	textureFeatures[3] = energy;
	textureFeatures[4] = entropy;
	textureFeatures[5] = contrast;
}

Mat element(int figure){
	if (figure=3){
		//DIBUJA UN CUADRADO
		Mat element(3, 3, CV_8UC1, Scalar(0));

		return element;
	}else
		cout<<"\n\n FIGURA NO DEFINIDA"<<endl;
}

Mat dilatation(Mat image, Mat element){
	Mat newImage = image.clone();
	int cX = round(element.cols/2), cY = round(element.rows/2), data=0;
	int cElement = element.data[cY*element.cols + cX];

	for (int i=0; i<image.rows; i++){
	for (int j=0; j<image.cols; j++){
		if( image.data[i*image.cols + j] == cElement ){
		if( i-cY >=0 && i+cY <= image.rows && i-cX >= 0 && i+cX <= image.cols){
			for (int ni=i-cY; ni<=i+cY; ni++){
			for (int nj=j-cX; nj<=j+cX; nj++){
				newImage.data[ni*newImage.cols + nj] = cElement;
			}
			}
		}
		}
	}
	}

	return newImage;
}

Mat erosion(Mat image, Mat element){
	Mat newImage = image.clone();
	int cX = round(element.cols/2), cY = round(element.rows/2), data=0;
	int cElement = element.data[cY*element.cols + cX], pixels = element.rows*element.cols, count=0;

	for (int i=0; i<image.rows; i++){
	for (int j=0; j<image.cols; j++){

		if( image.data[i*image.cols + j] == cElement ){
				count=0;

				for(int ni=i-cY; ni<=i+cY; ni++){
				for(int nj=j-cX; nj<=j+cX; nj++){
					data = image.data[ni*image.cols + nj];
					if ( data == cElement )
						count++;
					else
						count--;
				}
				}

				if ( count == pixels ){
					newImage.data[i*newImage.cols + j] = 0;
				}else{
					for (int ni=i-cY; ni<=i+cY; ni++){
					for (int nj=j-cX; nj<=j+cX; nj++){
						newImage.data[ni*newImage.cols + nj] = 255;
					}
					}
				}

		}
	}
	}

	return newImage;
}

void fill_Image(Mat circle_detected){
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  findContours( circle_detected, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  Mat filled = Mat::zeros( circle_detected.size(), CV_8UC1 );

  for (size_t i=0; i<contours.size(); i++){
  		Scalar color = 255;
  		drawContours( filled, contours, int(i), color, -1, 8, hierarchy, 0, Point() );
  }

	for(int i=0; i<imageIn.rows; i++)
	for(int j=0; j<imageIn.cols; j++)
  		if( filled.data[i*imageIn.cols + j] != 255 )
  			imageIn.data[i*imageIn.cols + j] = 0;

  plot(imageIn);
}

void conect2Arduino(){
    Arduino.Open("/dev/ttyUSB0");

	if( Arduino.good() ){
		std::cout<<"\n\n ARDUINO CONECTADO \n\n";

		Arduino.SetBaudRate(SerialStreamBuf::BAUD_9600);
	    Arduino.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);

	    char num;
	    cout<<" Number of blinks = ";
	    cin>>num;

	    Arduino << char(num);
	}else
		cout<<"\n\n ** NO SE PUEDE CONECTAR CON ARDUINO ** \n\n";
}

void plot(Mat in){
	namedWindow("Imagen de salida", 0);
	imshow("Imagen de salida", in);
	waitKey(0);
}

void plot(Mat in, Mat out){
	namedWindow("Imagen de entrada", 0);
	imshow("Imagen de entrada", in);
	waitKey(0);

	namedWindow("Imagen de salida", 0);
	imshow("Imagen de salida", out);
	waitKey(0);
}

//	ABRIR CON stdio y fopen el puerto serial

//	COMPILAR DESDE CONSOLA:
//	g++ testSerial.cpp -o testSerial -pthread -lserial
