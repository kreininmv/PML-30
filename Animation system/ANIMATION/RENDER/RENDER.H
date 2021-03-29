/* FILE NAME   : RND.
 * PURPOSE     : Render system.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : None
 */

#ifndef __RND_H_
#define __RND_H_

#include "..//RESOURCES/PRIMITIVE.H"
#include "..//RESOURCES/OBJECT.H"

namespace mk5
{
  class render
  {
  private:
    HDC hDC;      // Descriptor context handle
    HGLRC hGLRC;  // Graphics Library Render Context handle
    INT W, H;     // Width and heing of monitor
  public:
    static mth::CAMERA<FLT> Cam;   // Camera

    /* Render class constructor.
     * ARGUMENTS:
     *   - work window handle:
     *       HWND hWnd;
     */
    render( HWND hWnd );
    /* End of 'render' function */

    /* Render class deconstructor.
     */
    ~render( VOID )
    {
    }
    /* End of '~render' function */

    /* Render system frame resize function.
     * ARGUMENTS:
     *   - new frame size:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID Resize( INT W, INT H );
    /* End of 'Resize' function */

    /* Render system start frame render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID );
    /* End of 'FrameStart function '*/

    /* Render system finish frame render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );
    /* End of 'FrameEnd' function */

    /* Render system copy frame buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameCopy( VOID );
    /* End of 'FrameCopy' function */

    /* Draw primitive function.
     * ARGUMENTS:
     *   - pointer to primitive:
     *       const prim *Pr
     * RETURNS: None.
     */
    static VOID Draw( const prim *Pr );
    /* End of 'Draw' function */
    
    /* Draw primitive function.
     * ARGUMENTS:
     *   - pointer to primitive:
     *       const prim *Pr
     *   - matrix to primitive:
     *       const matr &Matr
     * RETURNS: None.
     */
    static VOID DrawMatr( prim *Pr, const matr &Matr );
    /* End of 'DrawMatr' function */

    /* Render system for draw primitive function
     * ARGUMENTS: 
     *   - stock of primitves for drawing
     *       prim &Pr;
     * RETURNS: None.
     */
    VOID Draw( const stock<prim> &Pr) ;
    /* End of 'Draw' function */

    /* Draw object whis matrix function.
     * ARGUMENTS:
     *   - pointer to object:
     *       object *obj;
     *   - link to matr:
     *       const matr &W;
     * RETURNS: None.
     */
    VOID DrawMatr( object *obj , const matr &W );
  }; /* End of 'render' clas */
} /* End of 'mk5' namespace */

#endif /* __RND_H_ */

/* END OF 'RND.H' FILE */