/* FILE NAME   : CTRL.H
 * PURPOSE     : Control Unit.
 *               Unit module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __CTRL_H
#define __CTRL_H_

#include "..\\ANIMATION.H"

using namespace mth;

namespace mk5
{  
  /* Control unit class */
  class unit_control : public unit
  {
  private:
    // Camera distance to look at point, rotation angles
    FLT Dist = 18, Rx = 0, Ry = 0;
    FLOAT Dv = 0, Du = 0, Dw = 0;
    // Camera look at point
    vec At = vec(0);
  public:
    /* Class constructor.
    * ARGUMENT: None.
    */
    unit_control( VOID )
    {
    } /* End of 'unit_control' function */

      /* Interframe animation response function.
      * ARGUMENT:
      *   - animation interface pointer:
      *       anim *Ani;
      * RETURNS: None.
      */
    VOID Response( anim *Ani )
    {
    //// Keyboard handle
    if (Ani->Keys[VK_ESCAPE])
      Ani->DoExit();
    if (Ani->KeysClick['F'])
      Ani->FlipFullScreen();
    if (Ani->KeysClick['P'])
      Ani->IsPause = !Ani->IsPause;
    if (Ani->KeysClick[VK_HOME])
      Ani->Cam.At = vec(0);
    //
    //
    ////Handle camera
    //matr m1, m2;
    //
    //Dv += (30 * Ani->Mdy * Ani->Keys[VK_LBUTTON] + 30 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])) * Ani->GlobalDeltaTime;
    //Du += (-30 * Ani->Mdx * Ani->Keys[VK_LBUTTON] + 30 * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])) * Ani->GlobalDeltaTime;
    //Dw += (3 * Ani->Mdz + 3 * Ani->Keys[VK_SHIFT] * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR])) * Ani->GlobalDeltaTime;
    //m1 = mth::MATR<FLT>::RotateX(Dv * 0.30);
    //m2 = mth::MATR<FLT>::RotateY(Du * 0.30);
    //m1 = m1 * m2;
    //Ani->Cam.Loc = m1.TransformPoint(vec(0, 0, Dw));
    //if (!Ani->Keys[VK_SHIFT])
    //{
    //  vec
    //    R = vec(Ani->Cam.View[0][0], Ani->Cam.View[4][0], Ani->Cam.View[8][0]),
    //    D = vec(-Ani->Cam.View[2][0], -Ani->Cam.View[6][0], -Ani->Cam.View[10][0]),
    //    U = vec(Ani->Cam.View[1][0], Ani->Cam.View[5][0], Ani->Cam.View[9][0]),
    //    shift = (R * ((-Ani->Keys['D'] + Ani->Keys['A']) * Dw ) +
    //             D * ((-Ani->Keys['W'] + Ani->Keys['S']) * Dw ) +
    //             U * ((Ani->Keys[VK_PRIOR] - Ani->Keys[VK_NEXT]) * Dw / 10.0)) *
    //             2.8 * Ani->GlobalDeltaTime;
    //  Ani->Cam.At += shift;
    //}
    ////Ani->Cam.SetLocAtUp(Ani->Cam.Loc + Ani->Cam.At, Ani->Cam.At, vec(0, 1, 0));
    } /* End of 'Response' function */

    /* Render unit function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */
  }; /* End of 'unit_control' class */
}
#endif /* __CTRL_H_ */
/* END OF 'CTRL.H' FILE */