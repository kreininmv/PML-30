/* FILE NAME   : INPUT.H
 * PURPOSE     : Input system.
 *               Handle Module.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.
 */

#ifndef __INPUT_H_
#define __INPUT_H_

#include <cstring>
#include <mmsystem.h>

#include "..//..//BASE/DEF.H"

#pragma comment(lib, "winmm")

/* Joystic axis value obtain macro function */
#define mk5_INPUT_GET_JOYSTICK_AXIS(A) \
  (2.0 * (ji.dw ## A ## pos - jc.w ## A ## min) / (jc.w ## A ## max - jc.w ## A ## min - 1) - 1)

/* Project namespace */
namespace mk5
{
  /* Keyboard handle class */
  class keyboard
  {
  public:
    BYTE
      Keys[256],      /* Current key states */
      OldKeys[256],   /* Previous frame key states */
      KeysClick[256]; /* Click key flags */

                      /* Class constructor */
    keyboard( VOID )
    {
      memset(Keys, 0, 256);
      memset(OldKeys, 0, 256);
      memset(KeysClick, 0, 256);
    } /* End of 'keyboard' function */

    /* Response keyboard input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      GetKeyboardState(Keys);

      for (auto &key : Keys)
        key >>= 7;
      for (INT i = 0; i < 256; i++)
        KeysClick[i] = !OldKeys[i] && Keys[i];
      memcpy(OldKeys, Keys, 256);
    } /* End of 'Response' function */
  }; /* End of 'keyboard' class */

  /* Mouse handle class */
  class mouse
  {
  private:
    /* Window handle */
    HWND hWnd;

    /* Mouse wheel delta value reference */
    INT &MouseWheel;
  public:
    INT
      Mx, My,        /* Mouse cursor position */
      Mz,            /* Mouse wheel absolute value */
      Mdx, Mdy, Mdz; /* Delta values of mouse axes */

    BYTE
      MBut[3],      /* Current mouse button states */
      OldMBut[3],   /* Previous frame mouse button states */
      MButClick[3]; /* Click mouse button flags */

    /* Class constructor.
     * ARGUMENTS:
     *   - window handle value:
     *       HWND hWnd;
     *   - reference to mouse wheel delta value variable:
     *       INT &MouseWheelStoreVariable;
     */
    mouse( HWND hWnd, INT &MouseWheelStoreVariable ) :
      hWnd(hWnd), MouseWheel(MouseWheelStoreVariable),
      Mx(0), My(0), Mz(0), Mdx(0), Mdy(0), Mdz(0)
    {
      memset(MBut, 0, 3);
      memset(OldMBut, 0, 3);
      memset(MButClick, 0, 3);
    } /* End of 'mouse' function */

    /* Response mouse input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      /* Mouse cursor position */
      POINT pt;
      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);
      Mdx = pt.x - Mx;
      Mdy = pt.y - My;
      Mx = pt.x;
      My = pt.y;

      /* Mouse wheel value */
      Mz += MouseWheel;
      Mdz = MouseWheel;
      MouseWheel = 0;

      /* Mouse buttons */
      BYTE keys[256];
      GetKeyboardState(keys);
      MBut[0] = keys[VK_LBUTTON] >>= 7;
      MBut[1] = keys[VK_RBUTTON] >>= 7;
      MBut[2] = keys[VK_MBUTTON] >>= 7;

      for (INT i = 0; i < 3; i++)
        MButClick[i] = !OldMBut[i] && MBut[i];
      memcpy(OldMBut, MBut, 3);

    } /* End of 'Response' function */
  }; /* End of 'mouse' class */

  /* Mouse handle class */
  class joystick
  {
  public:
    BYTE
      JBut[32],       /* Joystick button state */
      OldJBut[32],    /* Previous frame joystick button states */
      JButClick[32];  /* Click joystick button flags */
    INT JPov;         /* Joystick point-of-view control [0,1..8] */
    DBL
      JX, JY, JZ, JR; /* Joystick axes */

                      /* Class constructor */
    joystick( VOID ) :
      JPov(0), JX(0), JY(0), JZ(0), JR(0)
    {
      memset(JBut, 0, 32);
      memset(OldJBut, 0, 32);
      memset(JButClick, 0, 32);
    } /* End of 'joystick' function */

      /* Response joystick input function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      //  VOID Response( VOID )
      //  {
      //    if (joyGetNumDevs() > 0)
      //    {
      //      JOYCAPS jc;
      //
      //      if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
      //      {
      //        JOYINFOEX ji = {sizeof(JOYINFOEX), JOY_RETURNALL};
      //
      //        if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
      //        {
      //          /* Buttons */
      //          for (INT i = 0; i < 32; i++)
      //            JBut[i] = (ji.dwButtons >> i) & 1;
      //          for (INT i = 0; i < 32; i++)
      //            JButClick[i] = !OldJBut[i] && JBut[i];
      //          memcpy(OldJBut, JBut, 32);
      //
      //          /* Axes */
      //          JX = mk5_INPUT_GET_JOYSTICK_AXIS(X);
      //          JY = mk5_INPUT_GET_JOYSTICK_AXIS(Y);
      //          JZ = mk5_INPUT_GET_JOYSTICK_AXIS(Z);
      //          JR = mk5_INPUT_GET_JOYSTICK_AXIS(R);
      //
      //          /* Point-of-view */
      //          JPov = ji.dwPOV == 0xFFFF ? 0 : ji.dwPOV / 4500 + 1;
      //        }
      //      }
      //    }
      //  } /* End of 'Response' function */
  }; /* End of 'joystick' class */

  /* Input system handle class */
  class input : public keyboard, public mouse, public joystick
  {
  public:
    /* Class constructor.
     * ARGUMENTS:
     *   - window handle value:
     *       HWND hWnd;
     *   - reference to mouse wheel delta value variable:
     *       INT &MouseWheelStoreVariable;
     */
    input( HWND hWnd, INT &MouseWheelStoreVariable ) : mouse(hWnd, MouseWheelStoreVariable)
    {
    } /* End of 'input' function */

    /* Response input function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      keyboard::Response();
      mouse::Response();
      //joystick::Response();
    } /* End of 'Response' function */
  }; /* End of 'input' class */
} /* End of 'mk5' namespace */



#endif /* __INPUT_H_ */

  /* END OF 'INPUT.H' FILE */