#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#define WINDOW_NAME1 "source window"
#define WINDOW_NAME2 "result window"

using namespace std;
using namespace cv;

Mat srcImage, grayImage, dstImage;
RNG g_rng(12345);
int g_nThreshold = 100;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

void on_Contour(int, void*);

int main()
{
	srcImage = imread("boat.jpg");
	namedWindow(WINDOW_NAME1);
	imshow(WINDOW_NAME1, srcImage);

	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	createTrackbar("value", WINDOW_NAME1, &g_nThreshold, 255, on_Contour);
	on_Contour(0, 0);

	while (1)
	{
		char key = waitKey();
		if (key == 38)
			g_nThreshold++;
		if (key == 40)
			g_nThreshold--;
		if (key == 27 || key == 'q')
			break;
	}

	return 0;
}

void on_Contour(int, void*)
{
	Canny(grayImage, dstImage, g_nThreshold, g_nThreshold * 2, 3, false);

	//find contours
	findContours(dstImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// calculate rect moment
	vector<Moments> mome(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		mome[i] = moments(contours[i], false);
	}
	// get center moment
	vector<Point2f> mome_center(contours.size());
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		mome_center[i] = Point2f(static_cast<float>(mome[i].m01 / mome[i].m00),
			static_cast<float>(mome[i].m10 / mome[i].m00));
	}

	//drawing contour + rectangle + circle
	Mat drawing = Mat::zeros(srcImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		/*cout << "(moment get area: " << mome[i].m00 << ", function get area: " <<
			contourArea(contours[i], true) << ")";*/
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
		circle(drawing, mome_center[i], 4, color, -1, 8, 0); // point for every moment use circle
	}
	namedWindow(WINDOW_NAME2);
	imshow(WINDOW_NAME2, drawing);
}