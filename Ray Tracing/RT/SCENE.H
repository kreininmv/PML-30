/* FILE NAME   : SCENE.H
 * PURPOSE     : System of scenes.
 *               Header Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mert'.
 */

#ifndef __SCENE_H_
#define __SCENE_H_

#include "..//DEF.H"
#include "SHAPES/SHAPE.H"
#include "..//WIN/WIN.H"
#include "LIGHT/LIGHT.H"
#include "MATERIAL/MATERIAL.H"
#include "IMAGE/IMAGE.H"

namespace mert
{
  class scene
  {
  private:
    shape_list SList;                // Shapes list
    std::vector<light *> LList;      // Lights list
    INT CurrentLevel, MaxLevel = 3;  // Recursion trackers
    material TestM = material(vec(0.5), vec(0.6), vec(0.3), 10);
  public:
    vec 
      Background = vec(1),           // Background color
      Ambient = vec(0.2);              // Default ambient

    /* Scene render function.
     * ARGUMENTS:
     *   - camera:
     *       camera Cam;
     *   - image to draw in:
     *       image *Img;
     * RETURNS: None.
     */
    template <class FeedBack>
    VOID Render( camera &Cam, image *Img, FeedBack &FB )
    {
      for (INT ys = 0; ys < -Img->ImageH; ys++)
        for (INT xs = 0; xs < Img->ImageW; xs++)
        {
          ray R = Cam.CastRay(xs, ys);
          vec Color = Trace(R, Cam);

          CurrentLevel = 0;
          FB(xs, ys, Color);
        }
    } /* End of 'Render' function */

    /* Trace ray function.
     * ARGUMENTS:
     *   - ray to trace:
     *       ray R;
     * RETURNS:
     *   (vec) Color;
     */
    vec Trace( const ray &R, const camera &Cam )
    {
      vec Color(Background);
      intr Intr;

      if (++CurrentLevel <= MaxLevel)
      {
        if (SList.Intersect(R, Intr))
        {
          Shade(Intr, Cam, Color);
        }
      }
      CurrentLevel--;
      return Color;
    } /* End of 'Trace' function */

    VOID Shade( const intr &Intr, const camera &Cam, vec &Color )
    {
      vec DifL = vec(0), SpecL = vec(0.3), DSF = vec(0);

      Color = vec(0.2, 0.2, 0.2) * TestM.Ka;

      DBL F = 0;

      for (auto Lght : LList)
      {
        vec 
          L = Lght->GetL(Intr.P),
          V = (Intr.P - Cam.Loc).Normalize(),
          R = V - Intr.N * 2 * (V & Intr.N);
        intr_list Shad;
        DifL = vec(mth::Max(Intr.N & L, 0.0f)) * Lght->Color;
        SpecL = vec(pow(mth::Max(R & L, 0.0f), TestM.Ph)) * Lght->Color;
        if (SList.AllIntersect(ray(Intr.P, L), Shad) == 0 || abs(Shad[Shad.size() - 1]->T) < 0.0001)
        {
          DBL Dist = Lght->GetDist(Intr.P);
          F = mth::Min(1 / (Lght->Cc + Lght->Cl * Dist + Lght->Cq * Dist * Dist), 1.0);
        }
        Color += (TestM.Kd * DifL + TestM.Ks * SpecL) * F;
        for (auto I : Shad)
          delete I;
      }
      Color += (TestM.Kd * DifL + TestM.Ks * SpecL) * F;

      //Color = vec::Clamp(Color, 0.0, 1.0);
    }

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new shape:
     *       shape *S;
     * RETURNS: None.
     */
    VOID AddShape( shape *S )
    {
      SList.Shapes.push_back(S);
    } /* End of 'AddShape' function */

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new shape:
     *       shape *S;
     * RETURNS: None.
     */
    scene & operator<<( shape *S )
    {
      SList.Shapes.push_back(S);
      return *this;
    } /* End of 'operator<<' function */

    /* Add light to list function.
     * ARGUMENTS:
     *   - new light:
     *       light *L;
     * RETURNS: None.
     */
    VOID AddLight( light *L )
    {
      LList.push_back(L);
    } /* End of 'AddShape' function */

    /* Add shape to list function.
     * ARGUMENTS:
     *   - new light:
     *       light *L;
     * RETURNS: None.
     */
    scene & operator<<( light *L )
    {
      LList.push_back(L);
      return *this;
    } /* End of 'operator<<' function */

    ~scene( VOID )
    {
    }
  }; /* End of 'scene' class */
} /* End of 'mert' namespace */

#endif /* __SCENE_H_ */
/* END OF 'SCENE.H' FILE */