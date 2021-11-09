//===================================
//         Main App Data
//===================================
//TODO: Implement an entry point for the window data
// typedef struct window{
//     const char* window_name;
//     int window_width;
//     int window_height;
// }window;
// window myWindow;

// void
// create_window(window myWindow)
// {
//     SystemWindowCreateProc(myWindow.window_name, myWindow.window_width, myWindow.window_height);
// }

//===================================
//         System includes
//===================================
#include <windows.h>
#include <stdio.h>

//===================================
//         Preprocessors
//===================================
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#ifndef bool
#define b8 _Bool
#endif

//===================================
//         OpenGL Includes
//===================================
#include "ext/glcorearb.h"
#include "ext/wglext.h"

//===================================
//         Global Variables
//===================================
HDC global_context;
HWND WindowHandle;
MSG Message;

typedef enum AppState
{
    AppInit,
    AppLoading,
    AppEditing,
    AppNoFile,
    AppTerminate
}AppState;
AppState myAppState;

typedef enum running
{
    true,
    false
}running;
running isRunning = true;

//===================================
//       Function Prototypes
//===================================
void LoadWinMsg( void );
unsigned int AppShouldClose( void );

//===================================
//         Window Callback
//===================================
LRESULT CALLBACK
MainWindowCallback(HWND Window,
                   UINT Message,
                   WPARAM wParam,
                   LPARAM lParam)
{
    switch (Message)
    {
        case 
        WM_CLOSE:
        {
            if(MessageBox(Window, "Are you sure you want to quit?", "Windows App Speedrun", MB_OKCANCEL) == IDOK)
            {
                isRunning = false;
                myAppState = AppTerminate;
            }
        }break;

        case 
        WM_KEYDOWN:
        {
            printf("A key was pressed!\n");
        }break;

        case
        WM_LBUTTONDOWN:
        {
            printf("You pressed down the left mouse button\n");
        }break;

        case
        WM_LBUTTONUP:
        {
            printf("You released the left mouse button\n");
        }
    }

    return (DefWindowProc(Window, Message, wParam, lParam));
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
        
        HGLRC dummy_context = wglCreateContext(global_context);
        wglMakeCurrent(global_context, dummy_context);

        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribs");

        myAppState = AppInit;
        if(WindowHandle != 0)
        {

            while(!AppShouldClose())
            {
                
                while(myAppState == AppInit) // Will run when the app initiates
                {
                    LoadWinMsg(); // loads windows system messages
                }
            }
        }
    }
    
    return 0;
}

void 
LoadWinMsg()
{
    GetMessage(&Message, 0, 0, 0);
    TranslateMessage(&Message);
    DispatchMessage(&Message);
}

unsigned int
AppShouldClose()
{
    return (isRunning == false && myAppState == AppTerminate);
}
