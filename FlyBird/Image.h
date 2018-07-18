#pragma once
#include<stdio.h>

struct Color
{
	unsigned char r, g, b, a;
};
class Image
{
private:
	int _width;
	int _height;
	unsigned char* _buffer;
public:
	Image(int w,int h,void *buffer)
	{
		if (w == 0 || h == 0 || buffer == 0)
		{
			_width = 0;
			_height = 0;
			_buffer = 0;
		}
		else
		{
			_width = w;
			_height = h;
			_buffer =(unsigned char*)buffer;
			
		}
	}
	int  height()
		{
		return this->_height;
		};
	int width()
	{
		return this->_width;
	}
	Color getPixel(int x,int y)
	{	
		Color col = { 0 };
		if (x < _width&&y < _height&&x >= 0 && y >= 0)
		{
		col.r = _buffer[(y*_width + x) * 3];
		col.g = _buffer[(y*_width + x) * 3 + 1];
		col.b = _buffer[(y*_width + x) * 3 + 2];
		col.a = 255;
		}

		return col;
	}
	~Image()
	{
			delete []_buffer;
	}

public:
	static Image* loadTeture( char const *url)
	{

		FILE *file = fopen(url, "rb");
		if (0 == file)return 0;
		if (file <= 0);
		int h, w;
		fseek(file, 0x0012, SEEK_SET);
		fread(&w, sizeof(w), 1, file);
		fread(&h, sizeof(h), 1, file);


		unsigned char *buffer = new unsigned char[w*h*3];
		if (0 == buffer)return 0;

		fseek(file, 0x0036, SEEK_SET);

		int sum = w * 3;
		if(sum % 4 == 0)
		{
			fread(buffer, sum*h, 1, file);
		}
		else
		{
			for (int i = 0; i < h; i++)
			{
				fread(&buffer[i*sum],sum, 1, file);
				fseek(file, 4 - sum % 4, SEEK_CUR);
			}
				

		}


		Image *img = new  Image(w, h, buffer);
		fclose(file);
		//delete[]buffer;
		return img;
	}


};