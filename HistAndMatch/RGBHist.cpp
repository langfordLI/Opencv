#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("scenery2.jpg");
	imshow("srcImage", srcImage);

	int channels_r = 0;
	MatND redHist;
	int bins = 256; int hist_size[] = { bins };
	float range[] = { 0, 256 }; 
	const float* ranges[] = { range };
	calcHist(&srcImage, 1, &channels_r, Mat(), redHist, 1, hist_size, ranges, true, false);

	int channels_g = 1;
	MatND greenHist;
	calcHist(&srcImage, 1, &channels_g, Mat(), greenHist, 1, hist_size, ranges, true, false);

	int channels_b = 2;
	MatND blueHist;
	calcHist(&srcImage, 1, &channels_b, Mat(), blueHist, 1, hist_size, ranges, true, false);

	double maxValue_red, maxValue_green, maxValue_blue;
	minMaxLoc(redHist, 0, &maxValue_red, 0, 0);
	minMaxLoc(greenHist, 0, &maxValue_green, 0, 0);
	minMaxLoc(blueHist, 0, &maxValue_blue, 0, 0);
	int scale = 1;
	int histHeight = 256;
	Mat histImage = Mat::zeros(histHeight, bins * 3, CV_8UC3);

	for (int i = 0; i < bins; i++)
	{
		float binValue_red = redHist.at<float>(i);
		float binValue_green = greenHist.at<float>(i);
		float binValue_blue = blueHist.at<float>(i);
		
		int intensity_red = cvRound(binValue_red * histHeight / maxValue_red);
		int intensity_green = cvRound(binValue_green * histHeight / maxValue_green);
		int intensity_blue = cvRound(binValue_blue * histHeight / maxValue_blue);

		rectangle(histImage, Point(i * scale, histHeight - 1),
			Point((i + 1) * scale - 1, histHeight - intensity_red), Scalar(255, 0, 0));
		rectangle(histImage, Point((i + bins) * scale, histHeight - 1),
			Point((i + bins + 1) * scale - 1, histHeight - intensity_green), Scalar(0, 255, 0));
		rectangle(histImage, Point((i + 2 * bins) * scale, histHeight - 1),
			Point((i + 2 * bins + 1) * scale - 1, histHeight - intensity_blue), Scalar(0, 0, 255));
	}

	imshow("result", histImage);
	waitKey(0);
	return 0;
}

