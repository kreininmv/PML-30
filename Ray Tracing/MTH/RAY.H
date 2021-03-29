/* FILE NAME   : RAY.H
 * PURPOSE     : Rays.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mth'.
 */

#ifndef __RAY_H_
#define __RAY_H_

#include "VEC.h"

 /* Math library namespace */
namespace mth
{
  /* Space transformation Matrix handle class */
  template <typename Type = double>
  class RAY
  {
  public:
    VEC<Type> Org,  /* Position of start ray */
              Dir;  /* Direction of ray */

                    /* Default class constructor */
    RAY( VOID ) : Org(0), Dir(0)
    {
    } /* End of 'RAY' constructor */

    /* Ray constructor.
     * ARGUMENTS:
     *   - new origin:
     *       const vec &NewOrg;
     *   - new direction:
     *       const vec &NewDir;
     * RETURNS: None.
     */
    RAY( const VEC<Type> &NewOrg, const VEC<Type> &NewDir ) : Org(NewOrg), Dir(NewDir)
    {
    } /* End of 'RAY' constructor */

    /* Default class destructor */
    ~RAY( VOID )
    {
    } /* End of 'RAY' destructor */
    
    /* Get point in ray function.
     * ARGUMENTS:
     *   - distance from origin:
     *       Type t;
     * RETURNS:
     *   (vec) point on ray.
     */
    VEC<Type> operator()(Type t) const
    {
      return Org + Dir * t;
    } /* End of 'operator()' function */

  }; /* End of 'RAY' class */
} /* End of 'mert' namespace*/

#endif /* __RAY_H_ */
/* END OF 'RAY.H' FILE */
