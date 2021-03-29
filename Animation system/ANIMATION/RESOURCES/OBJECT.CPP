/* FILE NAME   : OBJECT.CPP
 * PURPOSE     : Texture system.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "OBJECT.H"
#include "..//RENDER/RENDER.H"
#include "..\\ANIMATION.H"

namespace mk5
{
  resource_manager<object> object::Objects;
  /* Load primitives from 'G3DM' file function.
   * ARGUMENTS:
   *   - file name:
   *       const std::string &FileName;
   *   - transformation matrix:
   *       const matr &Transform;
   *   - shader name:
   *       const std::string &ShaderName;
   * RETURNS:
   *   (BOOL) TRUE if success, FALSE otherwise.
   */
  BOOL object::Load( const std::string &FileName, matr &Transform, const std::string &ShaderName )
  {
    FILE *F;
    DWORD Sign;
    INT NoofP = 0, NoofM = 0, NoofT = 0, i;
    anim &Ani = anim::Get();

    /* Open file */
    if ((F = fopen(FileName.c_str(), "rb")) == NULL)
      return FALSE;
    /* Check signature */
    fread(&Sign, 4, 1, F);
    if (Sign != *(DWORD *)"G3DM")
    {
      fclose(F);
      return FALSE;
    }

    /* Read quantities */
    fread(&NoofP, 4, 1, F);
    fread(&NoofM, 4, 1, F);
    fread(&NoofT, 4, 1, F);

    Prims.resize(NoofP);

    /* Primitive material indices */
    std::vector<INT> prims_mtl;
    prims_mtl.resize(NoofP);

    /* Load primitives */
    for (i = 0; i < NoofP; i++)
    {
      INT nv = 0, ni = 0, j;
      std::vector<vertex> V;
      std::vector<INT> I;

      fread(&nv, 4, 1, F);
      fread(&ni, 4, 1, F);
      fread(&prims_mtl[i], 4, 1, F);
      V.resize(nv);
      I.resize(ni);

      fread(&V[0], 1, sizeof(vertex) * nv, F);
      fread(&I[0], 1, sizeof(INT) * ni, F);

      for (j = 0; j < nv; j++)
      {
        V[j].P = Transform.TransformPoint(V[j].P);
        V[j].N = Transform.TransformNormal(V[j].N);
      }
      trimesh T(V, I);
      Prims[i] = new prim(T, FileName + std::to_string(i));
      prim::Primitives.Add(Prims[i]);
    }

    /* Load materials */
    struct STORE_MATERIAL
    {
      CHAR Name[300]; /* Material name */

                      /* Illumination coefficients */ 
      vec Ka, Kd, Ks;        /* Ambient, diffuse, specular coefficients */
      FLT Ph;                /* Phong power coefficient */
      FLT Trans;             /* Transparency factor */
      INT Tex[8];            /* Texture references */

                             /* Shader string */
      CHAR ShaderStr[300];
      INT Shader;            /* Shader id */
    }; /* End of 'STORE_MATERIAL' struct */

    std::vector<material *> mtls;
    std::vector<STORE_MATERIAL> store_mtls;
    mtls.resize(NoofM);
    store_mtls.resize(NoofM);
    if (NoofM > 0)
    {
      fread(&store_mtls[0], sizeof(STORE_MATERIAL), NoofM, F);
      for (INT i = 0; i < NoofM; i++)
      {
        std::string s = store_mtls[i].Name;
        mtls[i] = new material(FileName + s,
          store_mtls[i].Ka, store_mtls[i].Kd, store_mtls[i].Ks,
          store_mtls[i].Ph, store_mtls[i].Trans);
        material::Materials.Add(mtls[i]);
      }
    }

    /* Load textures */
    std::vector<texture *> texs;
    texs.resize(NoofT);
    for (i = 0; i < NoofT; i++)
    {
      CHAR Name[300];
      INT W, H, C;
      BYTE *mem;

      fread(Name, 1, 300, F);
      fread(&W, 4, 1, F);
      fread(&H, 4, 1, F);
      fread(&C, 4, 1, F);
      mem = new BYTE[W * H * C];
      glDrawPixels(W, H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, mem);
      fread(mem, C, W * H, F);
      texs[i] = new texture(Name, W, H, C, mem);
      delete[] mem;
      Ani.Textures.Add(texs[i]);
    }
    fclose(F);

    /* Correct material texture references */
    for (INT i = 0; i < NoofM; i++)
      for (INT t = 0; t < 8; t++)
        if (store_mtls[i].Tex[t] != -1)
          mtls[i]->Tex[t] = texs[store_mtls[i].Tex[t]];

    /* Correct primitives material references */
    for (INT i = 0; i < NoofP; i++)
      if (prims_mtl[i] != -1)
        Prims[i]->mtl = mtls[prims_mtl[i]],
        Prims[i]->mtl->Shd = shader::Shad.Find(ShaderName);
      else
        Prims[i]->mtl = new material(FileName + "mtl" + (CHAR)i),
        Ani.Materials.Add(Prims[i]->mtl);
    return TRUE;
  } /* End of 'mk5::primitives::Load' function */

 // VOID obj::Draw( matr M )
 // {
 //  for (auto r : Prims)
 //   {
 //     render::DrawMatr(r, M);
 //   }
 //   
 // }
}

/* END OF 'OBJECT.CPP' FILE */
