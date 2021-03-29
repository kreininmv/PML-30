/* FILE NAME   : ANIMATION.CPP
 * PURPOSE     : Animation system.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "ANIMATION.H"
#include "UNITS/TEST.H"
#include "UNITS/CTRL.H"

namespace mk5
{
  anim::anim( VOID ) : win(), input(win::hWnd, win::MouseWheel), render(win::hWnd),
    timer(), ReloadTime(timer::GlobalTime)
  {
  }

  anim::~anim( VOID )
  {
    /* Delete all system units */
    Units.Walk([]( unit *Uni )
    {
      delete Uni;
    });
  }

  anim & anim::Get( VOID )
  {
    static anim Klass;
    return Klass;
  }
}
/* END OF 'ANIM.CPP' FILE */