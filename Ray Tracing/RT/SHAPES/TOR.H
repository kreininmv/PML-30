/* FILE NAME   : TOR.H
 * PURPOSE     : Class of tor.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 04.09.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __TOR_H_
#define __TOR_H_

#include "SHAPE.H"
#include "..//..//MTH/EQUATION/SOL.H"
#include "..//..//DEF.H"

namespace mert
{
  /* Class of tor */
  class tor : public shape
  {
  private:
    DBL R, R2, r, r2; /* Radius of big and small district */
  public:

   /* Main class constructor */
    tor(DBL Rad, DBL rad) : R(Rad), r(rad), R2(Rad * Rad), r2(rad * rad)
    {
    } /* End of class constuctor */

    /* Intersection of tor and ray
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray<Type> &r;
     *   - intersection struct:
     *       intr *I.
     * RETURNS:
     *   (BOOL) TRUE if intersect else - FALSE
     */
    BOOL Intersect(const ray &r, intr &I) const override
    {
      
      vec
        O = r.Org,
        D = r.Dir;
      DBL
        a = O[0],
        b = D[0],
        c = O[1],
        d = D[1],
        e = O[2],
        f = D[2],
        a2 = a * a,
        b2 = b * b,
        c2 = c * c,
        d2 = d * d,
        e2 = e * e,
        f2 = f * f,


      /* First coef of intesection equal */
      x1 =
      2 * b2 * d2 +
      2 * b2 * f2 +
      2 * d2 * f2 +
      b2 * b2 +
      d2 * d2 +
      f2 * f2,

      /* Second coef of intesection equal */
      x2 =
      4 * (
        a * b * b2 +
        a * b * d2 +
        a * b * f2 +
        b2 * c * d +
        b2 * e * f +
        c * d * d2 +
        c * d * f2 +
        d2 * e * f +
        e * f * f2),

      /* Third coef of intesection equal */
      x3 =
      2 * (
        a2 * f2 +
        b2 * c2 +
        b2 * e2 +
        3 * c2 * d2 +
        c2 * f2 +
        4 * a * b * c * d +
        4 * c * d * e * f +
        d2 * e2 +
        3 * a2 * b2 +
        3 * e2 * f2 +
        4 * a * b * e * f +
        a2 * d2 -
        b2 * r2 -
        d2 * r2 -
        b2 * R2 -
        d2 * R2 -
        f2 * r2 +
        f2 * R2),

      /* Fourth coef of intesection equal */
      x4 =
      4 * (
        c2 * c * d +
        c2 * e * f +
        c * d * e2 +
        a * b * e2 +
        a * b * c2 +
        a2 * c * d +
        e2 * e * f +
        a2 * e * f +
        a2 * a * b -
        c * d * R2 -
        a * b * r2 -
        a * b * R2 -
        e * f * r2 +
        e * f * R2 -
        c * d * r2),

      /* Fifth coef of intesection equal */
      x5 =
      2 * a2 * c2 +
      2 * a2 * e2 +
      2 * c2 * e2 +
      e2 * e2 +
      c2 * c2 +
      a2 * a2 -
      2 * a2 * r2 -
      2 * c2 * r2 -
      2 * c2 * R2 -
      2 * a2 * R2 -
      2 * e2 * r2 +
      2 * e2 * R2 -
      2 * R2 * r2 +
      r2 * r2 +
      R2 * R2;

      sol EqIntr(x1, x2, x3, x4, x5);

      if (!EqIntr.eqsol.empty())
      {
        DBL Max_t = 0;
        INT Size = EqIntr.eqsol.size();
        for (INT k = 0; k < Size - 1; k++)
          for (INT i = 0; i < Size - 1 - k; i++)
            if (EqIntr.eqsol[i] > EqIntr.eqsol[i + 1])
            {
              DBL Tmp = EqIntr.eqsol[i];
              EqIntr.eqsol[i] = EqIntr.eqsol[i + 1];
              EqIntr.eqsol[i + 1] = Tmp;
            }

        for (INT i = 0; i < Size; i++)
          if (EqIntr.eqsol[i] > mth::Treshold)
          {
            I.P = r(EqIntr.eqsol[i]);
            I.N = I.P - vec(I.P[0], 0, I.P[2] * (R / sqrt(I.P[0] * I.P[0] + I.P[2] * I.P[2])));
            //I.N = vec(1);
            I.N.Normalize();
            I.IsN = TRUE;
            I.T = EqIntr.eqsol[i];
            I.IsP = TRUE;
            I.Shp = (shape *)this;
           
            if ((I.N & r.Dir) > 0)
              I.IsEnter = TRUE;
            else
              I.IsEnter = FALSE;
            return TRUE;
          }


      }
      return FALSE;

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
      INT Count = 0;
      std::vector<DBL> Sol;
      vec
        O = Ray.Org,
        D = Ray
        .Dir;
      DBL
        a = O[0],
        b = D[0],
        c = O[1],
        d = D[1],
        e = O[2],
        f = D[2],
        a2 = a * a,
        b2 = b * b,
        c2 = c * c,
        d2 = d * d,
        e2 = e * e,
        f2 = f * f,

      /* First coef of intesection equal */
      x1 =
        2 * b2 * d2 +
        2 * b2 * f2 +
        2 * d2 * f2 +
        b2 * b2 +
        d2 * d2 +
        f2 * f2,

      /* Second coef of intesection equal */
      x2 =
        4 * (
        a * b * b2 +
        a * b * d2 +
        a * b * f2 +
        b2 * c * d +
        b2 * e * f +
        c * d * d2 +
        c * d * f2 +
        d2 * e * f +
        e * f * f2),

      /* Third coef of intesection equal */
      x3 =
        2 * (
        a2 * f2 +
        b2 * c2 +
        b2 * e2 +
        3 * c2 * d2 +
        c2 * f2 +
        4 * a * b * c * d +
        4 * c * d * e * f +
        d2 * e2 +
        3 * a2 * b2 +
        3 * e2 * f2 +
        4 * a * b * e * f +
        a2 * d2 -
        b2 * r2 -
        d2 * r2 -
        b2 * R2 -
        d2 * R2 -
        f2 * r2 +
        f2 * R2),

        /* Fourth coef of intesection equal */
      x4 =
        4 * (
        c2 * c * d +
        c2 * e * f +
        c * d * e2 +
        a * b * e2 +
        a * b * c2 +
        a2 * c * d +
        e2 * e * f +
        a2 * e * f +
        a2 * a * b -
        c * d * R2 -
        a * b * r2 -
        a * b * R2 -
        e * f * r2 +
        e * f * R2 -
        c * d * r2),

        /* Fifth coef of intesection equal */
      x5 =
        2 * a2 * c2 +
        2 * a2 * e2 +
        2 * c2 * e2 +
        e2 * e2 +
        c2 * c2 +
        a2 * a2 -
        2 * a2 * r2 -
        2 * c2 * r2 -
        2 * c2 * R2 -
        2 * a2 * R2 -
        2 * e2 * r2 +
        2 * e2 * R2 -
        2 * R2 * r2 +
        r2 * r2 +
        R2 * R2;

      sol EqIntr(x1, x2, x3, x4, x5);

      if (EqIntr.eqsol.empty())
        return 0;

      DBL Max_t = 0;
      INT Size = EqIntr.eqsol.size();
      for (INT k = 0; k < Size - 1; k++)
        for (INT i = 0; i < Size - 1 - k; i++)
          if (EqIntr.eqsol[i] > EqIntr.eqsol[i + 1])
          {
            DBL Tmp = EqIntr.eqsol[i];
            EqIntr.eqsol[i] = EqIntr.eqsol[i + 1];
            EqIntr.eqsol[i + 1] = Tmp;
          }
      
      for (auto It = EqIntr.eqsol.begin(); It != EqIntr.eqsol.end(); It++)
        if (*It > mth::Treshold)
        {
          InterList.push_back(intr((shape *)this, *It));
          Count++;
        }
      return Count;
    } /* End of 'AllIntersect' function */

    /* Getting normal
     * ARGUMENTS:
     *   - intersection struct:
     *       intr *I.
     * RETURNS: None.
     */
    VOID GetNormal(intr *I)
    {
      I->N = I->P - vec(I->P[0], 0, I->P[2]) * (R /
        sqrt(I->P[0] * I->P[0] + I->P[2] * I->P[2]));
      I->N.Normalize();
      I->IsN = TRUE;
    } /* End of 'GetNormal' function */
  }; /* End of 'tor' class */
}
#endif /* __TOR_H_ */

/* END OF 'TOR.H' FILE */