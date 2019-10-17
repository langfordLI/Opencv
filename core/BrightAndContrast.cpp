#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;
Mat g_srcImage, g_dstImage;
int g_nContrastValue;
int g_nBrightValue;

static void on_ContrastAndBright(int, void*);


int main()
{
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	g_srcImage = imread("girl2.jpg");
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	namedWindow("beautiful girl", 1);

	//create track bar
	createTrackbar("contrast:", "beautiful girl", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("bright:", "beautiful girl", &g_nBrightValue, 200, on_ContrastAndBright);
	

	while (char(waitKey(1)) != 'q') {}

	return 0;
}

static void on_ContrastAndBright(int, void*)
{
	namedWindow("original window", 1);

	for (int y = 0; y < g_srcImage.rows; y++) // scan rows
	{
		for (int x = 0; x < g_srcImage.cols; x++) // scan cols
		{
			for (int c = 0; c < 3; c++)
			{
				// new_srcImage = contrast * srcImage(i, j) + bright
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue * 0.01)
					* (g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);
			}
		}
	}

	imshow("original window", g_srcImage);
	imshow("beautiful gril", g_dstImage);
}




