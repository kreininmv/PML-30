/* FILE NAME   : IMAGE.H
 * PURPOSE     : Image module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include "..//..//DEF.H"

namespace mert
{
  class image
  {
  public:
    HWND hWnd;              // Window handle
    HDC hMemDc;             // Context
    HBITMAP hBm;            // Bitmap
    BITMAPINFOHEADER bmih;  // Bitmap header
    DWORD *Bits;            // Bitmap data
    INT ImageW, ImageH;     // Image size

    /* Class contsructor function.
     * ARGUMENTS:
     *   - window handle:
     *       const HWND &hWWnd;
     */
    image( const HWND &hWWnd );

    ~image( VOID )
    {
    }

    VOID DrawImage( VOID );

    /* Convert components function.
     * ARGUMENTS:
     *   - color components:
     *       INT r, g, b;
     * RETURNS:
     *   (DWORD) color.
     */
    static DWORD DWORDRGB( INT r, INT g, INT b )
    {
      return (DWORD)((r << 16) | (g << 8) | b);
    } /* End of 'DWORDRGB' function */


    /* Save image to BMP format function.
     * ARGUMENTS:  None.
     * RETURNS: None.
     */
    VOID SaveBMP( VOID );
    /* End of 'SaveBMP' function */
    
    /* Set  pixel color function.
     * ARGUMENTS:
     *   - pixel coords:
     *       INT x, y;
     *   - pixel color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( const INT X, const INT Y, const DWORD Color );
    /* End of 'PutPixel' function */
  };
}



#endif /* __IMAGE_H_ */
/* END OF 'IMAGE.H' FILE */