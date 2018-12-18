
#ifndef MY_RANSAC_H_
#define MY_RANSAC_H_

#include <set>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "ParameterEsitmator.h"
#include "Point2D.h"

/*
		���ʵ�֣�ֻ�����ά�㣬��ȡֱ��


		 Compute the k parameter (k=log(1-p)/log(1-w^n))
		 k����������
		 p��probability_��ʾһЩ���������д����ݼ������ѡȡ���ĵ��Ϊ���ڵ�ĸ���
		 w = ���ڵ����Ŀ / ���ݼ�����Ŀ
		 n�����ݼ��ĵ���


		 model_parameters: ģ�Ͳ�����������ֱ�߷��̵Ĳ�����ֱ�߷���ʹ�� dot(n, p-a) = 0����ʾ
							nΪ���ߣ�|n|=1��
							aΪֱ����һ����
							��������������˳���ǣ� [n_x,n_y,a_x,a_y]

		param_estimator��	ģ�͹��ƶ��������ַ�����һ����ֱ��ȡ�������ֱ�߷��̣���һ������С���˷�

		data��	���ݼ�

		num_for_estimate������ģ������ĵ�����ֱ�ߵĹ��ƣ����ȡ���������
								
		
		��С���˷������Ͻ��ñȽϺõ�����
		https://www.zhihu.com/question/37031188

		�������һ���ԣ���������
		http://www.cnblogs.com/xrwang/archive/2011/03/09/ransac-1.html
									
*/




class MyRANSAC 
{
public:
	MyRANSAC();


	double compute(std::vector<double> &model_parameters, 
		ParameterEsitmator<Point2D,double> *param_estimator , 
		std::vector<Point2D> &data, 
		int num_for_estimate		//����ģ��ʱ����Ҫ�ĵ������˴�ֱ����ֱ�ߣ���Ϊ2, ��ʼ����2����õ�ֱ�߷���
		);


private:

	class SubSetIndexComparator 
	{
	private:
		int m_length;
	public:
		SubSetIndexComparator(int arrayLength) : m_length(arrayLength){}
		bool operator()(const int *arr1, const int *arr2) const 
		{
			//��С��Ҫ�Ƚϣ���Ȼ�ͻ��ж�����
			for(int i=0; i<m_length; i++)
			{	if(arr1[i] < arr2[i])
				{
					return true;
				}
				if (arr1[i] > arr2[i])
				{
					return false;
				}
			}
			return false;			
		}
	};

	double probability_;	//p��ʾһЩ���������д����ݼ������ѡȡ���ĵ��Ϊ���ڵ�ĸ���

	int max_iterations_;	//����������
};


#endif