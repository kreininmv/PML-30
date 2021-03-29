/* FILE NAME   : LIGHT.H
 * PURPOSE     : Lights module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 27.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#include "..//..//DEF.H"
#include "..//IMAGE/IMAGE.H"

#ifndef  __LIGHT_H_
#define  __LIGHT_H_

namespace mert
{
  class light
  {
  public:
    DBL Cc = 1, Cl = 1, Cq = 1;  // Light coefitients
    vec Color = vec(1, 1, 1);          // Light color

    /* Get direction of light function.
     * ARGUMENTS:
     *   - point to direction from light:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    virtual vec GetL( const vec &P )
    {
      return vec(0);
    } /* End of 'GetL' function */

    /* Get distance of light function.
     * ARGUMENTS:
     *   - point to get distance from:
     *       vec P;
     * RETURNS:
     *   (DBL) distance to light;
     */
    virtual DBL GetDist( const vec &P )
    {
      return 1;
    }
  }; /* End of 'light' class */

  class point_light : public light
  {
  public:
    vec Loc; // Light location

    /* point_light constructor function
     * ARGUMENTS:
     *   - location:
     *       vec L;
     * RETURNS: None.
     */
    point_light( const vec &L ) : Loc(L)
    {
    } /* End of 'point_light' constructor */

    /* point_light constructor function
     * ARGUMENTS:
     *   - location:
     *       vec L;
     *   - color:
     *       vec C;
     *   - light coefs:
     *       DBL CC, CL, CQ;
     * RETURNS: None.
     */
    point_light( const vec &L, const vec &C, const DBL CC, const DBL CL, const DBL CQ ) : Loc(L)
    {
      Color = C;
      Cc = CC;
      Cl = CL;
      Cq = CQ;
    } /* End of 'point_light' constructor */

    /* Get direction to light function
     * ARGUMENTS:
     *   - point to get direction from:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    vec GetL( const vec &P ) override
    {
      return (Loc - P).Normalize();
    } /* End of 'GetL' function */

    /* Get distance to light function
     * ARGUMENTS:
     *   - point to get distance from:
     *       vec P;
     * RETURNS:
     *   (DBL) distance to light;
     */
    DBL GetDist( const vec &P ) override
    {
      return Loc.Distance(P);
    } /* End of 'GetDist' function */

  }; /* End of 'point_light' class */

  class dir_light : public light
  {
  public:
    vec Dir; // Light direction

    /* dir_light constructor function
     * ARGUMENTS:
     *   - direction:
     *       vec D;
     * RETURNS: None.
     */
    dir_light( const vec &D ) : Dir(D)
    {

    } /* End of 'dir_light' constructor */

    /* dir_light constructor function
     * ARGUMENTS:
     *   - direction:
     *       vec D;
     *   - color:
     *       vec C;
     *   - light coefs:
     *       DBL CC, CL, CQ;
     * RETURNS: None.
     */
    dir_light( const vec &D, const vec &C, const DBL CC, const DBL CL, const DBL CQ ) : Dir(D)
    {
      Color = C;
      Cc = CC;
      Cl = CL;
      Cq = CQ;
    } /* End of 'dir_light' constructor */

    /* Get direction to light function
     * ARGUMENTS:
     *   - point to get direction from:
     *       vec P;
     * RETURNS:
     *   (vec) direction to light;
     */
    vec GetL( const vec &P ) override
    {
      return -(Dir.Normalize());
    } /* End of 'GetL' function */
  }; /* End of 'dir_light' class */

} /* End of 'mert' function */

#endif /* __LIGHT_H_ */
/* END OF 'LIGHT.H' FILE */