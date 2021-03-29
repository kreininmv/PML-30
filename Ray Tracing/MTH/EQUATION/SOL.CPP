/* FILE NAME   : SOL.H
 * PURPOSE     : Solution module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 03.09.2018
 * NOTE        : Module namespace 'mert'.
 */


#include "..//..//MTH/MTH.H"
#include "..//..//DEF.H"

#include "SOL.H"

using namespace mert;

/* class constuctor for equals of 2 pow
* ARGUMENTS:
*   - coefficients:
*       DBL a, b, c;
*/
sol::sol(DBL a, DBL b, DBL c) : A(a), B(b), C(c)
{
  if (fabs(a) < mth::Treshold)
    eqsol.push_back(-c / b);
  else
  {
    DBL D = b * b - 4 * a * c;
    if (fabs(D) < mth::Treshold)
      eqsol.push_back(-b / (2 * a));
    else if (D > mth::Treshold)
    {
      eqsol.push_back((-b - sqrt(D)) / (2 * a));
      eqsol.push_back((-b + sqrt(D)) / (2 * a));
    }
  }
}/* End of 'sol' function */

/* Class constuctor for equals of 3 pow
 * ARGUMENTS:
 *   - coefficients:
 *       DBL a, b, c, d;
 */
sol::sol(DBL a, DBL b, DBL c, DBL d) : A(a), B(b), C(c), D(d)
{
  if (fabs(a - mth::Treshold) > 0)
  {
    DBL
      p = (3 * a * c - b * b) / (3 * a * a),
      q = (2 * b * b * b -
        9 * a * b * c +
        27 * a * a * d) /
        (27 * a * a * a),

      D = (p / 3.0) * (p / 3.0) * (p / 3.0) + (q / 2.0) * (q / 2.0);

    if (fabs(D) < mth::Treshold)
    {
      DBL ab = pow(fabs(q / 2), 1 / 3.0) * fabs(-q) / -q * 2;
      eqsol.push_back(ab - b / (a * 3.0));
      eqsol.push_back(-ab / 2 - b / (a * 3.0));
    }
    else if (D > mth::Treshold)
    {
      double alfa = -q / 2 + sqrt(D);
      double sgn_alfa = (alfa > 0 ? 1 : -1);

      DBL beta = -q / 2 - sqrt(D);
      DBL sgn_beta = (beta > 0 ? 1 : -1);

      DBL ab = sgn_alfa* pow(fabs(alfa), 1 / 3.0) +
        sgn_beta * pow(fabs(beta), 1 / 3.0);
      eqsol.push_back(ab - b / (a * 3.0));
    }
    else if (D < -mth::Treshold)
    {
      DBL p = c - b * b / 3.0;
      DBL q = 2.0 * b * b * b / 27.0 - b * c / 3.0 + d;
      DBL A = sqrt(-4.0 * p / 3.0);

      DBL c3phi = -4.0 * q / (A * A * A);

      DBL phi = acos(c3phi) / 3.0;

      DBL root1 = A * cos(phi) - b / 3.0;
      eqsol.push_back(root1);
      DBL root2 = A * cos(phi + 2 * mth::PI / 3.0) - b / 3.0;
      DBL root3 = A * cos(phi - 2 * mth::PI / 3.0) - b / 3.0;
      eqsol.push_back(root1);
      eqsol.push_back(root2);
      eqsol.push_back(root3);
    }
  }
  if (fabs(a) < mth::Treshold)
  {
    if (fabs(b) < mth::Treshold)
      eqsol.push_back(-d / c);
    else
    {
      sol f(b, c, d);
      eqsol = f.eqsol;
    }
  }
} /* End of constructor */


/* Class constuctor for equals of 4 pow
 * ARGUMENTS:
 *   - coefficients:
 *       DBL a, b, c, d, e;
 */
sol::sol(DBL a, DBL b, DBL c, DBL d, DBL e) : A(a), B(b), C(c), D(d), E(e)
{
  if (fabs(a) < mth::Treshold)
  {
    sol f(b, c, d, e);

    eqsol = f.eqsol;
    return;
  }
  DBL
    a1 = b / a,
    b1 = c / a,
    c1 = d / a,
    d1 = e / a;

  sol f(
    1,
    -b1,
    a1 * c1 - 4 * d1,
    -a1 * a1 * d1 + 4 * d1 * b1 - c1 * c1);
  DBL
    y1 = f.eqsol[0];

  INT
    sgn = (a1 / 2 * y1 - c1) > 0 ? 1 : -1;

  DBL
    a2 = 1,
    b2 = a1 / 2 - sqrt(fabs(a1 * a1 / 4 - b1 + y1)),
    c2 = y1 / 2 - sgn * sqrt(fabs(y1 * y1 / 4 - d1));

  sol f1(a2, b2, c2);
  for (auto s : f1.eqsol)
    eqsol.push_back(s);

  sgn = (a1 / 2 * y1 - c1) > 0 ? 1 : -1;

  a2 = 1;
  b2 = a1 / 2 + sqrt(fabs(a1 * a1 / 4 - b1 + y1));
  c2 = y1 / 2 + sgn * sqrt(fabs(y1 * y1 / 4 - d1));

  sol f2(a2, b2, c2);
  for (auto s : f2.eqsol)
    eqsol.push_back(s);
} /* End of 'sol' function */

/* Main class destructor */
sol::~sol( VOID )
{
  eqsol.clear();
} /* End of '~sol' function */

/* END OF 'SOL.CPP' FILE */
