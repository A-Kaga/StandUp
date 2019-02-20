#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

//#include "FaceRecognition.cpp"

using namespace cv;
using namespace std;

bool faceRecognition(Mat, vector<Rect>&, CascadeClassifier);

int main()
{
	Mat frame, frame_gray;
	VideoCapture cap(0);
	CascadeClassifier face;
	vector<Rect> faceRect;

	if (!face.load("haarcascade_frontalface_alt.xml"))
	{
		cout << "Failed to load haarcascade_frontalface_alt.xml!" << endl;
		return -1;
	}

	if (!cap.isOpened())
	{
		cout << "Failed to open the camera!" << endl;
		return -1;
	}

	namedWindow("BigBrotherVideo", CV_WINDOW_AUTOSIZE);
	while (1)
	{
		if (!cap.read(frame))
		{
			cout << "Failed to read the frame" << endl;
			break;
		}

		if (!faceRecognition(frame, faceRect, face))
		{
			cout << "Error! Exiting!" << endl;
			break;
		}

		/*
		cvtColor(frame, frame_gray, CV_BGR2GRAY);
		equalizeHist(frame_gray, frame_gray);
		face.detectMultiScale(frame_gray, faceRect, 1.1, 2, 0);
		*/

		for (size_t i = 0; i < faceRect.size(); i++)
		{
			rectangle(frame, faceRect[i], Scalar(0, 0, 255), 3);
		}

		imshow("BigBrotherVideo", frame);

		if (waitKey(30) == 27)
		{
			cout << "Exiting!" << endl;
			break;
		}
	}

	waitKey(0);
	return 0;
}

bool faceRecognition(Mat img, vector<Rect>& res, CascadeClassifier face)
{
	Mat img_gray;

	cvtColor(img, img_gray, CV_BGR2GRAY);
	equalizeHist(img_gray, img_gray);
	face.detectMultiScale(img_gray, res, 1.1, 2, 0);

	return true;
}