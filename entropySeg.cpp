#include "entropySeg.h"

/***************************************************************************************
Function: ����طָ��㷨
Input:    Mat ���ָ��ԭͼ��
Output:   �ָ��ͼ��
maximum entropy
***************************************************************************************/
Mat entropySeq::EntropySeg(Mat src)
{
	int tbHist[256] = { 0 };                                          //ÿ������ֵ����
	int index = 0;                                                  //����ض�Ӧ�ĻҶ�
	double Property = 0.0;                                          //������ռ����
	double maxEntropy = -1.0;                                       //�����
	double frontEntropy = 0.0;                                      //ǰ����
	double backEntropy = 0.0;                                       //������
	//����������������
	int TotalPixel = 0;
	int nCol = src.cols * src.channels();                           //ÿ�е����ظ���
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
		//���㱳��������
		double backTotal = 0;
		for (int j = 0; j < i; j++)
		{
			backTotal += tbHist[j];
		}

		//������
		for (int j = 0; j < i; j++)
		{
			if (tbHist[j] != 0)
			{
				Property = tbHist[j] / backTotal;
				backEntropy += -Property * logf((float)Property);
			}
		}
		//ǰ����
		for (int k = i; k < 256; k++)
		{
			if (tbHist[k] != 0)
			{
				Property = tbHist[k] / (TotalPixel - backTotal);
				frontEntropy += -Property * logf((float)Property);
			}
		}

		if (frontEntropy + backEntropy > maxEntropy)    //�õ������
		{
			maxEntropy = frontEntropy + backEntropy;
			index = i;
		}
		//��ձ��μ�����ֵ
		frontEntropy = 0.0;
		backEntropy = 0.0;
	}
	Mat dst;
	//index += 20;
	cv::threshold(src, dst, index, 255, 0);             //������ֵ�ָ�
	return dst.clone();
}