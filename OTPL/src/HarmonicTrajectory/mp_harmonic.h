/*harmonic_rajectory*/
#ifndef MP_HAMONIC_H_
#define MP_HAMONIC_H_

#ifdef __cplusplus
extern "C" {
#endif // 

/**
@brief 轨迹规划结构体

用于存储输入参数和函数输出结果
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
	double t0;	
	double t1;	
	double T;	
	double q0;	
	double q1;
	double dT;
	double h;
	double vs;
	double ve;
	double acc;
	double jerk;
	double snap;
}mp_para;

int mp_harmonic_traj(double *t0, double *t1, double *q0, double *q1, double *dT, mp_para *out);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif