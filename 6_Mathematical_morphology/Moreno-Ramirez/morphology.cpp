#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

Mat element(int figure);
Mat dilatation(Mat image, Mat element);
Mat erotion(Mat image, Mat element);
void opening(Mat image, Mat element);
void closing(Mat image, Mat element);
void border(Mat image, Mat element);
void plot(Mat image, Mat element);

int main(int argc, char **argv)
{
	if(argc != 2) {
	cout <<" Type currently the picture name and extension " << endl;
	return -1;
	}

	Mat image, img, newImage;
	img = imread(argv[1], 1);
	cvtColor(img, image, CV_BGR2GRAY);

	if (!image.data){
		cout<<"take care how type the picture name"<<endl;
		return -1;
	}

//	newImage = erotion(image,element(1));
	border(image, element(1));

//	plot(image, newImage);

	return 0;
}

Mat element(int figure){
	if (figure=1){
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
				newImage.data[ni*newImage.cols + nj] = 0;
			}
			}
		}
		}
	}
	}

	return newImage;
}

Mat erotion(Mat image, Mat element){
	Mat newImage = image.clone();
	int cX = round(element.cols/2), cY = round(element.rows/2), data=0;
	int cElement = element.data[cY*element.cols + cX], pixels = element.rows*element.cols, count=0;

	for (int i=0; i<image.rows; i++){
	for (int j=0; j<image.cols; j++){
		if( image.data[i*image.cols + j] == cElement ){
		if( i-cY >=0 && i+cY <= image.rows && i-cX >= 0 && i+cX <= image.cols){
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
	}

	return newImage;
}

void opening(Mat image, Mat element){
	Mat newImage;
	newImage = dilatation(erotion(image, element),element);
	plot(image, newImage);
}

void closing(Mat image, Mat element){
	Mat newImage;
	newImage = erotion(dilatation(image, element),element);
	plot(image, newImage);
}

void border(Mat image, Mat element){
	Mat newImage(image.rows, image.cols, CV_8UC1, Scalar(255)), ero = erotion(image, element);

	for(int i=0; i<newImage.rows; i++){
		for(int j=0; j<newImage.cols; j++){
			if ( image.data[i*image.cols + j] != ero.data[i*ero.cols + j]){
				newImage.data[i*newImage.cols + j] = 0;
			}

		}
	}

	plot(image, newImage);
}

void plot(Mat image, Mat newImage){
 	namedWindow("Imagen de entrada",WINDOW_AUTOSIZE);
	imshow("Imagen de entrada",image);
	waitKey(0);

	namedWindow("Imagen de salida",WINDOW_AUTOSIZE);
	imshow("Imagen de salida",newImage);
	waitKey(0);
}

