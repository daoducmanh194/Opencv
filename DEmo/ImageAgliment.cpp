#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <math.h>
#include <opencv2\core\core.hpp>
#include <opencv2\calib3d.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\features2d.hpp>

using namespace std;
using namespace cv;
using namespace chrono;

const int MAX_FEATURES = 500;
const float GOOD_MATCH_PERCENTAGE = 0.2;

int main3()
{
	Mat img_obj = imread("JabberWorthky.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_plt = imread("right1.jpg", CV_LOAD_IMAGE_COLOR);

	auto start = steady_clock::now();
	// Convert to the gray
	Mat obj_gray, plt_gray;
	cvtColor(img_obj, obj_gray, CV_BGR2GRAY);
	cvtColor(img_plt, plt_gray, CV_BGR2GRAY);

	// keypoint and description
	vector<KeyPoint>  keypoint1, keypoint2;
	Mat description1, description2;
	
	// Detect ORB features and compute descriptions
	Ptr<Feature2D> orb = ORB::create(MAX_FEATURES);
	orb->detectAndCompute(obj_gray, Mat(), keypoint1, description1);
	orb->detectAndCompute(plt_gray, Mat(), keypoint2, description2);

	// Match features
	vector<DMatch> matches;
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
	matcher->match(description1, description2, matches, Mat());

	// Sort matches by score
	std::sort(matches.begin(), matches.end());

	// Remove not do good matches
	const int numGoodMatches = matches.size()*GOOD_MATCH_PERCENTAGE;
	matches.erase(matches.begin() + numGoodMatches, matches.end());

	// Draw top matches
	Mat imMatches;
	drawMatches(img_obj, keypoint1, img_plt, keypoint2, matches, imMatches);
	auto end = steady_clock::now();
	double time_ns = double(duration_cast<nanoseconds>(end - start).count());
	string str1 = to_string(time_ns / 1e9);
	string str2 = to_string(matches.size());
	string Time_excution = "TimeExcution :" + str1 + "s";
	string Matches_Number = "NumberOfMatches :" + str2;
	putText(imMatches, Time_excution, Point(9, 13), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 255), 1);
	putText(imMatches, Matches_Number, Point(18, 26), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 255), 1);
	namedWindow("Results", CV_WINDOW_AUTOSIZE);
	imshow("Results", imMatches);

	auto start1 = steady_clock::now();
	// Extract location of good matches
	std::vector<Point2f> points1, points2;

	for (size_t i = 0; i < matches.size(); i++)
	{
		points1.push_back(keypoint1[matches[i].queryIdx].pt);
		points2.push_back(keypoint2[matches[i].trainIdx].pt);
	}

	Mat h, im1Reg;
	// Find homography
	h = findHomography(points1, points2, CV_RANSAC);
	double averge=0;
	for (int i = 0; i < matches.size()-1; i++) {
		double x1 = keypoint1[i].pt.x - keypoint1[i + 1].pt.x;
		double y1 = keypoint1[i].pt.y - keypoint1[i + 1].pt.y;
		for (int j = 0; j < matches.size()-1; j++) {
			double x2 = keypoint2[j].pt.x - keypoint2[j+1].pt.x;
			double y2 = keypoint2[j].pt.y - keypoint2[j+1].pt.y;
			double arc_angle = (x1*x2 + y1*y2) / (sqrt(x1*x1 + y1*y1) * sqrt(x2*x2 + y2*y2));
			double angle = acos(arc_angle) * 180 / acos(-1);
			//if (angle < acos(-1) & angle > acos(-1)/2) angle = 90 + angle;
			//if (angle < 0 & angle > 3*acos(-1) / 2) angle = 90 + angle;
			averge += angle;
		}
	}
	cout << averge/(matches.size()*matches.size()) << endl;
	// Use homography to wrap image
	warpPerspective(img_obj, im1Reg, h, img_plt.size());
	auto end1 = steady_clock::now();
	double time_ns1 = double(duration_cast<nanoseconds>(end1 - start1).count());
	string str3 = to_string(time_ns1/1e9);
	string TimeExtract = "TimeExtract :" + str3 + "s";
	string str4 = to_string(averge/(matches.size()*matches.size()));
	string Angle = "Angle :" + str4 + "degree";
	putText(im1Reg, TimeExtract, Point(9, 13), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 255), 1);
	putText(im1Reg, Angle, Point(18, 26), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 255), 1);
	putText(im1Reg, Matches_Number, Point(27, 39), FONT_HERSHEY_DUPLEX, 0.5, Scalar(0, 0, 255), 1);
	namedWindow("Reg", CV_WINDOW_AUTOSIZE);
	imshow("Extrac", im1Reg);

	// Rotate
	Mat im2Reg = img_obj.clone();
	double Angle1 = 180;
	double scale = 1;
	Point2f center(img_obj.cols / 2, img_obj.rows / 2);
	Mat mat_rot = getRotationMatrix2D(center, Angle1, scale);
	warpAffine(img_obj, im2Reg, mat_rot, img_obj.size());
	namedWindow("Rota_Point", CV_WINDOW_AUTOSIZE);
	imshow("Rota_Point", im2Reg);
	waitKey(0);
	destroyAllWindows();
	cout << h << endl;
	return 0;
 }