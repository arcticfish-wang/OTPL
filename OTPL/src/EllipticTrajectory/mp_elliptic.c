/**
* @file mp_elliptic.c
* @brif 该文件的函数实现椭圆轨迹规划。
*
* 根据输入起始时刻t0,终止时刻t1,起始位置q0，终止位置q1和插值间隔（时间分割间隔）dT
* 生成椭圆轨迹。
* @author:LiBing
* @date  :2018/1/27
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<mp_elliptic.h>

#define MP_OK			0	/*速度规划成功*/
#define PARA_ERR		1	/*输入参数非法*/
#define MALLOC_ERR		2   /*内存分配失败*/

#define MIN_ERR  1.0E-6 /*数值比较允许的误差*/
#define TIME_ERR  1.0E-6 /*时间允许的误差大小*/
#define M_PI       3.14159265358979323846264338328      /* pi */   

#define INTEGER(x) ((int)(x))    //取整

#define DEBUG 1

/**
@brief 轨迹规划结构体

用于存储输入参数和函数输出结果
@para n 椭圆的长轴与短轴之比
@para t0 初始时刻
@para t1 终点时刻
@para T  运动持续时间
@para q0 初始位置
@para q1 终点位置
@para dT 插值间隔（时间分割）
@para h  相对位移
@para vs 起始速度
@para ve 终点速度
@para acc 加速度
@para jerk 加加速度
@para snap 加加加速度
运动规划参数结构体
*/
typedef struct {
	double n;		/**<ratio between major and minor ellipse axes */
	double t0;		/**<initial time*/
	double t1;		/**<final time*/
	double T;		/**<duration time*/
	double q0;		/**<initial position*/
	double q1;		/**<final position*/
	double dT;		/**<interpolation cycle*/
	double Tn[3];	/**<duration time  of each continue segments */
	double h;		///<relative displacement
	double vs;		///<initial velocity
	double ve;		///<final velocity
	double acc;     ///<acceleration
	double jerk;	///<jerk
	double snap;	///<snap
	int dataN;		///<numbers of the interpolation data
}mp_para;


int ret = 0;

/*初始化输入参数*/
static int mp_para_initial(double n,double t0, double t1, double q0, double q1, double dT, mp_para *out)
{
	memset(out, 0, sizeof(mp_para));
	if (t0 < 0.0f || t1 < 0.0f || q0<0.0f || q1<0.0f || dT<0.0f || n<1.0E-6)
	{
		ret = PARA_ERR;
		return ret;
	}
	out->n = n;
	out->t0 = t0;
	out->t1 = t1;
	out->T = t1 - t0;
	out->q0 = q0;
	out->q1 = q1;
	out->h = q1 - q0;
	out->dT = dT;
	return MP_OK;

}


/**
@brief 采用时间分割法计算分割数据点

计算时间、位移、速度和加速度等
@para *in 指向运动规划结构体（mp_para）的指针
*/
static int mp_data_generate(mp_para *in, double *data[6], int *dataNum)
{
	int T_N = 0;//Total number of interpolation cycles of motion
	int t_N[3] = { 0 };//number of interpolation cycles of each section
	int ret = 0;
	int i = 0;
	double temp1 = 0;
	double temp2 = 0;
	//Temporary data
	double timeTemp = in->t0;
	double DispTemp = in->q0;
	double vecTemp = in->vs;
	double accTemp = in->acc;
	double jerkTemp = in->jerk;

	double tRemain = 0.0;/**<当前段减去整数个周期后剩余的时间*/
	double tCompen = 0.0;/**<需要从下一个周期补偿的时间*/
	double timeTotal = 0.0;/**<运动的总时间*/
	double TnSplit[3] = { 0 };/**<用于存储分割后各段的时间,只有一段*/

	int cur_n = 0;
	int next_n = cur_n + 1;
	double alpha = (in->n*in->n - 1) / (in->n*in->n);
	double w = M_PI / in->T;


	for (int i = 0; i < 1; i++)
	{
		TnSplit[i] = in->Tn[i];
		if (in->Tn[i] > TIME_ERR)
		{
			timeTotal = timeTotal + in->Tn[i];
			t_N[i] = INTEGER(in->Tn[i] / in->dT);
		}
	}
	T_N = INTEGER(timeTotal / in->dT);
	if (fabs(timeTotal - T_N*in->dT) >= TIME_ERR)
	{
		T_N = T_N + 1;
	}
	T_N = T_N + 1;
	//分配内存
	for (i = 0; i<6; i++)
	{
		if ((data[i] = (double *)malloc(T_N * sizeof(double))) == NULL)
		{
			ret = MALLOC_ERR;
			printf("内存分配错误 error:%d\n", ret);
			return ret;
		}
		
		else 
		{ 
			memset(data[i], 0, (size_t)T_N); ret = MP_OK;
		}
	}

	data[0][0] = in->t0;
	data[1][0] = in->q0;
	data[2][0] = in->vs;
	data[3][0] = in->acc;
	data[4][0] = in->jerk;
	data[5][0] = in->snap;


	//计算数据
	if (in->Tn[0]>TIME_ERR)
	{
		//局部时间坐标
		double tau1 = 0;
		if (t_N[0] >= 1)
		{
			//时间大于或等于一个周期时，进行计算
			for (int i = cur_n; i< cur_n + t_N[0] + 1; i++)
			{
				tau1 = i*in->dT;
				temp1 = sin(w*tau1);
				temp2 = cos(w*tau1);
				//时间、位置、速度和加速度
				data[0][i] = timeTemp + tau1;
				data[1][i] = DispTemp + in->h/2.0 *(1.0f - temp2/sqrt(1.0f-alpha*temp1*temp1));
				data[2][i] = vecTemp + w*in->h / 2.0f*temp1 / (in->n*in->n) /
					sqrt(pow(1.0f - alpha*temp1*temp1, 3));
				data[3][i] = accTemp + w*w*in->h / 2.0f  * temp2*(1 + 2 * alpha*temp1*temp1)
					/ (in->n*in->n) / sqrt(pow(1.0f - alpha*temp1*temp1, 5));
				data[4][i] = jerkTemp - w*w*w*in->h / 2.0 * temp1*(1 + 2 * alpha*temp1*temp1) / (in->n*in->n) /
					sqrt(pow(1.0f - alpha*temp1*temp1, 5)) + w*w*w*in->h / 2.0f / (in->n*in->n)*temp2*(2.0f*alpha*temp1*temp2
						*sqrt(pow(1.0f - alpha*temp1*temp1, 5)) + 5.0f*alpha*temp1*temp2 * (1 + 2.0f*alpha*temp1*temp1)
						*sqrt(pow(1 - alpha*temp1*temp1, 3))) / pow(1.0f - alpha*temp1*temp1, 5);
			}
			next_n = cur_n + t_N[0] + 1;
		}

		//计算切换点（该段的结束点）处的数据
		tau1 = in->Tn[0];
		timeTemp = in->Tn[0];
		temp1 = sin(w*tau1);
		temp2 = cos(w*tau1);
		DispTemp = DispTemp + in->h / 2.0 *(1.0f - cos(w*tau1) / sqrt(1.0f - alpha*temp1*temp1));
		vecTemp = vecTemp + M_PI*in->h / (2.0f*in->T)*temp1 / (in->n*in->n) /
			sqrt(pow(1.0f - alpha*temp1*temp1, 3));
		accTemp = accTemp + M_PI * M_PI*in->h / (2.0 *in->T*in->T) * temp2*(1 + 2 * alpha*temp1*temp1)
			/ (in->n*in->n) / sqrt(pow(1.0f - alpha*temp1*temp1, 5));
		jerkTemp = jerkTemp - w*w*w*in->h / 2.0 * temp1*(1 + 2 * alpha*temp1*temp1) / (in->n*in->n) /
			sqrt(pow(1.0f - alpha*temp1*temp1, 5)) + w*w*w*in->h / 2.0f / (in->n*in->n)*temp2*(2.0f*alpha*temp1*temp2
				*sqrt(pow(1.0f - alpha*temp1*temp1, 5)) + 5.0f*alpha*temp1*temp2 * (1 + 2.0f*alpha*temp1*temp1)
				*sqrt(pow(1 - alpha*temp1*temp1, 3))) / pow(1.0f - alpha*temp1*temp1, 5);

		tRemain = TnSplit[0] - t_N[0] * in->dT;
		if (tRemain > TIME_ERR)
		{
			tCompen = in->dT - tRemain;
			//剩余时间不足一个周期，按一个周期算
			//若末速度较大，最后一个周期会存在较大的速度突变
			data[0][next_n] = timeTemp + tCompen;
			data[1][next_n] = DispTemp;
			data[2][next_n] = (vecTemp - data[2][next_n - 1]) / in->dT;
			data[3][next_n] = (accTemp - data[3][next_n - 1]) / in->dT;
			data[4][next_n] = (jerkTemp - data[3][next_n - 1]) / in->dT;
			next_n = next_n + 1;
		}
		cur_n = next_n;
	}
	in->dataN = cur_n;
	*dataNum = cur_n;
	return MP_OK;
}


/**
@brief 摆线轨迹规划接口函数。

@para n 椭圆的长轴与短轴之比
@para t0,double，初始时刻。
@para t1,double，终止时刻。
@para q0,double，初始位移。
@para q1,double，终点位移。
@para dT,double，时间分割间隔。
@para *data[6],double，存放数据的指针数组，data[0]指向时间，data[1]指向位移，data[2]指向速度,...。对于
椭圆轨迹只输出位移前二阶导数（即加速度，高于二阶导数的值无效）
@para *data double，指针，指向数据大小，即data[i]的元素个数。
@return 返回值指示函数的执行情况。
@retval 0,函数执行成功。
@retval 1,输入参数非法。
@retval 2,动态内存分配出错。
@waring 调用该函数后必须对data指针指向的内存释放，执行以下代码：
for (int i = 0; i < 6; i++)
{
free(data[i]);
}
*/
int mp_elliptic_traj(double n,double t0, double t1, double q0, double q1, double dT, double *data[6], int *dataNum)
{
	mp_para mp_st;
	if ((ret = mp_para_initial(n,t0, t1, q0, q1, dT, &mp_st)) != MP_OK)
	{
#ifdef DEBUG
		printf("输入参数非法\n");
#endif // DEBUG		
		return ret;
	}
	mp_st.Tn[0] = mp_st.T;
	//计算数据点
	if ((ret = mp_data_generate(&mp_st, data, dataNum)) != MP_OK)
	{
#ifdef DEBUG
		printf("计算数据点失败\n");
#endif // DEBUG

		return ret;
	}

#ifdef DEBUG
	printf("mp_para_initial ok\n");
#endif // DEBUG
	return MP_OK;
}


