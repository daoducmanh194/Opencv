#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	cout << "The five black-wing of Abyss" << endl;
	Mat img1 = imread("Jabberworthky.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread("Griffin.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img3 = imread("Raven.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img4 = imread("Owl.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img5 = imread("Dodo.jpg", CV_LOAD_IMAGE_GRAYSCALE);

	imshow("JabberWorthky", img1);
	imshow("Griffin", img2);
	imshow("Raven", img3);
	imshow("Owl", img4);
	imshow("Dodo", img5);
	waitKey(0);
	destroyAllWindows();
	return 0;
}