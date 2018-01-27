/*mp_cycloidal.h*/

#ifndef MP_CYCLOIDAL_H_
#define MP_CYCLOIDA_H_

#ifdef __cplusplus  
extern "C" {
#endif // 


	/**
	@brief 摆线轨迹规划接口函数。

	@para t0,double，初始时刻。
	@para t1,double，终止时刻。
	@para q0,double，初始位移。
	@para q1,double，终点位移。
	@para dT,double，时间分割间隔。
	@para *data[6],double，存放数据的指针数组，data[0]指向时间，data[1]指向位移，data[2]指向速度,...。
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
	int mp_cycloidal_traj(double t0, double t1, double q0, double q1, double dT, double *data[6], int *dataNum);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
