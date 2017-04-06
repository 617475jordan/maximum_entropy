#include "RegionGrowing.h"
#include "entropySeg.h"
#include "rtcprgb2gray.h"
#include <time.h>
#include <conio.h>

void main()
{
	Mat image,image0;
	Mat out;
	Mat grayImage;
	char filename[14];
	char name[14];
	for (int i = 1; i <= 4; i++)
	{
		sprintf(filename, "Wechat//%d.jpg", i);
		image = imread(filename);
		image0 = imread(filename);
		if (image.empty() || image0.empty())
			exit(-1);

		/**********对比度保留之彩色图像去色算法*****/
		rtcprgb2Gray rtcprgb2Gray;
		out = rtcprgb2Gray.rtcprgb2gray(image);
		grayImage = out;
		clock_t startTime = clock();
		regionGrowing RegionGrowing;
		out = RegionGrowing.RegionGrow(out, 120, 1);//说明：区域生长算法

		//Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
		//GaussianBlur(out, out, Size(3, 3), 0, 0, 4);
		//(out, out, element);//进行腐蚀

		//GaussianBlur(out, out, Size( 3, 3), 0, 0, 4);
		printf("SRCNN time: %d ms\n", clock() - startTime);

		Mat temp0 = image;
		Mat temp1 = image0;

		/****************前景与背景进行分割************************/

		for (int i = 0; i < out.rows; i++)
		{
			for (int j = 0; j < out.cols; j++)
			{
				if (out.at<uchar>(i, j)>0)
				{
					temp1.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
				}
				if (out.at<uchar>(i, j) <= 0)
				{
					temp0.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
				}
			}
		}

		imshow("background0", temp0);
		imshow("background1", temp1);
		/******************图像合并************************/
		//通过矩阵按位或进行比较，使用矩阵，效率提高90%
		bitwise_or(temp1, temp0, temp1);

		imshow("show", temp1);
		waitKey(0);
	}
}