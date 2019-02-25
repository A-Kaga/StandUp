#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

#include <ctime>
#include <Windows.h>

#include "Python.h"

//#include "FaceRecognition.cpp"

using namespace cv;
using namespace std;

bool initialization(VideoCapture&, CascadeClassifier&);
bool get_img(VideoCapture, Mat&);
bool faceRecognition(Mat, vector<Rect>&, CascadeClassifier);
void sit_or_not(vector<Rect>);
void notification();

int detected = 0;
int absent = 0;
int sit_count = 0;
bool sit_flag = false;
bool sent_flag = false;
bool test_flag = true;

int main()
{
	notification();
	return 0;
	/*Mat frame, frame_gray;
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

		sit_or_not(faceRect);

		imshow("BigBrotherVideo", frame);

		if (waitKey(30) == 27)
			break;

		Sleep(2000);
	}

	waitKey(0);
	return 0;*/
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


void sit_or_not(vector<Rect> faceRect)
{
	if (faceRect.size() == 0)
	{
		absent++;
		//cout << "Buzai" << endl;
	}
	else
	{
		absent = 0;
		detected++;
		//cout << "Zai" << endl;
	}

	if (!sit_flag && detected >= 5)
		sit_flag = true;
	if (absent >= 2)
	{
		sit_flag = false;
		detected = 0;
	}

	if (sit_flag)
	{
		if ((sent_flag && sit_count % 3 == 0) || !sent_flag)
		{
			notification();
			sent_flag = true;
		}
		sit_count++;
	}
	cout << "Current data:" << endl
		 << "Detected: " << detected << endl
		 << "Absent: " << absent << endl << endl;
}


void notification()
{
	Py_Initialize();
	/*
	string path = "~/python";
	string chdir_cmd = string("sys.path.append(\"") + path + "\")";
	const char* cstr_cmd = chdir_cmd.c_str();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString(cstr_cmd);
	*/

	PyObject * pModule = PyImport_ImportModule("notification");
	PyObject * pFunc = PyObject_GetAttrString(pModule, "notification");
	PyEval_CallObject(pFunc, NULL);
	Py_Finalize();
}