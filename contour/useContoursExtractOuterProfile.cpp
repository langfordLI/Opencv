#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#define WINDOW_NAME1 "source window"
#define WINDOW_NAME2 "result window"

using namespace std;
using namespace cv;

Mat srcImage, grayImage, dstImage;
RNG g_rng(12345);
int g_nThreshold;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

void on_Contour(int, void*);

int main()
{
	srcImage = imread("seneryHouse.jpg");
	namedWindow(WINDOW_NAME1);
	imshow(WINDOW_NAME1, srcImage);

	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	createTrackbar("value", WINDOW_NAME1, &g_nThreshold, 255, on_Contour);
	on_Contour(0, 0);

	while (1)
	{
		char key = waitKey();
		if (key == 38)
			g_nThreshold++;
		if (key == 40)
			g_nThreshold--;
		if (key == 27 || key == 'q')
			break;
	}

	return 0;
}

void on_Contour(int, void*)
{
	threshold(grayImage, dstImage, g_nThreshold, 255, THRESH_BINARY); // 255 is when exceed threshold value

	//find contours
	findContours(dstImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//save contours use different contaings
	vector<vector<Point>> contours_poly(contours.size()); // use polypon save contours
	vector<Rect> boundRect(contours.size()); // rectangle save
	vector<Point2f> center(contours.size()); vector<float> radius(contours.size()); //circle save

	for (int i = 0; i < contours.size(); i++)	//iterate every contours
	{	
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);
	}

	//drawing contour + rectangle + circle
	Mat drawing = Mat::zeros(srcImage.size(), CV_8UC3);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}
	namedWindow(WINDOW_NAME2);
	imshow(WINDOW_NAME2, drawing);
}