#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	Mat srcImage = imread("1.jpg");
	imshow("source image", srcImage);

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); // create same picture

	double time0 = static_cast<double>(getTickCount());

	colorReduce(srcImage, dstImage, 32);

	time0 = ((double)getTickCount() - time0) / getTickFrequency(); // calculate time
	cout << "work time" << time0 << "s" << endl;

	imshow("result", dstImage);
	waitKey(0);

}

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();
	//get iterator
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); // initial sit
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); // end sit

	for (; it != itend; ++it)
	{
		(*it)[0] = (*it)[0] / div * div + div / 2; // blue aisle
		(*it)[1] = (*it)[1] / div * div + div / 2; // green aisle
		(*it)[2] = (*it)[2] / div * div + div / 2; // red aisle
	}
}