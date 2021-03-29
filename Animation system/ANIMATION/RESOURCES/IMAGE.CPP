/* FILE NAME   : IMAGE.CPP
 * PURPOSE     : Image system.
 *               Image handle class implementation module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "IMAGE.H"

/* Class default construtor */
mk5::image::image( VOID )
{
} /* End of 'mk5::image::image' function */

/* Class construtor.
 * ARGUMENTS:
 *   - image file name:
 *       const std::string &FileName;
 */
mk5::image::image( const std::string &FileName )
{
  HBITMAP hBm;
  if ((hBm = (HBITMAP)LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) != NULL)
  {
    // Case of BMP file

    /* Create contextes */
    HDC hDC = GetDC(NULL);
    HDC hMemDC = CreateCompatibleDC(hDC);
    HDC hMemDC1 = CreateCompatibleDC(hDC);
    SelectObject(hMemDC, hBm);
    ReleaseDC(NULL, hDC);

    BITMAP bm;
    GetObject(hBm, sizeof(bm), &bm);

    BITMAPINFOHEADER bmih;

    Width = bm.bmWidth;
    Height = bm.bmHeight;

    /* Build DIB section */
    memset(&bmih, 0, sizeof(bmih));
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biBitCount = 32;                   /* BGRx - DWORD */
    bmih.biPlanes = 1;                      /* always */
    bmih.biCompression = BI_RGB;            /* 0 - no compression */
    bmih.biWidth = bm.bmWidth;              /* width */
    bmih.biHeight = -bm.bmHeight;           /* height + first coded row is 0 */
    bmih.biSizeImage = bm.bmWidth * bm.bmHeight * 4;  /* image size in bytes */

    VOID *Bits;
    HBITMAP hImage = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS,
      (VOID **)&Bits, NULL, 0);
    SelectObject(hMemDC1, hImage);

    /* Draw load image to DIB */
    BitBlt(hMemDC1, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
    DeleteDC(hMemDC);
    DeleteDC(hMemDC1);

    Pixels.resize(bmih.biSizeImage);
    CopyMemory(&Pixels[0], Bits, bmih.biSizeImage);
    DeleteObject(hImage);

    // Make alpha channel
    for (INT i = 3; i < Width * Height * 4; i += 4)
      Pixels[i] = 255;
  }
  else
  {
    FILE *F;

    if ((F = fopen(FileName.c_str(), "rb")) != NULL)
    {
      // Case of G24/G32
      INT fw = 0, fh = 0;
      fread(&fw, 2, 1, F);
      fread(&fh, 2, 1, F);
      fseek(F, 0, SEEK_END);
      INT flen = ftell(F);
      if (flen == 4 + fw * fh * 3)
      {
        // G24
        fseek(F, 4, SEEK_SET);
        Pixels.resize(fw * fh * 4);
        Width = fw;
        Height = fh;
        for (INT r = 0, p = 0; r < fh; r++)
          for (INT c = 0; c < fw; c++)
          {
            BYTE rgb[3];
            fread(rgb, 3, 1, F);
            Pixels[p++] = rgb[0];
            Pixels[p++] = rgb[1];
            Pixels[p++] = rgb[2];
            Pixels[p++] = 255;
          }
      }
      else if (flen == 4 + fw * fh * 3)
      {
        // G32
        fseek(F, 4, SEEK_SET);
        Pixels.resize(fw * fh * 4);
        Width = fw;
        fread(&Pixels[0], 4, fw * fh, F);
      }
      fclose(F);
    }
  }
  // Setup row pointers
  INT i;
  RowsD.resize(Height);
  i = 0;
  for (auto &r : RowsD)
    r = (DWORD *)&Pixels[i++ * Width * 4];
  RowsB.resize(Height);
  i = 0;
  for (auto &r : RowsB)
    r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
} /* End of 'mk5::image::image' function */

/* END OF 'IMAGE.CPP' FILE */
