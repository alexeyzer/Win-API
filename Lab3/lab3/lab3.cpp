// lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab3.h"
#include <Windows.h>
#include <stdlib.h >
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <atlstr.h>

HWND listbox;
HWND textbox1;
HWND textbox2;
HWND listbox2;
HWND button;
int buttonnow = 0;
int buttonnow2 = 0;
struct MyStruct
{
	TCHAR firstworld[30];
	TCHAR secondworld[30];
	TCHAR thirdworld[30];
};
class Translate
{
private:
	int count = 4;
	MyStruct* p_struct = new MyStruct[count];


public:
	Translate()
	{
		p_struct[0] = { _T("дом"), _T("house"), _T("dom") };
		p_struct[1] = { _T("кот"), _T("cat"), _T("cat") };
		p_struct[2] = { _T("ракета"), _T("Midfield"), _T("rakieta") };
		p_struct[3] = { _T("еда"), _T("food"), _T("jedzenie") };
	}

	int getcount()
	{
		return count;
	}
	
	TCHAR *cmp(TCHAR *string, int counter, int k)
	{
		int i = 0;
		while (i < count)
		{
			//strncmp()
			int a = _tcscmp(p_struct[i].firstworld, string);
			if (a == 0)
			{
				switch (counter)
				{
					//case 0:
					//	return(p_struct[i].firstworld);
					case 0:
						return(p_struct[i].secondworld);
					case 1:
						return(p_struct[i].thirdworld);
				}
			}
			i++;
		}
		return (NULL);
	}
	void addword(TCHAR* string, TCHAR* string2, int kakoe)
	{
		count++;
		_tcscpy(p_struct[count - 1].firstworld, string);
		switch (kakoe)
		{
			//case 0:
			//	return(p_struct[i].firstworld);
		case 0:
			_tcscpy(p_struct[count-1].secondworld, string2);
		case 1:
			_tcscpy(p_struct[count-1].thirdworld,string2);
		}
	}

};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


TCHAR WinName[] = _T("MainFrame");
TCHAR WinName2[] = _T("ploxo");

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
		_T("Перводчик"), 		// Заголовок окна 
		WS_SYSMENU | WS_BORDER, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		100, 				// width 
		200, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// Показать окно
	HMENU WINAPI a;
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();

	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Настройки");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Добавить слово");
		AppendMenu(hPopupMenu, MF_SEPARATOR,0, L"");

	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1003, L"&?");
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, 1002, L"&Выход");
	SetMenu(hWnd, MainMenu);

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
HWND forasking;
Translate trans;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
		case WM_CREATE:
		{
			textbox1 = CreateWindow(_T("EDIT"),
			_T(""),
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			0,
			25,
			120,
			25,
			hWnd,
			NULL,
			NULL,
			NULL
			);
			button = CreateWindow(_T("BUTTON"),
				_T("Перевести"),
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				0,
				50,
				120,
				33,
				hWnd,
				(HMENU)1,
				NULL,
				NULL);
			textbox2 = CreateWindow(_T("EDIT"),
				_T(""),
				WS_BORDER | WS_CHILD | WS_VISIBLE,
				0,
				75,
				120,
				25,
				hWnd,
				NULL,
				NULL,
				NULL
			);
			listbox = CreateWindow(_T("listbox"),
				NULL,
				WS_CHILD | WS_VISIBLE | LBS_STANDARD,
				0,
				0,
				120,
				33,
				hWnd,
				NULL,
				NULL,
				NULL);
			SendMessage(listbox, WM_SETREDRAW, FALSE, 0L);
			// Добавляем в список несколько строк
			SendMessage(listbox, LB_ADDSTRING, 1,
				(LPARAM)(LPSTR)_T("Английский"));
			//SendMessage(listbox, LB_ADDSTRING, 2,
			//	(LPARAM)(LPSTR)_T("Немецкий"));
			SendMessage(listbox, LB_ADDSTRING, 3,
				(LPARAM)(LPSTR)_T("Польский"));
			// Включаем режим перерисовки списка
			SendMessage(listbox, WM_SETREDRAW, TRUE, 0L);
			SetFocus(listbox);
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_DESTROY:
			PostQuitMessage(0);
		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_COMMAND:
		{
			switch (HIWORD(wParam))
			{
			case LBN_SELCHANGE:
				{
					
					buttonnow = SendMessage(listbox, LB_GETCURSEL, 0, wParam);
				}
			}
			switch (LOWORD(wParam))
			{
				case 1:
				{
					if (buttonnow2 == 0)
					{
						TCHAR text[30];
						int r = 0;
						TCHAR* text1;

						GetWindowText(textbox1, text, GetWindowTextLength(textbox1) + 1);

						int i = 0;
						while (text[i] != '\0')
							i++;
						text1 = trans.cmp(text, buttonnow, i);
						if (text1 == NULL)
						{
							const int result = MessageBox(NULL, L"Токого слова нет,Добавить?", L"нет слова", MB_YESNO| MB_ICONQUESTION);
							switch (result)
							{
							case IDYES:
							{
								SetWindowText(button, L"добавить");
								MessageBox(NULL, L"Введите перевод слова и нажмите кнопку добавить", L"юхуу", MB_OK);
								SetWindowText(textbox2, L"");
								buttonnow2 = 1;
							}
							case IDNO:
								return DefWindowProc(hWnd, message, wParam, lParam);
								break;
							}
						}
						else
						{
							SetWindowText(textbox2, text1);
						}
						//MessageBox(hWnd, text1, _T("ыыыыы"), MB_OK);

					}
					else
					{
						TCHAR text[30];
						TCHAR text1[30];
						GetWindowText(textbox1, text, GetWindowTextLength(textbox1) + 1);
						GetWindowText(textbox2, text1, GetWindowTextLength(textbox2) + 1);
						trans.addword(text, text1, buttonnow);
						SetWindowText(button, L"перевести");
						SetWindowText(textbox1, L"");
						SetWindowText(textbox2, L"");
						buttonnow2 = 0;
					}
					
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}

			switch (wParam)
			{
				case 1001:
				{
					SetWindowText(button, L"добавить");
					MessageBox(NULL, L"Введите перевод слова и нажмите кнопку добавить", L"юхуу", MB_OK);
					buttonnow2 = 1;

					return DefWindowProc(hWnd, message, wParam, lParam);
				}
				case 1003:
				{
					MessageBox(hWnd, _T("Хочу зачет"), _T("ыыыыы"), MB_OK);
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
				case 1002:
				{
					exit(0);
				}
			}

		}

	}
	return 0;
}
