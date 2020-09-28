#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <chrono>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
using namespace chrono;

int main2()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	auto start = steady_clock::now();
	// load input
	Mat plt = imread("coca2.jpg", CV_LOAD_IMAGE_COLOR);
	Mat obj = imread("stock.jpg", CV_LOAD_IMAGE_COLOR);

	// check size
	if (plt.rows > obj.rows || plt.cols > obj.cols)
	{
		cout << "Template must smaller than object to detect" << endl;
	}

	Mat matDisplay, result;
	obj.copyTo(matDisplay);
	int result_cols = obj.cols - plt.cols + 1;
	int result_rows = obj.cols - plt.cols + 1;
	result.create(result_rows, result_cols, CV_32FC1);

	// Find mode
	matchTemplate(obj, plt, result, CV_TM_CCORR_NORMED);
	threshold(result, result, 0.9, 1, CV_THRESH_TOZERO);
	int count = 0;
	double minval, maxval;
	// threshold reduces, more objs can be detected but with high loss
	double threshold = 0.9;

	while (true)
	{
		Point minloc, maxloc;
		minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);

		if (maxval > threshold)
		{
			// draw rect
			rectangle(obj, maxloc, Point(maxloc.x + plt.cols, maxloc.y + plt.rows), Scalar(255, 0, 0), 2);
			floodFill(result, maxloc, Scalar(0), 0, Scalar(.1), Scalar(1.));
			count++;
		}
		else
			break;
	}
	auto end = steady_clock::now();
	double time_ns = double(duration_cast<nanoseconds>(end - start).count());
	string str1 = to_string(time_ns / 1e9);
	string str2 = to_string(count);
	str2.resize(2);
	string Excution_time = "ExcutionTime" + str1 + "s";
	string Threshhol_obj = "MaxThresh" + str2;
	putText(obj, Excution_time, Point(9, 13), FONT_HERSHEY_DUPLEX, 0.5, Scalar(225, 0, 0), 1);
	putText(obj, Threshhol_obj, Point(36, 26), FONT_HERSHEY_DUPLEX, 0.5, Scalar(225, 225, 225), 1);
	namedWindow("Detected", CV_WINDOW_AUTOSIZE);
	imshow("detected", obj);
	cout << "Counted: " << count << endl;
	cout << time_ns << endl;
	waitKey(0);
	destroyAllWindows();
	return 0;
}