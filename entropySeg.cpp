#include "entropySeg.h"

/***************************************************************************************
Function: 最大熵分割算法
Input:    Mat 待分割的原图像
Output:   分割后图像
maximum entropy
***************************************************************************************/
Mat entropySeq::EntropySeg(Mat src)
{
	int tbHist[256] = { 0 };                                          //每个像素值个数
	int index = 0;                                                  //最大熵对应的灰度
	double Property = 0.0;                                          //像素所占概率
	double maxEntropy = -1.0;                                       //最大熵
	double frontEntropy = 0.0;                                      //前景熵
	double backEntropy = 0.0;                                       //背景熵
	//纳入计算的总像素数
	int TotalPixel = 0;
	int nCol = src.cols * src.channels();                           //每行的像素个数
	for (int i = 0; i < src.rows; i++)
	{
		uchar* pData = src.ptr<uchar>(i);
		for (int j = 0; j < nCol; ++j)
		{
			++TotalPixel;
			tbHist[pData[j]] += 1;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		//计算背景像素数
		double backTotal = 0;
		for (int j = 0; j < i; j++)
		{
			backTotal += tbHist[j];
		}

		//背景熵
		for (int j = 0; j < i; j++)
		{
			if (tbHist[j] != 0)
			{
				Property = tbHist[j] / backTotal;
				backEntropy += -Property * logf((float)Property);
			}
		}
		//前景熵
		for (int k = i; k < 256; k++)
		{
			if (tbHist[k] != 0)
			{
				Property = tbHist[k] / (TotalPixel - backTotal);
				frontEntropy += -Property * logf((float)Property);
			}
		}

		if (frontEntropy + backEntropy > maxEntropy)    //得到最大熵
		{
			maxEntropy = frontEntropy + backEntropy;
			index = i;
		}
		//清空本次计算熵值
		frontEntropy = 0.0;
		backEntropy = 0.0;
	}
	Mat dst;
	//index += 20;
	cv::threshold(src, dst, index, 255, 0);             //进行阈值分割
	return dst.clone();
}