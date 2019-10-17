#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

bool ROI_AddImage()
{
	Mat srcImage = imread("picture\\dota_pa.jpg");
	Mat logoImage = imread("picture\\dota_logo.jpg");
	if (!srcImage.data)
	{
		printf("read srcImage error~!\n");
		return false;
	}
	if (!logoImage.data)
	{
		printf("read logoImage error~!\n");
		return false;
	}

	//define a area to set ROI(region of interest)
	Mat imageROI = srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));
	//load mask(must grey picture)
	Mat mask = imread("picture\\dota_logo.jpg", 0);
	// copy mask to ROI
	logoImage.copyTo(imageROI, mask);


	namedWindow("use image overlay");
	imshow("image overlay", srcImage);

	return true;
}

bool LinearBlending()
{
	Mat srcImage1 = imread("picture\\mogu.jpg");
	Mat srcImage2 = imread("picture\\rain.jpg");
	if (!srcImage1.data)
	{
		printf("srcImage1 read error!");
		return false;
	}
	if (!srcImage2.data)
	{
		printf("srcImage2 read error!");
		return false;
	}

	Mat dstImage;
	double alphaValue = 0.5;
	double betaValue = 1.0 - alphaValue;

	addWeighted(srcImage2, alphaValue, srcImage1, betaValue, 0.0, dstImage);

	/*namedWindow("Linear mixture", 1);
	imshow("Linear mixture", srcImage1);*/
	namedWindow("Linear mixture", 1);
	imshow("Linear mixture", dstImage);

	return true;
}

int main()
{
	if (ROI_AddImage() && LinearBlending())
	{
		cout << "succeed" << endl;
	}
	waitKey(0);
	return 0;
}