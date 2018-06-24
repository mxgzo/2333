#include<Windows.h>
#include"Scene.h"


const int Height = 600;
const int Width = 800;


Scene *_scene=new Scene(Width, Height);//��������


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


	case WM_CREATE:						// ��������

		return 0;		break;
	case WM_CLOSE:						// �رմ���

		PostQuitMessage(0);
		return 0;		break;
	case WM_SIZE:						// ���ڳߴ�仯

		return 0;		break;
	case WM_DESTROY:					// �˳���Ϣ
		PostQuitMessage(0);
		return 0;		break;
	case WM_KEYUP:						// ��ESC�˳���ȫ��ģʽ����Ҫ������˳���ʽ��
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

	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// ʹ���ھ���3D���
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

	HBITMAP hBmp = CreateDIBSection(hDC, &bmpInfor, DIB_RGB_COLORS, (void**)&_ppBuffer, 0, 0);//����һ��λͼ���������buffer

	SelectObject(hMem, hBmp);

	//��Ϣѭ��

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

			

				_scene->setBackground();//���ñ���
				_scene->setBird();//����С�� ��ʼλ����_birdsY��width/2��

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

