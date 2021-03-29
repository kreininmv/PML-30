/* FILE NAME   : WIN.CPP
 * PURPOSE     : Win Api.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 18.07.2018
 * NOTE        : None
 */

#include "WIN.H"
#include "..//RT/RT.H"

using namespace mert;

/* Window constructor function.
* ARGUMENTS:
*   - application handle:
*       HINSTANCE hInstance;
* RETURNS: None.
*/
win::win( HINSTANCE hInst ) : hInstance(hInst), IsInit(FALSE), IsFullScreen(FALSE)
{
  WNDCLASS wc;
  CHAR WND_CLASS_NAME[] = "My WindowClass";

  wc.style = CS_VREDRAW | CS_HREDRAW;

  wc.cbClsExtra = 0;                          /* Additional bytes for class */
  wc.cbWndExtra = sizeof(VOID *);             /* Additional bytes for window */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;    /* Background color - chosen in system */
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);   /* Cursor loading */
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);       /* Icon loading */
  wc.lpszMenuName = NULL;                     /* Menu resource name */
  wc.hInstance = hInstance;                   /* Application descriptor */
  wc.lpfnWndProc = WinFunc;                   /* Pointer to processing function */
  wc.lpszClassName = WND_CLASS_NAME;          /* Class name */

  /* Registration of class in system */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return;
  }

  /* Window creation */
  hWnd = CreateWindow("My WindowClass", "RAY TRACING KLASS!!!",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
    NULL, NULL, hInstance, (VOID *)this);

  /* Show and redraw window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
} /* End of 'win' constructor */

win::~win( VOID )
{

} /* End of 'win' destructor */

LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (DWORD) ((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBackground((HDC)wParam);
      case WM_PAINT:
        Win->OnPaint();
        return 1;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_CLOSE:
        Win->OnClose();
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30);
        return 0;
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

VOID win::Run( VOID )
 {
  MSG msg;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      Idle();
    }
  }
} /* End of 'Run' function */
  
/* Set/reset full screen mode function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID win::FlipFullScreen( VOID )
{
  static RECT SaveRC;
  static BOOL IsFullScreen = FALSE;

  if (IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    /* Saving old window size */
    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *) &moninfo);

    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOPMOST, SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top, SWP_NOZORDER);
    IsFullScreen = FALSE;
  }

} /* End of 'FlipFullScreen' function */


/* END OF 'WIN.CPP' FILE */
