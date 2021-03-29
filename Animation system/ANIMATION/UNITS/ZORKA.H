/* FILE NAME   : ZORKA.H
 * PURPOSE     : Example Unit.
 *               Unit module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __ZORKA_H_
#define __ZORKA_H_

#include "..\\ANIMATION.H"
#include "..\\RESOURCES\OBJECT.H"

/* Project namespace */
namespace mk5
{
  /* Test unit class */
  class unit_zorka : public unit
  {
  public:
    // Camera distance to look at point, rotation angles
    FLT Dist = 18, Rx = 0, Ry = 0;
    FLOAT Dv = 0, Du = 0, Dw = 0;

    // Objects
    object *Obj = new object("BIN\\MODELS\\Cyprys_House.g3dm", mth::MATR<FLT>::Identity(), "OBJ");
    object *Obj1 = new object("BIN\\MODELS\\cycle.g3dm", mth::MATR<FLT>::Identity(), "OBJ1");
    object *Obj2 = new object("BIN\\MODELS\\PML30.g3dm", mth::MATR<FLT>::Identity(), "OBJ2");

    // Shaders 
    shader *Sh = new shader("OBJ");
    shader *Sh1 = new shader("TEX");
    
    // Topology
    plane *Pl = new plane(vec(0, 0, 0), vec(500, 0, 0), vec(0, 0, 500), 100, 100);
    
    // Primitives
    prim *Pr = new prim("Klass");
    prim *Plane = new prim(Pl, "Plane");
    
    // Textures
    texture *text = new texture("grass.bmp");
    texture *text1 = new texture("doroga.bmp");
    texture *text2 = new texture("karta2.bmp");

    // Control of bike
    float Angle = 0, Acsel = 0.1, Speed = 0, Pereda4a = 0, rotate = 0;
    
    // Debug
    float rot = 0, xx = 0, yy = 1, zz = 0, x = 0, z = 0;
    
    // Handle camera
    vec Dir = vec(1, 0, 0), Loc = vec(0), CamLoc;

    //sphere *Sky = new sphere(vec(165, 0, 165), 300, 100, 100);
    //texture *text1 = new texture("Sky.bmp");
    //prim *SkyBox = new prim(Sky, "SkyBox", 30 );

    /* Class constructor.
     * ARGUMENT:
     *   - animation interface pointer:
     *       mk5::anim *Ani;
     */
    unit_zorka( VOID )
    {
      delete Pl;
      anim & Ani = anim::Get();
      
      //Loc(-5.13727188, 3.97122955, -0.0465596914); 
      //At(61.9846611, -17.3384933, 0.437863827)
      
      // Load shaders
      Sh->ShaderLoad("OBJ");
      Sh1->ShaderLoad("TEX");

      // Load textures
      text->FromFile("grass.bmp");
      text1->FromFile("doroga.bmp");
      text2->FromFile("karta2.bmp");

      // Add textures
      Ani.Textures.Add(text);
      Ani.Textures.Add(text1);
      Ani.Textures.Add(text2);

      // Shaders
      Ani.Shad.Add(Sh1);
      Ani.Shad.Add(Sh);
      //text1->FromFile("Sky.bmp");
      //SkyBox->mtl->TexKoef = 0.01;
      //Pr->LoadFromFile((CHAR *)"C:\\Users\\MK5\\source\\repos\\T05ANIM\\OBJECTS\\cow.object");
      //SkyBox->mtl->Tex[0] = text1;
      //delete text;
      //Plane->mtl->Tex[0] = text;
      //Ani.Primitives.Add(SkyBox);
      //SkyBox->mtl->Shd = Sh1;
      
      // Topology
      Plane->mtl->Tex[0] = text;
      Plane->mtl->Tex[0]->TexKoef = 30;
      Plane->mtl->Tex[1] = text1;
      Plane->mtl->Tex[2] = text2;
      Plane->mtl->Shd = Sh1;

      // Add to stocks 
      Ani.Primitives.Add(Pr);
      Ani.Primitives.Add(Plane);
      Ani.Objects.Add(Obj);
      Ani.Objects.Add(Obj1);
      Ani.Objects.Add(Obj2);
    }
    /* End of 'unit_test' function */

    /* Default class deconstructor function.
     * ARGUMENTS: None.
     */
    ~unit_zorka( VOID )
    {
    } /* End of '~unit_zorka' function */

    /* Interframe animation response function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani )
    {
      /* Control of bike */
      if (Ani->Keys['Y'] && Pereda4a < 3 )
      {
        Pereda4a += 0.2;
        Acsel -= Acsel / 5;
        Speed -= Speed / 10;
        Ani->Keys['Y'] = 0;
      }

      if (Ani->Keys['U'])
      {
        Acsel /= 1.5;
        Speed /= 1.5;
        Pereda4a /= 1.2;
      }

      if (Ani->Keys['J'])
      {
        x -= 212 * Ani->DeltaTime ;
        if (Angle > -50)
          Angle -= 90 * Ani->DeltaTime, Acsel /= 1.009, Speed /= 1.009;
      }
      else if (Ani->Keys['L'])
      {
        x += 212 * Ani->DeltaTime;

        if (Angle < 50)
          Angle += 90 * Ani->DeltaTime, Acsel /= 1.009, Speed /= 1.009; 
      }
      else
      {
        Angle /= 1.04;
      }

      if (Ani->Keys['I'])
      {
        if (Acsel / Pereda4a< 4 && Speed / Pereda4a < 50)
        {
          Acsel += Pereda4a * Ani->DeltaTime;
          Speed += Acsel;
        }
        //Loc += mth::MATR<FLT>::RotateY(-x) * Dir * Speed;
      }
      else if (Ani->Keys['K'])
      {
        if (Acsel / Pereda4a > -4 && Speed / Pereda4a> -50)
        {
          Acsel -= Pereda4a * Ani->DeltaTime;
          Speed += Acsel;
        }
      }
      else 
      {
        Acsel -= Acsel/46;
        Speed -= Speed/49;
        Pereda4a /= 1.01;
      }
      if (!Ani->Keys['O'])
        Loc = Loc + mth::MATR<FLT>::RotateY(-x) * Dir * Speed * Ani->DeltaTime + mth::MATR<FLT>::RotateY(-x) * Dir * Acsel * Ani->DeltaTime / 2;
     /* End of control of bike */ 

      /* Debug */
      if (Ani->Keys['Z'])
        xx += 1;
      if (Ani->Keys['X'])
        xx -= 1;
      if (Ani->Keys['C'])
        zz += 1;
      if (Ani->Keys['V'])
        zz -= 1;
      if (Ani->Keys['B'])
        rotate += 3;
      if (Ani->Keys['N'])
        yy *= 2;
      if (Ani->Keys['M'])
        yy /= 1.1;

      // Keyboard handle
      if (Ani->Keys[VK_ESCAPE])
	Ani->DoExit();
      if (Ani->KeysClick['F'])
	Ani->FlipFullScreen();
      if (Ani->KeysClick['P'])
	Ani->IsPause = !Ani->IsPause;
      if (Ani->KeysClick[VK_HOME])
	Ani->Cam.At = vec(0);


      //Handle camera
      matr m1, m2;

      Dv += (30 * Ani->Mdy * Ani->Keys[VK_LBUTTON] + 30 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])) * Ani->GlobalDeltaTime;
      Du += (-30 * Ani->Mdx * Ani->Keys[VK_LBUTTON] + 30 * (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT])) * Ani->GlobalDeltaTime;
      Dw += (3 * Ani->Mdz + 3 * Ani->Keys[VK_SHIFT] * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR])) * Ani->GlobalDeltaTime;
      m1 = mth::MATR<FLT>::RotateX(Dv * 0.30);
      m2 = mth::MATR<FLT>::RotateY(Du * 0.30);
      m1 = m1 * m2;
      Ani->Cam.Loc = m1.TransformPoint(vec(0, 0, Dw));
      if (!Ani->Keys[VK_SHIFT])
      {
	vec
	  R = vec(Ani->Cam.View[0][0], Ani->Cam.View[4][0], Ani->Cam.View[8][0]),
	  D = vec(-Ani->Cam.View[2][0], -Ani->Cam.View[6][0], -Ani->Cam.View[10][0]),
	  U = vec(Ani->Cam.View[1][0], Ani->Cam.View[5][0], Ani->Cam.View[9][0]),
	  shift = (R * ((-Ani->Keys['D'] + Ani->Keys['A']) * Dw) +
	    D * ((-Ani->Keys['W'] + Ani->Keys['S']) * Dw) +
	    U * ((Ani->Keys[VK_PRIOR] - Ani->Keys[VK_NEXT]) * Dw / 10.0)) *
	  2.8 * Ani->GlobalDeltaTime;
	Ani->Cam.At += shift;
      }
      Ani->Cam.SetLocAtUp(Ani->Cam.Loc + Ani->Cam.At, Ani->Cam.At, vec(0, 1, 0));

    }

    /* End of 'Response' function */

    /* Render unit function.
     * ARGUMENT:
     *   - animation interface pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani )
    {
      //-0.400002062, 2.04797864, 0.804000199 
      /* Draw houses */
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(0.509999812) * mth::MATR<FLT>::Translate(vec(126, 0, 91)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(6.18004656) * mth::MATR<FLT>::Translate(vec(140, 0, 73)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(11.8001747) * mth::MATR<FLT>::Translate(vec(157, 0, 82)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(0) * mth::MATR<FLT>::Translate(vec(208, 0, 71)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(0.649999678) * mth::MATR<FLT>::Translate(vec(195, 0, 84)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(5.63003397) * mth::MATR<FLT>::Translate(vec(222, 0, 78)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(1068.00000) * mth::MATR<FLT>::Translate(vec(362.000000, 0, 76.0000000)));
      Ani->DrawMatr(Obj, mth::MATR<FLT>::Identity() * mth::MATR<FLT>::RotateY(36) * mth::MATR<FLT>::Translate(vec(52, 0, 89)));
      Ani->DrawMatr(Obj2, mth::MATR<FLT>::Scale(vec(0.287073493)) * mth::MATR<FLT>::Translate(vec(221, 0, 447)));

      Ani->DrawMatr(Obj, mth::MATR<FLT>::Scale(vec(2.97896099)) * mth::MATR<FLT>::RotateY(696.000000) * mth::MATR<FLT>::Translate(vec(386.000000, 0, 157.000000)));
      //Ani->DrawMatr(Obj, mth::MATR<FLT>::Scale(vec(yy)) * mth::MATR<FLT>::RotateY(rotate) * mth::MATR<FLT>::Translate(vec(xx, 0, zz)));

      //Dir = matr::RotateY(CarAngle) * vec(0, 0, 1)  * Ani->DeltaTime * Acsel / 5;
      //Loc += Dir;

      if (!(Loc - CamLoc) > 100)
        CamLoc = Loc - vec(0, 0, 8);
      CamLoc += (Loc - CamLoc) * Ani->DeltaTime * (((!(Loc - CamLoc) - 8)) * 10) * 0.01;
      CamLoc[1] = 4.0f;
      //CamLoc = vec(-0.400002062, 2.04797864, 0.804000199) + Loc;
      Ani->Cam.SetLocAtUp(CamLoc, Loc);// + (mth::MATR<FLT>::RotateY(-x)) * vec(4.26800632, 0.433999747, 0.596000373));
      /* Draw tron */
      Ani->DrawMatr(Obj1, mth::MATR<FLT>::Translate(vec(-0.170000011, 0, -0.779999554)) * mth::MATR<FLT>::RotateX(-90 + Angle) * mth::MATR<FLT>::RotateY(-x) * mth::MATR<FLT>::Translate(vec(0.170000011, 0, 0.779999554)) * mth::MATR<FLT>::Translate(Loc) * mth::MATR<FLT>::Translate(vec(0, 0.671998560, 0)));
      //Ani->Cam.Dir = vec(x, 0, rot);
      //Ani->Cam.At = vec(61.9846611, -17.3384933, 0.437863827);
      //Ani->Cam.Loc = vec(-5.13727188, 3.97122955, -0.0465596914); 
      //Ani->Cam.SetLocAtUp(Ani->Cam.Loc + Ani->Cam.At, Ani->Cam.At, vec(0, 1, 0));

      //Ani->DrawMatr(Obj1, mth::MATR<FLT>::Translate(vec(-z, 0, 0)) * mth::MATR<FLT>::RotateZ(-x) * mth::MATR<FLT>::RotateX(-90) * mth::MATR<FLT>::RotateX(x));
      Ani->DrawMatr(Plane, mth::MATR<FLT>::Identity());
      //Ani->DrawMatr(SkyBox, mth::MATR<FLT>::Identity());
    }
    /* End of 'Render' function */

  }; /* End of 'primitives' class */
} /* end of 'mk5' namespace */

#endif /* __ZORKA_H_ */

/* END OF 'ZORKA.H' FILE */