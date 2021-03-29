/* FILE NAME   : BOX.H
 * PURPOSE     : Class of box.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __BOX_H_
#define __BOX_H_

#include "..//..//DEF.H"
#include "SHAPE.H"

namespace mert
{
  class box : public shape 
  {
  public:
    vec BB1, BB2; // points wich defines box

    /* sphere constructor function.
     * ARGUMENTS:
     *   - sphrere center:
     *       vec Center;
     *   - sphere radius:
     *       DBL Radius;
     * RETURNS: None.
     */
    box(const vec &V1, const vec &V2)
    {
      BB1 = vec::Min(V1, V2);
      BB2 = vec::Max(V1, V2);
    } /* End of 'sphere' constructor */
    
    /* Shape intersect function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersection distance:
     *       intr Inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection is succesful, FALSE otherwise.
     */
    BOOL Intersect(const ray &Ray, intr &Inter) const override
    {
      DBL tnear = -mth::Infinity, tfar = mth::Infinity;
      vec Norms[3]{ vec(1, 0, 0), vec(0, 1, 0), vec(0, 0, 1) };
      INT ind = 0;
    
      for (INT i = 0; i < 3; i++)
      {
        DBL tn, tf;
      
        if (Ray.Dir[i] == 0)
        {
          if (Ray.Dir[i] < BB1[i] || Ray.Dir[i] > BB2[i])
        	  return FALSE;
        }
        else
        {
          tn = (BB1[i] - Ray.Org[i]) / Ray.Dir[i];
          tf = (BB2[i] - Ray.Org[i]) / Ray.Dir[i];
        
          if (tn > tf)
            mth::Swap(tn, tf);
        
          if (tf < 0)
            return FALSE;
        
          if (tnear < tn)
          {
            tnear = mth::Max(tnear, tn);
            ind = i;
          }
          if (tfar > tf)
          {
            tfar = mth::Min(tfar, tf);
            ind = i;
          }
          if (tnear > tfar)
            return FALSE;
        }
      }
    
      Inter.IsN = TRUE;
      Inter.T = tnear;
      Inter.P = Ray(Inter.T);
      Inter.N = mth::VEC<DBL>::GetN((Inter.P - vec((BB1[0] + BB2[0]) / 2, (BB1[1] + BB2[1]) / 2, (BB1[2] + BB2[2]) / 2)));//Norms[ind] * -mth::Sign(Norms[ind] & Ray.Dir);
      Inter.Shp = (shape *)this;
      Inter.IsP = TRUE;
      Inter.IsEnter = TRUE;
      return TRUE;
    } /* End of 'Intersect' function */
    
    /* Evaluate all intersections function.
    * ARGUMENTS:
    *   - ray to intersect:
    *       ray Ray;
    *   - intersections list:
    *       intr_list InterList;
    * RETURNS:
    *   (INT) amount of intersections.
    */
    INT AllIntersect(const ray &Ray, intr_list &InterList) const
    {
      DBL tnear = -mth::Infinity, tfar = mth::Infinity;
      vec Norms[3]{ vec(1, 0, 0), vec(0, 1, 0), vec(0, 0, 1) };
      INT ind = 0;
    
      for (INT i = 0; i < 3; i++)
      {
        DBL tn, tf;
    
        if (Ray.Dir[i] == 0)
        {
          if (Ray.Dir[i] < BB1[i] || Ray.Dir[i] > BB2[i])
            return 0;
        }
        else
        {
          tn = (BB1[i] - Ray.Org[i]) / Ray.Dir[i];
          tf = (BB2[i] - Ray.Org[i]) / Ray.Dir[i];
        
          if (tn > tf)
            mth::Swap(tn, tf);
        
          if (tf < 0)
            return 0;
        
          if (tnear < tn)
          {
            tnear = mth::Max(tnear, tn);
            ind = i;
          }
          if (tfar > tf)
          {
            tfar = mth::Min(tfar, tf);
            ind = i;
          }
        
          if (tnear > tfar)
            return 0;
        }
        ind = i;
      }
      intr Inter;
    
      Inter.IsN = TRUE;
      Inter.T = tfar;
      Inter.Shp = (shape *)this;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      Inter.IsEnter = FALSE;
      Inter.N = mth::VEC<DBL>::GetN((Inter.P - vec((BB1[0] + BB2[0]) / 2, (BB1[1] + BB2[1]) / 2, (BB1[2] + BB2[2]) / 2)));
      InterList.push_back(Inter);
    
      Inter.IsN = TRUE;
      Inter.T = tnear;
      Inter.Shp = (shape *)this;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      Inter.IsEnter = TRUE;
      Inter.N = mth::VEC<DBL>::GetN((Inter.P - vec((BB1[0] + BB2[0]) / 2, (BB1[1] + BB2[1]) / 2, (BB1[2] + BB2[2]) / 2)));
      InterList.push_back(Inter);
    
      return 2;
      } /* End of 'AllIntersect' function */

  }; /* End of 'box' class */
} /* End of 'mert' namespace */

#endif /* __BOX_H_ */
/* END OF 'BOX.H' FILE */