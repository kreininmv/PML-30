/* FILE NAME   : RESMANAGER.H
 * PURPOSE     : Resourse manager.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __RESMAN_H_
#define __RESMAN_H_

#include "..//..//BASE/DEF.H"

namespace mk5
{
  template <typename Type>
  class resource_manager
  {
  public:
    std::map<std::string, Type*> Stock;

    /* Resourse manager add function.
     * ARGUMENTS:
     *   - point new resourse:
     *       const Type *Res
     * RETURNS:
     *   (resource_manager &) link to the new resource_manager
     */
    resource_manager & Add( Type *Res)
    {
      Stock[Res->Name] = Res;
      return *this;
    } /* End of 'Add' function */

    /* Deconstructor resourse manager function.
     * ARGUMENTS: None.
     */
    ~resource_manager( VOID )
    {
      for (auto r : Stock)
        delete r.second;
    } /* End of '~resourse manager' function */

    /* Find resource at stock function.
     * ARGUMENTS:
     *   - resource name to find:
     *       const std::string &Name;
     * RETURNS:
     *   (type *) reference to found elememt.
     */
    Type * Find( const std::string &Name )
    {
      if (Stock.find(Name) == Stock.end())
        return nullptr;
      return Stock[Name];
    } /* End of 'Find' function */
  }; /* End of 'resourse_manage' class */
} /* End of 'mk5' namespace */
#endif /* __RESMAN_H_ */

/* END OF 'RESMANAGER.H' FILE */