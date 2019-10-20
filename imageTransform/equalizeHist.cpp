#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("scenery2.jpg");
	Mat grayImage;
	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);

	imshow("original image", srcImage);
	Mat dstImage;
	equalizeHist(grayImage, dstImage);
	imshow("result image", dstImage);

	waitKey(0);
	return 0;
}

