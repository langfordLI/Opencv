/*first use mouse divide the picture
then use space to calculate show different color */

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat g_srcImage, g_maskImage;
Point prevPt(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void*);

int main()
{
	g_srcImage = imread("mountain.jpg");
	imshow("program1", g_srcImage);

	Mat srcImage, grayImage; //src used to save image
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY); // change mask image to gray image
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0); // at last all black

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
			g_maskImage = Scalar::all(0); // clear mask image
			srcImage.copyTo(g_srcImage);
			imshow("program1", g_srcImage);
		}
		if ((char)key == ' ')
		{
			int compCount = 0; // save total contours count
			int i, j;

			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			// search contours on mask image
			findContours(g_maskImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
			{
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1,
					8, hierarchy, INT_MAX);
			}
			//deal with 0 condition
			if (compCount == 0)
			{
				continue;
			}
			vector<Vec3b> colorTab;
			for (int i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);
				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}

			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage); // direct input src image, output mask
			dTime = (double)getTickCount() - dTime;
			cout << "deal time " << dTime * 1000 / getTickFrequency() << endl;

			// watershed image iterate to save in mask image
			Mat watershedImage(maskImage.size(), CV_8UC3); // first copy a type
			for (i = 0; i < maskImage.rows; i++)
			{
				for (j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0 || index > compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
				
			}
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("watershed transform", watershedImage);
			
		}
	}

	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//deal mouse not in picture
	if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows)
		return;

	//deal left button of mouse
	if (event == EVENT_LBUTTONDOWN || !(flags & EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);

	// left mouse button down and move
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow("program1", g_srcImage);
	}
}
