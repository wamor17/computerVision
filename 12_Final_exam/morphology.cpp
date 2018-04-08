#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

Mat image, img, newImage;

Mat element(int figure);
Mat dilatation(Mat image, Mat element);
Mat erosion(Mat image, Mat element);
void opening(Mat image, Mat element);
void closing(Mat image, Mat element);
void border(Mat image, Mat element);
void plot(Mat image);

int main(int argc, char **argv){

	img = imread(argv[1], 0);

	if ( !img.data ){
		cout<<"take care how type the picture name"<<endl;
		return -1;
	}

	Mat out = img.clone();

	out = erosion(erosion(erosion(erosion(erosion(img, element(3)), element(3)), element(3)), element(3)), element(3));
	plot(out);

//	border(image, element(3));

	return 0;
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

void opening(Mat image, Mat element){
	Mat newImage;
	newImage = dilatation(erosion(image, element),element);
	plot(newImage);
}

void closing(Mat image, Mat element){
	Mat newImage;
	newImage = erosion(dilatation(image, element),element);
	plot(newImage);
}

void border(Mat image, Mat element){
	Mat newImage(image.rows, image.cols, CV_8UC1, Scalar(255)), ero = erosion(image, element);

	for(int i=0; i<newImage.rows; i++){
		for(int j=0; j<newImage.cols; j++){
			if ( image.data[i*image.cols + j] != ero.data[i*ero.cols + j]){
				newImage.data[i*newImage.cols + j] = 0;
			}

		}
	}

	plot(newImage);
}

void plot(Mat image){
 	namedWindow("Imagen de entrada", 0);
	imshow("Imagen de entrada",image);
	waitKey(0);
}

