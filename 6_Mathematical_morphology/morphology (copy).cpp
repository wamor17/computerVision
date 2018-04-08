#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <cstdlib>

using namespace std;
using namespace cv;

Mat element(int figure);
Mat dilatation(Mat image, Mat element);
Mat erotion(Mat image, Mat element);
Mat opening();
Mat closing();
void plot(Mat image, Mat element);

int main(int argc, char **argv)
{
	if(argc != 2) {
	cout <<" Type currently the picture name and extension " << endl;
	return -1;
	}

	Mat image;
	image = imread(argv[1], 0);

	if (!image.data){
		cout<<"take care how type the picture name"<<endl;
		return -1;
	}

	dilatation(image, element(3));

	return 0;
}

Mat element(int figure){
	if(figure==1){
		// DIBUJA UN CÍRCULO
		Mat element(30, 30, CV_8UC1, Scalar(255));
		int xc=round(element.cols/2), yc=round(element.rows/2), R=round(element.cols/2), r=0;
	
		for(int i=0; i<element.rows; i++){
			for(int j=0; j<element.cols; j++){
				r = round(sqrt(pow((j-xc),2)+pow((i-yc),2)));
				if(r <= R)
					element.data[element.cols*i + j] = 0;
				else
					element.data[element.cols*i + j] = 255;
			}
		}

		return element;
	}else if(figure==2){
		// DIBUJA UNA CRUZ
		Mat element(30, 30, CV_8UC1, Scalar(255));
		int xc=round(element.cols/2), yc=round(element.rows/2), R=round(element.cols/2), r=0;
		int L=R/2;

		for(int i=0; i<element.rows; i++){
			for(int j=0; j<element.cols; j++){
				if(i<=(yc+L) && i>=(yc-L) || j<=(xc+L) && j>=(xc-L))
					element.data[element.cols*i + j] = 0;
				else
					element.data[element.cols*i + j] = 255;
			}
		}

		return element;
	}else if (figure=3){
		//DIBUJA UN CUADRADO
		Mat element(3, 3, CV_8UC1, Scalar(0));

		return element;
	}else
		cout<<"\n\n FIGURA NO DEFINIDA"<<endl;
}

Mat dilatation(Mat image, Mat element){
	Mat newImage = image.clone();
	int cX = round(element.cols/2), cY = round(element.rows/2);
	int cElement = element.at<Vec3b>(cX,cY)[0];
	float ni=0, nj=0;

	for (int i=0; i<newImage.rows; i++){
		for (int j=0; j<newImage.cols; j++){
			if( newImage.at<Vec3b>(i,j)[0] == cElement ){
				newImage.at<Vec3b>(i,j)[0] = 177;
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


