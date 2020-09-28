#include <iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main2()
{
	Mat label = imread("coca2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat find = imread("stock.jpg", CV_LOAD_IMAGE_COLOR);


}