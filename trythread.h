#ifndef trythread_h
#define trythread_h
#include <windows.h>

class Thread
{
   public:
      Thread();
      int Start(void * arg);
   
   protected:
      int Run(void * arg);
      static void * EntryPoint(void*);
      virtual void Setup();
      virtual void Execute(void*);
      void * Arg() const 
	  {
		  return Arg_;
	  }
      void Arg(void* a)
	  {
		  Arg_ = a;
	  }
   
   private:
      THREADID ThreadId_;
      void * Arg_;

};

Thread::Thread() {}  //constructor

int Thread::Start(void * arg)
{
   Arg(arg); // store user data
   int code = thread_create(Thread::EntryPoint, this, & ThreadId_);
   return code;
}

int Thread::Run(void * arg)
{
   Setup();
   Execute( arg );
}

/*static */
void * Thread::EntryPoint(void * pthis)
{
   Thread * pt = (Thread*)pthis;
   pthis->Run( Arg() );
}

#endif
