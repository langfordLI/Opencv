#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

Mat srcImage, edgeImage, grayImage, dstImage;

int g_nCannyLowThreshold = 1;

Mat g_nSobel_X, g_nSobel_Y;
Mat g_nAbsSobel_X, g_nAbsSobel_Y;
int g_nKernelSize = 1;

Mat g_nScharr_X, g_nScharr_Y;
Mat g_nAbsScharr_X, g_nAbsScharr_Y;

void on_Canny(int, void*);
void on_Sobel(int, void*);
void on_Scharr();

int main()
{
	srcImage = imread("girl3.jpg");
	namedWindow("canny detection");
	imshow("original detection", srcImage);

	dstImage.create(Size(srcImage.cols, srcImage.rows), srcImage.type());
	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);

	createTrackbar("Canny detection", "canny detection", &g_nCannyLowThreshold,
		120, on_Canny);
	on_Canny(0, 0);

	namedWindow("sobel detection");
	createTrackbar("sobel detection", "sobel detection", &g_nKernelSize, 3, on_Sobel);

	on_Scharr();

	//Mat src = imread("TreeGirl.jpg");
	//Mat grad_x, grad_y;
	//Mat abs_grad_x, abs_grad_y;
	//Mat dst;

	//imshow("sobel edge detection", src);

	////x direction gradient
	//Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(grad_x, abs_grad_x);
	//imshow("x direction sobel", abs_grad_x);

	////y direction gradient
	//Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	//convertScaleAbs(grad_y, abs_grad_y);
	//imshow("y direction sobel", abs_grad_y);

	//// merge gradient
	//addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	//imshow("total result sobel", dst);

	waitKey(0);

	return 0;
}

void on_Canny(int, void*)
{
	blur(grayImage, edgeImage, Size(3, 3));
	Canny(edgeImage, edgeImage, g_nCannyLowThreshold, g_nCannyLowThreshold * 3, 3);
	dstImage = Scalar::all(0);
	srcImage.copyTo(dstImage, edgeImage);

	imshow("canny detection", dstImage);

}

void on_Sobel(int, void*)
{
	//x direction gradient
	Sobel(srcImage, g_nSobel_X, CV_16S, 1, 0, (2 * g_nKernelSize + 1), 1, 1,  BORDER_DEFAULT);
	convertScaleAbs(g_nSobel_X, g_nAbsSobel_X); // convert result to 8 bit


	//y direction gradient
	Sobel(srcImage, g_nSobel_Y, CV_16S, 0, 1, (2 * g_nKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(g_nSobel_Y, g_nAbsSobel_Y);


	// merge gradient
	addWeighted(g_nAbsSobel_X, 0.5, g_nAbsSobel_Y, 0.5, 0, dstImage);
	imshow("sobel detection", dstImage);
}

void on_Scharr()
{
	Scharr(srcImage, g_nScharr_X, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_nScharr_X, g_nAbsScharr_X);

	Scharr(srcImage, g_nScharr_Y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(g_nScharr_Y, g_nAbsScharr_Y);

	addWeighted(g_nAbsScharr_X, 0.5, g_nAbsScharr_Y, 0.5, 0, dstImage);
	imshow("Scharr detection", dstImage);
}