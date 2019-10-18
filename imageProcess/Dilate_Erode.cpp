#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage;
Mat resImage;

int g_nTrackbarNumber = 0; // 0 express dilate, 1 express erode
int g_nStructElementSize = 3;

void Process();
void on_TrackbarNumberChange(int, void*);
void on_TrackbarSizeChange(int, void*);


int main()
{
	srcImage = imread("cat.jpg");
	namedWindow("original picture");
	imshow("original picture", srcImage);

	namedWindow("result picture");
	createTrackbar("Dilate_Erode", "result picture", &g_nTrackbarNumber, 1,
		on_TrackbarNumberChange);
	on_TrackbarNumberChange(g_nTrackbarNumber, 0);
	createTrackbar("kernel size", "result picture", &g_nStructElementSize, 21, 
		on_TrackbarSizeChange);
	on_TrackbarSizeChange(g_nStructElementSize, 0);
	waitKey(0);
	

	return 0;
}

void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, 
		Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1),
		Point(g_nStructElementSize, g_nStructElementSize)
	);

	if (g_nTrackbarNumber == 0)
	{
		dilate(srcImage, resImage, element);
	}
	else
	{
		erode(srcImage, resImage, element);
	}
	imshow("result picture", resImage);

}
void on_TrackbarNumberChange(int, void*)
{
	Process();
}
void on_TrackbarSizeChange(int, void*)
{
	Process();
}




