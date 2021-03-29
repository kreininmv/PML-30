/* FILE NAME   : WIN.CPP
 * PURPOSE     : Win Api.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 18.07.2018
 * NOTE        : None
 */

#include "WIN.H"

using namespace mk5;

HWND win::hWnd;
INT win::CreationCounter(0);

/* Window message handle function (CALLBACK version).
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier:
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (DWORD) ((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      switch (Msg)
      {
      case WM_CLOSE:
        Win->OnClose();
        return 0;
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
        break;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
          (INT)(SHORT)HIWORD(lParam),
          (INT)(SHORT)HIWORD(wParam),
          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        return 0;
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* Window class constructor.
 *   - handle idenfication: 
 *       HINSTANCE hInst.
 */
win::win( HINSTANCE hInst ) : hInstance(hInst)
{
  if (CreationCounter == 0)
  {
    WNDCLASS wc;

    wc.style = CS_VREDRAW | CS_HREDRAW;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(void *);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WinFunc;
    wc.lpszClassName = "Class hardbass";

    if (!RegisterClass(&wc))
    {
      MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
      return;
    }
  }
  hWnd = 
    CreateWindow("Class hardbass", 
      "PML #30", 
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL, 
      NULL, 
      hInstance,
      (void *)this);
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  CreationCounter++;
} /* End of 'win' function */

/* Default deconstructor.
 */
win::~win( VOID )
{
} /* End of '~win' function */

/* Run message function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
INT win::Run( VOID )
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
  return msg.wParam;
} /* End of 'Run' function */

/* Set/reset full screen mode function.
 * ARGUMENTS: None.
 * RETUNRS: None.
 */
VOID win::FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRect;

  if (IsFullScreen)
  {
    /* restore window size */
    SetWindowPos(hWnd, HWND_NOTOPMOST,
      SaveRect.left, SaveRect.top,
      SaveRect.right - SaveRect.left, SaveRect.bottom - SaveRect.top,
      SWP_NOOWNERZORDER);
  }
  else
  {
    /* Set full screen size to window */
    HMONITOR hmon;
    MONITORINFOEX moninfo;
    RECT rc;

    /* Store window old size */
    GetWindowRect(hWnd, &SaveRect);

    /* Get nearest monitor */
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    /* Obtain monitor info */
    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    /* Set window new size */
    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;

} /* End of 'FlipFullScreen' function */

/* Do exit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::DoExit( VOID )
{
  PostQuitMessage(30);
} /* End of 'mk5::win::DoExit' function */

/* END OF 'WIN.CPP' FILE */
