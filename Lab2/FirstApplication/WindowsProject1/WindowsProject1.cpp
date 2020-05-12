#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");
TCHAR WinName2[] = _T("MainFrame2");

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
		_T("Первое приложение"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		300, 				// width 
		200, 				// Height 
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
	HWND deskriptor;
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_LBUTTONDOWN:
		{
			deskriptor = FindWindow(WinName2, NULL);
			if (deskriptor != NULL)
			{
				MessageBox(hWnd, _T("Окно 2 нашли посылаем сообщение!"), _T("Нашли"), MB_OK);
				SendMessage(deskriptor, WM_USER + 1, WPARAM(hWnd), NULL);
			}
			else
			{
				MessageBox(hWnd,_T("Окно 2 скорее всего закрыто!"),_T("не нашли окошечко то"), MB_OK);
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_RBUTTONDOWN:
		{
			deskriptor = FindWindow(WinName2, NULL);
			if (deskriptor != NULL)
			{
				MessageBox(hWnd, _T("Окно 2 нашли посылаем сообщение выключения!"), _T("Нашли"), MB_OK);
				SendMessage(deskriptor, WM_USER + 2, WPARAM(hWnd), NULL);
			}
			else
			{
				MessageBox(hWnd, _T("Окно 2 скорее всего закрыто!"), _T("не нашли окошечко то"), MB_OK);
			}
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_USER+3:
		{
			SetTimer(hWnd, 1, 15000, (TIMERPROC)NULL); 
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_TIMER:
		{
			exit(0);
		}

	}
	return 0;
}

