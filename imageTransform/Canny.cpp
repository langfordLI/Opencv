#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>	
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	Mat src = imread("orange.jpg");
	Mat src1 = src.clone();

	imshow("Canny edge detection", src);

	//1.create same matrix dst
	Mat dst;
	dst.create(src1.size(), src1.type());

	//2.turn to grey 
	Mat gray;
	cvtColor(src1, gray, COLOR_BGR2GRAY);

	//3.noise reduction
	Mat edge;
	blur(gray, edge, Size(3, 3));

	//4 canny operator
	Canny(edge, edge, 3, 9, 3);

	//5. destination all element 0
	dst = Scalar::all(0);

	//6. use canny operator output edge picture as mask, source copy to destination
	src1.copyTo(dst, edge);
	imshow("new Window", edge);
	imshow("Canny result", dst);
	waitKey(0);

	return 0;
}