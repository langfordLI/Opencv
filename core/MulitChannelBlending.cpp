#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread("dota_jugg.jpg");
	Mat logoImage = imread("dota_logo.jpg", 0); // turn to grey graph to change
	vector<Mat> channels;
	split(srcImage, channels);
	Mat imageChannels = channels.at(1);
	addWeighted(imageChannels(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0,
		logoImage, 0.5, 0, imageChannels(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("split");
	
	imshow("split", srcImage);
	waitKey(0);
	return 0;
}






