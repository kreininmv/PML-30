/* FILE NAME   : SOL.H
 * PURPOSE     : Solution module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 03.09.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __SOL_H_
#define __SOL_H_

#include "..//..//DEF.H"

namespace mert
{
  /* Equation solution class */
  class sol
  {
  private:
    DBL A, B, C, D, E;  /* Equation coefficients */
  public:
    std::vector<DBL> eqsol; /* Array of solutions */

    /* class constuctor for equals of 2 pow
     * ARGUMENTS:
     *   - coefficients:
     *       DBL a, b, c;
     */
    sol(DBL a, DBL b, DBL c);
    /* End of 'sol' function */

      /* Class constuctor for equals of 3 pow
       * ARGUMENTS:
       *   - coefficients:
       *       DBL a, b, c, d;
       */
    sol(DBL a, DBL b, DBL c, DBL d);

    /* Class constuctor for equals of 4 pow
     * ARGUMENTS:
     *   - coefficients:
     *       DBL a, b, c, d, e;
     */
    sol(DBL a, DBL b, DBL c, DBL d, DBL e);

    /* Main class destructor */
    ~sol(VOID);

  }; /* End of 'sol' class */
}
#endif /* __SOL_H_ */

/* END OF 'SOL.H' FILE */