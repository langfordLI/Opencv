#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>	
#define WINDOW_NAME "picture"


using namespace std;
using namespace cv;

Mat srcImage, tmpImage, dstImage;

int main()
{
	srcImage = imread("my_car.jpg");
	tmpImage = srcImage;
	dstImage = tmpImage;

	int key = 0;

	while (1)
	{
		key = waitKey(0);

		if (key == 27 || key == 'q')
		{
			break;
		}

		switch (key)
		{
		case 'a':
			cout << "pyrUp\n";
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			break;
		case 'w':
			cout << "resize up\n";
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			break;
		case 'd':
			cout << "pyrDown\n";
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			break;
		case 's':
			cout << "resize down\n";
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			break;
		
		}
		imshow(WINDOW_NAME, dstImage);
		tmpImage = dstImage;

	}

	return 0;

}
