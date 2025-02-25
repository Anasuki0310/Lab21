#include <windows.h>
#include <stdio.h>

#define ID_EDIT1 1
#define ID_EDIT2 2
#define ID_BUTTON_ADD 3
#define ID_BUTTON_SUB 4
#define ID_BUTTON_MUL 5
#define ID_BUTTON_DIV 6

HWND hEdit1, hEdit2, hStatic;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    char buffer[100];
    double num1, num2, result;

    switch (Message) {
        case WM_CREATE:

            hStatic = CreateWindow("STATIC", "Please input two numbers",
                                   WS_CHILD | WS_VISIBLE, 20, 15, 200, 20,
                                   hwnd, NULL, NULL, NULL);


            hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  50, 50, 140, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);


            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
                                  50, 80, 140, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);



            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
                         45, 120, 30, 20, hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);


            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
                         85, 120, 30, 20, hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);


            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
                         125, 120, 30, 20, hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);


            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
                         165, 120, 30, 20, hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) >= ID_BUTTON_ADD && LOWORD(wParam) <= ID_BUTTON_DIV) {
                GetWindowText(hEdit1, buffer, 100);
                num1 = atof(buffer);
                GetWindowText(hEdit2, buffer, 100);
                num2 = atof(buffer);

                switch (LOWORD(wParam)) {
                    case ID_BUTTON_ADD: result = num1 + num2; break;
                    case ID_BUTTON_SUB: result = num1 - num2; break;
                    case ID_BUTTON_MUL: result = num1 * num2; break;
                    case ID_BUTTON_DIV:
                        if (num2 == 0) {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2;
                        break;
                }

                sprintf(buffer, "Result: %.6f", result);
                MessageBox(hwnd, buffer, "Result", MB_OK | MB_ICONINFORMATION);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(600, 0, 100));
    wc.lpszClassName = "CalculatorClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindow("CalculatorClass", "My Calculator",
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
                        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
                        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
