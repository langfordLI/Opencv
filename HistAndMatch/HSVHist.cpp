#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("glass.jpg");
	imshow("srcImage", srcImage);

	Mat hsvImage;
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	int channels[] = { 0, 1 };

	MatND dstHist;
	int hueBinNum = 30;
	int saturationBinNum = 32;
	int histSize[] = { hueBinNum, saturationBinNum }; // svae every dimension hist array size

	float hueRange[] = { 0, 180 }; // compress hue to 0-180
	float saturationRagne[] = { 0, 256 }; // compress satruation to 0-255
	const float* ranges[] = { hueRange, saturationRagne }; // save in two dimension array

	calcHist(&hsvImage, 1, channels, Mat(), dstHist, 2, histSize, ranges,
		true, false);

	double maxValue = 0; // max value
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);  // get global value
	int scale = 10;
	Mat histImage = Mat::zeros(saturationBinNum * scale, hueBinNum * scale, CV_8UC3);

	for (int hue = 0; hue < hueBinNum; hue++)
	{
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue * 255 / maxValue); // filled color

			rectangle(histImage, Point(hue * scale, saturation * scale),
				Point((hue + 1) * scale - 1, (saturation + 1) * scale - 1),
				Scalar::all(intensity), FILLED);
		}
	}

	imshow("result", histImage);
	waitKey(0);
	return 0;
}