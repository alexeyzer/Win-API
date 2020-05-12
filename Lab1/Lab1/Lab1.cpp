#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 



	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Форматирование диска"), 		// Заголовок окна 
		WS_BORDER, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		200, 				// width 
		100, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static short x = 50, y = 100;
	int speed = 30;
	static short widthSCR, heightSCR;
	static short widthW, heightW;
	static int direct = rand() % 8 + 1; // 8 направлений движения
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_CREATE:
	{
		widthSCR = GetSystemMetrics(SM_CXSCREEN);
		heightSCR = GetSystemMetrics(SM_CYSCREEN);
		widthW = 200;
		heightW = 100;
		return 0;
	}
	case WM_LBUTTONDOWN:
	{
		ExitWindowsEx(0, EWX_SHUTDOWN);
	}
	case WM_MOUSEMOVE:
	{

		switch (direct)
		{
		case 1:
		{
			if (((x + widthW + speed) <= widthSCR))
			{
				MoveWindow(hWnd, x + speed, y, widthW, heightW, TRUE);
				x += 20;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 2:
		{
			if (((y + heightW + speed) <= heightSCR))
			{
				MoveWindow(hWnd, x, y + speed, widthW, heightW, TRUE);
				y += speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 3:
		{
			if (((y + heightW + speed) <= heightSCR) && ((x + widthW + speed) <= widthSCR))
			{
				MoveWindow(hWnd, x + speed, y + speed, widthW, heightW, TRUE);
				y += speed;
				x += speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 4:
		{
			if (((y + heightW + speed) <= heightSCR) && ((x - speed) >= 0))
			{
				MoveWindow(hWnd, x - 5, y + 5, widthW, heightW, TRUE);
				y += speed;
				x -= speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 5:
		{
			if (((y - speed) >= 0) && ((x + widthW + speed) <= widthSCR))
			{
				MoveWindow(hWnd, x - speed, y + speed, widthW, heightW, TRUE);
				y -= speed;
				x += speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 6:
		{
			if ((y - speed) >= 0)
			{
				MoveWindow(hWnd, x, y - speed, widthW, heightW, TRUE);
				y -= speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 7:
		{
			if ((y - speed) >= 0 && (x - speed) >= 0)
			{
				MoveWindow(hWnd, x - speed, y - speed, widthW, heightW, TRUE);
				y -= speed;
				x -= speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		case 8:
		{
			if ((x - speed) >= 0)
			{
				MoveWindow(hWnd, x - speed, y, widthW, heightW, TRUE);
				x -= speed;
			}
			else
				direct = rand() % 8 + 1;
			break;
		}
		}
	}
	}
	return 0;
}