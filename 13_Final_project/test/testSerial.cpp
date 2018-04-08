#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <SerialStream.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace LibSerial;
using namespace cv;

Mat imageIn;

int main(int argc, char** argv){

    SerialStream Arduino;
    Arduino.Open("/dev/ttyUSB0");

	if( Arduino.good() ){
		std::cout<<"\n\n ARDUINO CONECTADO :D \n\n";

		Arduino.SetBaudRate(SerialStreamBuf::BAUD_9600);
	    Arduino.SetCharSize( SerialStreamBuf::CHAR_SIZE_8);

	    char num;
	    cout<<" Number of blinks = ";
	    cin>>num;

	    Arduino << char(num);
	}

    cout<<endl<<endl;

//    system("wget http://192.168.43.1:8080/photo.jpg -O p1.jpg");
    imageIn = imread("p1.jpg");

    namedWindow("IMAGEN", 0);
    imshow("IMAGEN", imageIn);
	waitKey(0);

    return 0;
}


//	ABRIR CON stdio y fopen el puerto serial
//	USAR LA CAMARA DEL CELULAR CON IPWEBCAM

//	COMPILAR:
//	g++ testSerial.cpp -o testSerial -pthread -lserial
