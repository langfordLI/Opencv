#include <opencv2/opencv.hpp>	
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage; //original, gray picture, mask picture
int g_nFillMode = 1; // flood fill mode
int g_nLowDifference = 20, g_nUpDifference = 20; // max negative difference and pasitive difference
int g_nConnectivity = 4; // floodfill low 8 connective value
int g_bIsColor = true; // color picture identifier
int g_bUseMask = false; // mask windows bool value
int g_nNewMaskVal = 255; // new draw pixel

static void onMouse(int event, int x, int y, int, void*)
{
	/*if left button not down direct return */
	if (event != EVENT_LBUTTONDOWN)
		return;

	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference; // if 0 set null range floodfill
	// or set global varible
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;
	

	/*
	0 - 7: g_nConnectivity
	8 - 15: g_nNewMaskVal left shift 8
	16 - 32: CV_FLOODFILL_FIXED_RANGE or 0
	*/
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	int b = (unsigned)theRNG() & 255; // random return 0 - 255
	int g = (unsigned)theRNG() & 255; 
	int r = (unsigned)theRNG() & 255; 
	Rect ccomp; // min border rect range
	/* if color model set scalar(b, g, r) if grey model set scalar(r * 0.299 + g * 0.587 + b * 0.114 */
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);
	
	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;
	int area;

	if (g_bUseMask)
	{
		threshold(g_maskImage, g_maskImage, 1, 128, THRESH_BINARY);

		area = floodFill(dst, g_maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference),
			flags);
		imshow("mask", g_maskImage);

	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference),
			flags);
	}
	imshow("result", dst);
	cout << area << " pixel redraw!\n";

}

int main(int argc, char** argv)
{
	g_srcImage = imread("room.jpg");
	if (!g_srcImage.data)
	{
		printf("read picture error");
		return false;
	}

	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY); // turn to grey picture
	g_maskImage.create(g_srcImage.rows + 2, g_srcImage.cols + 2, CV_8UC1); // use srcImage initial mask

	namedWindow("result", WINDOW_AUTOSIZE);

	createTrackbar("negative difference", "result", &g_nLowDifference, 255, 0);
	createTrackbar("passitive difference", "result", &g_nUpDifference, 255, 0);

	setMouseCallback("result", onMouse, 0);

	while (1)
	{
		imshow("result", g_bIsColor ? g_dstImage : g_maskImage);

		int c = waitKey(0);
		if ((c & 255) == 27)
		{
			cout << "quit...\n";
			break;
		}

		switch ((char)c)
		{
		case '1':
			if (g_bIsColor) // if original is color, turn to grey, and all element mask set 0
			{
				cout << "1 down change model to grey\n";
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else
			{
				cout << "1 down change model to color\n";
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case '2':
			if (g_bUseMask) // if 2 down, show/hide mask window
			{
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}
			break;
		case '3':
			cout << "3 down, restore original image\n";
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;
		case '4':
			cout << "4 down, use null range fill\n";
			g_nFillMode = 0;
			break;
		case '5':
			cout << "5 down, use gradient fixed fill\n";
			g_nFillMode = 1;
			break;
		case '6':
			cout << "6 down, use gradient float fill\n";
			g_nFillMode = 2;
			break;
		case '7':
			cout << "7 down, low 8 bit set 4 connectivity mode\n";
			g_nConnectivity = 4;
			break;
		case '8':
			cout << "8 down, low 8 bit set 8 connectivity mode\n";
			g_nConnectivity = 8;
			break;
		}
		

	}
	return 0;
}