/* FILE NAME   : RND.CPP
 * PURPOSE     : Render system.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : None
 */

#include "RENDER.H"
#include "..\\WIN\WIN.H"

namespace mk5
{
  mth::CAMERA<FLT> render::Cam;

  /* Render class constructor. 
   * ARGUMENTS: None.
   */
  render::render( HWND hWnd )
  {
    PIXELFORMATDESCRIPTOR pfd;
    INT i;

    hDC = GetDC(hWnd);
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 32;
    i = ChoosePixelFormat(hDC, &pfd);
    DescribePixelFormat(hDC, i, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    SetPixelFormat(hDC, i, &pfd);

    hGLRC = wglCreateContext(hDC);

    wglMakeCurrent(hDC, hGLRC);

    if (glewInit() != GLEW_OK || !(GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader
      && GLEW_ARB_tessellation_shader && GLEW_ARB_geometry_shader4))
    {
      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(hGLRC);
      ReleaseDC(win::hWnd, hDC);
      MessageBox(win::hWnd, "Glew init error", "Ahtung", 0);
      return;
    }
    glClearColor(0.3, 0.5, 0.7, 1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(-1);
  } /* End of 'render::render' function */

  /* Render system frame resize function.
   * ARGUMENTS:
   *   - new frame size:
   *       INT W, H;
   * RETURNS: None.
   */
  VOID render::Resize( INT W, INT H )
  {
    glViewport(0, 0, W, H);
    Cam.Resize(W, H);
  }
  /* End of 'render::Resize' function */

  /* Render system start frame render function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameStart( VOID )
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  } /* End of 'render::FrameStart' function */

  /* Render system copy frame buffer function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameCopy( VOID )
  {
    SwapBuffers(hDC);
  } /* End of 'render::FrameCopy' function */

  /* Render system finish frame render function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID render::FrameEnd( VOID )
  {
    glFinish();
  } /* End of 'render::FrameEnd' function */

  /* Draw primitive function.
   * ARGUMENTS:
   *   - pointer to primitive:
   *       const prim *Pr
   * RETURNS: None.
   */
  VOID render::Draw( const prim *Pr )
  {

    glLoadMatrixf(Cam.VP[0]);

    glBindVertexArray(Pr->VA);
    glUseProgram(0);

    if (Pr->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElements(GL_TRIANGLES, Pr->VertexCount, GL_UNSIGNED_INT, nullptr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArrays(GL_TRIANGLES, 0, Pr->VertexCount);

    glUseProgram(0);
    glBindVertexArray(0);
  } /* End of 'Draw' function */
  /* Draw primitive whis matrix function.
   * ARGUMENTS:
   *   - pointer to primitive:
   *       const prim *Pr;
   *   - link to matr:
   *       const matr &W;
   * RETURNS: None.
   */
  VOID render::DrawMatr( prim *Pr , const matr &W )
  {
    INT loc;
    static matr World;
    World = W;

    glBindVertexArray(Pr->VA);

    Pr->mtl->Apply();

    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "MatrWVP")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, (W * Cam.VP)[0]);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "World")) != -1)
      glUniformMatrix4fv(loc, 1, FALSE, World.Inverse()[0]);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "Ka")) != -1)
      glUniform3fv(loc, 1, &Pr->mtl->Ka[0]);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "Kd")) != -1)
      glUniform3fv(loc, 1, &Pr->mtl->Kd[0]);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "Ks")) != -1)
      glUniform3fv(loc, 1, &Pr->mtl->Ks[0]);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "Ph")) != -1)
      glUniform1f(loc, Pr->mtl->Ph);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "Trans")) != -1)
      glUniform1f(loc, Pr->mtl->Trans);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "IsTex")) != -1)
      glUniform1i(loc, Pr->mtl->Tex[0] == nullptr ? 0 : 1);
    if ((loc = glGetUniformLocation(Pr->mtl->Shd->ProgId, "CamLoc")) != -1)
      glUniform3fv(loc, 1, &Cam.Loc[0]);

    UINT type = Pr->TYPE == base::STRIP ? GL_TRIANGLE_STRIP : GL_TRIANGLES;


    if (Pr->IBuf != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
      glDrawElements(type, Pr->VertexCount, GL_UNSIGNED_INT, nullptr);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
      glDrawArrays(GL_TRIANGLES, 0, Pr->VertexCount);

    glUseProgram(0);
    glBindVertexArray(0);
  } /* End of 'DrawMatr' function */

  /* Draw object whis matrix function.
   * ARGUMENTS:
   *   - pointer to object:
   *       object *obj;
   *   - link to matr:
   *       const matr &W;
   * RETURNS: None.
   */
  VOID render::DrawMatr( object *obj , const matr &W )
  {
    for (INT i = 0; i < obj->Prims.size(); i++)
      if (obj->Prims[i]->mtl != nullptr && obj->Prims[i]->mtl->Trans >= 1)
        DrawMatr(obj->Prims[i], W);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);
    for (INT i = 0; i < obj->Prims.size(); i++)
      if (obj->Prims[i]->mtl != nullptr && obj->Prims[i]->mtl->Trans < 1)
        DrawMatr(obj->Prims[i], W);

    glCullFace(GL_FRONT);
    for (INT i = 0; i < obj->Prims.size(); i++)
      if (obj->Prims[i]->mtl != nullptr && obj->Prims[i]->mtl->Trans < 1)
        DrawMatr(obj->Prims[i], W);

    glDisable(GL_CULL_FACE);
  }
}

/* END OF 'RND.CPP' FILE */