#include <iostream>  
#include "cv.h"  
#include "cxcore.h"  
#include "highgui.h"  
using namespace std;

double MyminValue;

CvPoint getNextMinLoc(IplImage *result, CvPoint minLoc, int maxVaule, int templatW, int templatH)
{

	// �Ƚ���һ����Сֵ�㸽������ģ���Ⱥ͸߶ȵĶ�����Ϊ���ֵ��ֹ��������  
	int startX = minLoc.x - templatW;
	int startY = minLoc.y - templatH;
	int endX = minLoc.x + templatW;
	int endY = minLoc.y + templatH;
	if (startX < 0)
	{
		startX = 0;
	}
	if (startY < 0)
	{
		startY = 0;
	}
	if (endX > result->width - 1)
	{
		endX = result->width - 1;
	}
	if (endY > result->height - 1)
	{
		endY = result->height - 1;
	}
	int y, x;
	for (y = startY; y <= endY; y++)
	{
		for (x = startX; x <= endX; x++)
		{
			cvSetReal2D(result, y, x, maxVaule);
		}
	}
	// Ȼ��õ���һ����Сֵ���ҷ���  
	double new_minVaule, new_maxValue;
	CvPoint new_minLoc, new_maxLoc;
	cvMinMaxLoc(result, &MyminValue, &new_maxValue, &new_minLoc, &new_maxLoc);
	return new_minLoc;

}
int main()
{
	IplImage *src = cvLoadImage("ԭͼ��.png", 0);
	IplImage *srcResult = cvLoadImage("ԭͼ��.png", 3);  //������ʾ  
	IplImage *templat = cvLoadImage("ģ��.png", 0);
	IplImage *result;  // ������Ž��  
	if (!src || !templat)
	{
		cout << "��ͼƬʧ��" << endl;
		return 0;
	}
	int srcW, srcH, templatW, templatH, resultH, resultW;
	srcW = src->width;
	srcH = src->height;
	templatW = templat->width;
	templatH = templat->height;
	if (srcW < templatW || srcH < templatH)
	{
		cout << "ģ�岻�ܱ�ԭͼС" << endl;
		return 0;
	}
	resultW = srcW - templatW + 1;
	resultH = srcH - templatH + 1;
	result = cvCreateImage(cvSize(resultW, resultH), 32, 1);    //  ƥ�䷽������Ľ����СֵΪfloat  
	cvMatchTemplate(src, templat, result, CV_TM_SQDIFF);
	double minValue, maxValue;
	CvPoint minLoc, maxLoc;
	cvMinMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc);
	cvRectangle(srcResult, minLoc, cvPoint(minLoc.x + templatW, minLoc.y + templatH), cvScalar(0, 0, 255));
	CvPoint new_minLoc;

	// ������һ����Сֵ  
	new_minLoc = getNextMinLoc(result, minLoc, maxValue, templatW, templatH);
	while (cvGetReal2D(result, new_minLoc.y, new_minLoc.x) < 0.8*minValue + 0.2*maxValue)
	//for(int i = 5; i>0 ;i--)
	{
		cout << new_minLoc.x << " , " << new_minLoc.y << endl;
		cvRectangle(srcResult, new_minLoc, cvPoint(new_minLoc.x + templatW, new_minLoc.y + templatH), cvScalar(0, 0, 255));
		new_minLoc = getNextMinLoc(result, new_minLoc, maxValue, templatW, templatH);
	}

	//cvRectangle(srcResult, new_minLoc, cvPoint(new_minLoc.x + templatW, new_minLoc.y + templatH), cvScalar(0, 0, 255));
	cvNamedWindow("srcResult", 0);
	cvNamedWindow("template", 0);
	cvShowImage("srcResult", srcResult);
	cvShowImage("template", templat);
	cvWaitKey(0);
	cvReleaseImage(&result);
	cvReleaseImage(&templat);
	cvReleaseImage(&srcResult);
	cvReleaseImage(&src);
	return 0;
}
