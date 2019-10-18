#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage;
Mat resImage;

int g_nElementShape = MORPH_RECT;

int g_nMaxIteratorNum = 10; // 0 express dilate, 1 express erode
int g_nOpenCloseNum = 0; // open or close operator
int g_nErodeDilateNum = 0;	// erode or delate operator
int g_nTopBlackHatNum = 0; // top or black hat operator


void on_TrackOpenClose(int, void*);
void on_TrackErodeDilate(int, void*);
void on_TrackTopBlackDilate(int, void*);


int main()
{
	srcImage = imread("CaptainAmerica.jpg");
	namedWindow("original picture");
	imshow("original picture", srcImage);

	namedWindow("close_open picture");
	createTrackbar("Open_Close", "close_open picture",
		&g_nOpenCloseNum, 2 * g_nMaxIteratorNum + 1,
		on_TrackOpenClose);
	


	namedWindow("erode_dilate picture");
	createTrackbar("erode_dilate", "erode_dilate picture",
		&g_nErodeDilateNum, 2 * g_nMaxIteratorNum + 1,
		on_TrackErodeDilate);
	

	namedWindow("top_black picture");
	createTrackbar("Top_Black", "top_black picture",
		&g_nTopBlackHatNum, 2 * g_nMaxIteratorNum + 1,
		on_TrackTopBlackDilate);
	


	
	while (1)
	{
		int c;

		on_TrackOpenClose(g_nOpenCloseNum, 0);
		on_TrackErodeDilate(g_nErodeDilateNum, 0);
		on_TrackTopBlackDilate(g_nTopBlackHatNum, 0);

		c = waitKey(0);

		if ((char)c == 'q' || (char)c == 27)
			break;
		else if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;
		else if ((char)c == 50)
			g_nElementShape = MORPH_RECT;
		else if ((char)c == 51)
			g_nElementShape = MORPH_CROSS;
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;
	}
	

	return 0;
}

void on_TrackOpenClose(int, void*)
{
	int offset = g_nOpenCloseNum - g_nMaxIteratorNum;
	int Absoluate_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
		Size(2 * Absoluate_offset + 1, 2 * Absoluate_offset + 1),
		Point(Absoluate_offset, Absoluate_offset)
	);
	if (offset < 0)
	{
		morphologyEx(srcImage, resImage, MORPH_OPEN, element);
	}
	else
	{
		morphologyEx(srcImage, resImage, MORPH_CLOSE, element);
	}
	imshow("close_open picture", resImage);
}
void on_TrackErodeDilate(int, void*)
{
	int offset = g_nErodeDilateNum - g_nMaxIteratorNum;
	int Absoluate_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
		Size(2 * Absoluate_offset + 1, 2 * Absoluate_offset + 1),
		Point(Absoluate_offset, Absoluate_offset)
	);
	if (offset < 0)
	{
		morphologyEx(srcImage, resImage, MORPH_ERODE, element);
	}
	else
	{
		morphologyEx(srcImage, resImage, MORPH_DILATE, element);
	}
	imshow("erode_dilate picture", resImage);
}
void on_TrackTopBlackDilate(int, void*)
{
	int offset = g_nTopBlackHatNum - g_nMaxIteratorNum;
	int Absoluate_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,
		Size(2 * Absoluate_offset + 1, 2 * Absoluate_offset + 1),
		Point(Absoluate_offset, Absoluate_offset)
	);
	if (offset < 0)
	{
		morphologyEx(srcImage, resImage, MORPH_TOPHAT, element);
	}
	else
	{
		morphologyEx(srcImage, resImage, MORPH_BLACKHAT, element);
	}
	imshow("top_black picture", resImage);
}