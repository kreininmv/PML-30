/* FILE NAME   : MAIN.CPP
 * PURPOSE     : Main module.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 24.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "DEF.H"
#include "WIN/WIN.H"
#include "RT/RT.H"

using namespace mert;

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
  rt &RayTracing = rt::Get();

  RayTracing.Run();

  return 30;
} /* End of 'WinMain' function*/

/* END OF 'MAIN.CPP' FILE */