/* FILE NAME   : MATER.H
 * PURPOSE     : Material system.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __MATER_H_
#define __MATER_H_

#include "..//../BASE/DEF.H"
#include "TEXTURE.H"

namespace mk5
{
  /* Shaders class */
  class material
  {
  public:
    /* Material name */
    std::string Name;

    static resource_manager<material> Materials;

    /* Illumination coefficients (anbient, diffuse, specular) */
    vec Ka;
    vec Kd;
    vec Ks;


    /* Phong coefficient and transparency value */
    FLT Ph, Trans;

    /* Shader pointer */
    shader *Shd;

    /* Texture pointers */
    texture *Tex[8];

    /* Class default constructor */
    material( VOID )
    {
    } /* End of 'material' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &NewName;
     *   - illumination coefficients (ambient. diffuse, specular):
     *       const color3 &NewKa, &NewKd, &NewKs;
     *   - Phong shininess coefficient:
     *       FLT NewPh;
     *   - transparency coefficient:
     *       FLT NewTrans;
     *   - shader pointer:
     *       shader *NewShd;
     *   - texture 0 pointer:
     *       texture *NewTex0;
     *   - texture 1 pointer:
     *       texture *NewTex1;
     *   - texture 2 pointer:
     *       texture *NewTex2;
     *   - texture 3 pointer:
     *       texture *NewTex3;
     */
    material( const std::string &NewName, const vec &NewKa = vec(0.1), const vec &NewKd = vec(0.9), const vec &NewKs = vec(0),
      FLT NewPh = 30, FLT NewTrans = 1, shader *NewShd = nullptr, std::initializer_list<texture *> Textures = {} ) :
      Name(NewName), Ka(NewKa), Kd(NewKd), Ks(NewKs), Ph(NewPh), Trans(NewTrans), Shd(NewShd)
    {
      INT i;
      for (INT i = 0; i < 8; i++)
        Tex[i] = nullptr;
      i = 0;
      for (auto t : Textures)
        Tex[i++] = t;
    } /* End of 'material' function */

    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID );

  }; /* End of 'material' class */
} /* End of 'mk5' namespace */

#endif /* __MATER_H_*/

/* END OF 'MATERIAL.H' FILE */