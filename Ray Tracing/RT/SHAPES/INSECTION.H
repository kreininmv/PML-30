/* FILE NAME   : INSECTION.H
 * PURPOSE     : Ray tracing system.
 *               Plane shape class.
 * PROGRAMMER  : MK5.
 * LAST UPDATE : 27.07.2018.
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __INTER_H_
#define __INTER_H_

#include <vector>

#include "..//..//DEF.H"
#include "SHAPE.H"

namespace mert
{
  class shape;
  class intr
  {
  public:
    shape *Shp;   // Shape reference
    DBL T;        // Intersect distance
    BOOL IsEnter; // Is ray starts inside
    vec N;        // Normal at intersected point
    BOOL IsN;     // Is normal calculataed
    vec P;        // Intersected point
    BOOL IsP;     // Is point calculated

    /* intr constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    intr( VOID ) : Shp()
    {
    } /* End of 'intr' constructor */

    /* Intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter = FALSE) : Shp(Sh), T(T), IsEnter(IsEnter)
    {
    } /* End of 'intr' constructor */

    /* Intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N ) : Shp(Sh), T(T), IsEnter(IsEnter), N(N)
    {

    } /* End of 'intr' constructor */

    /* Intr constructor function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     *   - intersection point:
     *       vec P;
     * RETURNS: None.
     */
    intr( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N, const vec &P ) : Shp(Sh), T(T), IsEnter(IsEnter), N(N), P(P)
    {

    } /* End of 'intr' constructor */

    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter = FALSE )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
    } /* End of 'Set' function */

    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
      this->N = N;
    } /* End of 'Set' function */

    /* Set intersection function.
     * ARGUMENTS:
     *   - shape reference:
     *       shape *Shp;
     *   - intersection distance:
     *       DBL T;
     *   - was ray inside shape:
     *       BOOL IsEnter;
     *   - normal at intersection point:
     *       vec N;
     *   - intersection point:
     *       vec P;
     * RETURNS: None.
     */
    VOID Set( shape *Sh, const DBL T, const BOOL IsEnter, const vec &N, const vec &P )
    {
      Shp = Sh;
      this->T = T;
      this->IsEnter = IsEnter;
      this->N = N;
      this->P = P;
    } /* End of 'Set' function */

  }; /* End of 'intr' class */

  typedef std::vector<intr> intr_list;
} /* end of 'mert' namespace */

#endif // __INTER_H_

/* END OF 'INSECTION.H' FILE */