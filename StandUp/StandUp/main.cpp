#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <ctime>
#include <Windows.h>

//#include "FaceRecognition.cpp"

using namespace cv;
using namespace std;

bool initialization(VideoCapture&, CascadeClassifier&);
bool get_img(VideoCapture, Mat&);
bool faceRecognition(Mat, vector<Rect>&, CascadeClassifier);
void Sit_or_Not(vector<Rect>);

int detected = 0;
int absent = 0;

int main()
{
	Mat frame, frame_gray;
	VideoCapture cam(0);
	CascadeClassifier face;
	vector<Rect> faceRect;

	if (!initialization(cam, face))
		return -1;

	while (1)
	{
		if (!get_img(cam, frame))
			break;

		if (!faceRecognition(frame, faceRect, face))
			break;

		Sit_or_Not(faceRect);
		//for (size_t i = 0; i < faceRect.size(); i++)
		//	rectangle(frame, faceRect[i], Scalar(0, 0, 255), 3);

		imshow("BigBrotherVideo", frame);

		if (waitKey(30) == 27)
			break;

		Sleep(10000);
	}

	waitKey(0);
	return 0;
}


bool initialization(VideoCapture &cam, CascadeClassifier &face)
{
	if (!face.load("haarcascade_frontalface_alt.xml"))
	{
		cout << "Failed to load haarcascade_frontalface_alt.xml!" << endl;
		return false;
	}

	if (!cam.isOpened())
	{
		cout << "Failed to open the camera!" << endl;
		return false;
	}

	return true;
}


bool get_img(VideoCapture cam, Mat &frame)
{
	if (!cam.read(frame))
	{
		cout << "Failed to read the frame" << endl;
		return false;
	}
	return true;
}


bool faceRecognition(Mat img, vector<Rect>& res, CascadeClassifier face)
{
	Mat img_gray;

	cvtColor(img, img_gray, CV_BGR2GRAY);
	equalizeHist(img_gray, img_gray);
	face.detectMultiScale(img_gray, res, 1.1, 2, 0);

	return true;
}


void Sit_or_Not(vector<Rect> faceRect)
{
	if (faceRect.size() == 0)
	{
		absent++;
		cout << "Buzai" << endl;
	}
	else
	{
		absent = 0;
		detected++;
		cout << "Zai" << endl;
	}

	cout << "Current data:"
		 << "Detected: " << detected << endl
		 << "Absent: " << absent << endl;
}