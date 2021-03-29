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

#include "..//DEF.H"

namespace mert
{
  class win
  {
  protected :
    HWND hWnd;           // window handle
    INT W, H;            // windwo size
    HINSTANCE hInstance; // application handle

  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
      WPARAM wParam, LPARAM lParam );
    BOOL IsInit = TRUE;

  public:
    BOOL IsActive, IsFullScreen;

    win( HINSTANCE hInst = GetModuleHandle(NULL) );
    ~win( VOID );

    VOID Run( VOID );

    VOID FlipFullScreen( VOID );

    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS )
    {
      SetTimer(hWnd, 30, 10, NULL);
      return TRUE;
    } /* End of 'OnCreate' function */

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H )
    {
      this->W = W;
      this->H = H;
    } /* End of 'OnSize' function */

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id )
    {
      if (!IsInit)
        IsInit = TRUE; 
      Timer();
    } /* End of 'OnTimer' function */

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
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
    {
    } /* End of 'OnMouseWheel' function */

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBackground( HDC hDC )
    {
      return FALSE;
    } /* End of 'OnEraseBkgnd' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnPaint( VOID )
    {
      HDC hDC;
      PAINTSTRUCT ps;

      hDC = BeginPaint(hWnd, &ps);
      if (IsInit)
        Paint(hDC);
      EndPaint(hWnd, &ps); 
    } /* End of 'OnPaint' function */ 
    
    /* Function for close window.
     * ARGUMENTS: None.
     * RETUNRS: None.
     */
    VOID OnClose( VOID )
    {
      PostMessage(hWnd, WM_DESTROY, 0, 0);
    } /* End of 'OnClose' function */

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID )
    {
    } /* End of 'OnDestroy' function */

    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

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
      * ARGUMENTS:
      *   - activation window flag:
      *       BOOL IsActive;
      * RETURNS: None.
      */
    virtual VOID Activate( BOOL IsActive )
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
} /* End of 'megl' namespace */

#endif /* __WIN_H_ */

/* END OF 'WIN.H' FILE */