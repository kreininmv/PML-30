/* FILE NAME   : MTHDEF.H
 * PURPOSE     : Mathematics definition.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mth'.
 */

#ifndef __MTHDEF_H_
#define __MTHDEF_H_

#include <windows.h>

/* Common float point types */
typedef DOUBLE DBL;
typedef FLOAT FLT;
typedef long double LDBL;

/* Math library namespace */
namespace mth
{
  /* Angle transform constants */
  const LDBL PI = 3.14159265358979323846L;

  /* Maximum big number */
  const LDBL Infinity = 99999999999999;

  /* Multiplier for degree to radian conversions */
  const LDBL MultiplierDegree2Radian = 0.01745329251994329576L;

  /* Convertion from degrees to radians function.
   * ARGUMENTS:
   *   - angle value in degrees:
   *       type AngleInDegree;
   * RETURNS:
   *   (type) converted value in radians.
   */
  template<class type>
  type D2R( type AngleInDegrees )
  {
    return AngleInDegrees * PI / 180.0;
  } /* End of 'D2R' function */

  /* Convertion from radians to degrees function.
   * ARGUMENTS:
   *   - angle value in radians:
   *       type AngleInRadians;
   * RETURNS:
   *   (type) converted value in degrees.
   */
  template<class type>
  type R2D( type AngleInRadians )
  {
    return AngleInDegree * 180.0 / PI;
  } /* End of 'R2D' function */

  /* Get minimum value function.
   * ARGUMENTS:
   *   - compared values:
   *       const type A, B;
   * RETURNS:
   *   (type ) result of comparision.
   */
  template<class type>
  type Min( const type A, const type B )
  {
    return A < B ? A : B;
  } /* End of 'Min' function */

  /* Get maximum value function.
   * ARGUMENTS:
   *   - compared values:
   *       const type A, B;
   * RETURNS:
   *   (type) result of comparision.
   */
  template<class type>
  type Max( const type A, const type B )
  {
    return A > B ? A : B;
  } /* End of 'Max' function */
} /* End of 'mth' namespace */

#endif /* __MTHDEF_H_ */

/* END OF 'MTHDEF.H' FILE */