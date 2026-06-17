#ifndef __CLASS_ALLOCATEMEMORY_H_
#define __CLASS_ALLOCATEMEMORY_H_

#include <string>
#include <exception>

#include "BLKC_Log.h"

using namespace std;

template<typename T> class AllocateMemory
{
	public:
		AllocateMemory(uint32_t size);
		AllocateMemory(uint32_t size, string& name);
		virtual ~AllocateMemory();
		T* allocate();
		void clear(T val=0);
		T* getTopAddress();
		T* getFinalElementAddress();
		T* getElementAddress(uint32_t num);
		void release();
		uint32_t getSizeOfElement();
		T& operator[](uint32_t index); 
		uint32_t getTotalMemorySize();
		
	protected:
	private:
		AllocateMemory(AllocateMemory<T>&);
		uint32_t mElementCnt;
		uint32_t mMemorySize;
		T* mTopAddress;
		T* mFinalElementAddress;
		string *mName;
	
};


template<typename T> AllocateMemory<T>::AllocateMemory(uint32_t size)
:mElementCnt(size), mTopAddress(NULL), mFinalElementAddress(NULL), mName(NULL)

{
	mMemorySize = (uint32_t)(mElementCnt * sizeof(T));
}

template<typename T> AllocateMemory<T>::AllocateMemory(uint32_t size, string& name)
:mElementCnt(size), mTopAddress(NULL), mFinalElementAddress(NULL), mName(NULL)
{
	mMemorySize = mElementCnt * sizeof(T);
	mName = new string(name);
}

template<typename T> AllocateMemory<T>::AllocateMemory(AllocateMemory<T>& arg)
{
	
}

template<typename T> AllocateMemory<T>::~AllocateMemory()
{
	release();
	
}
		
template<typename T> T* AllocateMemory<T>::allocate()
{
	
	try{
		if(mTopAddress == NULL){
			mTopAddress = new T [mElementCnt];
			mFinalElementAddress = mTopAddress + (mElementCnt - 1);
		}
	}catch(exception &ex){
		mTopAddress = NULL;
		mFinalElementAddress = NULL;
	}
	return mTopAddress;
}
		
template<typename T> void AllocateMemory<T>::clear(T val)
{
	T* pt = mTopAddress;
	
	for(uint32_t i = 0;i < mElementCnt;i++){
		*(pt+i) = val;
	}
}

template<typename T> T* AllocateMemory<T>::getTopAddress()
{
	
	return mTopAddress;
	
}

template<typename T> T* AllocateMemory<T>::getFinalElementAddress()
{
	
	return mFinalElementAddress;

}

template<typename T> T* AllocateMemory<T>::getElementAddress(uint32_t num)
{
	T* ret = NULL;
	
	if(mTopAddress == NULL){
		return ret;
	}
	if(num >= mElementCnt){
		LOG_ERROR("malloc failed.\n");
		return ret;
	}

	ret = mTopAddress + num;

	return ret;
}

template<typename T> T& AllocateMemory<T>::operator[](uint32_t index)
{
	
	return *(this->getElementAddress(index));
}


template<typename T> void AllocateMemory<T>::release()
{
	if(mTopAddress != NULL){
		delete [] mTopAddress;
		mTopAddress = NULL;
		mFinalElementAddress = NULL;
	}
	if(mName != NULL){
		delete mName;
	}
	
}

template<typename T> uint32_t AllocateMemory<T>::getSizeOfElement()
{
	return (uint32_t)sizeof(T);
}

template<typename T> uint32_t AllocateMemory<T>::getTotalMemorySize()
{
	return mMemorySize;
}


#endif	// #ifndef __CLASS_ALLOCATEMEMORY_H_


