#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{

	
	Mat srcImage = imread("building.jpg");
	
	Mat midImage, grayImage, dstImage;

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, midImage, Size(3, 3));
	Canny(midImage, midImage, 50, 200, 3);
	
	
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);

	/* Standard Hough Transform*/
	//vector<Vec2f> lines;
	//HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);	

	/* Progressive Probabilistic Hough Transform*/
	vector<Vec4i> lines;
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);

	for (size_t i = 0; i < lines.size(); i++)
	{
		/*float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);*/

		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);

	}

	imshow("original", srcImage);
	imshow("detection", midImage);
	imshow("result", dstImage);

	/*Progressive Probabilistic Hough Transform*/

	


	waitKey(0);
}