#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void averageFilter(Mat img);
void medianFilter(Mat img);
int median(int neighbors[], int length);
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

	averageFilter(image);

	return 0;
}

void averageFilter(Mat img){
	Mat mask = Mat(3,3, CV_8UC1, Scalar(1));
	Mat imageOut = img.clone();
	int sum, N=round(mask.rows/2), mi=0, mj=0, neighbors=0, elements=9;
	
	for (int i=0; i<img.rows; i++){
	for (int j=0; j<img.cols; j++){
		sum=0; mi=0;
		for (int ni=i-N; ni<=i+N; ni++){
			mj=0;
		for (int nj=j-N; nj<=j+N; nj++){
			if ( ni-N >= 0 && nj-N >= 0 && ni+N < img.rows && nj+N < img.cols ){
				sum += mask.data[mi*mask.cols + mj]*(img.data[ni*img.cols + nj]);
			} else
				sum += 0;

			mj++;
			}
		mi++;
		}
		imageOut.data[i*imageOut.cols + j] = round(sum/elements);
		}
	}

	plot(img, imageOut);
}

void medianFilter(Mat img){
	Mat mask = Mat::ones(3,3, CV_32F);
	Mat imageOut = img.clone();
	int sum, N=round(mask.rows/2), mi=0, mj=0, m=0, neighbors[mask.rows*mask.cols];
	
	for (int i=0; i<img.rows; i++){
	for (int j=0; j<img.cols; j++){
		mi=0; m=0;
		for (int ni=i-N; ni<=i+N; ni++){
			mj=0;
		for (int nj=j-N; nj<=j+N; nj++){
			if ( ni-N >= 0 && nj-N >= 0 && ni+N < img.rows && nj+N < img.cols ){
				neighbors[m] = mask.data[mi*mask.cols + mj]*(img.data[ni*img.cols + nj]);
			}else
				neighbors[m] = 0;

			mj++; m++;
		}
			mi++;
		}
			imageOut.data[i*imageOut.cols + j] = median(neighbors, pow(mask.cols,2));
	}
	}

//	plot(img, imageOut);
}

int median(int neighbors[], int length){
	int temp=0, ret=0;
	for (int i=1; i<length; i++)
	for (int j=0; j<length-1; j++){
		if ( neighbors[j] > neighbors[j+1] ){
			temp = neighbors[j];
			neighbors[j] = neighbors[j+1];
			neighbors[j+1] = temp;
		}
	}

	ret = round(length/2);
	return neighbors[ret];
}

void plot(Mat image, Mat newImage){
	namedWindow("Imagen de entrada", WINDOW_AUTOSIZE);
	imshow("Imagen de entrada", image);
	waitKey(0);

	namedWindow("Imagen de salida", WINDOW_AUTOSIZE);
	imshow("Imagen de salida", newImage);
	waitKey(0);
}
