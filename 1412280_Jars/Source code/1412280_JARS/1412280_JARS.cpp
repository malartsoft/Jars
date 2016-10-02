// 1412280_JARS.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1412280_JARS.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

const int BUFFERSIZE = 260;
WCHAR bufferHeigh[BUFFERSIZE];
WCHAR bufferWidth[BUFFERSIZE];
WCHAR bufferX[BUFFERSIZE];
WCHAR bufferY[BUFFERSIZE];
WCHAR curPath[BUFFERSIZE];
WCHAR configPath[BUFFERSIZE];

int flag=0;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int heigh, width, x, y;

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
    LoadStringW(hInstance, IDC_MY1412280_JARS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1412280_JARS));

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

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1412280_JARS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(16);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1412280_JARS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//check input exist char
bool IsChar(WCHAR *s) {
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] > 57 || s[i] < 48)
			return 1;
		i++;
	}
	return 0;
}
HWND hWnd;
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
HWND button;
HWND hwndStatic;
HWND txtAmount;
HWND txtNEC;
HWND txtFFA;
HWND txtEDU;
HWND txtLTSS;
HWND txtPLAY;
HWND txtGIVE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(20, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

    switch (message)
    {
	case WM_CREATE:

		// get link file ini
		GetCurrentDirectory(BUFFERSIZE, curPath);
		wsprintf(configPath, L"%s\\config.ini", curPath);

		//set size screen default
		GetPrivateProfileString(L"default", L"x", L"500", bufferX, BUFFERSIZE, configPath);
		GetPrivateProfileString(L"default", L"y", L"200", bufferY, BUFFERSIZE, configPath);
		GetPrivateProfileString(L"default", L"width", L"410", bufferWidth, BUFFERSIZE, configPath);
		GetPrivateProfileString(L"default", L"height", L"400", bufferHeigh, BUFFERSIZE, configPath);
		x = _wtoi(bufferX);
		y = _wtoi(bufferY);
		width = _wtoi(bufferWidth);
		heigh = _wtoi(bufferHeigh);
		SetWindowPos(hWnd, 0, x, y, width, heigh,  SWP_NOZORDER | SWP_NOACTIVATE);

		//create label title and textbox for JARS
		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Nhập số tiền ($): ", WS_CHILD | WS_VISIBLE, 20, 20, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtAmount = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 20, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtAmount, WM_SETFONT, WPARAM(hFont), TRUE);

		//create botton Calculate
		button=CreateWindowEx(NULL, L"BUTTON", L"Tính", WS_VISIBLE| WS_CHILD | BS_PUSHBUTTON, 190, 80, 150, 30, hWnd, (HMENU)IDC_BUTTON_CALC, NULL, NULL);
		SendMessage(button, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Chi tiêu thiết yếu (55%): ", WS_CHILD | WS_VISIBLE, 20, 130, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtNEC = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 130, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtNEC, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Tự do tài chính (10%):", WS_CHILD | WS_VISIBLE, 20, 160, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtFFA = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 160, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtFFA, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic =CreateWindowEx(NULL, L"STATIC", L"Giáo dục (10%):", WS_CHILD | WS_VISIBLE, 20, 190, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtEDU = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 190, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtEDU, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Chi tiêu dài hạn (10%):", WS_CHILD | WS_VISIBLE, 20, 220, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtLTSS = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER|ES_CENTER, 190, 220, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtLTSS, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Tận hưởng (10%):", WS_CHILD | WS_VISIBLE, 20, 250, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtPLAY = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 250, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtPLAY, WM_SETFONT, WPARAM(hFont), TRUE);

		hwndStatic = CreateWindowEx(NULL, L"STATIC", L"Cho đi (5%):", WS_CHILD | WS_VISIBLE, 20, 280, 170, 20, hWnd, NULL, NULL, NULL);
		SendMessage(hwndStatic, WM_SETFONT, WPARAM(hFont), TRUE);
		txtGIVE = CreateWindowEx(NULL, L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_CENTER, 190, 280, 180, 25, hWnd, NULL, NULL, NULL);
		SendMessage(txtGIVE, WM_SETFONT, WPARAM(hFont), TRUE);
	break;
    case WM_COMMAND:
        {
		WCHAR* bufferAmount;
		WCHAR* bufferNEC;
		WCHAR* bufferFFA ;
		WCHAR* bufferEDU;
		WCHAR* bufferLTSS;
		WCHAR* bufferPLAY;
		WCHAR* bufferGIVE;

		int sizeAmount;
		int nAmount;
		int iNEC, iFFA, iEDU, iLTSS, iPLAY, iGIVE;


            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDC_BUTTON_CALC:
				sizeAmount = GetWindowTextLength(txtAmount);
				if (sizeAmount > 9) {
					MessageBox(0, L"Overflow!! Try again", L"Error", 0);
					return 0;
				}

				bufferAmount = new WCHAR[sizeAmount + 1];

				GetWindowText(txtAmount, bufferAmount, sizeAmount + 1);

				//if input number smaller 0
				if (bufferAmount[0] == '-') {
					MessageBox(0, L"Don't input number smaller 0 - Try again", L"Error", 0);
					return 0;
				}

				//exist char in textbox
				if (IsChar(bufferAmount) || IsChar(bufferAmount)) {
					MessageBox(0, L"Exist char in textbox - Try again", L"Error", 0);
					return 0;
				}
				if (bufferAmount[0] == '\0') {
					MessageBox(0, L"Can't input equal null - Try again", L"Error", 0);
					return 0;
				}

				nAmount = _wtoi(bufferAmount);

				if (nAmount < 20) {
					MessageBox(0, L"Number is so small - Try again", L"Error", 0);
					return 0;
				}
				iNEC = nAmount*0.55;
				iFFA = nAmount*0.1;
				iEDU = nAmount*0.1;
				iLTSS = nAmount*0.1;
				iPLAY = nAmount*0.1;
				iGIVE = nAmount*0.05;

				//show result 
				bufferNEC = new WCHAR[255];
				wsprintf(bufferNEC, L"%d", iNEC);
				SetWindowText(txtNEC, bufferNEC);

				bufferFFA = new WCHAR[255];
				wsprintf(bufferFFA, L"%d", iFFA);
				SetWindowText(txtFFA, bufferFFA);

				bufferEDU = new WCHAR[255];
				wsprintf(bufferEDU, L"%d", iEDU);
				SetWindowText(txtEDU, bufferEDU);

				bufferLTSS = new WCHAR[255];
				wsprintf(bufferLTSS, L"%d", iLTSS);
				SetWindowText(txtLTSS, bufferLTSS);

				bufferPLAY = new WCHAR[255];
				wsprintf(bufferPLAY, L"%d", iPLAY);
				SetWindowText(txtPLAY, bufferPLAY);

				bufferGIVE = new WCHAR[255];
				wsprintf(bufferGIVE, L"%d", iGIVE);
				SetWindowText(txtGIVE, bufferGIVE);
				break;

            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
			case ID_FILE_SETTING:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SETTING), hWnd, Setting);
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

//set screen's size
INT_PTR CALLBACK Setting(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_RADIO1 )
		{
			flag = 1;
		}
		if (LOWORD(wParam) == IDC_RADIO2)
		{
			flag = 2;
		}
		if (LOWORD(wParam) == IDC_SET_OK && flag == 1) {
			GetPrivateProfileString(L"size1", L"x", L"500", bufferX, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size1", L"y", L"200", bufferY, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size1", L"width", L"410", bufferWidth, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size1", L"height", L"400", bufferHeigh, BUFFERSIZE, configPath);
			x = _wtoi(bufferX);
			y = _wtoi(bufferY);
			width = _wtoi(bufferWidth);
			heigh = _wtoi(bufferHeigh);
			flag = 0;
			SetWindowPos(hWnd, 0, x, y, width, heigh, SWP_NOZORDER | SWP_NOACTIVATE);
			WritePrivateProfileString(L"default", L"x", bufferX, configPath);
			WritePrivateProfileString(L"default", L"y", bufferY, configPath);
			WritePrivateProfileString(L"default", L"width", bufferWidth, configPath);
			WritePrivateProfileString(L"default", L"height", bufferHeigh, configPath);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDC_SET_OK && flag == 2) {
			GetPrivateProfileString(L"size2", L"x", L"500", bufferX, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size2", L"y", L"200", bufferY, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size2", L"width", L"410", bufferWidth, BUFFERSIZE, configPath);
			GetPrivateProfileString(L"size2", L"height", L"400", bufferHeigh, BUFFERSIZE, configPath);
			x = _wtoi(bufferX);
			y = _wtoi(bufferY);
			width = _wtoi(bufferWidth);
			heigh = _wtoi(bufferHeigh);
			flag = 0;
			SetWindowPos(hWnd, 0, x, y, width, heigh, SWP_NOZORDER | SWP_NOACTIVATE);
			WritePrivateProfileString(L"default", L"x", bufferX, configPath);
			WritePrivateProfileString(L"default", L"y", bufferY, configPath);
			WritePrivateProfileString(L"default", L"width", bufferWidth, configPath);
			WritePrivateProfileString(L"default", L"height", bufferHeigh, configPath);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
