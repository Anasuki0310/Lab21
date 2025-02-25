#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

HWND textfield, button, hEdit1, hEdit2;
/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("My Calculator"), /* Title Text */
           WS_SYSMENU,          /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

            textfield = CreateWindow("STATIC",
                                     "Please input two numbers",
                                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                                     20, 15, 200, 20,
                                     hwnd, NULL, NULL, NULL);

             hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                                  40, 40, 140, 25, hwnd, (HMENU)ID_EDIT1, NULL, NULL);


            hEdit2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                                  40, 70, 140, 25, hwnd, (HMENU)ID_EDIT2, NULL, NULL);



            CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE,
                         30, 100, 30, 20, hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);


            CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE,
                         70, 100, 30, 20, hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);


            CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE,
                         110, 100, 30, 20, hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);


            CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE,
                         150, 100, 30, 20, hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;


        button = CreateWindow ("Button",
                               "This is a button!",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               20, 50, 100, 20,
                               hwnd, (HMENU) 1, NULL, NULL);


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
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = CreateSolidBrush(RGB(200, 0, 100));
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
    return 0;
}
