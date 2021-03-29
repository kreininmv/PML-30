/* FILE NAME   : TEST.H
 * PURPOSE     : Test Unit.
 *               Unit module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __TEST_H_
#define __TEST_H_

#include "..\\ANIMATION.H"
#include "..\\RESOURCES\OBJECT.H"

/* Project namespace */
namespace mk5
{
  /* Test unit class */
  class unit_test : public unit
  {
  public:
    //sphere *Sp = new sphere(vec(0), 5);
    //prim *Pr = new prim("Klass");
    //shader *Sh = new shader("OBJ");
    //object *Obj = new object("BIN\\MODELS\\Cyprys_House.g3dm", mth::MATR<FLT>::Identity(), "OBJ");
    
    /* Class constructor.
     * ARGUMENT:
     *   - animation interface pointer:
     *       mk5::anim *Ani;
     */
    unit_test( VOID )
    {
      //vertex VER[3];
      anim & Ani = anim::Get();
      //Sh->ShaderLoad("OBJ");
      //Sh->ShaderLoad("STD");
      //for (int i = 0; i < 3; i++)
      //{
      //  VER[i].P = vec(i * 3, 2, 2);
      //  VER[i].T = vec2(0);
      //  VER[i].N = vec(1);
      // VER[i].C = vec4(1);
      //}
      //VER[2].P = vec(2, 2, 1);
      //Pr->FromvertexArray(VER, 3);
      //Ani.Primitives.Add();
      //Ani.Shad.Add(Sh);
      //Pr->LoadFromFile((CHAR *)"C:\\Users\\MK5\\source\\repos\\T05ANIM\\OBJECTS\\cow.object");
      //Ani.Primitives.Add(Pr);
      //Ani.Objects.Add(Obj);
    }
    /* End of 'unit_test' function */

    ~unit_test( VOID )
    {
    }

    /* Interframe animation response function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani )
    {
    }
    /* End of 'Response' function */

    /* Render unit function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani )
    {
      //Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity());
      //Obj->Draw(mth::MATR<FLT>::Identity());
      //Ani->DrawMatr(Pr, mth::MATR<FLT>::Identity());
      //Ani->Draw(Pr);
    }
    /* End of 'Render' function */

  }; /* End of 'primitives' class */
} /* end of 'mk5' namespace */

#endif /* __TEST_H_ */

  /* END OF 'TEST.H' FILE */