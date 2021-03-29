/* FILE NAME   : PRIMITIVE.CPP
 * PURPOSE     : Primitives module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#include "..//ANIMATION.H"
#include "PRIMITIVE.H"

namespace mk5
{
  resource_manager<prim> prim::Primitives;
  /* Create primitive from vertexes array function.
  * ARGUMENTS:
  *   - pointer to vertex array:
  *       vertex *V;
  *   - Count of vertexes:
  *       UINT NumOfVer;
  *   - pointer to index array:
  *       int *I;
  *   - Count of indexes:
  *       UINT NumOfI;
  * RETURNS:
  *   (prim *) pointer to primitive
  */
  prim * prim::FromVertexArray( vertex *V, UINT NumOfVer, INT *I, UINT NumOfI )
  {
    glGenVertexArrays(1, &VA);
    glGenBuffers(1, &VBuf);

    glBindVertexArray(VA);

    glBindBuffer(GL_ARRAY_BUFFER, VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NumOfVer, V, GL_STATIC_DRAW);

    if (NumOfI != 0)
    {
      glGenBuffers(1, &IBuf);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * NumOfI, I, GL_STATIC_DRAW);
      VertexCount = NumOfI;
    }
    else
      VertexCount = NumOfVer;


    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)sizeof(vec));
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)(sizeof(vec) + sizeof(vec2)));
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(vertex), (VOID *)(sizeof(vec) * 2 + sizeof(vec2)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    return this;
  } /* End of 'FromVertexArray' function */

    /* Create primitive from file function.
    * ARGUMENTS:
    *   - file name:
    *       std::string &FileName;
    * RETURNS:
    *   (prim *) pointer to primitive.
    */
  prim * prim::FromFile( CHAR *FileName )
  {
    std::vector<vertex> V;
    std::vector<INT> I;
    FILE *F;
    CHAR Buf[1000];


    if ((F = fopen(FileName, "r")) == NULL)
      return FALSE;

    while (fgets(Buf, sizeof(Buf), F) != NULL)
      if (Buf[0] == 'v' && Buf[1] == ' ')
      {
        DBL x, y, z;

        sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
        V.push_back(vertex(vec(x, y, z), vec2(0), vec(0), vec4(1, 0, 0, 1)));
      }
      else if (Buf[0] == 'v' && Buf[1] == 'n' && Buf[2] == ' ')
      {
        static int i = 0;
        DBL x, y, z;

        sscanf(Buf + 3, "%lf%lf%lf", &x, &y, &z);
        V.at(i).N = vec(x, y, z);
        i++;
      }
      else if (Buf[0] == 'f' && Buf[1] == ' ')
      {
        INT n1, n2, n3;

        sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
          sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
          sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
          sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
        I.push_back(n1 - 1);
        I.push_back(n2 - 1);
        I.push_back(n3 - 1);
      }
    fclose(F);

    FromVertexArray(&V[0], V.size(), &I[0], I.size());

    return this;
  }
  
} /* End of 'mk5' namespace */

/* END OF 'PRIM.CPP' FILE */
