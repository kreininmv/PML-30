/* FILE NAME   : TIMER.H
 * PURPOSE     : Timer system.
 *               HeaderModule.
 * PROGRAMMER  : CGSG'2018
 *               MK5.
 * LAST UPDATE : 25.07.2018
 * NOTE        : Module namespace 'mk5'.                  
 */

#ifndef __TIMER_H_
#define __TIMER_H_

#include "..\\..\\BASE\DEF.H"

/* Project namespace */
namespace mk5
{
  /* Timer handle class */
  class timer
  {
  private:
    /* Timer local data */
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Time from program start to previous frame */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */
  public:
    /* Timer data */
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frames per seond value */
    BOOL IsPause;                  /* Pause flag */

                                   /* Default timer constructor */
    timer( VOID ) :
      FrameCounter(0), GlobalTime(0), GlobalDeltaTime(0), Time(0), DeltaTime(0),
      PauseTime(0), FPS(59.30), IsPause(FALSE)
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
    } /* End of 'timer' function */

      /* Interframe timer response function.
      * ARGUMENTS: None.
      * RETURN: None.
      */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;

      QueryPerformanceCounter(&t);

      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;

      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      OldTime = t.QuadPart;

      /* FPS */
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);

        //OutputDebugString((std::to_string(FPS) + "\n").c_str());
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }

      /* Increment frame counter */
      FrameCounter++;
    } /* End of 'Response' function */
  }; /* End of 'timer' class */
} /* end of 'mk5' namespace */

#endif /* __TIMER_H_ */

  /* END OF 'TIMER.H' FILE */
