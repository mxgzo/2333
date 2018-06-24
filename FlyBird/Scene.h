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
	int _pipeCount;//ͨ���˶��ٹ���
	Gravity* _gravity;
public:
	Scene(int _sceneWidth,int _sceneHeight);
	Color * colorBuffer();//ȡ��buffer
	void init();
	void setPixel(int x, int y,Color col);//��buffer�������ص�
	void setBackground();
	bool isOver();
	void setBird();
	void scoreView();
	void setBirdsVelocity(int vilocity);
	~Scene();
};

class Gravity
{
	double v;//��ǰ�ٶ�
	const int a = -10;//�������ٶ�
	double _position;//λ��
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
	double position()//λ��
	{

		_position += v;
		v += a;
		return _position;
	};
};