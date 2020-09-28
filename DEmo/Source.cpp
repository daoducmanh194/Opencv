#include <iostream>
#include <stdio.h>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << "Learn OpenCV" << endl;
	Mat img = imread("girl3.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_gray = imread("girl3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_blur, img_resize;
	// Blur
	blur(img, img_blur, Size(10, 10));
	namedWindow("image_blur", CV_WINDOW_AUTOSIZE);
	// Resize
	resize(img, img_resize, Size(img.cols / 2, img.rows / 2));
	namedWindow("image_resize", CV_WINDOW_AUTOSIZE);
	// Rotate
	Mat img_rot = img.clone();
	double angle = 45.0;
	double scale = 1.5;
	Point2f center(img.cols / 2, img.rows / 2);
	Mat mat_rot = getRotationMatrix2D(center, angle, scale);
	warpAffine(img, img_rot, mat_rot, img.size());
	namedWindow("image_rot", CV_WINDOW_AUTOSIZE);
	// Skew+Shearing
	Mat img_shrearing;
	double M[2][3] = { 1, 0.5, 0, 0, 1, 0 }; 
	Mat matRot(2, 3, CV_64F, M); 
	warpAffine(img, img_shrearing, matRot, img.size());
	namedWindow("image_Skew", CV_WINDOW_AUTOSIZE);
	// Threshold and Adapitive Threshold
	Mat img_bw;
	threshold(img_gray, img_bw, 125, 255, 0);
	namedWindow("image_Threshold", CV_WINDOW_AUTOSIZE);
	Mat img_adpThr;
	adaptiveThreshold(img_gray, img_adpThr, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -5);
	namedWindow("image_adpThreshold", CV_WINDOW_AUTOSIZE);
	//Otsu
	Mat img_ot = img_gray.clone();
	//cvThreshold(img_gray, img_ot, 125, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	namedWindow("image_Otsu", CV_WINDOW_AUTOSIZE);

	// Sang va tuong phan
	Mat tp = img.clone();
	double alpha = 2.0;
	double beta = 30;
	for (int i = 0; i < img.rows; i++)
		for (int j = 0; j < img.cols; j++)
			for (int k = 0; k < 3; k++)
				tp.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha*(tp.at<Vec3b>(i, j)[k]) + beta);
	namedWindow("tuongphan", CV_WINDOW_AUTOSIZE);

	imshow("Ex1", img);
	imshow("Ex2", img_gray);
	imshow("image_blur", img_blur);
	imshow("image_resize", img_resize);
	imshow("image_rotate", img_rot);
	imshow("image_Skew", img_shrearing);
	imshow("image_Threshold", img_bw);
	imshow("image_adpThreshold", img_adpThr);
	imshow("image_Otsu", img_ot);
	imshow("image_tuongphan", tp);
	waitKey(0);
	destroyAllWindows();
	return 0;
}