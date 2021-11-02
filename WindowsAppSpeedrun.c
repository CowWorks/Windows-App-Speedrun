//===================================
//         System includes
//===================================
#include <windows.h>
#include <stdio.h>

//===================================
//         Preprocessors
//===================================
#pragma comment(lib, "user32.dll")
#pragma comment(lib, "gdi32.dll")
#pragma comment(lib, "opengl32.dll")
#ifndef bool
#define b8 _Bool
#endif

//===================================
//         OpenGL Includes
//===================================
#include "glcorearb.h"
#include "wglext.h"

//===================================
//         Global Variables
//===================================
HDC global_context;
HWND WindowHandle;


//===================================
//         Window Callback
//===================================
LRESULT CALLBACK
MainWindowCallback(HWND Window,
                   UINT Message,
                   WPARAM wParam,
                   LPARAM lParam)
{
    LRESULT Result = 0;

    switch (Message)
    {
        case WM_CLOSE:
        {
            if(MessageBox(Window, "Are you sure you want to quit?", "Windows App Speedrun", MB_OKCANCEL) == IDOK)
            {
                DestroyWindow(Window);
            }
        }break;
        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        }break;
        case WM_KEYDOWN:
        {
            printf("A key was pressed!\n");
        }break;
        default:
        {
            Result = DefWindowProc(Window, Message, wParam, lParam);
        }
    }

    return Result;
}

//===================================
//       WinMain entry-point
//===================================
int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CommandLineShow,
        int showCode)
{
    WNDCLASS WindowClass = { 0 };
    WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    //WindowClass.hIcon = ;
    WindowClass.lpszClassName = "WindowsAppSpeedrun";

    if(RegisterClass(&WindowClass)){
        RECT rect_size = {0, 0, CW_USEDEFAULT, CW_USEDEFAULT};

        AdjustWindowRect(&rect_size, CS_OWNDC|CS_HREDRAW|CS_VREDRAW, 0);
        WindowHandle = CreateWindowEx(
                                        0,
                                        WindowClass.lpszClassName,
                                        "Windows App Speedrun",
                                        WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                        CW_USEDEFAULT,
                                        CW_USEDEFAULT,
                                        rect_size.right,
                                        rect_size.left,
                                        0,
                                        0,
                                        Instance,
                                        0
                                     );
        
        global_context = GetDC(WindowHandle);

        PIXELFORMATDESCRIPTOR x = { 0 };
        x.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        x.nVersion = 1;
        x.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        x.iPixelType = PFD_TYPE_RGBA;
        x. cColorBits = 24;

        int pixel_format = ChoosePixelFormat(global_context, &x);
        SetPixelFormat(global_context, pixel_format, &x);
        
        if(WindowHandle != 0)
        {
            MSG Message;

            while(GetMessage(&Message, 0, 0, 0))
            {
                TranslateMessage(&Message);
                DispatchMessage(&Message);

                
            }
        }
    }
    
    return 0;
}