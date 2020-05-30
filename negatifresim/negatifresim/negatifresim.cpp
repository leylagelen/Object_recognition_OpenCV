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
	VideoCapture vidCap(0); // Use Webcam thats why we enter 0
	if (!vidCap.isOpened())
	{
		cout << "Camera is not Open" << endl;
		waitKey();
	}
	int counter, wait = 0;
	cout << "plase enter count of negatif pictures" << endl;
	cin >> counter;
	ofstream file;
	file.open("C:\\OpencvCascade\\negatif.txt", ios::app);
	vector<int> sparam;
	sparam.push_back(CV_IMWRITE_JPEG_QUALITY);
	sparam.push_back(50);
	char article[250];
	while (true)
	{
		wait++;
		Mat frame;
		bool kont = vidCap.read(frame);
		if (!kont)
		{
			cout << "frame can not uploaded" << endl;
		}

		if (wait>11)
		{
			_snprintf_s(article, 250, "C:\\OpencvCascade\\Img\\Negatif\\%d.jpg", sayici);
			imwrite(article, frame, sparam);
			_snprintf_s(article, 250, "C:\\OpencvCascade\\Img\\Negatif\\%d.jpg", sayici);
			file << article << endl;
			counter++;
		}
		imshow("No more object", frame);
		if (waitKey(450) == 27)
		{
			file.close();
			break;
		}
	}
	return 0;
}


