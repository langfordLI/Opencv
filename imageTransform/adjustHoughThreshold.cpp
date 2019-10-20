#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

Mat srcImage, grayImage, midImage, edgeImage, dstImage;
std::vector<Vec4i> g_lines;
int g_nThreshold = 100;

void on_HoughLines(int, void*);

int main()
{
	srcImage = imread("building2.jpg");
	namedWindow("result");


	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(grayImage, midImage, Size(3, 3), 2, 2, BORDER_DEFAULT);
	Canny(midImage, edgeImage, 50, 200, 3);
	

	createTrackbar("threshold", "result", &g_nThreshold, 200, on_HoughLines);
	on_HoughLines(0, 0);

	waitKey(0);
	return 0;
}

void on_HoughLines(int, void*)
{
	// turn edgeImage to dstImage
	cvtColor(edgeImage, dstImage, COLOR_GRAY2BGR);
	HoughLinesP(edgeImage, g_lines, 1, CV_PI / 180, g_nThreshold + 1, 50, 10);

	for (size_t i = 0; i < g_lines.size(); i++)
	{
		Vec4i l = g_lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), 
			Scalar(23, 180, 55), 1, LINE_AA);

	}
	imshow("result", dstImage);
}