/* FILENAME    : QUAD.H
 * PURPOSE     : Ray Tracing Module.
 *               Shape Support.
 * PROGRAMMER  : MK5.
 * LAST UPDATE : 18.07.2018
 * NOTE        : module namespace 'mert'.
 */

#ifndef __QUAD_H_
#define __QUAD_H_

#include "shape.h"

/* namespace mert */
namespace mert
{
  /* class 'shape_quad' */
  class shape_quad : public shape
  {
  public:
    DBL A, B, C, D, E, F, G, H, I, J;  // coefficients

    /* Constructor of class 'shape_quad'.
     * ARGUMENTS:
     *   - material
     *       material &Mat;
     *   - enviroment information:
     *       enviroment &Envirem;
     *   - coefficients:
     *       DBL A, B, C, D, E, F, G, H, I, J;
     */
    shape_quad( const material &Mat, const enviroment &Envirem, const DBL NewA,
      const DBL NewB, const DBL NewC, const DBL NewD, const DBL NewE, const DBL NewF,
      const DBL NewG, const DBL NewH, const DBL NewI, const DBL NewJ ) : 
      A(NewA), B(NewB), C(NewC), D(NewD), E(NewE),
      F(NewF), G(NewG), H(NewH), I(NewI), J(NewJ)
    {
      Mtl = Mat;
      Envi = Envirem;
    } /* End of constructor class 'shape_quad' */

    /* Find intersect function.
     * ARGUMENTS:
     *   - ray for intersect:
     *       ray &R;
     *   - intersect struct:
     *       intr *Inters;
     * RETURNS:
     *   (BOOL) TRUE if intersect, FALSE in otherwise.
     */
    BOOL Intersect( const ray &R, intr *Inters ) override
    {
      vec Dir = R.Dir;
      vec Org = R.Org;
      DBL a = A * Dir[0] * Dir[0] + 2 * B * Dir[0] * Dir[1] +
        2 * C * Dir[0] * Dir[2] + E * Dir[1] * Dir[1] +
        2 * F * Dir[1] * Dir[2] + H * Dir[2] * Dir[2];
      DBL b2 = A * Org[0] * Dir[0] +
        B * (Org[0] * Dir[1] + Dir[0] * Org[1]) +
        C * (Org[0] * Dir[2] + Dir[0] * Org[2]) +
        D * Dir[0] + E * Org[1] * Dir[1] +
        F * (Org[1] * Dir[2] + Dir[1] * Org[2]) +
        G * Dir[1] + H * Org[2] * Dir[2] + I * Dir[2];
      DBL c = A * Org[0] * Org[0] + 2 * B * Org[0] * Org[1] +
        2 * C * Org[0] * Org[2] + 
        2 * D * Org[0] + E * Org[1] * Org[1] +
        2 * F * Org[1] * Org[2] + 2 * G * Org[1] +
        H * Org[2] * Org[2] + 2 * I * Org[2] + J;

      DBL
        SqrtD4 = sqrt(b2 * b2 - a * c),
        t1 = (-b2 - SqrtD4) / a,
        t2 = (-b2 + SqrtD4) / a;
      if (t1 < Threshold)
        if (t2 < Threshold)
          return FALSE;
        else
        {
          Inters->IsEnter = FALSE;
          Inters->T = t2;
          Inters->Shp = this;
          return TRUE;
        }
      if (t2 < Threshold)
      {
        Inters->IsEnter = FALSE;
        Inters->T = t1;
        Inters->Shp = this;
        return TRUE;
      }
      if (t2 < t1)
      {
        Inters->IsEnter = TRUE;
        Inters->T = t2;
        Inters->Shp = this;
        return TRUE;
      }
      Inters->IsEnter = TRUE;
      Inters->T = t1;
      Inters->Shp = this;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Find all intersect function.
     * ARGUMENTS:
     *   - ray for intersect:
     *       ray &R;
     *   - intersect list:
     *       intr_list IL;
     * RETURNS:
     *   (INT) number of intersect.
     */
    INT AllIntersect( const ray &R, intr_list &IL ) override
    {
      vec Dir = R.Dir;
      vec Org = R.Org;
      DBL a = A * Dir[0] * Dir[0] + 2 * B * Dir[0] * Dir[1] +
        2 * C * Dir[0] * Dir[2] + E * Dir[1] * Dir[1] +
        2 * F * Dir[1] * Dir[2] + H * Dir[2] * Dir[2];
      DBL b2 = A * Org[0] * Dir[0] +
        B * (Org[0] * Dir[1] + Dir[0] * Org[1]) +
        C * (Org[0] * Dir[2] + Dir[0] * Org[2]) +
        D * Dir[0] + E * Org[1] * Dir[1] +
        F * (Org[1] * Dir[2] + Dir[1] * Org[2]) +
        G * Dir[1] + H * Org[2] * Dir[2] + I * Dir[2];
      DBL c = A * Org[0] * Org[0] + 2 * B * Org[0] * Org[1] +
        2 * C * Org[0] * Org[2] + 
        2 * D * Org[0] + E * Org[1] * Org[1] +
        2 * F * Org[1] * Org[2] + 2 * G * Org[1] +
        H * Org[2] * Org[2] + 2 * I * Org[2] + J;

      DBL
        SqrtD4 = sqrt(b2 * b2 - a * c),
        t1 = (-b2 - SqrtD4) / a,
        t2 = (-b2 + SqrtD4) / a;
      if (t1 < Threshold)
        if (t2 < Threshold)
          return 0;
        else
        {
          IL.push_back(intr(this, t2, FALSE));
          return 1;
        }
      if (t2 < Threshold)
      {
        IL.push_back(intr(this, t1, FALSE));
        return 1;
      }
      if (t2 < t1)
      {
        IL.push_back(intr(this, t2, TRUE));
        IL.push_back(intr(this, t1, FALSE));
      }
      else
      {
        IL.push_back(intr(this, t1, FALSE));
        IL.push_back(intr(this, t2, TRUE));
      }
      return 2;
    } /* End of 'AllIntersect' function */

    /* Fill normal field in intersect function.
     * ARGUMENTS:
     *   - intersect:
     *       intr *Inters;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Inters ) override
    {
      Inters->N =
        vec(2 * A * Inters->P[0] + 2 * B * Inters->P[1] +
            2 * C * Inters->P[2] + 2 * D,
            2 * B * Inters->P[0] + 2 * E * Inters->P[1] +
            2 * F * Inters->P[2] + 2 * G,
            2 * C * Inters->P[0] + 2 * F * Inters->P[1] +
            2 * H * Inters->P[2] + 2 * I).Normalize();
      Inters->IsN = TRUE;
    } /* End of 'GetNormal' function */

  }; /* End of class 'shape_quad' */

} /* end of namespace 'mert' */

#endif // __QUAD_H_

/* END OF 'QUAD.H' FILE */
