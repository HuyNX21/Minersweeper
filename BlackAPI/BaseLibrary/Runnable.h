#ifndef __CLASS_RUNNABLE_H_
#define __CLASS_RUNNABLE_H_

class Runnable
{
	public:
		Runnable();
		
		virtual ~Runnable() = 0;
		
		virtual void run() = 0;
	
	
};

#endif	// #ifndef __CLASS_RUNNABLE_H_

