#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("scenery.jpg");
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
	Mat dstImage2;
	Mat warpImage, rotateImage, rotateImage2;

	imshow("original image", srcImage);

	// two point express two triangle
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);

	// hand create two triangle
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols * 0.0), 
		static_cast<float>(srcImage.rows * 0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols * 0.65),
		static_cast<float>(srcImage.rows * 0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols * 0.15),
		static_cast<float>(srcImage.rows * 0.6));

	//get affine transformation
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//use affine transformation change source
	warpAffine(srcImage, dstImage, warpMat, dstImage.size());
	imshow("rotation image", dstImage);

	//use rotation function create warp affine
	Point center = Point(dstImage.cols / 2, dstImage.rows / 2);
	double angle = -30;
	double scale = 0.8;
	rotateImage2 = getRotationMatrix2D(center, angle, scale);

	warpAffine(dstImage, dstImage2, rotateImage2, dstImage.size());
	imshow("rotation2 image", dstImage2);

	waitKey(0);
	return 0;
}

