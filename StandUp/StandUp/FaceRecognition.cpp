/*
#pragma once  

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

bool faceRecognition(Mat frame, vector<Rect>& res)
{
	Mat frame_gray;
	CascadeClassifier face;

	if (!face.load("haarcascade_frontalface_alt.xml"))
	{
		cout << "Failed to load haarcascade_frontalface_alt.xml!" << endl;
		return false;
	}

	cvtColor(frame, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	face.detectMultiScale(frame_gray, res, 1.1, 2, 0);

	return true;
}
*/