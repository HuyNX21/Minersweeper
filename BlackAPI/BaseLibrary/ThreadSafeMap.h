#ifndef __CLASS_THREADSAFEMAP_H_
#define __CLASS_THREADSAFEMAP_H_

#include <map>

#include "MutexLock.h"


template<typename THIS_KEY_T, typename THIS_VALUE_T> 
class ThreadSafeMap
{
	
	
	public :

		typedef std::map<THIS_KEY_T, THIS_VALUE_T>   MAP_T;
	
		ThreadSafeMap();

		ThreadSafeMap(MutexLock::MUTEX_TYPE type);
	
		virtual ~ThreadSafeMap();
	
		bool insert( THIS_KEY_T key, const THIS_VALUE_T& val );

		bool erase( THIS_KEY_T key );
		
		bool empty();

		unsigned int size();
		
		bool clear();
		
		unsigned int count( THIS_KEY_T key );

		bool find( THIS_KEY_T key, THIS_VALUE_T& val );

		MAP_T& reference();
	
		MutexLock& mutex();
		

	private :
		
		typedef typename MAP_T::iterator IT_T;
		typedef typename MAP_T::value_type PAIR_T;
	
		MAP_T mMap;
		
		MutexLock mMutex;
	
};

template<typename THIS_KEY_T, typename THIS_VALUE_T>
ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::ThreadSafeMap()
{
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::ThreadSafeMap(MutexLock::MUTEX_TYPE type) // 2018/08/24 APF AR.1026585 BlackAPI動的スレッド生成見直し（PaperCut対応）.
: mMutex(type)
{
}
	
template<typename THIS_KEY_T, typename THIS_VALUE_T>
ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::~ThreadSafeMap()
{
}
	
template<typename THIS_KEY_T, typename THIS_VALUE_T>
bool ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::insert( THIS_KEY_T key, const THIS_VALUE_T& val )
{
	std::pair<IT_T,bool> result;

	ScopeLock lock(mMutex);

	result = mMap.insert( PAIR_T(key, val) );

	return result.second;
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
bool ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::erase( THIS_KEY_T key )
{
	ScopeLock lock(mMutex);

	mMap.erase( key );
	
	return true;
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
bool ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::empty()
{
	ScopeLock lock(mMutex);
	
	return mMap.empty();
	
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
unsigned int ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::size()
{
	ScopeLock lock(mMutex);
	
	return mMap.size();
	
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
bool ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::clear()
{
	ScopeLock lock(mMutex);
	
	mMap.clear();
	return true;
}


template<typename THIS_KEY_T, typename THIS_VALUE_T>
unsigned int ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::count( THIS_KEY_T key )
{
	ScopeLock lock( mMutex );
	
	return (unsigned int)mMap.count( key );
	
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
bool ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::find( THIS_KEY_T key, THIS_VALUE_T& val )
{
	ScopeLock lock( mMutex );
	
	IT_T it = mMap.find( key );
	IT_T it_end = mMap.end();
	
	if(it != it_end){
		val = (*it).second;
		return true;
	}else{
		return false;
	}
}

template<typename THIS_KEY_T, typename THIS_VALUE_T>
typename ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::MAP_T& ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::reference()
{
	return mMap;
}
	
template<typename THIS_KEY_T, typename THIS_VALUE_T> 
MutexLock& ThreadSafeMap<THIS_KEY_T, THIS_VALUE_T>::mutex()
{
	return mMutex;
}


#endif // #ifndef __CLASS_THREADSAFEMAP_H_


