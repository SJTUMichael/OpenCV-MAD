#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <windows.h>

using namespace std;
using namespace cv;

int main()
{
	Mat templat, src; // result������Ž����srcΪԭͼ��
	char filename[100];

	templat = imread("C:\\Users\\Mark\\Desktop\\�����ز�\\data1\\mold\\mold.png", 0);


	for (unsigned int i = 0; i <= 7; ++i)
	{
		sprintf(filename, "C:\\Users\\Mark\\Desktop\\�����ز�\\data1\\��\\%d.png", i);//"C:\\Users\\Mark\\Desktop\\ԭͼ��.png"
		src = imread(filename, IMREAD_GRAYSCALE);

		if (src.empty() || templat.empty())
		{
			cout << "��ͼƬʧ��" << endl;
			cvWaitKey(0);
			return 0;
		}


		//  ����OpenCV������7��Hu��
		CvMoments moment;
		CvHuMoments hu;
		moment = moments(src, 0);
		cvGetHuMoments(&moment, &hu);
		//cout << hu.hu1 << "/" << hu.hu2 << "/" << hu.hu3 << "/" << hu.hu4 << "/" << hu.hu5 << "/" << hu.hu6 << "/" << hu.hu7 << "/" << "/" << endl;
		float I1 = hu.hu2 / (hu.hu1*hu.hu1);
		float I2 = hu.hu3 / (hu.hu1*hu.hu1*hu.hu1);
		float I3 = hu.hu4 / (hu.hu1*hu.hu1*hu.hu1*hu.hu1);
		float I4 = hu.hu5 / (hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1);
		float I5 = hu.hu6 / (hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1);
		float I6 = hu.hu7 / (hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1*hu.hu1);

		cout << I1 << "/" << I2 << "/" << I3 << "/" << I4 << "/" << I5 << "/" << I6 << "/"  << "/" << endl;
		//rectangle(templat, Point(meanX - tempW/2, meanY - tempH/2), Point(meanX + tempW / 2, meanY + tempH / 2), cvScalar(0, 0, 255));
		//imshow("result", templat);
		cvWaitKey(0);

	}

	return 0;
}