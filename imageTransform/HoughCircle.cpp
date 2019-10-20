#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("ball.jpg");
	imshow("original", srcImage);

	Mat grayImage, dstImage, midImage;

	// turn to gray picture and blur
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(grayImage, dstImage, Size(3, 3), 2, 2);
	

	//// no use to edge detection
	//// direct hough circle change
	//vector<Vec3f> circles;
	//// sixth parameter express canny
	//HoughCircles(dstImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0); 

	//for (size_t i = 0; i < circles.size(); i++)
	//{
	//	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	//	int radius = cvRound(circles[i][2]);
	//	// draw circle center
	//	circle(dstImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
	//	// draw circle
	//	circle(dstImage, center, radius, Scalar(155, 50, 255), -1, 8, 0);
	//}
	imshow("grayImage", grayImage);
	imshow("dstImage", dstImage);

	waitKey(0);
	return 0;
}


