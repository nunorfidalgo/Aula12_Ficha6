// ex6.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ex6.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	TrataEventos(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_EX6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EX6));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = TrataEventos; // WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(/*IDI_EX6*/IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, /*IDC_ARROW*/MAKEINTRESOURCE(/*IDI_ICON1*/IDC_CURSOR1));
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(/*IDC_EX6*/IDR_MENU1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(/*IDI_SMALL*/IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

TCHAR login[100], password[100], frase[200];

// Message handler for about box.
INT_PTR CALLBACK Login(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			GetDlgItemText(hDlg, IDC_Login, login, 100);
			GetDlgItemText(hDlg, IDC_Password, password, 100);

			/*	_tcscpy_s(frase, login);
				_tcscpy_s(frase, TEXT(" :: "));
				_tcscpy_s(frase, password);*/

			_stprintf_s(frase, 200, TEXT("%s :: %s"), login, password);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			_stprintf_s(frase, 200, TEXT(""));
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
		}
		//if (LOWORD(wParam) == IDC_Login || LOWORD(wParam) == IDC_Password)
		//{
		//	/*EndDialog(hDlg, LOWORD(wParam));*/
		//	MessageBox(hDlg, TEXT("qwe"), TEXT("Dados Login"), MB_YESNO);
		//	return (INT_PTR)TRUE;
		//}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return (INT_PTR)FALSE;
}


int num_clicks = 0;
int xPos, yPos;
TCHAR c = '?';

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	TCHAR text_clicks[20];

	switch (messg) {

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_MENU_LOGIN:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LOGIN), hWnd, Login);

			if (_tcscmp(frase, TEXT("")) != 0) {
				MessageBox(hWnd, frase, TEXT("Dados Login"), MB_YESNO);
				_tcscpy_s(frase, TEXT(""));
			}

			break;
		case ID_MENU_SAIR:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, messg, wParam, lParam);
		}
	}
	break;
	case WM_RBUTTONDOWN:
		num_clicks++;
		_stprintf_s(text_clicks, 20, TEXT("Num. de Clicks = %d"), num_clicks);
		InvalidateRect(hWnd, &rect, FALSE);
		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		rect.left = 5 + num_clicks * 15;
		rect.top = 5 + num_clicks * 15;
		//DrawText(hdc, text_clicks, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		InvalidateRect(hWnd, NULL, FALSE);
		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		//rect.left = xPos;
		//rect.top = yPos;
		//DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_CHAR:
		c = (TCHAR)wParam;
		InvalidateRect(hWnd, NULL, FALSE);

		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		//rect.left = xPos;
		//rect.top = yPos;
		//DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		rect.left = xPos;
		rect.top = yPos;
		DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);

		EndPaint(hWnd, &ps);

		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Are you sure?"), TEXT("Quit Application"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY: // Destruir a janela e terminar o programa
		// "PostQuitMessage(Exit Status)"
		PostQuitMessage(0);
		break;
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar")
		// não é efectuado nenhum processamento, apenas se segue o "default" do Windows
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return(0);
}