#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat g_srcImage, g_grayImage;
int g_threshold = 30;

void on_GoodFeaturesToTrack(int, void*);

int main()
{
	g_srcImage = imread("scenery4.jpg");
	imshow("source", g_srcImage);

	// draw on another picture
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	createTrackbar("value", "source", &g_threshold, 500, on_GoodFeaturesToTrack);
	on_GoodFeaturesToTrack(0, 0);

	waitKey(0);
	return 0;
}

void on_GoodFeaturesToTrack(int, void*)
{
	if (g_threshold <= 1)
	{
		g_threshold = 1; // if not deal the situation, when value is 1 the point size will reture 
		// to large size
	}

	std::vector<Point2f> corners;
	double qualityLevel = 0.01; // corner detect acceptable min feature value
	double minDistance = 10; // minimum corner distance
	int blockSize = 3; // correlate gradient matrix corner range
	double k = 0.04; // weight

	/* every time use gray image deal with algorithm */
	goodFeaturesToTrack(g_grayImage, corners, g_threshold, qualityLevel, minDistance, Mat(),
		blockSize, false, k);

	

	// not direct draw on source picture
	Mat copy = g_srcImage.clone(); // draw on the copy image
	for (unsigned int i = 0; i < corners.size(); i++)
	{
		circle(copy, corners[i], 4, Scalar(theRNG().uniform(0, 255), theRNG().uniform(0, 255),
			theRNG().uniform(0, 255)), -1, 8, 0);
	}
	imshow("result", copy);

	Size winSize = Size(5, 5);
	Size zeroSize = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001);
	cornerSubPix(g_grayImage, corners, winSize, zeroSize, criteria);
	for (int i = 0; i < corners.size(); i++)
	{
		std::cout << "precise corrdinate: (" << corners[i].x << ", " << corners[i].y << ")\n";
	}
	std::cout << std::endl;
}