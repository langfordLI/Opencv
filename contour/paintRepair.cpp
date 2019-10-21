#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImage, saveImage, inpaintMask;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void*);

int main()
{
	srcImage = imread("scenery.jpg");
	imshow("program1", srcImage);
	saveImage = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage.size(), CV_8U);
	

	//mouse recall function
	setMouseCallback("program1", on_Mouse, 0);

	while (1)
	{
		int key = waitKey(0);

		if (key == 27)
		{
			break;
		}
		if ((char)key == '2')
		{
			inpaintMask = Scalar::all(0); // clear mask image
			srcImage.copyTo(saveImage);
			imshow("program1", srcImage);
		}
		if ((char)key == ' ')
		{
			Mat inpaintImage;
			inpaint(saveImage, inpaintMask, inpaintImage, 3, INPAINT_TELEA);
			imshow("result", inpaintImage);
			
		}
	}

	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//deal mouse not in picture
	if (x < 0 || x >= saveImage.cols || y < 0 || y >= saveImage.rows)
		return;

	//deal left button of mouse up
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	//deal left button of mouse down
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);

	// left mouse button down and move
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(saveImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(inpaintMask, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("program1", saveImage);
	}
}
