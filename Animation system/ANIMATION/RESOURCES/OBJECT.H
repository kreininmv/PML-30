/* FILE NAME   : OBJECT.H
 * PURPOSE     : Texture system.
 *               HeaderModule.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "PRIMITIVE.H"
#include "RESMANAGER.H"

namespace mk5
{
  class object
{
public:
  static resource_manager<object> Objects; /* Objects manager */

  std::string Name;
  std::vector<prim *> Prims;

  object( VOID )
  {
  }

  /* Load primitives from 'G3DM' file function.
  * ARGUMENTS:
  *   - file name:
  *       const std::string &FileName;
  *   - transformation matrix:
  *       const matr &Transform;
  *   - shader name:
  *       const std::string &ShaderName;
  * RETURNS:
  *   (BOOL) TRUE if success, FALSE otherwise.
  */
  object( const std::string &FileName, matr Transform, const std::string &ShaderName = "" ) : Name(FileName)
  {
    Load(FileName, Transform, ShaderName);
  }

  /* Load primitives from 'G3DM' file function.
  * ARGUMENTS:
  *   - file name:
  *       const std::string &FileName;
  *   - transformation matrix:
  *       const matr &Transform;
  *   - shader name:
  *       const std::string &ShaderName;
  * RETURNS:
  *   (BOOL) TRUE if success, FALSE otherwise.
  */
  BOOL Load( const std::string &FileName, matr &Transform, const std::string &ShaderName = "" );

};
}


#endif /* __OBJECT_H_ */

/* END OF 'OBJECT.H' FILE */
