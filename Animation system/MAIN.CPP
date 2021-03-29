/* FILE NAME   : MAIN.CPP
 * PURPOSE     : Main module.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "BASE/DEF.H"
#include "ANIMATION/ANIMATION.H"
#include "ANIMATION/UNITS/CTRL.H"
#include "ANIMATION/UNITS/TEST.H"
#include "ANIMATION/UNITS/ZORKA.H"
#include "ANIMATION/UNITS/MANDELBROT.H"

/* The main porgram function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success);
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  mk5::anim & ani_sys = mk5::anim::Get(); 
    
  ani_sys.Units.Add(new mk5::your_class_unit);

  ani_sys.Run();
  return 0x1E;
} /* End of 'WinMain' function*/

/* END OF 'MAIN.CPP' FILE */