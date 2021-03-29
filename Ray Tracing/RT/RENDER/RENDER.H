/* FILE NAME   : RENDER.H
 * PURPOSE     : Render module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 27.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "..//..//DEF.H"
#include "..//IMAGE/IMAGE.H"

#ifndef  __RENDER_H_
#define  __RENDER_H_

namespace mert
{
  class render
  {
  private:
    HWND hWnd;       // Window handle
    INT WinW, WinH;  // Window size
    image *Img;      // Image with frame


  public:
    camera Cam;

    /* Class constructor function. 
     * ARGUMENTS:
     *   - window handle:
     *       const HWND &hWorkWnd;
     *   - width of window:
     *       const INT W;
     *   - height of window:
     *       const INT H;
     */
    render( const HWND &hWorkWnd, const INT W, const INT H );
    /* End of 'render' function */
    
    /* Class deconstructor function .
     * ARGUMENTS: None.
     */
    ~render( VOID )
    {
      delete Img;
    } /* End of '~render' function */

  }; /* End of 'render' class */
} /* End of 'mert' namespace */

#endif /* __RENDER_H_*/
/* END OF 'RENDER.H' FILE */

