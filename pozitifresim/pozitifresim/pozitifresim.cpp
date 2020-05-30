#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include<conio.h>
#include<fstream>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	VideoCapture vidCap(0);
	if (!vidCap.isOpened())
	{
		cout << "Camera is not Open" << endl;
		waitKey();
	}
	int counter = 0;
	cout << "Please enter count of positive pictures" << endl;
	cin >> counter;
	namedWindow("please show objet to middle.", CV_WINDOW_AUTOSIZE);
	ofstream file;
	file.open("C:\\OpencvCascadeEgitim\\pozitif.txt", ios::app);
	Mat gec; 
	vidCap.read(gec);
	Mat background;

	vector<int> sparam;
	sparam.push_back(CV_IMWRITE_JPEG_QUALITY);
	sparam.push_back(50);
	char article[250]; 
	int wait = 0; 

	int width = 120;
	createTrackbar("Width", "please show objet to middle", &width, 320);
	int height = 120;
	createTrackbar("Height", "please show objet to middle", &height, 240);
	int xeks1 = 200, xeks2 = 440, yeks1 = 120, yeks2 = 360;
	int start = -1;

	while (1)
	{

		Mat frame;
		bool kont = vidCap.read(frame);
		flip(frame, frame, 1); 
		if (!kont)
		{
			cout << "frame can not uploaded" << endl;
		}
		xeks1 = (640 - (width * 2)) / 2;
		xeks2 = xeks1 + (width * 2);
		yeks1 = (480 - (height * 2)) / 2;
		yeks2 = yeks1 + (height * 2);
		background = Mat::zeros(gec.size(), gec.type());
		line(background, Point(xeks1, 0), Point(xeks1, 480), Scalar(0, 255, 0), 1);
		line(background, Point(xeks2, 0), Point(xeks2, 480), Scalar(0, 255, 0), 1);
		line(background, Point(0, yeks1), Point(640, yeks1), Scalar(0, 255, 0), 1);
		line(background, Point(0, yeks2), Point(640, yeks2), Scalar(0, 255, 0), 1);
		char a = waitKey(480);
		if (start == -1) 
		{
			wait = 0;
			putText(background, "please show objet to middle", Point(20, 30), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
			putText(background, "Start learning with 'b' button", Point(20, 60), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
			putText(background, "Keep press to ESC button for exit", Point(10, 460), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
		}
		if (a == 'b') 
			start = start*(-1);
		if (start == 1 && wait <= 10) 
		{
			if (wait % 2 == 0)
			{
				_snprintf_s(article, 250, "%d", 5 - wait / 2); 
				putText(background, article, Point(20, 20), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
			}
			wait++;
		}
		if (wait >= 10)
		{
			putText(background, "Adding pictures…", Point(20, 20), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
			_snprintf_s(article, 250, "C:\\OpencvCascade\\img\\pozitif\\%d.jpg", counter);
			imwrite(article, frame, sparam); 
			_snprintf_s(article, 250, "C:\\OpencvCascade\\img\\pozitif\\%d.jpg", counter);
			file << article << " 1 " << xeks1 << " " << yeks1 << "  " << (width * 2) << "  " << (height * 2) << endl; 
			counter++;
		}
		frame = frame + background; 
		imshow("please show objet to middle", frame);
		if (waitKey(20) == 27)
		{
			file.close();
			break;
		}
	}
	return 0;
}