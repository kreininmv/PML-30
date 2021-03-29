/* FILE NAME   : RENDER.CPP
 * PURPOSE     : Render module.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 27.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "RENDER.H"
namespace mert
{
  /* rt constructor function.
   * ARGUMENTS:
   *   - window handle:
   *       HWND hWorkWnd;
   *   - window size:
   *       INT W, H;
   * RETURNS: None.
   */
  render::render( const HWND &hWorkWnd, const INT W, const INT H ) : hWnd(hWorkWnd)
  {
  
  } /* End of 'render' constructor */
} /* End of 'mert' namespace */

/* END OF 'RENDER.CPP' FILE */
