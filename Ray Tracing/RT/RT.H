/* FILE NAME   : RT.H
 * PURPOSE     : Ray tracing.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __RT_H_
#define __RT_H_


#include "..//DEF.H"


#include "..//WIN/WIN.H"
#include "SCENE.H"
#include "SHAPES/SHAPES.H"
#include "IMAGE/IMAGE.H"

namespace mert
{
  class rt : public win
  {
  private:
    rt ( VOID );
  public:
    image *Img;
    scene Scene;
    camera Cam;
  
    /* Getting ling function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (rt &) point to ray tracing class;
     */
    static rt & Get( VOID )
    {
      static rt RT;
  
      return RT;
    } /* End of 'Get' function */

    ~rt( VOID )
    {
    }
  
    /* Starting rendering function.
     * ARGUMENTS: None.
     * ARGUMENTS: None.
     */
    VOID StartRender( VOID )
    {
      Scene.Render(Cam, Img, *this);
    } /* End of 'StartRender' function */

    /* Put pixel function.
     * ARGUMENTS:
     *   - pixel coords:
     *       INT X, Y;
     *   - color:
     *       vec Color;
     * RETURNS: None.
     */
    VOID operator()( INT X, INT Y, vec Color )
    {
      Img->PutPixel(X, Y, Img->DWORDRGB(Color[0] * 255, Color[1] * 255, Color[2] * 255));
    } /* End of 'operator()' function */
    
    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID )
    {
  
    } /* End of 'Init' function */
  
    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
    } /* End of 'Close' function */
  
    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID )
    {
    } /* End of 'Resize' function */
  
    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */
  
    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC )
    {
      StartRender();
      Img->SaveBMP();
      Img->DrawImage();
    } /* End of 'Paint' function */
  
    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID )
    {
      InvalidateRect(win::hWnd, NULL, FALSE);
    } /* End of 'Timer' function */
  
    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    VOID Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */
  
    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID )
    {
    } /* End of 'Idle' function */
  }; /* End of 'rt' class */
} /* End of 'mert' namespace */

#endif /* __RT_H_ */

/* END OF 'RT.H' FILE */