#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while (1)
	{
		char key;

		//random generate some point
		int count = (unsigned)rng % 100 + 3;
		vector<Point> points;

		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		// detect point set
		vector<int> hull;
		convexHull(Mat(points), hull, true);

		//draw picture
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
				rng.uniform(0, 255)), FILLED, LINE_AA);
		}

		//draw convexity defects
		int hullcount = (int)hull.size();
		Point point0 = points[hull[hullcount - 1]]; // start of convexity
		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
			point0 = point;
		}
		imshow("convexity", image);

		key = (char)waitKey(0);
		if (key == 27 || key == 'q')
		{
			break;
		}
	}
	return 0;
}