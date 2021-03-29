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
#include "RAY.H"

/* Math library namespace */
namespace mth
{
  /* Space CAMERA handle class */
  template<typename Type = FLT>
  class CAMERA
  {
  public:
    Type Near,          // Camera render parameters
      Far,
      ProjSize;
    VEC<Type> Loc, Dir, // Camera parameters
      Up, Right,
      At, Up1;
   MATR<Type> MatrView, // Camera matricies
     MatrFrustum, 
     MatrOrtho, 
     MatrProj, 
     VP;
    Type FW, FH,        // Ray tracing parameters
      WP, HP;

    /* Camera construcor function.
     * ARGUMENTS:
     *   - camera params:
     *       vec L, A, U;
     *       Type l, r, b, t, n, f;
     *   - camera render mode:
     *       CamMode m;
     * RETURNS: None.
     */
    CAMERA( const VEC<Type> & L, const VEC<Type> & A, const VEC<Type> & U,
      const Type & l, const Type & r, const Type & b, const Type & t, const Type & n, const Type & f) : Loc(L), At(A), Up(U), Near(n), Far(f)
    {
      UpdateView();
    } /* End of 'camera' constructor */

    /* camera construcor function.
     * ARGUMENTS:
     *   - camera params:
     *       vec L, A, U;
     *   - camera render mode:
     *       CamMode m;
     * RETURNS: None.
     */
    CAMERA( const VEC<Type> & L, const VEC<Type> & A, const VEC<Type> & U ) : Loc(L), At(A), Up(U)
    {
      UpdateView();
    } /* End of 'camera' constructor */

    /* camera construcor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    CAMERA( void ) : Loc(0), At(0), Up(0, 1, 0)
    {
      UpdateView();
      Far = 1;
      Near = 0;
    } /* End of 'camera' constructor */


    /* Update camera project parameters function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    //VOID UpdateProj( VOID )
    //{
    //  Type ratio_x = ProjSize / 2, ratio_y = ProjSize / 2;
    //
    //  if (FW >= FH)
    //    ratio_x *= (Type)FW / FH;
    //  else
    //    ratio_y *= (Type)FH / FW;
    //  Proj = MATR<Type>::Frustum(-ratio_x, ratio_x, -ratio_y, ratio_y, ProjDist, FarClip);
    //} /* End of 'UpdateProj' function */

    /* Set camera project pixel size function.
     * ARGUMENTS:
     *   - new frame size in pixels:
     *       Type NewFrameW, NewFrameH;
     * RETURNS:
     *   (CAMERA &) self reference.
     */
    CAMERA & Resize( INT NewFrameW, INT NewFrameH )
    {
      FW = (FLT)NewFrameW;
      FH = (FLT)NewFrameH;

      //UpdateProj();
      return *this;
    } /* End of 'Resize' function */

    /* View matrix update function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateView( VOID )
    {
      Dir = (At - Loc).Normalize();
      Right = (Dir % Up).Normalize();
      Up = (Right % Dir).Normalize();
    } /* End of 'UpdateView' function */

    /* Camera move forward function.
     * ARGUMENTS:
     *   - direction:
     *       FLT Direction;
     * RETURNS:
     */
    VOID MoveForward( const FLT Direction )
    {
      Loc += (Dir * Direction);
      At += (Dir * Direction);
    } /* End of 'MoveForward' function */

    /* Camera move right function.
     * ARGUMENTS:
     *   - direction:
     *       FLT Direction;
     * RETURNS:
     */
    VOID MoveRight( const FLT Direction )
    {
      Loc += (Right * Direction);
      At += (Right * Direction);
    } /* End of 'MoveRight' function */

    /* Camera turn around Y axis function.
     * ARGUMENTS:
     *   - Angle:
     *       FLT Angle;
     * RETURNS:
     */
    VOID TurnY( const FLT Angle )
    {
      VEC<Type> TmpAt = (At - Loc);

      Dir = MatrView.VectorMulMatr(Dir, MatrView.Rotate(Angle, Up));
      At = MatrView.VectorMulMatr(TmpAt, MatrView.Rotate(Angle, Up)) + Loc;
      UpdateView();
    } /* End of 'TurnY' function */

    /* Camera turn around XZ axis function.
     * ARGUMENTS:
     *   - Angle:
     *       FLT Angle;
     * RETURNS:
     */
    VOID TurnXZ( const FLT Angle )
    {
      VEC<Type> TmpAt = (At - Loc);

      Dir = MatrView.VectorMulMatr(Dir, MatrView.Rotate(Angle, Right));
      At = MatrView.VectorMulMatr(TmpAt, MatrView.Rotate(Angle, Right)) + Loc;
      UpdateView();
    } /* End of 'TurnY' function */

    /* Set camera ray tracing parameters function.
     * ARGUMENTS:
     *   - Frame size in pixels:
     *       Type FrameW, FrameH;
     * RETURNS:
     */
    VOID SetRayTracing( const Type FrameW, const Type FrameH )
    {
      FW = FrameW;
      FH = FrameH;

      Type ratio_x, ratio_y, Size = ProjSize;

      ratio_x = ratio_y = 1;

      if (FrameW > FrameH)
        ratio_x = (Type)FrameW / FrameH;
      else
        ratio_y = (Type)FrameH / FrameW;

      WP = ratio_x * Size;
      HP = ratio_y * Size;
    } /* End of 'SetRayTracing' function */

    /* Create ray function.
     * ARGUMENTS:
     *   - screen coordinates:
     *       Type Wx, Wy;
     * RETURNS:
     *   (ray) new ray.
     */
    RAY<Type> CastRay( Type Wx, Type Wy )
    {
      VEC<Type> X = 
        VEC<Type>(Dir * Near + 
          Right * ((Wx + 0.5f - FW / 2) / FW) * WP +
          Up * ((-(Wy + 0.5f) + FH / 2) / FH) * HP);

      return RAY<Type>(X + Loc, X.Normalize());
    } /* End of 'CastRay' function */
  }; /* End of 'CAMERA' class */
} /* End of 'mth' namespace */

#endif /* __CAMERA_H_ */

  /* END OF 'CAMERA.H' FILE */