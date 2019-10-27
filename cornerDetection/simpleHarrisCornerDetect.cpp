#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("scenery1.jpg", 0);
	imshow("source", srcImage);

	Mat dstImage;
	cornerHarris(srcImage, dstImage, 2, 3, 0.01);

	// get 2 value image 
	Mat two_image;
	threshold(dstImage, two_image, 0.00001, 255, THRESH_BINARY);
	imshow("result", two_image);

	waitKey(0);
	return 0;
}