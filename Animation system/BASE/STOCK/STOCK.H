/* FILE NAME   : STOCK.H
 * PURPOSE     : Container.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "../DEF.H"

namespace mk5
{
  template<typename Type = double>
  class stock
  {
  private:
    INT RealSize, MaxSize;
    Type *Array;

  public:

    /* Default constructor.
     * ARGUMENTS:
     *   - stock to be copy:
     *       const stock<type> &CopyData;
     */
    stock( VOID ) : Array(NULL), RealSize(0), MaxSize(0)
    {
    } /* End of 'stock' function */

      /* Class destructor */
    ~stock( VOID )
    {
      if (Array != NULL)
        delete[] Array;
    } /* End of '~stock' function */

    /* Copying constructor.
     * ARGUMENTS:
     *   - stock to be copy:
     *       const stock<type> &CopyData;
     */
    stock<Type>( const stock<Type> &CopyData) : RealSize(CopyData.RealSize), MaxSize(CopyData.MaxSize), Array(new Type[MaxSize])
    {
      for (INT i = 0; i < RealSize; i++)
        Array[i] = CopyData.Array[i];
    } /* End of 'stock' function */

    /* Assignment operator function.
     * ARGUMENTS:
     *   - stock to be copy:
     *       const stock<type> &CopyData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock<Type> & operator=( const stock<Type> &CopyData)
    {
      if (Array != NULL)
        delete[] Array;

      Array = new Type[CopyData.MaxSize];
      RealSize = CopyData.RealSize;
      MaxSize = CopyData.MaxSize;

      for (INT i = 0; i < RealSize; i++)
        Array[i] = CopyData[i];
    } /* End of 'operator=' function */

    /* Obtain data size (count of stock element) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) number of elements.
     */
    INT Size( VOID ) const
    {
      return RealSize;
    } /* End of 'Size' function */

    /* Add a new element to stock function.
     * ARGUMENTS:
     *   - element to be add:
     *       const type &NewData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock<Type> & Add( const Type &NewData )
    {
      if (RealSize == 0)
        MaxSize = 1;
      else 
        MaxSize *= 2;

      Type *new_bulk = new Type[MaxSize];

      if (Array != NULL)
      {
        for (int i = 0; i < RealSize; i++)
          new_bulk[i] = Array[i];
        delete [] Array;
      }

      Array = new_bulk;
      Array[RealSize++] = NewData;
      return *this;
    } /* End of 'Add' function */

    /* Add a new element to stock function.
     * ARGUMENTS:
     *   - element to be add:
     *       const type &NewData;
     * RETURNS:
     *   (stock &) self reference.
     */
    stock<Type> & operator<<( const Type &NewData)
    {
      return Add(NewData);
    } /* End of 'operator<<' function */

    /* Access stock element by index function.
     * ARGUMENTS:
     *   - element index:
     *       INT Index;
     * RETURNS:
     *   (type &) element reference.
     */
    Type & operator[]( INT Index)
    {
      assert(Index >= 0 && Index < RealSize);
      return Array[Index];
    } /* End of 'operator[]' function */

    /* Clear stock function.
     * ARGUMENTS:
     * RETURNS:
     *   (stock &) self reference.
     */
    stock & Clear( VOID )
    {
      RealSize = 0;
    }  /* End of 'Clear' function */

    /* Walk through all stock elements function.
     * ARGUMENTS:
     *   - visiter object:
     *     type2 &Walker;
     * RETURNS: None.
     */
    template<class Type2>
    VOID Walk( const Type2 & Walker )
    {
      for (int i = 0; i < RealSize; i++)
        Walker(Array[i]);
    } /* End of 'Walk' function */
  }; /* End of 'stock' class */
} /* End of 'mk5' namespace */
/* END OF 'STOCK.H' FILE */