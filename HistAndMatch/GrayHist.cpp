#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("scenery.jpg", 0);
	imshow("srcImage", srcImage);

	int channels = 0;

	MatND dstHist;
	
	int dims = 1; // svae every dimension hist array size

	float hranges[] = { 0, 255 }; 
	const float* ranges[] = { hranges }; // construct two dimension array
	
	int size = 256;	// size of the every dimension hist array so when filled add &
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;
	

	// get min and max value
	double maxValue = 0, minValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	int hpt = saturate_cast<int>(0.9 * size);
	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i * scale, size - 1), Point((i + 1) * scale - 1, size - realValue),
			Scalar(255));
	}

	imshow("result", dstImage);
	waitKey(0);
	return 0;
}

