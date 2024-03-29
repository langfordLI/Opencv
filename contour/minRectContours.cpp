#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	RNG& rng = theRNG();
	Mat image(600, 600, CV_8UC3);

	while (1)
	{
		int count = rng.uniform(3, 103);
		vector<Point> points;

		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.rows * 3 / 4);
			point.y = rng.uniform(image.cols / 4, image.rows * 3 / 4);

			points.push_back(point);
		}
		RotatedRect box = minAreaRect(Mat(points)); // minAreaRect return a RotatedRect type
		/* compare with convexHull(Mat(points), hull, true)*/
		Point2f vertex[4];
		box.points(vertex);

		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
				rng.uniform(0, 255)), FILLED, LINE_AA);
		}

		for (int i = 0; i < 4; i++)
		{
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		}
		imshow("Rect result", image);

		char key = (char)waitKey();
		if (key == 27 || key == 'q')
			break;
	}
	return 0;
}