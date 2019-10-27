#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat BaseImage = imread("1.jpg");
	Mat testImage1 = imread("2.jpg");
	Mat testImage2 = imread("3.jpg");

	imshow("base image", BaseImage);
	imshow("test image1", testImage1);
	imshow("test image2", testImage2);

	Mat hsv_BaseImage, hsv_testImage1, hsv_testImage2;
	cvtColor(BaseImage, hsv_BaseImage, COLOR_BGR2HSV);
	cvtColor(testImage1, hsv_testImage1, COLOR_BGR2HSV);
	cvtColor(testImage2, hsv_testImage2, COLOR_BGR2HSV);

	Mat hsvImage_halfdown = hsv_BaseImage(Range(hsv_BaseImage.rows / 2, hsv_BaseImage.rows - 1),
		Range(0, hsv_BaseImage.cols - 1));

	int channels[] = { 0, 1 };
	MatND baseHist;
	int hue = 30, saturation = 32;
	int histSize[] = { hue, saturation };
	float h_range[] = { 0, 256 }, s_range[] = { 0, 180 };
	const float* ranges[] = { h_range, s_range };
	calcHist(&hsv_BaseImage, 1, channels, Mat(), baseHist, 2, histSize, ranges);
	normalize(baseHist, baseHist, 0, 1, NORM_MINMAX, -1, Mat());

	MatND testHist;
	calcHist(&hsv_testImage1, 1, channels, Mat(), testHist, 2, histSize, ranges);
	normalize(testHist, testHist, 0, 1, NORM_MINMAX, -1, Mat());

	MatND testHist2;
	calcHist(&hsv_testImage2, 1, channels, Mat(), testHist2, 2, histSize, ranges);
	normalize(testHist2, testHist2, 0, 1, NORM_MINMAX, -1, Mat());

	MatND halfDown_Hist;
	// hue and saturation reduce half to test hist type
	calcHist(&hsvImage_halfdown, 1, channels, Mat(), halfDown_Hist, 2, histSize, ranges);
	normalize(halfDown_Hist, halfDown_Hist, 0, 1, NORM_MINMAX, -1, Mat());


	double maxValue = 0;
	minMaxLoc(baseHist, 0, &maxValue, 0, 0);
	int scale = 10;
	// when create a mat form saturation * hue(x, y)
	Mat histImage_base = Mat::zeros(saturation * scale, hue * scale, CV_8UC3); 
	// when fill a mat outer hue, inner saturation(first rows then cols)
	for (int i = 0; i < hue; i++)
	{
		for (int j = 0; j < saturation; j++)
		{
			float binValue = baseHist.at<float>(i, j);
			int intensity = cvRound(binValue * 255 / maxValue);
			rectangle(histImage_base, Point(i * scale, j * scale),
				Point((i + 1) * scale - 1, (j + 1) * scale - 1), Scalar(intensity), FILLED);
		}
	}
	imshow("hsv hist", histImage_base);

	for (int i = 0; i < 4; i++)
	{
		double base_base = compareHist(baseHist, baseHist, i);
		double base_test1 = compareHist(baseHist, testHist, i);
		double base_test2 = compareHist(baseHist, testHist2, i);
		double base_half = compareHist(baseHist, halfDown_Hist, i);
		std::cout << "result:" <<
			"base_base:" << base_base <<
			"  base_test1:" << base_test1 <<
			" base_test2:" << base_test2 <<
			" base_half:" << base_half << std::endl;
	}

	waitKey(0);
	return 0;
}