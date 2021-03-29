/* FILE NAME   : VEC.H
 * PURPOSE     : Vectors.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mth'.
 */

#ifndef __VEC_H_
#define __VEC_H_

#include "MTHDEF.H"


/* Math library namespace */
namespace mth
{
  /* Space vector handle class */
  template <typename Type = double>
  class VEC
  {
    /* Delegate access right to other classes */
    template<class type> friend class MATR;

  private:
    /* Vector coordinates */
    Type X, Y, Z;

  public:
    /* Default constructor */
    VEC ( VOID )
    {
    } /* End of 'VEC' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector all coordinates value:
     *       Type A;
     */
    explicit VEC( Type a ) : X(a), Y(a), Z(a)
    {
    } /* End of 'VEC' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector coordinates:
     *       type A, B, C;
     */
    VEC( Type A, Type B, Type C ) : X(A), Y(B), Z(C)
    {
    } /* End of 'VEC' function */
   
    /* Get pointer to vector element operator
     * ARGUMENTS: 
     *   - element number:
     *       INT N;
     * RETURNS:
     *   (FLT *) pointer to vector element.
     */
    Type & operator[]( INT N )
    {
      if (N > 2)
        N = 2;
      else if (N < 0)
        N = 0;

      if (N == 0)
        return X;
      else if (N == 1)
        return Y;
      return Z;
    } /* End of 'operator[]' function */

    /* Sum of two VECtors function.
     * ARGUMENTS:
     *   - vector to be add:
     *       const VEC &V;
     * RETURNS:
     *   (VEC) result of addition.
     */
    VEC<Type> operator+( const VEC<Type> &V ) const
    {
      return VEC(V.X + X, V.Y + Y, V.Z + Z);
    } /* End of 'operator+' function */

    /* Add vector function.
     * ARGUMENTS:
     *   - vector to be add:
     *       const VEC &V;
     * RETURNS:
     *   (VEC &) self reference.
     */
    VEC<Type> & operator+=( const VEC<Type> &V )
    {
      X += V.X, Y += V.Y, Z += V.Z;
      return *this;
    } /* End of 'operator+=' function */

    /* Long of vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   - (Type) result of long of vector.
     */
    Type operator!( VOID ) const
    {
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator!' function */

    /* Subtract two vectors function.
     * ARGUMENTS:
     *   - vector to be subtract:
     *       const VEC &V;
     * RETURNS:
     *   (VEC) result of subtract.
     */
    VEC operator-( const VEC &V ) const
    {
      return VEC(X - V.X, Y - V.Y, Z - V.Z);
    } /* End of 'operator-' function */

    /* Negate vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VEC) result of negate.
     */
    VEC operator-( VOID )
    {
      return VEC(-X, -Y, -Z);
    } /* End of 'operator-' function */

    /* Dot product of two VECtors function.
     * ARGUMENTS:
     *   - vector to be producted:
     *       const VEC &V;
     * RETURNS:
     *   (type) result of dot product.
     */
    Type operator&( const VEC &V) const
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* End of 'operator&' function */

    /* Cross product of two VECtors function.
     * ARGUMENTS:
     *   - vector to be producted:
     *       const VEC &V;
     * RETURNS:
     *   (VEC) result of cross product.
     */
    VEC operator%( const VEC &V) const
    {
      return VEC(Y * V.Z - V.Y * Z, -(X * V.Z - V.X * Z),  X * V.Y - V.X * Y);
    } /* End of 'operator%' function */

    /* Multiply vector by number function.
     * ARGUMENTS:
     *   - number to be multiply:
     *       type N;
     * RETURNS:
     *   (VEC) result of division.
     */
    VEC operator*( const Type a ) const
    {
      return VEC(X * a, Y * a, Z * a);
    } /* End of 'operator*' function */

    /* Multiply vector by number function.
     * ARGUMENTS:
     *   - number to be multiply:
     *       type N;
     * RETURNS:
     *   (VEC &) self reference.
     */
    VEC & operator*=( const Type a )
    {
      X *= a, Y *= a, Z *= a;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply vector by vector function.
     * ARGUMENTS:
     *   - vector to be multiply:
     *       VEC V;
     * RETURNS:
     *   (VEC) result of division.
     */
    VEC operator*( const VEC &V ) const
    {
      return VEC(V.X * X, V.Y * Y, V.Z * Z);
    } /* End of 'operator*' function */

    /* Multiply vector by vector function.
     * ARGUMENTS:
     *   - vector to be multiply:
     *       (VEC) V;
     * RETURNS:
     *   (VEC &) self reference.
     */
    VEC operator*=( const VEC &V ) 
    {
      X *= V.X, Y *= V.Y, Z *= V.Z;
      return *this;
    } /* End of 'operator*=' function */

    /* Divide vector by number function.
     * ARGUMENTS:
     *   - number to be divide:
     *       type N;
     * RETURNS:
     *   (VEC) result of division.
     */
    VEC operator/( const Type a ) const
    {
      return VEC(X / a, Y / a, Z / a);
    } /* End of 'operator/' function */

    /* Divide vector by number function.
     * ARGUMENTS:
     *   - number to be divide:
     *       type N;
     * RETURNS:
     *   (VEC &) self reference.
     */
    VEC & operator/=( const Type a )
    {
      X /= a, Y /= a, Z /= a;
      return *this;
    } /* End of 'operator/=' function */

    /* Normalize vector itself function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VEC) self poINTer.
     */
    VEC & Normalize( VOID )
    {
      return *this /= !*this;
    } /* End of 'Normalize' function */

    /* Normalizing vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VEC) result of normalize.
     */
    VEC Normalizing( VOID ) const
    {
      Type len = *this & *this;
      if (len != 0 && len != 1)
      {
        len = sqrt(len);
        return VEC(X / len, Y / len, Z / len);
      }
      return *this;
    } /* End of 'Normalizing' function */

    /* Generate vector with random coordinates.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VEC) random vector.
     */
    static VEC Rand( VOID )
    {
      return VEC((Type)rand(), (Type)rand(), (Type)rand());
    } /* End of 'Rand' function */  


    /* Generate zero vector.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VEC) zero vector.
     */
    static VEC Zero( VOID )
    {
      return VEC(0, 0, 0);
    } /* End of 'Zero' function */
  };
  /* Plane vector handle class */
  template<class type>
  class VEC2
  {
  private:
    /* Vector coordinates */
    type X, Y;

  public:
    /* Default constructor */
    VEC2( VOID )
    {
    } /* End of 'vec' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector coordinates:
     *       type A, B;
     */
    VEC2( type A, type B ) : X(A), Y(B)
    {
    } /* End of 'VEC2' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector all coordinates value:
     *       Type A;
     */
    explicit VEC2( type A ) : X(A), Y(A)
    {
    } /* End of 'VEC2' function */

    /* Obtain vector first element pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (type *) pointer to X coordinate.
     */
    operator type *( VOID )
    {
      return &X;
    } /* End of 'operator type *' function */
  }; /* End of 'VEC2' class */

  /* Space homogenius vector handle class */
  template<class type>
  class VEC4
  {
  private:
    /* vector coordinates */
    type X, Y, Z, W;

  public:
    /* Default constructor */
    VEC4( VOID )
    {
    } /* End of 'VEC4' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector coordinates:
     *       type A, B, C, D;
     */
    VEC4( type A, type B, type C , type D = 1) : X(A), Y(B), Z(C), W(D)
    {
    } /* End of 'VEC4' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - vector all coordinates value:
     *       Type A;
     */
    explicit VEC4( type A ) : X(A), Y(A), Z(A), W(A)
    {
    } /* End of 'VEC4' function */

    /* Obtain vector first element pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (type *) pointer to X coordinate.
     */
    operator type *( VOID )
    {
      return &X;
    } /* End of 'operator type *' function */
  }; /* End of 'VEC4' class */
} /* End of 'mth' namespace */

#endif /* __VEC_H_ */

/* END OF 'VEC.H' FILE */