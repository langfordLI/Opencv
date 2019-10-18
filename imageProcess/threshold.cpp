#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>	
#define WINDOW_NAME "picture"


using namespace std;
using namespace cv;

Mat srcImage, tmpImage, dstImage;

int g_nThresholdValue = 100;
int g_nThresholdType = 3;


void on_Threshold(int, void*);

int main()
{
	srcImage = imread("lake.jpg");
	namedWindow(WINDOW_NAME);

	createTrackbar("value", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	createTrackbar("model", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);

	on_Threshold(0, 0);

	waitKey(0);

	return 0;

}

void on_Threshold(int, void*)
{
	threshold(srcImage, dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow(WINDOW_NAME, dstImage);
}
