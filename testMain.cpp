
#include "entropySeg.h"
#include "rtcprgb2gray.h"

void main()
{
	Mat image,temp;
	Mat out;
	Mat grayImage;
	image = imread("image//9.png");
	cvtColor(image, grayImage, CV_RGB2GRAY);
	imshow("grayImage", grayImage);
	imwrite("image//grayImage.png", grayImage);
	rtcprgb2Gray rtcprgb2Gray;
	out = rtcprgb2Gray.rtcprgb2gray(image);
	imshow("out", out);
	imwrite("image//out.png", out);
	entropySeq entropySeq;
	image = entropySeq.EntropySeg(out);
	imshow(" ", image);
	//Canny(out, out, 50, 200, 3);
	//GaussianBlur(out, out, Size(3, 3),0.5,0,4);
	//imshow("out", out);

	/*Mat hsi;
	cvtColor(temp, hsi, CV_BGR2HSV);
	//通道分离  
	vector<Mat> channels;
	split(hsi, channels);
	// 提取h通道  
	Mat gray = out;
	//imshow("gray", gray);
	vector<vector<Point> > regContours;
	vector<Vec4i> hierarchy;
	MSER mser1;
	//Mat gray;
	mser1(gray, regContours, Mat());
	gray = Mat::zeros(image.size(), CV_8UC1);
	for (int i = (int)regContours.size() - 1; i >= 0; i--)
	{
		// 根据检测区域点生成mser结果  
		const vector<Point>& r = regContours[i];
		for (int j = 0; j < (int)r.size(); j++)
		{
			Point pt = r[j];
			gray.at<unsigned char>(pt) = 255;
		}
	}
	// mser结果输出  
	//imwrite("resource/mserGray/demo1.jpg",gray);
	imshow("mserGray", gray);
	Mat bj_image;
	bj_image = gray.clone();
	Mat filt;
	//filt = gray.clone();
	findContours(gray, regContours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	//Mat dst = Mat::zeros(gray.size(), CV_8UC1); //最小外接矩形画布  
	vector< vector<Point> > filterContours; // 筛选后的轮廓 
	filterContours.clear();
	for (int i = 0; i<regContours.size(); i++)
	{
		//绘制轮廓  
		drawContours(bj_image, regContours, i, Scalar(255), 1, 8, hierarchy);
		//绘制轮廓的外接矩形  
		/*double area = 0;
		area = fabs(contourArea(Mat(regContours[i], true), true));
		Rect rect = boundingRect(regContours[i]);
		rectangle(bj_image, rect, cvScalar(255, 0, 0), 1);
		//if ((rect.height / (double)rect.width >0.1) && (rect.height / (double)rect.width <10))
		if (rect.height*rect.width>25 && (rect.height / (double)rect.width>0.2&&rect.height / (double)rect.width<5) && (rect.height>5 && rect.height<300) &&
			(rect.width>5 && rect.width<300) && area / (rect.height*rect.width)>0.1)
			filterContours.push_back(regContours[i]);

	}
	imshow("bjRect", bj_image);*/

	cv::waitKey(0);
}