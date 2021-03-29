/****************************************************************
 * Copyright (C) 2018
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ****************************************************************/

/* FILE NAME   : SPHERE.H
 * PURPOSE     : Class sphere.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "..//..//DEF.H"
#include "SHAPE.H"

namespace mert
{
  class sphere : public shape
  {
  public:
    vec C;     // Sphere center
    DBL R, R2; // Sphere radius

    /* sphere constructor function.
     * ARGUMENTS:
     *   - sphrere center:
     *       vec Center;
     *   - sphere radius:
     *       DBL Radius;
     * RETURNS: None.
     */
    sphere(const vec &Center, const DBL Radius) : C(Center), R(Radius), R2(R * R)
    {

    } /* End of 'sphere' constructor */


    /* Sphere intersect function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersection:
     *       intr Inter;
     * RETURNS:
     *   (BOOL) TRUE if intersection is succesful, FALSE otherwise.
     */
    BOOL Intersect(const ray &Ray, intr &Inter) const override
    {
      vec a = C - Ray.Org;
      DBL
        OC2 = a & a,
        OK = a & Ray.Dir,
        OK2 = OK * OK,
        h2 = R2 - (OC2 - OK2);

      /* Ray starts inside sphere */
      if (OC2 < R2)
      {
        Inter.Shp = (shape *)this;
        Inter.T = OK + sqrt(h2);
        Inter.IsEnter = FALSE;
        Inter.P = Ray(Inter.T);
        Inter.N = (Inter.P - C).Normalize();
        Inter.IsP = TRUE;
        Inter.IsN = TRUE;
        return TRUE;
      }
      /* Sphere center is behind ray */
      if (OK < 0)
        return FALSE;
      /* Ray doesnt intersect sphere */
      if (h2 < 0)
        return FALSE;
      /* Ray starts outside sphere */
      Inter.Shp = (shape *)this;
      Inter.T = OK - sqrt(h2);
      Inter.IsEnter = TRUE;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      Inter.N = (Inter.P - C).Normalize();
      Inter.IsN = TRUE;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Evaluate all intersections function.
     * ARGUMENTS:
     *   - ray to intersect:
     *       ray Ray;
     *   - intersections:
     *       intr inter;
     * RETURNS:
     *   (INT) amount of intersections.
     */
    INT AllIntersect(const ray &Ray, intr_list &InterList) const override
    {
      vec a = C - Ray.Org;
      DBL
        OC2 = a & a,
        OK = a & Ray.Dir,
        OK2 = OK * OK,
        h2 = R2 - (OC2 - OK2);
      intr Inter;

      /* Ray starts inside sphere */
      if (OC2 < R2)
      {
        Inter.Shp = (shape *)this;
        Inter.T = OK + sqrt(h2);
        Inter.IsEnter = FALSE;
        Inter.P = Ray(Inter.T);
        Inter.N = (Inter.P - C).Normalize();
        Inter.IsP = TRUE;
        Inter.IsN = TRUE;
        InterList.push_back(Inter);
        return 1;
      }

      /* Sphere center is behind ray */
      if (OK < 0)
        return 0;
      /* Ray doesnt intersect sphere */
      if (h2 < 0)
        return 0;
      /* Ray starts outside sphere */
      Inter.Shp = (shape *)this;
      Inter.T = OK - sqrt(h2);
      Inter.IsEnter = FALSE;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      Inter.N = (Inter.P - C).Normalize();
      Inter.IsN = TRUE;
      InterList.push_back(Inter);

      Inter.Shp = (shape *)this;
      Inter.T = OK + sqrt(h2);
      Inter.IsEnter = FALSE;
      Inter.P = Ray(Inter.T);
      Inter.IsP = TRUE;
      Inter.N = (Inter.P - C).Normalize();
      Inter.IsN = TRUE;
      InterList.push_back(Inter);

      return 2;
    } /* End of 'AllIntersect' function */
  }; /* End of 'sphere' class */
} /* End of 'mert' namespace */
#endif /* __SPHERE_H_ */
/* END OF 'SPHERE.H' FILE */