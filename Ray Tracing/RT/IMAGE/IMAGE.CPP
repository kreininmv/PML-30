/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : Image module
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "..//..//DEF.H"
#include "IMAGE.H"

namespace mert
{
  /* Class constructor function.
   * ARGUMENTS:
   *   - window handle:
   *       HWND hWorkWnd;
   * RETURNS: None.
   */
  image::image( const HWND &hWWnd ) : hWnd(hWWnd)
  {
    HDC hDC = GetDC(hWnd);
    hMemDc = CreateCompatibleDC(hDC);


    memset(&bmih, 0, sizeof(bmih));
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biBitCount = 32;
    bmih.biPlanes = 1;
    bmih.biCompression = BI_RGB;
    ImageW = bmih.biWidth = 1920;
    ImageH = bmih.biHeight = -1080;
    bmih.biSizeImage = ImageW * ImageH * 4;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;
    bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0; // resolution

    hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS, (VOID **)&Bits, NULL, 0);

    for (INT i = 0; i < -ImageH; i++)
      for (INT j = 0; j < ImageW; j++)
        Bits[i * ImageW + j] = i * j + j * i * 4 + 100;
  } /* End of 'image' constructor */

  /* Draw bitmap function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID image::DrawImage( VOID )
  {
    BITMAP bm;
    HDC hDC = GetDC(hWnd);

    GetObject(hBm, sizeof(BITMAP), &bm);
    SelectObject(hMemDc, hBm);
    BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hMemDc, 0, 0, SRCCOPY);
  } /* End of 'DrawImage' function */

  /* Save image in BMP format function.
   * ARGUMENTS:  None.
   * RETURNS: None.
   */
  VOID image::SaveBMP( VOID )
  {
    FILE *F;

    if ((F = fopen("test.bmp", "w")) == nullptr)
      return;

    UINT bpl = (ImageW * 3 + 3) / 4 * 4;
    BITMAPINFOHEADER bih;
    BITMAPFILEHEADER bfh;

    bfh.bfType = 'B' | ('M' << 8);
    bfh.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bpl * -ImageH;
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biWidth = ImageW;
    bih.biHeight = -ImageH;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = BI_RGB;
    bih.biSizeImage = bpl * -ImageH;
    bih.biClrImportant = 0;
    bih.biClrUsed = 0;
    bih.biXPelsPerMeter = bih.biYPelsPerMeter = 0;

    fwrite(&bfh, sizeof(BITMAPFILEHEADER), 1, F);
    fwrite(&bih, sizeof(BITMAPINFOHEADER), 1, F);

    BYTE *row = new BYTE[bpl];

    for (INT y = -ImageH - 1; y >= 0; y--)
    {
      for (INT x = 0; x < ImageW; x++)
      {
        row[x * 3 + 0] = Bits[y * ImageW + x] & 0xFF;
        row[x * 3 + 1] = (Bits[y * ImageW + x] >> 8) & 0xFF;
        row[x * 3 + 2] = (Bits[y * ImageW + x] >> 16) & 0xFF;
      }
      fwrite(row, 1, bpl, F);
    }

    delete row;
    fclose(F);
  } 
  /* End of 'SaveBMP' function */
   
  /* Set pixel color function.
   * ARGUMENTS:
   *   - pixel coords:
   *       INT x, y;
   *   - pixel color:
   *       DWORD Color;
   * RETURNS: None.
   */
  VOID image::PutPixel( const INT X, const INT Y, const DWORD Color )
  {
    Bits[Y * ImageW + X] = Color;
  } /* End of 'PutPixel' function */
} /* End of 'mert' namespace */

/* END OF 'IMAGE.CPP' FILE */