/* FILE NAME   : CAMERA.H
 * PURPOSE     : CAMERA.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mth'.
 */

#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "VEC.H"
#include "MATR.H"

/* Math library namespace */
namespace mth
{
  /* Space CAMERA handle class */
  template<typename Type = FLT>
  class CAMERA
  {
  private:
    /* Update CAMERA project parameters function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateProj( VOID )
    {
      Type ratio_x = Size / 2, ratio_y = Size / 2;

      if (FrameW >= FrameH)
        ratio_x *= (Type)FrameW / FrameH;
      else
        ratio_y *= (Type)FrameH / FrameW;
      Proj = MATR<Type>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, FarClip);
    } /* End of 'UpdateProj' function */

    /* Update CAMERA view parameters function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateView( VOID )
    {
      View = MATR<Type>::View(Loc, At, Up);
    } /* End of 'UpdateView' function */

  public:
    VEC<Type>
      Loc,            // CAMERA location
      Dir, Up, Right, // basis CAMERA directions
      At;             // CAMERA pivot poINT
    Type
      ProjDist,       // near project plane distance
      FarClip,        // far project plane distance
      Size;           // inner project plane rectangle size
    INT
      FrameW, FrameH; // CAMERA frame size
    MATR<Type>
      View,           // view MATRix
      Proj,           // projection MATRix
      VP;             // View and Proj madtrix production

                      /* Default constructor */
    CAMERA( VOID ) :
      Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(3, 0, 0),
      ProjDist(0.1f), FarClip(800), Size(0.1f),
      FrameW(1378), FrameH(750)
    { -
      Loc = VEC<Type>(-8.6568f, 5.2174f, -0.019f);
      UpdateProj();
      UpdateView();
      VP = View * Proj;
    } /* End of 'MATR' function */

    /* Set project CAMERA parameters function.
     * ARGUMENTS:
     *   - new near project plane size:
     *       Type NewSize;
     *   - new project distance:
     *       Type NewProjDist;
     *   - new far clip plane distance:
     *       Type FarC;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    CAMERA & SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
    {
      // Store new projection parameters
      ProjDist = NewProjDist;
      FarClip = NewFarClip;
      Size = NewSize;

      UpdateProj();
      VP = View * Proj;
      return *this;
    } /* End of 'SetProj' function */

    /* Set CAMERA project pixel size function.
     * ARGUMENTS:
     *   - new frame size in pixels:
     *       Type NewFrameW, NewFrameH;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    CAMERA & Resize( INT NewFrameW, INT NewFrameH )
    {
      FrameW = NewFrameW;
      FrameH = NewFrameH;

      UpdateProj();
      VP = View * Proj;
      return *this;
    } /* End of 'Resize' function */

    /* Set CAMERA location and orientation function.
     * ARGUMENTS:
     *   - new CAMERA location:
     *       const VEC<Type> &L;
     *   - new CAMERA pivot poINT:
     *       const VEC<Type> &A;
     *   - new CAMERA approx up direction:
     *       const VEC<Type> &U;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    CAMERA & SetLocAtUp( const VEC<Type> &L, const VEC<Type> &A, const VEC<Type> &U = VEC<Type>(0, 1, 0) )
    {
      Loc = L;
      At = A;
      Up = U;

      UpdateView();
      VP = View * Proj;
      return *this;
    } /* End of 'SetLocAtUp' function */

    /* CAMERA rotate function.
     * ARGUMENTS:
     *   - rotate axis:
     *       const VEC<Type> &Axis;
     *   - rotation angle (in degree):
     *       Type AngleInDegree;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    static CAMERA & Rotate( const VEC<Type> &Axis, Type AngleInDegree )
    {
      MATR<Type> m = MATR<Type>::Translate(-At) * MATR<Type>::Rotate(Axis, AngleInDegree) * MATR<Type>::Translate(At);
      Loc = m.TransformPoINT(Loc);
      Up = m.TransformVECtor(Up);
      SetLocAtUp(Loc, At, Up);
      return *this;
    } /* End of 'Rotate' function */

    /* CAMERA movement function.
     * ARGUMENTS:
     *   - movement directions:
     *       const VEC<Type> &Direction;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    CAMERA & Move( const VEC<Type> &Direction )
    {
      Loc += Direction;
      At += Direction;
      SetLocAtUp(Loc, At, Up);
      return *this;
    } /* End of 'Move' function */
  }; /* End of 'CAMERA' class */
} /* End of 'mth' namespace */

#endif /* __CAMERA_H_ */

  /* END OF 'CAMERA.H' FILE */