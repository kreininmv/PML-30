/* FILE NAME   : IMAGE.H
 * PURPOSE     : Image system.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __IMAGE_H_
#define __IMAGE_H_

#include <vector>

#include "..//..//BASE/DEF.H"

/* Project namespace */
namespace mk5
{
  /* Image representation class */
  class image
  {
  private:
    // Image size in pixels
    INT Width = 0, Height = 0;
    // Image pixel data
    std::vector<BYTE> Pixels;
  public:
    // Rows access pointer by DWORD
    std::vector<DWORD *> RowsD;
    // Rows access pointer by BYTE quads
    std::vector<BYTE (*)[4]> RowsB;

    // Image size references
    const INT &W = Width, &H = Height;

    /* Class default construtor */
    image( VOID );

    /* Class construtor.
     * ARGUMENTS:
     *   - image file name:
     *       const std::string &FileName;
     */
    image( const std::string &FileName );
  }; /* End of image class */
} /* End of 'mk5' namespace */

#endif /* __IMAGE_H_ */

/* END OF 'IMAGE.H' FILE */

