#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float* Mat2Array(Mat image);
void canny(Mat image);

int main(int argc, char **argv){

	if(argc != 2){
		cout<<"\n Type correctly the picture name and extension"<<endl;
		return -1;
	}

	Mat img;
	img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );

	if (!img.data){
		cout<<"\n Take care how type the picture name\n"<<endl;
		return -1;
	}
	
	canny(img);

	return 0;
}

void canny(Mat image){
	int rows = image.rows, cols = image.cols;
	typedef float arrayImage[rows];
	arrayImage array[cols];

	array = Mat2Array(image);

}

float* Mat2Array(Mat image){
//	SE PASAN TODOS LOS ELEMENTOS DE UN OBJETO MAT A UN ARREGLO BIDIMENSIONAL
	int rows = image.rows, cols = image.cols;
	float imageinArray[rows][cols];

	for (int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			imageinArray[i][j] = 0;
			imageinArray[i][j] = image.data[i*cols + j];
		}
	}

	return *imageinArray;
}
