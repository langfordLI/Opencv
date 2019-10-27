#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat srcImage, templateImage, resultImage;

void on_Matching(int, void*);

int match_method;
int main()
{
	srcImage = imread("girl.jpg", 1);
	templateImage = imread("template_girl.jpg", 1);

	namedWindow("source");
	namedWindow("result");

	createTrackbar("value", "source", &match_method, 5, on_Matching);
	on_Matching(0, 0);
	waitKey(0);
	return 0;
}
void on_Matching(int, void*)
{
	Mat l_srcImage;
	srcImage.copyTo(l_srcImage);
	int resultImage_cols = srcImage.cols - templateImage.cols + 1;
	int resultImage_rows = srcImage.rows - templateImage.rows + 1;
	resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);

	matchTemplate(srcImage, templateImage, resultImage, match_method);
	normalize(resultImage, resultImage, 0, 1, NORM_MINMAX, -1, Mat());

	// according minMaxLoc set most match sit
	double minValue, maxValue;
	Point minLocation, maxLocation;
	/* according match result get min match location and max match location */
	minMaxLoc(resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());
	Point matchLocation;
	/* As for SQDIFF and SQDIFF_NORMED the value is lower the match degree is higher
	other is reverse */
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation; 
	}
	else
	{
		matchLocation = maxLocation;
	}
	rectangle(l_srcImage, matchLocation,
		Point(matchLocation.x + templateImage.cols, matchLocation.y + templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);
	rectangle(resultImage, matchLocation, 
		Point(matchLocation.x + templateImage.cols, matchLocation.y + templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);
	imshow("source", l_srcImage);
	imshow("result", resultImage);
}





