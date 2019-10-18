#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage;
Mat dstImage1, dstImage2, dstImage3;
int g_nBoxFilterValue = 3; // box filter
int g_nMeanBlurValue = 3;
int g_nGaussianBlurValue = 3;

void on_BoxFilterBar(int, void*)
{
	boxFilter(srcImage, dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("girl blur1", dstImage1);
}
void on_MeanBlurBar(int, void*)
{
	blur(srcImage, dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("girl blur2", dstImage2);
}
void on_GaussianBlurBar(int, void*)
{
	GaussianBlur(srcImage, dstImage3, Size(g_nGaussianBlurValue * 2 + 1, g_nGaussianBlurValue * 2 + 1), 0, 0);
	imshow("girl blur3", dstImage3);
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
	
	srcImage = imread("1.jpg");
	namedWindow("girl original");
	imshow("girl original", srcImage);

	dstImage1 = srcImage.clone();
	dstImage2 = srcImage.clone();
	dstImage3 = srcImage.clone();

	namedWindow("girl blur1");
	createTrackbar("boxFilter", "girl blur1", &g_nBoxFilterValue, 40, on_BoxFilterBar);
	on_BoxFilterBar(g_nBoxFilterValue, 0);
	//imshow("girl blur1", dstImage1);

	namedWindow("girl blur2");
	createTrackbar("BlurFilter", "girl blur2", &g_nMeanBlurValue, 40, on_MeanBlurBar);
	on_BoxFilterBar(g_nMeanBlurValue, 0);
	//imshow("girl blur1", dstImage1);
	namedWindow("girl blur3");
	createTrackbar("GaussianFilter", "girl blur3", &g_nGaussianBlurValue, 40, on_GaussianBlurBar);
	on_BoxFilterBar(g_nGaussianBlurValue, 0);


	while (char(waitKey(1)) != 'q') {}

	return 0;
}




