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
	Mat mask = (Mat_<double>(3,3) << 1,1,1,1,1,1,1,1,1 );

	for (int i=0; i<mask.rows; i++){
		for (int j=0; j<mask.cols; j++){
			cout<<" "<<	int(mask.data[i*mask.rows + j]);
		}
		cout<<endl;
	}

	Mat imageOutX = img.clone();
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
		imageOutX.data[i*imageOutX.cols + j] = abs(sum);
		}
	}
//	plot(img, imageOutX);
//  APLICANDO LA MASCARA DE PREWITT EN X
	mask.data[0*mask.cols + 0] = 1;
	mask.data[0*mask.cols + 1] = 1;
	mask.data[0*mask.cols + 2] = 1;
	mask.data[1*mask.cols + 0] = 0;
	mask.data[1*mask.cols + 1] = 0;
	mask.data[1*mask.cols + 2] = 0;
	mask.data[2*mask.cols + 0] = -1;
	mask.data[2*mask.cols + 1] = -1;
	mask.data[2*mask.cols + 2] = -1;

	Mat imageOutY = img.clone();
	sum=0; N=round(mask.rows/2); mi=0; mj=0; neighbors=0; elements=9;
	
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
		imageOutY.data[i*imageOutY.cols + j] = abs(sum);
		}
	}
//	plot(img, imageOutY);
//	SE OBTIENE LA MAGNITUD DEL GRADIENTE
	Mat gradient = img.clone();
	int x=0, y=0;

	for (int i=0; i<gradient.rows; i++){
		for(int j=0; j<gradient.cols; j++){
			x = imageOutX.data[i*imageOutX.cols + j];
			y = imageOutY.data[i*imageOutY.cols + j];
			gradient.data[i*gradient.cols + j] = sqrt( pow(x,2) + pow(y,2));
		}
	}

	plot(img, gradient);
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
