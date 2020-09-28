#include <iostream>
#include <stdio.h>
#include <string>
#include <chrono>
#include <time.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
using namespace chrono;

int main1()
{
	auto start = steady_clock::now();
	Mat img = imread("JabberWorthky.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_rot = img.clone();
	double angle = 120;
	double scale = 1;
	Point2f center(img.cols/2, img.rows/2);
	Mat mat_rot = getRotationMatrix2D(center, angle, scale);
	warpAffine(img, img_rot, mat_rot, img.size());
	auto end = steady_clock::now();
	double elapsed_time_ns = double(duration_cast<nanoseconds>(end - start).count());
	string str1 = to_string(elapsed_time_ns / 1e9);
	string str2 = to_string(angle);
	str2.resize(2);
	string Elapsed_time = "Elapsed time" + str1 + "s";
	string Angle = "Rotation Angle" + str2;
	putText(img_rot, Elapsed_time, Point(9, 13), FONT_HERSHEY_DUPLEX, 0.5, Scalar(255, 255, 255), 1);
	putText(img_rot, Angle, Point(9, 29), FONT_HERSHEY_DUPLEX, 0.5, Scalar(255, 255, 255), 1);
	namedWindow("demo", CV_WINDOW_AUTOSIZE);
	imshow("demo", img);
	namedWindow("image_rot", CV_WINDOW_AUTOSIZE);
	imshow("image_rot", img_rot);
	//imwrite("right2.jpg", img_rot);
	waitKey(0);
	destroyAllWindows;
	return 0;
}