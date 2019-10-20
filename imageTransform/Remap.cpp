#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat src = imread("car.jpg");
	imshow("source", src);

	Mat dst, map_x, map_y;
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			map_x.at<float>(i, j) = static_cast<float>(j);
			map_y.at<float>(i, j) = static_cast<float>(src.rows - i);
		}
	}
	remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_DEFAULT, Scalar(0, 0, 0));
	imshow("dstination", dst);


	waitKey(0);
	return 0;
}