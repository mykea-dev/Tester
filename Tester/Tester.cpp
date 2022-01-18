// Tester.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Tester.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HWND hwnd;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTER));

    MSG msg;

    // Цикл основного сообщения:
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

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void TryAgain() {
    int msgboxIDD = MessageBox(
        NULL,
        (LPCWSTR)L"Ну так пидор или нет?",
        (LPCWSTR)L"Тест на пидора",
        MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON2
    );
    switch (msgboxIDD) {
    case IDCANCEL:
        MessageBox(
            NULL,
            (LPCWSTR)L"Пидора ответ!",
            (LPCWSTR)L"Тест на пидора",
            MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
        );
    case IDOK:
        MessageBox(
            NULL,
            (LPCWSTR)L"ХА! Пидор!\nЗато честно",
            (LPCWSTR)L"Тест на пидора",
            MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
        );
    }
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, TEXT("Тест провален!"), WS_OVERLAPPEDWINDOW,
       GetSystemMetrics(SM_CXSCREEN) / 2 - 150,
       GetSystemMetrics(SM_CYSCREEN) / 2 - 175,
       300, 350, nullptr, nullptr, hInstance, nullptr);
   HWND yes = CreateWindow(L"button", L"Yes", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 250, 120, 30, hWnd, nullptr, hInstance, nullptr);
   SetBkColor(HDC(yes), RGB(0, 0, 0));
   //HWND no = CreateWindow(L"button", L"No", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 250, 120, 30, hWnd, nullptr, hInstance, nullptr);
  // HWND text = CreateWindow(L"edit", L"Теск провален, поздравляем!", WS_CHILD | WS_VISIBLE  , 56, 100, 50, 500, hWnd, 0, hInstance, 0);
   int msgboxID = MessageBox(
       NULL,
       (LPCWSTR)L"Вы пидор?",
       (LPCWSTR)L"Тест на пидора",
       MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
   );

   switch (msgboxID)
   {
   case IDCANCEL:
       MessageBox(
           NULL,
           (LPCWSTR)L"Пидора ответ!",
           (LPCWSTR)L"Тест на пидора",
           MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
       );
       CloseWindow(hWnd);
       break;
   case IDCONTINUE:
       MessageBox(
           NULL,
           (LPCWSTR)L"ХА! Пидор!\nЗато честно",
           (LPCWSTR)L"Тест на пидора",
           MB_ICONWARNING | MB_OK | MB_DEFBUTTON2
       );
       CloseWindow(hWnd);
       break;
   case IDTRYAGAIN:
       TryAgain();
       break;
   }   
   CloseWindow(hWnd);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static COLORREF bkcolor = RGB(45, 45, 45);
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
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
            RECT rc;
            HDC hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rc);
            SetDCBrushColor(hdc, bkcolor);
            FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
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

// Обработчик сообщений для окна "О программе".
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
