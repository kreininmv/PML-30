/* FILE NAME   : MATERIAL.H
 * PURPOSE     : Material module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 27.07.2018
 * NOTE        : Module namespace 'mert'.
 */
  
#include "..//..//DEF.H"
#include "..//IMAGE/IMAGE.H"

#ifndef  __MATERIAL_H_
#define  __MATERIAL_H_

namespace mert
{
  class material
  {
  public:
    vec 
      Ka,   // Ambient
      Kd,   // Diffuse
      Ks;   // Specular
    DBL Ph; // Phong
  
    /* Material constructor function.
     * ARGUMENTS:
     *   - material coefitients:
     *       vec Ka, Kd, Ks;
     *   - phong coefitient:
     *       DBL Ph;
     * RETURNS: None.
     */
    material( const vec &Ka, const vec &Kd, const vec &Ks, const DBL Ph ) : Ka(Ka), Kd(Kd), Ks(Ks), Ph(Ph)
    {
    } /* End of 'material' constructor function */
  }; /* End of 'material' class */
} /* End of 'mert' namespace */

#endif /* __MATERIAL_H_ */

/* END OF 'MATERIAL.H' FILE */