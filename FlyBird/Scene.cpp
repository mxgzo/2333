#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include "Scene.h"
#include"Image.h"

Scene::Scene(int sceneWidth, int sceneHeight)
{
	_pBuffer = new Color[sceneWidth*sceneHeight];
	_Height = sceneHeight;
	_Width = sceneWidth;
	_pipeHeight = 0;
	_overFlag = false;
	_pipeCount = 0;
	_gravity = new Gravity(_Height / 2);
}

void Scene::init()
{
	for (int i = 0; i < _Height*_Width; i++)
		_pBuffer[i] = {0,0,0,255};
}

void Scene::setPixel(int x,int y,Color col)
{
	if (x>0&&y>0&&x<_Width&&y<_Height) 
	{	col.r = _pBuffer[y*_Width + x].r*(1 - (double)col.a / 255)   +  col.r*((double)col.a / 255);
		col.g = _pBuffer[y*_Width + x].g*(1 - (double)col.a / 255)   +	 col.g*((double)col.a / 255);
		col.b = _pBuffer[y*_Width + x].b*(1 - (double)col.a / 255)   +	 col.b*((double)col.a / 255);
		col.a = 255;
		_pBuffer[y*_Width + x] = col;
	}
}

Color * Scene::colorBuffer()
{
	return _pBuffer;
}


void Scene::setBackground()
{
//画背景
	static int time = 0;
	if(!_overFlag)
	time+=10;
		 Image *_background = Image::loadTeture("background.bmp");
		for ( int j = 0; j < _background->width(); j++)
			for (int i = 0; i < _background->height(); i++)
			{
				int cx = (_Width-1+j - time % _Width) %  _Width;
				setPixel(cx, i, _background->getPixel(j,i));
			}	
		delete _background;
/*。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。*/
//画管子
	Image *Pipe_Top = Image::loadTeture("Pipe_Top.bmp");
	Image *Pipe_Bottom = Image::loadTeture("Pipe_Bottom.bmp");
//存储管子高度
	static	int _heightBuffer[8] = { 100,200,200,250 };
//随机管子高度
	if (time == 800 * (time / 800))
	{
		if ((time / 800) % 2 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				_heightBuffer[i] =50+ rand() % 250;
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				 _heightBuffer[4+i] =50+ rand() % 250;
			}
		}

	}
	if (time >= 400)
	{
		_pipeCount = (time - 400 + 40) / 200;
	}


	if (time>= (_Width / 2-40)+ _pipeCount * 200 && time <= _pipeCount * 200 + _Width / 2 + Pipe_Bottom->width())
	{
		_pipeHeight = _Height- _heightBuffer[_pipeCount % 8]-200;
	}
	else
		_pipeHeight = 0;

				for (int t = 0; t <= time / 200; t++)
				{
					int _topPipeHeight = _heightBuffer[t%8];
					int _bottomPipeHeight = _Height- _topPipeHeight-200;

					for (int i = 0; i < Pipe_Bottom->width(); i++)
					{
						for(int j=0;j<_topPipeHeight;j++)
							setPixel((_Width  -  time +  i+t*200), _Height- _topPipeHeight+j, Pipe_Top->getPixel(i, j));
						for (int j = 0; j<_bottomPipeHeight; j++)
							setPixel((_Width  -  time +  i+t*200) ,  j, Pipe_Bottom->getPixel(i, Pipe_Bottom->height()-_bottomPipeHeight+j));
					}
				}
	
		delete Pipe_Bottom;
		delete Pipe_Top;
/*....................................................................*/
		Image *_ground = Image::loadTeture("Ground.bmp");
		for (int j = 0; j < _Width; j++)
			for (int i = 0; i < _ground->height(); i++)
			{
				int cx = (_Width - 1 + j - time % _Width) % _Width;
				Color col = _ground->getPixel(j%_ground->width(), i);
				setPixel(cx, i,col);
			}
		delete _ground;
	
}


bool Scene::isOver()
{
	return _overFlag;
}
//url：图片地址，offsetX offsetY ：偏移x，y轴
void Scene::setBird()
{
	int positionX = _Width / 2;
	int positionY = _gravity->position();
	if (_pipeHeight>0)
	{
		if (positionY <=_pipeHeight|| positionY >=_pipeHeight + 200-40)
			_overFlag = true;
	}
	if(positionY >= _Height || positionY <= 0)
		_overFlag = true;



	//每次加40像素，画一只鸟（小鸟图片的像素是120，大于120像素时，从头开始）
	static int _iPosX = -40;
	_iPosX += 40;
	if (_iPosX >= 120)
		_iPosX = 0;
	//
		//读取像素到缓存
		Image *img = Image::loadTeture("Birds.bmp");
		for (int j = 0; j < img->width() / 3; j++)
			for (int i = 0; i < img->height() / 2; i++)
			{
				int cx = (j + positionX) % _Width;
				int cy = i + positionY;
				Color col1 = img->getPixel(j + _iPosX, i + img->height() / 2);
				Color col = img->getPixel(j + _iPosX, i);//相当于蒙版
				if (!col.r)//col.r==0的时候对应图片黑色部分 所以画col1;否则就不画
					setPixel(cx, cy, col1);
			}
		delete img;


}

void Scene::scoreView()
{
	Image *_scoreView = Image::loadTeture("gameOver.bmp");

	for(int i=0;i<_scoreView->width();i++)
		for (int j = 0; j < _scoreView->height(); j++)
		{
			setPixel(250 + i, 140 + j, _scoreView->getPixel(i, j));
		}

	Image*_font = Image::loadTeture("ScoreFont.bmp");
	for (int i = 0; i<_font->width()/5; i++)
		for (int j = 0; j < _font->height()/2; j++)
		{
			setPixel(425 + i, 260 + j, _font->getPixel(i+((_pipeCount+1)/10%5)*_font->width() / 5, j+(((_pipeCount+1) / 10 / 5+1)%2)*_font->height() / 2));
			setPixel(425+ _font->width() / 5 + i, 260 + j, _font->getPixel(i + ((_pipeCount+1) % 10 % 5)*_font->width() / 5, j + (((_pipeCount+1) % 10 / 5+1)%2)*_font->height() / 2));

		}

	delete _font;
	delete _scoreView;
}

void Scene::setBirdsVelocity(int vilocity)
{
	if(!_overFlag)
	_gravity->setV(vilocity);
}



Scene::~Scene()
{
	delete[]_pBuffer;
	delete _gravity;
}

