#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat gammaTransform(Mat &srcImage, float kFactor)
{
	unsigned char LUT[256];
	for (int i = 0; i < 256; i++)
	{
		float f = (i + 0.5f) / 255;
		f = (float)(pow(f, kFactor));
		LUT[i] = saturate_cast<uchar>(f*255.0f - 0.5f);

	}
	Mat resultImage = srcImage.clone();
	if (srcImage.channels() == 1)
	{
		MatIterator_<uchar>iterator = resultImage.begin<uchar>();
		MatIterator_<uchar>iteratorEnd = resultImage.end<uchar>();
		for (; iterator != iteratorEnd; iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	}
	else
	{
		MatIterator_<Vec3b> iterator = resultImage.begin<Vec3b>();
		MatIterator_<Vec3b> iteratorEnd = resultImage.end<Vec3b>();
		for (; iterator != iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];//b
			(*iterator)[1] = LUT[((*iterator)[1])];//g
			(*iterator)[2] = LUT[((*iterator)[2])];//r
		}

	}
	return resultImage;

}
int main()
{
	Mat srcImage = imread("C:/Users/DELL/Desktop/30.jpg");
	if (srcImage.empty())
	{
		cout<<"fail to read Image"<<endl;
		return -1;
	}
	
	float gamma1 =2.22f;
	float gamma2 = 0.22f;
	float kFactor1 = 1 / gamma1;
	float kFactor2 = 1 / gamma2;
	Mat result1 = gammaTransform(srcImage, kFactor1);
	Mat result2 = gammaTransform(srcImage, kFactor2);
	imshow("srcImage", srcImage);
	imshow("res1", result1);
	imshow("res2", result2);
	waitKey(0);
	return 0;
}

