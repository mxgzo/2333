#include<Windows.h>
#include"Scene.h"


const int Height = 600;
const int Width = 800;


Scene *_scene=new Scene(Width, Height);//创建场景


LRESULT CALLBACK RenderWindowproc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParm)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
			_scene->setBirdsVelocity(25);

		default:
			break;
		}
	
	}


	case WM_CREATE:						// 建立窗口

		return 0;		break;
	case WM_CLOSE:						// 关闭窗口

		PostQuitMessage(0);
		return 0;		break;
	case WM_SIZE:						// 窗口尺寸变化

		return 0;		break;
	case WM_DESTROY:					// 退出消息
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// 按ESC退出，全屏模式必需要加入的退出方式。
		switch (wParam)
		{
		case VK_ESCAPE:

			PostQuitMessage(0);
			return 0; break;
		}
	default:			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParm);
}

INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	WNDCLASSEX wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = NULL;
	wndClass.hIconSm = NULL;
	wndClass.hInstance = NULL;
	wndClass.lpfnWndProc = RenderWindowproc;
	wndClass.lpszClassName = "OpenglWindow";
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// 使窗口具有3D外观
	ATOM atom = RegisterClassEx(&wndClass);



	HWND hwnd = CreateWindowEx(NULL, "OpenglWindow", "Render Window", WS_OVERLAPPEDWINDOW, 100, 100, Width, Height, NULL, NULL, hInstance, NULL);

	if (!hwnd)
	{
		return 0;
	}
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	void *_ppBuffer = NULL;
	HDC hDC = GetDC(hwnd);
	HDC hMem = ::CreateCompatibleDC(hDC);

	BITMAPINFO bmpInfor;
	bmpInfor.bmiHeader.biBitCount = 32;
	bmpInfor.bmiHeader.biClrImportant = 0;
	bmpInfor.bmiHeader.biClrUsed = 0;
	bmpInfor.bmiHeader.biCompression = BI_RGB;
	bmpInfor.bmiHeader.biHeight = Height;
	bmpInfor.bmiHeader.biPlanes = 1;
	bmpInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfor.bmiHeader.biSizeImage = 0;
	bmpInfor.bmiHeader.biWidth = Width;
	bmpInfor.bmiHeader.biXPelsPerMeter = 0;
	bmpInfor.bmiHeader.biYPelsPerMeter = 0;

	HBITMAP hBmp = CreateDIBSection(hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&_ppBuffer, 0, 0);//创建一张位图，返回输出buffer

	SelectObject(hMem, hBmp);

	//消息循环

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))

		{
			if (msg.message == WM_QUIT)
			{

				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			

				_scene->setBackground();//设置背景
				_scene->setBird();//设置小鸟 初始位置在_birdsY和width/2；

				if (_scene->isOver())
				{
					_scene->scoreView();
				}

				void * _rgbBuffer = _scene->colorBuffer();

				
				memcpy(_ppBuffer, _rgbBuffer, 4 * Width*Height);
				BitBlt(hDC, 0, 0, Width, Height, hMem, 0, 0, SRCCOPY);
		}
	


		}

	}

