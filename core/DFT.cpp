#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat srcImage = imread("1.jpg", 0); // read image as grey picture
	if (!srcImage.data)
	{
		printf("read picture error!");
		return false;
	}
	imshow("original", srcImage);


	//get optimal dft size
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);
	Mat padded;
	// fill border with 0
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, 
		n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	// assign space for dft result(real and virtual)
	// add a new aisle to save virtual
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	// merge the planes to complexI as 2 aisle 
	merge(planes, 2, complexI);
	//dft (discrete fourier transform)
	dft(complexI, complexI);

	// plural transfrom to amplitude
	split(complexI, planes); // split multi input array into signal aisle
	magnitude(planes[0], planes[1], planes[0]);
	Mat magnitudeImage = planes[0];

	// logarithmic scale transform
	magnitudeImage += Scalar::all(1);
	log(magnitudeImage, magnitudeImage);

	//if has odd columns or odd rows, crop the spectrum
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

	//rearrange the quadrant
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy)); // ROI left up
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy));
	Mat q2(magnitudeImage, Rect(0, cy, cx, cy));
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy));

	Mat tmp;
	// left up and right down
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	// right up & left down
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	imshow("spectrum", magnitudeImage);

	waitKey();

	return 0;
}




