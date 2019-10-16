//#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "time.h"
#define WINDOW_WIDTH 600

using namespace cv;

/*different rotate, same size ellipse*/
/*
img
Image.
position
The point where the crosshair is positioned.
color
Line color.
markerType
The specific type of marker you want to use, see MarkerTypes
thickness
Line thickness.
line_type
Type of the line, See LineTypes
markerSize
The length of the marker axis [default = 20 pixels
)
*/
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(
		img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2),
		Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType
		
	);
}


/*filled cycle*/
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(
		img,
		center,
		WINDOW_WIDTH / 32,
		Scalar(0, 0, 255),
		thickness,
		lineType
	);
}

/*polygon*/
void DrawPolygon(Mat img)
{
	int lineType = 8;
	int base_length = WINDOW_WIDTH / 10;

	Point rootPoints[1][12];
	rootPoints[0][0] = Point(4 * base_length, 2 * base_length);
	rootPoints[0][1] = Point(5 * base_length, 2 * base_length);
	rootPoints[0][2] = Point(5 * base_length, 4 * base_length);
	rootPoints[0][3] = Point(7 * base_length, 4 * base_length);
	rootPoints[0][4] = Point(7 * base_length, 5 * base_length);
	rootPoints[0][5] = Point(5 * base_length, 5 * base_length);
	rootPoints[0][6] = Point(5 * base_length, 10 * base_length);
	rootPoints[0][7] = Point(4 * base_length, 10 * base_length);
	rootPoints[0][8] = Point(4 * base_length, 5 * base_length);
	rootPoints[0][9] = Point(2 * base_length, 5 * base_length);
	rootPoints[0][10] = Point(2 * base_length, 4 * base_length);
	rootPoints[0][11] = Point(4 * base_length, 4 * base_length);
	
	const Point* ppt[1] = { rootPoints[0] };
	int npt[] = { 12 };
	fillPoly(
		img,
		ppt,
		npt,
		1,
		Scalar(255, 255, 255),
		lineType
	);

}

void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(
		img,
		start,
		end,
		Scalar(0, 0, 0),
		thickness,
		lineType
	);
}

int main()
{
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	/* atom*/
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	/*combine picture*/
	DrawPolygon(rookImage);
	rectangle(
		rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8
	);

	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH ));
	DrawLine(rookImage, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));

	imshow("picture1", atomImage);
	moveWindow("picture1", 0, 200);
	imshow("picture2", rookImage);
	moveWindow("picture2", WINDOW_WIDTH, 200);

	waitKey(0);
	return 0;

}