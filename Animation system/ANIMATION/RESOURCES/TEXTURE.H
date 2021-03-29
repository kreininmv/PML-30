/* FILE NAME   : TEXTURE.H
 * PURPOSE     : Texture system.
 *               HeaderModule.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __TEXT_H_
#define __TEXT_H_

#include "RESMANAGER.H"
#include "SHADER.H"

namespace mk5
{
  class texture 
  {
  public:
    FLT TexKoef;                                /*     Texture coefficent    */
    UINT TexNo;                                 /*     Text identificator    */
    INT W, H;                                   /* Texture weight and height */
    std::string Name;                           /*        Texture name       */
    static INT SamplerNo;                       /*       Sampler counter     */
    static resource_manager<texture> Textures;  /*       Texture manager     */

    /* Texture create function.
     * ARGUMENTS:
     *   - link to texture name:
     *       const std::string &nName;
     *   - texture weight and height:
     *       const INT nW, nH;
     *   - pointer to texture data:
     *       DWORD *Bits;
     * RETURNS: None.
     */
    texture( const std::string &nName, const INT nW, const INT nH, INT C, BYTE *Bits )
    {
      TexCreate(nName, nW, nH, C, Bits);
    }
    /* Texture constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    texture( VOID )
    {
      TexKoef = 1;
    } /* End of 'texture' constructor */

    /* Texture destructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~texture( VOID )
    {
    } /* End of '~texture' destructor */

    /* Texture constructor.
     * ARGUMENTS:
     *   - link to texture name:
     *       const std::string &name;
     * RETURNS: None.
     */
    texture( const std::string &name ) : Name(name)
    {
      TexKoef = 1;
    } /* End of 'texture' constructor */
    
    /* Texture create function.
     * ARGUMENTS:
     *   - link to texture name:
     *       const std::string &nName;
     *   - texture weight and height:
     *       const INT nW, nH;
     *   - pointer to texture data:
     *       DWORD *Bits;
     * RETURNS: None.
     */
    VOID TexCreate( const std::string &nName, const INT nW, const INT nH, INT C, BYTE *Bits )
    {
      /* Allocate texture space */
      glGenTextures(1, &TexNo);
      glBindTexture(GL_TEXTURE_2D, TexNo);

      /* Upload texture */
      gluBuild2DMipmaps(GL_TEXTURE_2D, C, nW, nH, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Bits);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      H = nH;
      W = nW;
      Name = nName;
      glBindTexture(GL_TEXTURE_2D, 0);
    } /* End of 'TexCreate' function */

    /* Load texture from G24 
     * ARGUMENTS:
     *   - name of file
     *       const std::string &FileName
     * RETURNS: None.
     */
    VOID LoadTex( const std::string &FileName )
    {
      BYTE *img;
      INT w = 0, h = 0;
      FILE *F;

      F = fopen(FileName.c_str(), "rb");
      if (F == NULL)
        return;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);

      img = new BYTE(3 * w * h);
      if (img == NULL)
      {
        fclose(F);
        return;
      }

      fread(img, 3, w * h, F);

      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      gluBuild2DMipmaps(GL_TEXTURE_2D, 3, w, h, GL_BGR_EXT, GL_UNSIGNED_BYTE, img);
      delete [] img;
      fclose(F);
    } /* End of 'LoadTex' function */

    /* Texture create function.
     * ARGUMENTS:
     *   - texture number:
     *       const INT Number;
     * RETURNS: None.
     */
    VOID Apply( const INT Number )
    {
      glActiveTexture(GL_TEXTURE0 + Number);
      glBindTexture(GL_TEXTURE_2D, TexNo);
    } /* End of 'Apply' function */

    VOID FromFile( const std::string &nFileName )
    {
      HBITMAP hBm;
      // Image pixel data
      std::vector<BYTE> Pixels;

      std::string FileName = "BIN\\TEXTURES\\" + nFileName;

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

        W = bm.bmWidth;
        H = bm.bmHeight;

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
        BitBlt(hMemDC1, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
        DeleteDC(hMemDC);
        DeleteDC(hMemDC1);

        Pixels.resize(bmih.biSizeImage);
        CopyMemory(&Pixels[0], Bits, bmih.biSizeImage);
        DeleteObject(hImage);

        // Make alpha channel
        for (INT i = 3; i < W * H * 4; i += 4)
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
            W = fw;
            H = fh;
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
            W = fw;
            fread(&Pixels[0], 4, fw * fh, F);
          }
          fclose(F);
        }
      }

      /* Allocate texture space */
      glGenTextures(1, &TexNo);
      glBindTexture(GL_TEXTURE_2D, TexNo);

      /* Upload texture */
      gluBuild2DMipmaps(GL_TEXTURE_2D, 4, W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Pixels.data());
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      Name = FileName;
      glBindTexture(GL_TEXTURE_2D, 0);
    } /* End of 'TexCreate' function */
  }; /* End of 'texture' class */
} /* End of 'mk5' namespace */

#endif /* __TEXT_H_ */

/* END OF 'TEXT.H' FILE */