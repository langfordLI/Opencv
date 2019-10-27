#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat g_srcImage, g_grayImage, g_srcImage_change;
int g_threshold = 30;

void on_CornerHarris(int, void*);

int main()
{
	g_srcImage = imread("scenery2.jpg");
	imshow("source", g_srcImage);
	g_srcImage_change = g_srcImage.clone(); // do not change source image

	// draw on another picture
	cvtColor(g_srcImage_change, g_grayImage, COLOR_BGR2GRAY);
	createTrackbar("value", "source", &g_threshold, 175, on_CornerHarris);
	on_CornerHarris(0, 0);

	waitKey(0);
	return 0;
}

void on_CornerHarris(int, void*)
{
	Mat dstImage = Mat::zeros(g_srcImage.size(), CV_32FC1);
	g_srcImage_change = g_srcImage.clone();


	// first corner detect
	Mat cornerImage;
	cornerHarris(g_grayImage, cornerImage, 2, 3, 0.04, BORDER_DEFAULT);
	// then normalize
	Mat normalizeImage;
	/* after normalize or threshold save current corner point information */
	normalize(cornerImage, normalizeImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	// end turn image to unsigned int8 
	convertScaleAbs(normalizeImage, dstImage);

	for (int i = 0; i < normalizeImage.rows; i++)
	{
		for (int j = 0; j < normalizeImage.cols; j++)
		{
			if ((int)normalizeImage.at<float>(i, j) > g_threshold + 80)
			{
				circle(g_srcImage_change, Point(i, j), 5, Scalar(10, 10, 255), 2, 8, 0);
				circle(dstImage, Point(i, j), 5, Scalar(0, 10, 255), 2, 8, 0);
			}
		}
	}
	imshow("result2", dstImage);
	imshow("result3", normalizeImage);
	imshow("result1", g_srcImage_change);
}