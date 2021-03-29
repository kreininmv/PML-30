/* FILE NAME   : DEF.H
 * PURPOSE     : Defintion module.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : None
 */

#ifndef __DEF_H_
#define __DEF_H_

#include "MATH/MTH.H"

/* Debug memory allocation support */ 
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 

# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy 
{ 
public: 
  /* Class constructor */
  __Dummy( VOID ) 
  { 
    SetDbgMemHooks(); 
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */


#include <COMMONDF.H>
#include <exception>
#include <string>
#include <cassert>

#include <ostream>
#include <istream>
#include <fstream>
#include <map>
#include <string>
#include <cstdio>
#include <vector>

#include "STOCK/STOCK.H"

#define GLEW_STATIC

#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

#pragma comment(lib, "glew32s")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "glu32")

namespace mk5
{
  typedef mth::VEC<FLT> vec;
  typedef mth::MATR<FLT> matr;
  typedef mth::CAMERA<FLT> camera;
  typedef mth::VEC2<FLT> vec2;
  typedef mth::VEC4<FLT> vec4;
}

#endif /* __DEF_H_ */

/* END OF 'DEF.H' FILE */