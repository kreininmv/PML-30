/* FILE NAME   : RT.CPP
 * PURPOSE     : Ray tracing.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 27.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "RT.H"

namespace mert
{
  /* rt constructor function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  rt::rt ( VOID ) : win()
  {
    Scene << new sphere(vec(3, 3, 3), 1.44) << new sphere(vec(-3, 1, -1), 1.89) << //new plane(vec(0, 1, 0), 0) <<
      /*new dir_light(vec(0, -1, 1), vec(1), 1, 1, 1) <<*/ //new dir_light(vec(0, -1, -1), vec(1), 1, 1, 1);
      new point_light(vec(-5, 15, 5), vec(1, 0, 0), 0.0, 0.0, 0.0) <<
      new point_light(vec(-5, 15, -5), vec(0, 1, 0), 0.0, 0.0, 0.0);// << new point_light(vec(0, 10, 0), vec(1, 0, 0), 0.01, 0.01, 0.01);

    Img = new image(win::hWnd);
  
    Cam = camera();
    Cam.Loc = vec(10, 2, 0);
    Cam.At = vec(0);
    Cam.Up = vec(0, 1, 0);
    Cam.UpdateView();
    Cam.ProjSize = 1;
    Cam.Near = 1;
    Cam.SetRayTracing(Img->ImageW, -Img->ImageH);
  } /* End of 'rt' constructor */
} /* End of 'mert' namespace */
/* END OF 'RT.CPP' FILE */