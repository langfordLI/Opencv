#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

Mat srcImage, dstImage, grayImage;
int g_nThreshold = 80;
int g_nThreshold_max = 255;
vector<vector<Point>> g_nContours;
vector<Vec4i> g_nHierarchy;
RNG g_rng(12345);

void on_ThresholdChange(int, void*);

int main()
{
	//console font
	system("color 1F");

	srcImage = imread("animate.jpg", 1);
	namedWindow("source image", WINDOW_AUTOSIZE);
	imshow("source image", srcImage);


	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	//namedWindow("result image");
	//imshow("result image", grayImage);

	createTrackbar("threshold", "source image", &g_nThreshold, g_nThreshold_max, on_ThresholdChange);
	on_ThresholdChange(0, 0);

	waitKey(0);
	return  0;
}

void on_ThresholdChange(int, void*)
{
	// two-value model transform 
	threshold(grayImage, dstImage, g_nThreshold, 255, THRESH_BINARY);
	// a series point construct convexity
	findContours(dstImage, g_nContours, g_nHierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//traveling every contours search convexity
	vector<vector<Point> > hull(g_nContours.size());
	for (unsigned int i = 0; i < g_nContours.size(); i++)
	{
		//search every contours in all find contours
		convexHull(Mat(g_nContours[i]), hull[i], false);
	}
	//draw all convexity
	Mat drawing = Mat::zeros(dstImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_nContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_nContours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}

	
	imshow("result image", drawing);
}

