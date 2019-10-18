#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage;
Mat dstImage4, dstImage5;

int g_nMedianBlurValue = 3;
int g_nBilateralFilterValue = 3;


void on_medianBlurBar(int, void*)
{
	medianBlur(srcImage, dstImage4, g_nMedianBlurValue * 2 + 1); // lager than 1 odd number
	imshow("girl blur4", dstImage4);
}
void on_BilateralFilter(int, void*)
{
	bilateralFilter(srcImage, dstImage5, g_nBilateralFilterValue,
		g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
	imshow("girl blur5", dstImage5);
}

int main()
{

	/*Mat image = imread("girl.jpg");
	namedWindow("girl");
	namedWindow("gril2");
	imshow("girl", image);
	Mat out;*/


	// box filter 
	/*boxFilter(image, out, -1, Size(5, 5), cv::Point(-1, -1), BORDER_DEFAULT);
	imshow("gril2", out);*/

	//mean filter
	/*blur(image, out, Size(5, 5));
	imshow("girl2", out);*/

	// guassian filter
	/*GaussianBlur(image, out, Size(5, 5), 0, 0);
	imshow("girl2", out);*/
	
	srcImage = imread("car.jpg");
	namedWindow("girl original");
	imshow("girl original", srcImage);

	
	dstImage4 = srcImage.clone();
	dstImage5 = srcImage.clone();

	

	namedWindow("girl blur4");
	createTrackbar("MedianFilter", "girl blur4", &g_nMedianBlurValue, 40, on_medianBlurBar);
	on_medianBlurBar(g_nMedianBlurValue, 0);

	namedWindow("girl blur5");
	createTrackbar("BilateralFilter", "girl blur5", &g_nBilateralFilterValue, 40, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);


	while (char(waitKey(1)) != 'q') {}

	return 0;
}




