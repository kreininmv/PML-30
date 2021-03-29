/* FILE NAME   : MATERIAL.H
 * PURPOSE     : Materials module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "..//ANIMATION.H"
#include "MATERIAL.H"


namespace mk5
{
  resource_manager<material> material::Materials;

  /* Apply material function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID material::Apply( VOID )
  {
    anim &Ani = anim::Get();

    /* Apply shader */
    if (Shd == nullptr)
      Shd = Ani.Shad.Find("OBJ");
    Shd->Apply();

    /* Textures */
    for (INT i = 0, k = 0; i < 8; i++)
      if (Tex[i] != nullptr)
        Tex[i]->Apply(k++);
  } /* End of 'Apply' function */
} /* End of 'mk5' namespace */

/* END OF 'MATERIAL.CPP' FILE */