#Trigonometric Trajectories

## Harmonic trajectory

谐波运动的特征是加速度曲线与位置曲线成比例，符号相反。

设点$q$为点$p$在圆的直径上的投影，如果点$p$在圆上匀速运动，那么点$q$的运动称为谐波运动。可用下式描述
$$
s(\theta)=R(1-\text{cos} \theta)
\tag{1}
$$
这里$R$为圆的半径。更一般的形式，谐波运动可以定义为
$$
q(t)=\frac{h}{2}\left (  1-\text {cos}  \frac{\pi(t-t_0)}{T}\right)+q_0
\tag{2}
$$
由此可得
$$
\begin{cases}
\dot q(t)=\frac{\pi h}{2T}\text{sin}\left ( \frac{\pi(t-t_0)}{T}\right )\\
\ddot q(t)=\frac{\pi^2 h}{2T^2}\text{cos}\left ( \frac{\pi(t-t_0)}{T}\right )\\
q^{(3)}(t)=-\frac{\pi^3 h}{2T^3}\text{sin}\left ( \frac{\pi(t-t_0)}{T}\right )\\
\end{cases}
$$
