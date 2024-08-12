using namespace System;
using namespace System::Threading;

// Simple threading scenario:  Start a Shared method running
// on a second thread.
public ref class ThreadExample
{
public:

   // The ThreadProc method is called when the thread starts.
   // It loops ten times, writing to the console and yielding 
   // the rest of its time slice each time, and then ends.
   static void ThreadProc()
   {
      for ( int i = 0; i < 10; i++ )
      {


         // Yield the rest of the time slice.
         Thread::Sleep( 0 );

      }
   }

};

