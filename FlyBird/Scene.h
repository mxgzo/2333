#pragma once
#include"Image.h"
class Gravity;
class Scene
{
private :
	int _Height;
	int _Width;
	Color *_pBuffer;
	bool _overFlag;
	int _pipeHeight;
	int _pipeCount;//通过了多少管子
	Gravity* _gravity;
public:
	Scene(int _sceneWidth,int _sceneHeight);
	Color * colorBuffer();//取得buffer
	void init();
	void setPixel(int x, int y,Color col);//对buffer设置像素点
	void setBackground();
	bool isOver();
	void setBird();
	void scoreView();
	void setBirdsVelocity(int vilocity);
	~Scene();
};

class Gravity
{
	double v;//当前速度
	const int a = -10;//重力加速度
	double _position;//位置
public:
	Gravity(int _position0)
	{
		this->v = 0;
		_position = _position0;
	};
	~Gravity() {};
	void setV(int v)
	{
		this->v = v;
	}
	double position()//位置
	{

		_position += v;
		v += a;
		return _position;
	};
};