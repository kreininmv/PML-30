/* FILE NAME   : MATR.H
 * PURPOSE     : Matrix.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mth'.
 */

#ifndef __MATR_H_
#define __MATR_H_

#include "mthdef.h"
#include "VEC.h"

/* Math library namespace */
namespace mth
{
  /* Space transformation Matrix handle class */
  template <typename Type = double>
  class MATR
  {
    /* Delegate access rig;ht to other classes */
    friend class VEC<Type>;

  private:
    /* Transfomation Matrix */
    Type M[4][4];

    /* Inverse Matrix and it presence flag */
    mutable BOOL IsInverseObtain;
    mutable Type InverseM[4][4];

    /* Matrix 3x3 determinant obtain function.
     * ARGUMENTS:
     *   - Matrix elements:
     *       FLT A11, A12, A13,
     *           A21, A22, A23,
     *           A31, A32, A33;
     * RETURNS:
     *   (Type) determinant value.
     */
    Type MATRDeterm3x3( Type A11, Type A12, Type A13, Type A21, Type A22, Type A23, Type A31, Type A32, Type A33 )
    {
      return A11 * A22 * A33 - 
        A11 * A23 * A32 - 
        A12 * A21 * A33 + 
        A12 * A23 * A31 + 
        A13 * A21 * A32 - 
        A13 * A22 * A31;
    } /* End of 'MATRDeterm3x3' function */ 

    /* Matrix determinant obtain function.
     * ARGUMENTS:
     *   - source Matrix:
     *       MATR M;
     * RETURNS:
     *   (Type) determinant value.
     */
    Type Determ( VOID )
    {
      return
        M[0][0] * MATRDeterm3x3(M[1][1], M[1][2], M[1][3],
          M[2][1], M[2][2], M[2][3],
          M[3][1], M[3][2], M[3][3]) - 
        M[0][1] * MATRDeterm3x3(M[1][0], M[1][2], M[1][3],
          M[2][0], M[2][2], M[2][3],
          M[3][0], M[3][2], M[3][3]) +
        M[0][2] * MATRDeterm3x3(M[1][0], M[1][1], M[1][3],
          M[2][0], M[2][1], M[2][3],
          M[3][0], M[3][1], M[3][3]) -
        M[0][3] * MATRDeterm3x3(M[1][0], M[1][1], M[1][2],
          M[2][0], M[2][1], M[2][2],
          M[3][0], M[3][1], M[3][2]);
    } /* End of 'Determ' function */

    /* Evaluate inverse Matrix function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvaluateInverseMATRix( VOID )
    {
      if (IsInverseObtain)
        return;

      IsInverseObtain = TRUE;
      Type det = Determ();

      if (det == 0)
      {
        memcpy(InverseM, MATR<Type>::Identity().M, sizeof(InverseM));
        return;
      }

      /* Build adjoINT Matrix */
      InverseM[0][0] =
        MATRDeterm3x3(M[1][1], M[1][2], M[1][3],
          M[2][1], M[2][2], M[2][3],
          M[3][1], M[3][2], M[3][3]) / det;
      InverseM[1][0] =
        -MATRDeterm3x3(M[1][0], M[1][2], M[1][3],
          M[2][0], M[2][2], M[2][3],
          M[3][0], M[3][2], M[3][3]) / det;
      InverseM[2][0] =
        MATRDeterm3x3(M[1][0], M[1][1], M[1][3],
          M[2][0], M[2][1], M[2][3],
          M[3][0], M[3][1], M[3][3]) / det;
      InverseM[3][0] =
        -MATRDeterm3x3(M[1][0], M[1][1], M[1][2],
          M[2][0], M[2][1], M[2][2],
          M[3][0], M[3][1], M[3][2]) / det;

      InverseM[0][1] =
        -MATRDeterm3x3(M[0][1], M[0][2], M[0][3],
          M[2][1], M[2][2], M[2][3],
          M[3][1], M[3][2], M[3][3]) / det;
      InverseM[1][1] =
        MATRDeterm3x3(M[0][0], M[0][2], M[0][3],
          M[2][0], M[2][2], M[2][3],
          M[3][0], M[3][2], M[3][3]) / det;
      InverseM[2][1] =
        -MATRDeterm3x3(M[0][0], M[0][1], M[0][3],
          M[2][0], M[2][1], M[2][3],
          M[3][0], M[3][1], M[3][3]) / det;
      InverseM[3][1] =
        MATRDeterm3x3(M[0][0], M[0][1], M[0][2],
          M[2][0], M[2][1], M[2][2],
          M[3][0], M[3][1], M[3][2]) / det;

      InverseM[0][2] =
        MATRDeterm3x3(M[0][1], M[0][2], M[0][3],
          M[1][1], M[1][2], M[1][3],
          M[3][1], M[3][2], M[3][3]) / det;
      InverseM[1][2] =
        -MATRDeterm3x3(M[0][0], M[0][2], M[0][3],
          M[1][0], M[1][2], M[1][3],
          M[3][0], M[3][2], M[3][3]) / det;
      InverseM[2][2] =
        MATRDeterm3x3(M[0][0], M[0][1], M[0][3],
          M[1][0], M[1][1], M[1][3],
          M[3][0], M[3][1], M[3][3]) / det;
      InverseM[3][2] =
        -MATRDeterm3x3(M[0][0], M[0][1], M[0][2],
          M[1][0], M[1][1], M[1][2],
          M[3][0], M[3][1], M[3][2]) / det;

      InverseM[0][3] =       
        -MATRDeterm3x3(M[0][1], M[0][2], M[0][3],
          M[1][1], M[1][2], M[1][3],
          M[2][1], M[2][2], M[2][3]) / det;

      InverseM[1][3] =
        MATRDeterm3x3(M[0][0], M[0][2], M[0][3],
          M[1][0], M[1][2], M[1][3],
          M[2][0], M[2][2], M[2][3]) / det;
      InverseM[2][3] =
        -MATRDeterm3x3(M[0][0], M[0][1], M[0][3],
          M[1][0], M[1][1], M[1][3],
          M[2][0], M[2][1], M[2][3]) / det;
      InverseM[3][3] =
        MATRDeterm3x3(M[0][0], M[0][1], M[0][2],
          M[1][0], M[1][1], M[1][2],
          M[2][0], M[2][1], M[2][2]) / det;
    } /* End of 'EvaluateInverseMATRix' function */

  public:
    /* Class default constructor.
     */
    MATR( VOID ) : IsInverseObtain(FALSE)
    {
    } /* End of 'MATR' function */

    /* Matrix constructor 
     * ARGUMENTS:
     *   - Type a
     */
    explicit MATR( Type a ) : IsInverseObtain(FALSE)
    {
      for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
          M[i][j] = a;
    } /* End of 'MATR' function */

    /* Matrix constructor.
     * ARGUMENTS:
     *   - Matrix 4x4 values:
     *       type
     *         A00, A01, A02, A03,
     *         A10, A11, A12, A13,
     *         A20, A21, A22, A23,
     *         A30, A31, A32, A33;
     */
    MATR( Type A00, Type A01, Type A02, Type A03,
      Type A10, Type A11, Type A12, Type A13,
      Type A20, Type A21, Type A22, Type A23,
      Type A30, Type A31, Type A32, Type A33) : IsInverseObtain(FALSE)
    {
      M[0][0] = A00, M[0][1] = A01, M[0][2] = A02, M[0][3] = A03,
        M[1][0] = A10, M[1][1] = A11, M[1][2] = A12, M[1][3] = A13,
        M[2][0] = A20, M[2][1] = A21, M[2][2] = A22, M[2][3] = A23,
        M[3][0] = A30, M[3][1] = A31, M[3][2] = A32, M[3][3] = A33;
    } /* End of 'MATR' function */

    /* Obtain inverse Matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MATR) result Matrix.
     */
    MATR Inverse( VOID )
    {
      EvaluateInverseMATRix();
      return MATR(InverseM[0][0], InverseM[0][1], InverseM[0][2], InverseM[0][3],
        InverseM[1][0], InverseM[1][1], InverseM[1][2], InverseM[1][3], 
        InverseM[2][0], InverseM[2][1], InverseM[2][2], InverseM[2][3],
        InverseM[3][0], InverseM[3][1], InverseM[3][2], InverseM[3][3]);
    } /* End of 'Inverse' function */

    /* Obtain transpose Matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MATR) result Matrix.
     */
    static MATR Transpose( VOID )
    {
      return MATR(M[0][0], M[1][0], M[2][0], M[3][0],
        M[0][1], M[1][1], M[2][1], M[3][1],  
        M[0][0], M[1][0], M[2][0], M[3][0],
        M[0][1], M[1][1], M[2][1], M[3][1]);
    } /* End of 'Transpose' function*/

    /* Set identity transformation Matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (MATR) result Matrix.
     */
    static MATR Identity( VOID )
    {
      return MATR(1, 0, 0, 0,
        0, 1, 0, 0, 
        0, 0, 1, 0,
        0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Get pointer to Matrix element operator
     * ARGUMENTS: 
     *   - element number:
     *       INT N;
     * RETURNS:
     *   (FLT *) pointer to Matrix element.
     */
    FLT * operator[]( INT N )
    {
      if (N < 0)
        N = 0;
      else if (N > 15)
        N = 15;
      return (*(M + N / 4) + N % 4);
    } /* End of 'operator[]' function */

    /* Multiplication of two Matrix function.
     * ARGUMENTS:
     *   - Matrix to be multiply:
     *       const MATR<type> &A;
     * RETURNS:
     *   (MATR) result Matrix.
     */
    MATR operator*( const MATR<Type> &A ) const
    {
      MATR<Type> r;

      return MATR(M[0][0] * A.M[0][0] + M[0][1] * A.M[1][0] + M[0][2] * A.M[2][0] + M[0][3] * A.M[3][0],
        M[0][0] * A.M[0][1] + M[0][1] * A.M[1][1] + M[0][2] * A.M[2][1] + M[0][3] * A.M[3][1],
        M[0][0] * A.M[0][2] + M[0][1] * A.M[1][2] + M[0][2] * A.M[2][2] + M[0][3] * A.M[3][2],
        M[0][0] * A.M[0][3] + M[0][1] * A.M[1][3] + M[0][2] * A.M[2][3] + M[0][3] * A.M[3][3],

        M[1][0] * A.M[0][0] + M[1][1] * A.M[1][0] + M[1][2] * A.M[2][0] + M[1][3] * A.M[3][0],
        M[1][0] * A.M[0][1] + M[1][1] * A.M[1][1] + M[1][2] * A.M[2][1] + M[1][3] * A.M[3][1],
        M[1][0] * A.M[0][2] + M[1][1] * A.M[1][2] + M[1][2] * A.M[2][2] + M[1][3] * A.M[3][2],
        M[1][0] * A.M[0][3] + M[1][1] * A.M[1][3] + M[1][2] * A.M[2][3] + M[1][3] * A.M[3][3],

        M[2][0] * A.M[0][0] + M[2][1] * A.M[1][0] + M[2][2] * A.M[2][0] + M[2][3] * A.M[3][0],
        M[2][0] * A.M[0][1] + M[2][1] * A.M[1][1] + M[2][2] * A.M[2][1] + M[2][3] * A.M[3][1],
        M[2][0] * A.M[0][2] + M[2][1] * A.M[1][2] + M[2][2] * A.M[2][2] + M[2][3] * A.M[3][2],
        M[2][0] * A.M[0][3] + M[2][1] * A.M[1][3] + M[2][2] * A.M[2][3] + M[2][3] * A.M[3][3],

        M[3][0] * A.M[0][0] + M[3][1] * A.M[1][0] + M[3][2] * A.M[2][0] + M[3][3] * A.M[3][0],
        M[3][0] * A.M[0][1] + M[3][1] * A.M[1][1] + M[3][2] * A.M[2][1] + M[3][3] * A.M[3][1],
        M[3][0] * A.M[0][2] + M[3][1] * A.M[1][2] + M[3][2] * A.M[2][2] + M[3][3] * A.M[3][2],
        M[3][0] * A.M[0][3] + M[3][1] * A.M[1][3] + M[3][2] * A.M[2][3] + M[3][3] * A.M[3][3]);
    } /* End of 'operator*' function */

    /* Multiplication with assignment of two Matrix function.
     * ARGUMENTS:
     *   - Matrix to be multiply:
     *       const MATR<type> &A;
     * RETURNS:
     *  (MATR &) self reference.
     */
    MATR operator*=( const MATR &A ) const
    {
      MATR r;

      r.M[0][0] = M[0][0] * A.M[0][0] + M[0][1] * A.M[1][0] + M[0][2] * A.M[2][0] + M[0][3] * A.M[3][0];
      r.M[0][1] = M[0][0] * A.M[0][1] + M[0][1] * A.M[1][1] + M[0][2] * A.M[2][1] + M[0][3] * A.M[3][1];
      r.M[0][2] = M[0][0] * A.M[0][2] + M[0][1] * A.M[1][2] + M[0][2] * A.M[2][2] + M[0][3] * A.M[3][2];
      r.M[0][3] = M[0][0] * A.M[0][3] + M[0][1] * A.M[1][3] + M[0][2] * A.M[2][3] + M[0][3] * A.M[3][3];

      r.M[1][0] = M[1][0] * A.M[0][0] + M[1][1] * A.M[1][0] + M[1][2] * A.M[2][0] + M[1][3] * A.M[3][0];
      r.M[1][1] = M[1][0] * A.M[0][1] + M[1][1] * A.M[1][1] + M[1][2] * A.M[2][1] + M[1][3] * A.M[3][1];
      r.M[1][2] = M[1][0] * A.M[0][2] + M[1][1] * A.M[1][2] + M[1][2] * A.M[2][2] + M[1][3] * A.M[3][2];
      r.M[1][3] = M[1][0] * A.M[0][3] + M[1][1] * A.M[1][3] + M[1][2] * A.M[2][3] + M[1][3] * A.M[3][3];

      r.M[2][0] = M[2][0] * A.M[0][0] + M[2][1] * A.M[1][0] + M[2][2] * A.M[2][0] + M[2][3] * A.M[3][0];
      r.M[2][1] = M[2][0] * A.M[0][1] + M[2][1] * A.M[1][1] + M[2][2] * A.M[2][1] + M[2][3] * A.M[3][1];
      r.M[2][2] = M[2][0] * A.M[0][2] + M[2][1] * A.M[1][2] + M[2][2] * A.M[2][2] + M[2][3] * A.M[3][2];
      r.M[2][3] = M[2][0] * A.M[0][3] + M[2][1] * A.M[1][3] + M[2][2] * A.M[2][3] + M[2][3] * A.M[3][3];

      r.M[3][0] = M[3][0] * A.M[0][0] + M[3][1] * A.M[1][0] + M[3][2] * A.M[2][0] + M[3][3] * A.M[3][0];
      r.M[3][1] = M[3][0] * A.M[0][1] + M[3][1] * A.M[1][1] + M[3][2] * A.M[2][1] + M[3][3] * A.M[3][1];
      r.M[3][2] = M[3][0] * A.M[0][2] + M[3][1] * A.M[1][2] + M[3][2] * A.M[2][2] + M[3][3] * A.M[3][2];
      r.M[3][3] = M[3][0] * A.M[0][3] + M[3][1] * A.M[1][3] + M[3][2] * A.M[2][3] + M[3][3] * A.M[3][3];

      *this = r;
      IsInverseObtain = FALSE;
      return *this;
    } /* End of 'operator*=' function */

    /* Obtain translation Matrix function.
     * ARGUMENTS:
     *   - VECtor delta value:
     *       const VEC<type> &D;
     * RETURNS:
     *   (MATR) translate transforMATRion Matrix.
     */
    static MATR Translate( const VEC<Type> &D)
    {
      return MATR(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        D.X, D.Y, D.Z, 1);
    } /* End of 'Translate' function */

    /* Obtain translation Matrix function.
     * ARGUMENTS:
     *   - coordinates delta values:
     *       type X, Y, Z;
     * RETURNS:
     *   (MATR) translate transforMATRion Matrix.
     */
    static MATR Translate( Type X, Type Y, Type Z)
    {
      return MATR(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        X, Y, Z, 1);
    } /* End of 'Translate' function */

    /* Obtain scale Matrix function.
     * ARGUMENTS:
     *   - coordinates scale values:
     *       type Sx, Sy, Sz;
     * RETURNS:
     *   (MATR) scale transforMATRion Matrix.
     */
    static MATR<Type> Scale( Type Sx, Type Sy, Type Sz)
    {
      return MATR<Type>(Sx, 0, 0, 0,
                        0, Sy, 0, 0, 
                        0, 0, Sz, 0,
                        0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Obtain scale Matrix function.
     * ARGUMENTS:
     *   - VECtor delta value:
     *       const VEC<type> &D;
     * RETURNS:
     *   (MATR) scale transforMATRion Matrix.
     */
    static MATR<Type> Scale( const VEC<Type> &V )
    {
      return MATR<Type>(V.X, 0, 0, 0,
                        0, V.Y, 0, 0,
                        0, 0, V.Z, 0,
                        0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Vector mul matrix function.
     *  ARGUMENTS:
     *   - vector:
     *       VEC<Type> V;
     *  RETURNS:
     *   (VEC<Type) result of operation;
     */
    VEC<Type> operator*( VEC<Type> V )
    {
      Type w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];
      VEC<Type> VecMatr;

      VecMatr.X = (V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w;
      VecMatr.Y = (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w;
      VecMatr.Z = (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w;

      return VecMatr;
    } /* End of 'operator*' function */

    /* Start of 'MatrRotateX' function
     *  ARGUMENTS:
     *    - FLOAT:
     *    FLT AngleInDegree
     *  RETURNS:
     *    - Matr:
     *    Matrix rotating by X
     */
    static MATR RotateX( Type AngleInDegree )
    {
      MATR MatrRotateX = Identity();
      Type Angle = D2R<Type>(AngleInDegree);
      Type SI = sin(Angle), CO = cos(Angle);
      MatrRotateX.M[1][1] = CO;
      MatrRotateX.M[1][2] = SI;
      MatrRotateX.M[2][1] = -SI;
      MatrRotateX.M[2][2] = CO;

      return MatrRotateX;
    } /* End of 'MatrRotateX' function */

    /* Start of 'MatrRotateY' function
     *  ARGUMENTS:
     *    - Type:
     *    Type AngleInDegree
     *  RETURNS:
     *    - Matr:
     *    Matrix rotating by Y
     */
    static MATR RotateY( Type AngleInDegree )
    {
      MATR MatrRotateY = Identity();
      Type Angle = D2R<Type>(AngleInDegree);
      Type SI = sin(Angle), CO = cos(Angle);
      MatrRotateY.M[0][0] = CO;
      MatrRotateY.M[0][2] = -SI;
      MatrRotateY.M[2][0] = SI;
      MatrRotateY.M[2][2] = CO;
      return MatrRotateY;
    } /* End of 'MatrRotateY' function */

    /* Start of 'MatrRotateZ' function
     *  ARGUMENTS:
     *    - Type:
     *    Type AngleInDegree
     *  RETURNS:
     *    - Matr:
     *    Matrix rotating by Z
     */
    static MATR RotateZ(Type AngleInDegree )
    {
      MATR MatrRotateZ = Identity();
      Type Angle = D2R<Type>(AngleInDegree);
      Type SI = sin(Angle), CO = cos(Angle);
      MatrRotateZ.M[0][0] = CO;
      MatrRotateZ.M[1][0] = -SI;
      MatrRotateZ.M[0][1] = SI;
      MatrRotateZ.M[1][1] = CO;

      return MatrRotateZ;
    } /* End of 'MatrRotateZ' function */

    /* Obtain rotation around arbitrary radius-VECtor transformation Matrix function.
     * ARGUMENTS:
     *   - rotation ange in degrees:
     *       type AngleInDegree;
     *   - VECtor rotate around:
     *       const VEC<type> &Axis;
     * RETURNS:
     *   (MATR) result Matrix.
     */
    static MATR Rotate( Type AngleInDegree, VEC<Type> R )
    {
      Type A = D2R(AngleInDegree), si = sin(A), co = cos(A);
      VEC<Type> V = R.Normalizing();    
      return MATR(co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0,
        V.Y * V.X * (1 - co) - V.Z * si,co + V.Y * V.Y * (1 - co),V.Y * V.Z * (1 - co) + V.X * si, 0,
        V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0,
        0, 0, 0, 1);
    } /* End of 'MATRRotate' function */

    /* Obtain view Matrix (by location, look-at and up VECtors) function.
     * ARGUMENTS:
     *   - view camera location:
     *       const VEC<type> &Loc;
     *   - look-at poINT:
     *       const VEC<type> &LookAt;
     *   - approximate up direction:
     *       const VEC<type> &Up1;
     * RETURNS:
     *   (MATR) view transforMATRion Matrix.
     */
    static MATR View( VEC<Type> Loc, VEC<Type> At, VEC<Type> Up1 )
    {
      VEC<Type>
        Dir = (At - Loc).Normalizing(),
        Right = (Dir % Up1).Normalizing(),
        Up = Right % Dir;

      return MATR(Right.X, Up.X, -Dir.X, 0,
        Right.Y, Up.Y, -Dir.Y, 0,
        Right.Z, Up.Z, -Dir.Z, 0,
        -(Loc & Right), -(Loc & Up), (Loc & Dir), 1); 
    } /* End of 'View' function */

    /* Obtain perspective projection Matrix function.
     * ARGUMENTS:
     *   - 3D frustum bound coordinates:
     *       type Left, Right, Bottom, Top, Near, Far;
     * RETURNS:
     *   (MATR) perspective projection transforMATRion Matrix.
     */
    static MATR Frustum( Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far )
    {
      return MATR(2 * Near / (Right - Left), 0, 0, 0,
        0, 2 * Near / (Top - Bottom), 0, 0,
        (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), -1,
        0, 0, -2 * Near * Far / (Far - Near),  0);
    } /* End of 'Frustum' function */

    static MATR Ortho( Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far )
    {
      return MATR(2.0 / (Right - Left), 0, 0, 0,
        0, 2.0 / (Top - Bottom), 0, 0,
        0, 0, -2.0 / (Far - Near), 0,
        -((Right + Left) / (Right - Left)), -((Top + Bottom) / (Top - Bottom)), -((Far + Near) / (Far - Near)), 1);
    } /* End of 'Ortho' function */

    /* Transformation normal VECtor by Matrix function.
     * ARGUMENTS:
     *   - VECtor to be tranform:
     *       const VEC<type> &V;
     * RETURNS:
     *   (VEC) transformed VECtor.
     */
    VEC<Type> TransformNormal( VEC<Type> &V )
    {
      EvaluateInverseMATRix();
      return VEC<Type>(V.X * InverseM[0][0] + V.Y * InverseM[0][1] + V.Z * InverseM[0][2],
        V.X * InverseM[1][0] + V.Y * InverseM[1][1] + V.Z * InverseM[1][2],
        V.X * InverseM[2][0] + V.Y * InverseM[2][1] + V.Z * InverseM[2][2]);
    } /* End of 'TransformNormal' function */

    /* Transformation VECtor by Matrix function.
     * ARGUMENTS:
     *   - VECtor to be tranform:
     *       const VEC<type> &V;
     * RETURNS:
     *   (VEC) transformed VECtor.
     */
    VEC<Type> TransformVector( const VEC<Type> &V ) const
    {
      return VEC<Type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
        V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
        V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
    } /* End of 'TransformVECtor' function */

    /* Transformation poINT by Matrix function.
     * ARGUMENTS:
     *   - VECtor to be tranform:
     *       const VEC<type> &V;
     * RETURNS:
     *   (VEC) transformed VECtor.
     */
    VEC<Type> TransformPoint( const VEC<Type> &V ) const
    {
      Type w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];

      return VEC<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w,
        (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w,
        (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w);
    } /* End of 'TransformPoint' function */
  }; /* End of 'MATR' class */
} /* End of 'mth' namespace */

#endif /* __MATR_H_ */

/* END OF 'MATR.H' FILE */