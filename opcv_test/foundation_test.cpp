#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;


#define WINDOW_NAME "Linear Mixture" // define window title

const int g_nMaxAlphaValuee = 100; // alpha maximum value
int g_nAlphaValueSlidre; // currnt valu
double g_dAlphaValuee;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

/*function declaration*/
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);
void ShowHelpText();

/*global variable declaration*/
Rect g_rectangle;
bool g_bDrawingBox = false; // draw or not
RNG g_rng(12345);


void on_Trackbar(int, void*)
{
	g_dAlphaValuee = (double)g_nAlphaValueSlidre / g_nMaxAlphaValuee; // get proportion
	g_dBetaValue = (1.0 - g_dAlphaValuee); // get beta value

	addWeighted(g_srcImage1, g_dAlphaValuee, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	imshow(WINDOW_NAME, g_dstImage);

}

int main()
{
	///*1.import a picture and show*/
	//Mat girl = imread("girl.jpg");
	//namedWindow("1.animate_picture");
	//imshow("1.animate_picture", girl);

	///*2.primary picture mixture*/
	//Mat image = imread("dota.jpg"); // load 3 aisle color image
	//Mat logo = imread("dota_logo.jpg");

	//namedWindow("2original_image");
	//imshow("2original_image", image);

	//namedWindow("3logo_image");
	//imshow("3logo_image", logo);

	//Mat imageROI;
	//imageROI = image(Rect(800, 350, logo.cols, logo.rows));	// method 1
	////imageROI =  image(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols)); // method 2

	//addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI); // add logo on original imag

	//namedWindow("4logo+original");
	//imshow("4logo+originao", image);

	/////*3.write image in file*/
	//imwrite("generate_image.jpg", image);
	//waitKey();
	

	/*4.image blending*/
	//g_srcImage1 = imread("1.jpg");
	//g_srcImage2 = imread("2.jpg");
	//if (!g_srcImage1.data)
	//{
	//	printf("read first picturee error, check directroy!");
	//	return -1;
	//}
	//if (!g_srcImage2.data)
	//{
	//	printf("read second picture error, check directory!");
	//	return -1;
	//}

	//g_nAlphaValueSlidre = 70; // set slider initial value 70

	//namedWindow(WINDOW_NAME, 1);
	//
	//char TrackbarName[50];
	//sprintf_s(TrackbarName, "transparent value %d", g_nMaxAlphaValuee);

	//createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlidre, g_nMaxAlphaValuee, on_Trackbar);

	//on_Trackbar(g_nAlphaValueSlidre, 0);

	//waitKey(0);


	/*5.mouse operator*/
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	// main cycle when drawingBox = True draw
	while (1)
	{
		srcImage.copyTo(tempImage);	// copy src image to temp variable
		if (g_bDrawingBox)
			DrawRectangle(tempImage, g_rectangle);
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)
			break; //when press esc, exit program
	}


	return 0;


}

void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox) //if label is true, record length and weight in variable
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0); // record start point
	}
	break;

	case EVENT_LBUTTONUP :
	{
		g_bDrawingBox = false; // set label false
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width += -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		DrawRectangle(image, g_rectangle);

	}
	break;
	}
}
void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
		g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
void ShowHelpText();