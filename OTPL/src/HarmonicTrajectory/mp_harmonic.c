/**
* @file mp_harmonic.c
* @brif 该函数生成谐波轨迹。
*
* 根据输入起始时刻t0,终止时刻t1,起始位置q0，终止位置q1和插值间隔（时间分割间隔）dT
* 生成谐波轨迹。
* @author LiBing
* @date 2018/1/9
*/
#include<stdio.h>
#include<math.h>
#include<mp_harmonic.h>

#define MP_OK 0			/*速度规划成功*/
#define PARA_ERR 1		/*输入参数非法*/


#define MIN_ERR  1.0E-6 /*数值比较允许的误差*/


#define DEBUG 1
int ret = 0;

//轨迹规划函数接口
int mp_harmonic_traj(double *t0,double *t1,double *q0,double *q1,double *dT,mp_para *out)
{
	if ((ret = mp_para_initial(t0, t1,q0, q1, dT, out)) != MP_OK)
	{
		if (DEBUG)
			printf("输入参数非法\n");
		return ret;
	}



	if (DEBUG)printf("mp_para_initial ok\n");
	return MP_OK;
}


/*初始化输入参数*/
static int mp_para_initial(double *t0, double *t1, double *q0, double *q1, double *dT, mp_para *out)
{	
	
	if (*t0 < 0.0f || *t1 < 0.0f || *q0<0.0f ||*q1<0.0f || *dT<0.0f)
	{
		ret = PARA_ERR;
		return ret;
	}
	out->t0 = *t0;
	out->t1 = *t1;
	out->T = *t1 - *t0;
	out->q0 = *q0;
	out->q1 = *q1;
	out->h = *q1 - *q0;
	out->dT = *dT;
	return MP_OK;

}