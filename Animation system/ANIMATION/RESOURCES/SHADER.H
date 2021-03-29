/* FILE NAME   : SHADER.H
 * PURPOSE     : Shader manager.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __SHADER_H_
#define __SHADER_H_

#include <fstream>
#include <ostream>
#include <istream>
#include "RESMANAGER.H"

namespace mk5
{
  /* Shaders class */
  class shader
  {
  public:
    std::string Name, FName;

    static resource_manager<shader> Shad;

    UINT ProgId;

    /* Shader constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    shader( VOID )
    {

    } /* End of 'shader' constructor */

    /* Shader constructor.
     * ARGUMENTS:
     *   - link to sting:
     *       const std::string &S;
     * RETURNS: None.
     */
    shader( const std::string &S ) : Name(S)
    {
    } /* End of 'shader' constructor */

    /* Shader destructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~shader( VOID )
    {
      UINT Shaders[5];
      INT n;

      glGetAttachedShaders(ProgId, 5, &n, Shaders);

      if (ProgId == 0)
        return;
      for (INT i = 0; i < n; i++)
      {
        glDetachShader(ProgId, Shaders[i]);
        glDeleteShader(Shaders[i]);
      }
      glDeleteProgram(ProgId);
    } /* End of '~shader' destructor */

    /* Save error text to log file function.
     * ARGUMENTS:
     *   - text 1:
     *       const std::string &Stage;
     *   - text 2:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID Log( const std::string &Stage, const std::string &Text )
    {
      std::ofstream("SHAD30.LOG", std::ios_base::app) << Stage << ":" << Text << "\n";
    } /* End of 'Log' function */

    /* Text file load to memory function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (std::string) load text.
     */
    std::string LoadTextFile( const std::string &FileName )
    {
      std::ifstream F(FileName);
      std::string str, txt = "";

      std::getline(F, str);
      if (str == "")
        return "";
      else
      {
        txt += str += "\n";
        while (!F.eof())
        {
          std::getline(F, str);
          txt += str += "\n";
        }
        return txt;
      }
    } /* End of 'LoadTextFile' function */

    /* Load shader function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS: None.
     */
    VOID ShaderLoad( const std::string &FileNamePrefix )
    {
      INT res, i, NumOfShaders = 5;
      BOOL isok = TRUE, ok[5];
      UINT
        Shaders[5] = {0},
        ShdTypes[5] = {GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER};

      FName = FileNamePrefix;

      std::string Suff[5] = {"VERT", "CTRL", "EVAL", "GEOM", "FRAG"}, txt, s;

      for (i = 0; i < NumOfShaders; i++)
      {
        s = "BIN\\SHADERS\\" + FileNamePrefix + "\\" + FileNamePrefix + "." + Suff[i];
        if ((Shaders[i] = glCreateShader(ShdTypes[i])) == 0)
        {
          isok = FALSE;
          Log(Suff[i], "Create shader error");
          break;
        }

        if ((txt = LoadTextFile(s)) == "")
        {
          ok[i] = FALSE;
          continue;
        }
        const CHAR *l = txt.c_str();
        glShaderSource(Shaders[i], 1, &l, NULL);
        glCompileShader(Shaders[i]);

        glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &res);
        if (res != 1)
        {
          CHAR Buf[100];
          glGetShaderInfoLog(Shaders[i], 100, &res, Buf);
          s = std::string(Buf);
          Log(s, "");
          isok = FALSE;
          break;
        }
        ok[i] = TRUE;
      }

      if (isok)
        if ((ProgId = glCreateProgram()) == 0)
          isok = FALSE;
        else
        {
          for (i = 0; i < NumOfShaders; i++)
            if (Shaders[i] != 0)
              if (ok[i])
                glAttachShader(ProgId, Shaders[i]);
          glLinkProgram(ProgId);
          glGetProgramiv(ProgId, GL_LINK_STATUS, &res);
          if (res != 1)
          {
            CHAR Buf[100];
            glGetShaderInfoLog(Shaders[i], 100, &res, Buf);
            s = std::string(Buf);
            Log(s, "");
            isok = FALSE;
          }
        }
      if (!isok)
      {
        for (i = 0; i < 5; i++)
          if (Shaders[i] != 0)
          {
            if (ProgId != 0)
              glDetachShader(ProgId, Shaders[i]);
            glDeleteShader(Shaders[i]);
          }
        if (ProgId != 0)
          glDeleteProgram(ProgId);
        ProgId = 0;
      }
    } /* End of 'ShaderLoad' function */

    /* Delete shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Delete( VOID )
    {
      UINT Shaders[5];
      INT n;

      glGetAttachedShaders(ProgId, 5, &n, Shaders);

      if (ProgId == 0)
        return;
      for (INT i = 0; i < n; i++)
      {
        glDetachShader(ProgId, Shaders[i]);
        glDeleteShader(Shaders[i]);
      }
      glDeleteProgram(ProgId);
    } /* End of 'Delete' function */

    /* Apply shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      glUseProgram(ProgId);
    } /* End of 'Apply' function */

    /* Update shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID )
    {
      Delete();
      ShaderLoad(FName);
    } /* End of 'Update' function */
  }; /* End of 'shader' class */
} /* End of 'mk5' namespace*/

#endif /* __SHADER_H_ */

/* END OF 'SHADER.H' FILE */