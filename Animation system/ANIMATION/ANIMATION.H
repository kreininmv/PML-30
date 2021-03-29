/* FILE NAME   : ANIMATION.H
 * PURPOSE     : Animation system.
 *               HeaderModule.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __ANIM_H_
#define __ANIM_H_

#include "WIN/WIN.H"
#include "INPUT/INPUT.H"
#include "RENDER/RENDER.H"
#include "TIMER/TIMER.H"
#include "RESOURCES/SHADER.H"
#include "RESOURCES/MATERIAL.H"
#include "RESOURCES/TEXTURE.H"
#include "RESOURCES/OBJECT.H"

namespace mk5
{
  class anim;

  /* Anymation system active element base class declaration */
  class unit
  {
  public:
    /* Interframe animation response function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */

    /* Render unit function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */

  }; /* End of 'unit' class */

  class anim : public win, public render, public timer, public input, public prim, public shader, public material, public texture, public object
  {
  private:
    /* Time for reload shaders */
    FLT ReloadTime;

    anim( VOID );
    ~anim( VOID );

  public:
    static anim & Get( VOID );

    /* Animation unit stock */
    stock<unit *> Units;

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      /* Update timer data */
      timer::Response();

      /* Update input system */
        input::Response();

      // Call all responses of units
      Units.Walk([this]( unit *Uni )
      {
        Uni->Response(this);
      });

      // Update shaders
      if (GlobalTime - ReloadTime > 3)
      {
        SetWindowText(win::hWnd, (std::to_string(timer::FPS)).c_str());
        for (auto s : Shad.Stock)
          s.second->Update();
        ReloadTime = GlobalTime;
      }

      render::FrameStart();
      glLoadMatrixf(Cam.VP[0]);
      glBegin(GL_TRIANGLES);
      glColor3d(1, 0, 0);
      glVertex3d(0, 0, 0);
      glVertex4d(1, 0, 0, 0);

      glColor3d(0, 1, 0);
      glVertex3d(0, 0, 0);
      glVertex4d(0, 1, 0, 0);
      glColor3d(0, 0, 1);
      glVertex3d(0, 0, 0);
      glVertex4d(0, 0, 1, 0);

      glEnd();
      // Call all renders of units
      Units.Walk([this]( unit *Uni )
      {
        Uni->Render(this);
      });
      render::FrameEnd();
      render::FrameCopy();
    } /* End of 'Render' function */

    /***
     * Functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID )
    {
    }
    /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Resize( VOID )
    {
      render::Resize(win::W, win::H);
      Render();
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Erase( HDC hDC )
    {
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Timer handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Timer( VOID )
    {
      Render();
    } /* End of 'Timer' function */

    /* Activate handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Activate( VOID )
    {
    } /* End of 'Activate' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Idle( VOID )
    {

    } /* End of 'Idle' function */
  };
}
#endif /* __ANIM_H_ */

/* END OF 'ANIM.H' FILE */