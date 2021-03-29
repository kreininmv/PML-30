/* FILE NAME   : WIN.H
 * PURPOSE     : WinApi.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 18.07.2018
 * NOTE        : None
 */

#ifndef __WIN_H_
#define __WIN_H_

#include "..//..//BASE/DEF.H"

namespace mk5
{
  class win
  {
  protected:
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle

  private:
    /* Window creation counter */
    static INT CreationCounter;

    /* Window initialization flag */
    BOOL IsInit;

    /* Window message handle function (CALLBACK version).
     *   - window handle:
     *       HWND hWnd;
     *   - message identifier (see WM_***):
     *       UINT Msg;
     *   - message first parameter ('word' param):
     *       WPARAM wParam;
     *   - message second parameter ('long' param):
     *       LPARAM lParam;
     * RETURNS:
     *   (LRESULT) message return code (depended to Msg type).
     */
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
    /* End of 'WinFunc' function */

  public:
    static HWND hWnd;                     // window handle
    INT MouseWheel;                       // Mouse wheel delta value
    BOOL IsActive;
    static const INT TimerInitID = 87;    // initialization timer identifier
    static const INT TimerRefreshID = 30; // window permanent timer


    win( HINSTANCE hInst = GetModuleHandle(NULL) );
    ~win( VOID );

    /* Run message function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    INT Run( VOID );
    /* End of 'Run' function */

    /* Set/reset full screen mode function.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    static VOID FlipFullScreen( VOID );
    /* End of 'FlipFullScreen' function */

    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    /* End of 'OnGetMinMaxInfo' function */

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS );
    /* End of 'OnCreate' function */

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     *  RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );
    /* End of 'OnSize' function */

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );
    /* End of 'OnTimer' function */

    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    /* End of 'OnMouseWheel' function */

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBackground( HDC hDC );
    /* End of 'OnEraseBackground' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnPaint( VOID );
    /* End of 'OnPaint' function */

    /* Function for close window.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID OnClose( VOID );
    /* End of 'OnClose' function */

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID );
    /* End of 'OnDestroy' function */

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
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    /* End of 'OnActivate' function */

    /* Do exit function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DoExit( VOID );
    /* End of 'DoExit' function */

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Init( VOID )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Resize( VOID )
    {
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Timer( VOID )
    {
    } /* End of 'Timer' function */

    /* Activate handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Idle( VOID )
    {
    } /* End of 'Idle' function */

  }; /* End of 'win' class */
} /* End of 'mk5' namespace */

#endif /* __WIN_H_ */

/* END OF 'WIN.H' FILE */