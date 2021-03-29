/* FILE NAME   : WINMSG.CPP
 * PURPOSE     : Win message system.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 18.07.2018
 * NOTE        : None
 */

#include "WIN.H"

using namespace mk5;

/* Function for close window.
* ARGUMENTS: None.
* RETUNRS: None.
*/
VOID win::OnClose( VOID )
{
  if (MessageBox(NULL, "Are u sure?", "Exit", MB_YESNO) == IDYES)
    OnDestroy();
} /* End of 'win::OnClose' function */

  /* WM_CREATE window message handle function.
  * ARGUMENTS:
  *   - structure with creation data:
  *       CREATESTRUCT *CS;
  * RETURNS:
  *   (BOOL) TRUE to continue creation window, FALSE to terminate.
  */
BOOL win::OnCreate( CREATESTRUCT *CS )
{
  SetTimer(hWnd, TimerInitID, 1, nullptr);
  return TRUE;
} /* End of 'win::OnCreate' function */

  /* WM_DESTROY window message handle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID win::OnDestroy( VOID )
{
  if (IsInit)
  {
    IsInit = FALSE;
    Close();
    KillTimer(hWnd, TimerRefreshID);
  }
  else
    KillTimer(hWnd, TimerInitID);
  if (CreationCounter == 1)
    PostQuitMessage(30);
  hWnd = nullptr;
  CreationCounter--;
} /* End of 'win::OnDestroy' function */

  /* WM_SIZE window message handle function.
  * ARGUMENTS:
  *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
  *       UINT State;
  *   - new width and height of client area:
  *       INT W, H;
  * RETURNS: None.
  */
VOID win::OnSize( UINT State, INT W, INT H )
{
  win::H = H;
  win::W = W;
  if (IsInit)
    Resize();
} /* End of 'win::OnSize' function */

  /* WM_ERASEBKGND window message handle function.
  * ARGUMENTS:
  *   - device context of client area:
  *       HDC hDC;
  * RETURNS:
  *   (BOOL) TRUE if background is erased, FALSE otherwise.
  */
BOOL win::OnEraseBackground( HDC hDC )
{
  // if (IsInit)
  //  Erase(hDC);               
  return TRUE;
} /* End of 'win::OnEraseBkgnd' function */

  /* WM_PAINT window message handle function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID win::OnPaint( VOID )
{
  HDC hDC;
  PAINTSTRUCT ps;

  hDC = BeginPaint(hWnd, &ps);
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps);
} /* End of 'win::OnPaint' function */ 

  /* WM_ACTIVATE window message handle function.
  * ARGUMENTS:
  *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
  *       UINT Reason;
  *   - handle of active window:
  *       HWND hWndActDeact;
  *   - minimized flag:
  *       BOOL IsMinimized;
  * RETURNS: None.
  */
VOID win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
  if (IsInit)
    Activate();
} /* End of 'win::OnActivate' function */

  /* WM_TIMER window message handle function.
  * ARGUMENTS:
  *   - specified the timer identifier.
  *       INT Id;
  * RETURNS: None.
  */
VOID win::OnTimer( INT Id ) 
{ 
  if (Id == TimerInitID && !IsInit)
  {
    KillTimer(hWnd, TimerInitID);
    SetTimer(hWnd, TimerRefreshID, 0, nullptr);
    IsInit = TRUE;

    Init();
    Resize();
    Activate();
    Timer();
    Idle();
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
  }
  else
    Timer();
} /* End of 'win::OnTimer' function */

  /* WM_MOUSEWHEEL window message handle function.
  * ARGUMENTS:
  *   - mouse window position:
  *       INT X, Y;
  *   - mouse wheel relative delta value:
  *       INT Z;
  *   - mouse keys bits (see MK_*** bits constants):
  *       UINT Keys;
  * RETURNS: None.
  */
VOID win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'win::OnMouseWheel' function */

  /* END OF 'WINMSG.CPP' FILE */