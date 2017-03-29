
#include "entropySeg.h"
#include "rtcprgb2gray.h"


void main()
{
	Mat image,image0;
	Mat out;
	Mat grayImage;
	image = imread("image//12.png");
	image0 = imread("image//12.png");
	if (image.empty()||image0.empty())
		exit(-1);

	/**********�Աȶȱ���֮��ɫͼ��ȥɫ�㷨*****/
	rtcprgb2Gray rtcprgb2Gray;
	out = rtcprgb2Gray.rtcprgb2gray(image);
	grayImage = out;
	
	
	entropySeq entropySeq;//Function: ����طָ��㷨
	out = entropySeq.EntropySeg(out);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
	erode(out, out, element);//���и�ʴ

	Mat temp0=image;
	Mat temp1=image0;

	/****************ǰ���뱳�����зָ�************************/
	for (int i = 0; i < out.rows; i++)
	{
		for (int j = 0; j < out.cols; j++)
		{
			if (out.at<uchar>(i, j)>0)
			{
				temp1.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
			if (out.at<uchar>(i, j)<= 0)
			{
				temp0.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
			}
		}
	}
	imshow("background0", temp0);
	imshow("background1", temp1);
	/****************    **ͼ��ϲ�************************/
	Mat show=temp1;
	int cPointR0, cPointG0, cPointB0, cPoint0;//currentPoint;
	int x = 0;
	for (int i = 0; i < out.rows; i++)
	{
		for (int j = 0; j < out.cols; j++)
		{
			cPointB0 = temp1.at<Vec3b>(i, j)[0];
			cPointG0 = temp1.at<Vec3b>(i, j)[1];
			cPointR0 = temp1.at<Vec3b>(i, j)[2];
			if (cPointB0 == 0 & cPointR0 == 0 & cPointG0 == 0)
			{
				temp1.at<Vec3b>(i, j) = temp0.at<Vec3b>(i, j);
			}

		}
	}
	imshow("show", temp1);
	//cout << "whitecount: " << whitecount << endl;
	//cout << "blackcount: " << blackcount << endl;
	waitKey(0);

}