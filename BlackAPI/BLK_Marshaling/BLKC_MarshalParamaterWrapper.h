#if !defined(__BLKC_MARSHALPARAMATERWRAPPER_H__)
#define	__BLKC_MARSHALPARAMATERWRAPPER_H__

#include "BLKC_Common.h"
#include <string>

template<typename ARRAY_T>
class BLKC_NullEndArray
{
private:
	short mSize;
	ARRAY_T* mDataptr;
	void calcDataSize();
	bool mIsNewArray;
public:
	BLKC_NullEndArray(ARRAY_T* dataptr);
	BLKC_NullEndArray();
	virtual ~BLKC_NullEndArray();
	short getSize();
	ARRAY_T* getDataptr();
	void setDataptr(ARRAY_T* dataptr);
	void newArray(ARRAY_T*& array, short size);
	void deleteArray();
};

template<typename ARRAY_T> 
BLKC_NullEndArray<ARRAY_T>::BLKC_NullEndArray(ARRAY_T* dataptr) : mSize(0) , mDataptr(dataptr), mIsNewArray(false)
{
	calcDataSize();
}

template<typename ARRAY_T> 
BLKC_NullEndArray<ARRAY_T>::BLKC_NullEndArray() : mSize(0) , mDataptr(NULL), mIsNewArray(false)
{
}

template<typename ARRAY_T> 
BLKC_NullEndArray<ARRAY_T>::~BLKC_NullEndArray()
{
	deleteArray();
}

template<typename ARRAY_T> 
void BLKC_NullEndArray<ARRAY_T>::calcDataSize()
{
	if( mDataptr != NULL ){
		ARRAY_T* tmpptr = mDataptr;
		for(mSize=0; *tmpptr!=NULL;mSize++, tmpptr++)
		{
		}
	}
}

template<typename ARRAY_T>
short BLKC_NullEndArray<ARRAY_T>::getSize()
{
	return (short)(mSize+1);  
}

template<typename ARRAY_T>
ARRAY_T* BLKC_NullEndArray<ARRAY_T>::getDataptr()
{
	return mDataptr;
}

template<typename ARRAY_T>
void BLKC_NullEndArray<ARRAY_T>::setDataptr(ARRAY_T* dataptr)
{
	mDataptr = dataptr;
	calcDataSize();
}

template<typename ARRAY_T>
void BLKC_NullEndArray<ARRAY_T>::newArray(ARRAY_T*& array, short size)
{
	array = new ARRAY_T[size];

	mDataptr = array;
	mSize = size - 1;

	mIsNewArray = true;
}

template<typename ARRAY_T>
void BLKC_NullEndArray<ARRAY_T>::deleteArray()
{
	if( mIsNewArray )
	{
		mIsNewArray = false;
		if( mDataptr != NULL )
		{
			delete [] mDataptr;
			mDataptr = NULL;
			mSize = 0;
		}
	}
}


template<typename ARRAY_T>
class BLKC_SizeArray
{
private:
	short mSize;
	ARRAY_T* mDataptr;
	void calcDataSize(short s_datasize);
	bool mIsNewArray;
public:
	BLKC_SizeArray(ARRAY_T* dataptr);
	BLKC_SizeArray();
	virtual ~BLKC_SizeArray();
	short getSize();
	ARRAY_T* getDataptr();
	bool isNewArray();
	void setDataptr(ARRAY_T* dataptr , short s_datasize);
	void newArray(ARRAY_T*& array, short size);
	void deleteArray();
};

template<typename ARRAY_T> 
BLKC_SizeArray<ARRAY_T>::BLKC_SizeArray(ARRAY_T* dataptr) : mSize(0) , mDataptr(dataptr), mIsNewArray(false)
{
	calcDataSize(0);
}

template<typename ARRAY_T> 
BLKC_SizeArray<ARRAY_T>::BLKC_SizeArray() : mSize(0) , mDataptr(NULL), mIsNewArray(false)
{
}

template<typename ARRAY_T> 
BLKC_SizeArray<ARRAY_T>::~BLKC_SizeArray()
{
	deleteArray();
}

template<typename ARRAY_T>
short BLKC_SizeArray<ARRAY_T>::getSize()
{
	return mSize;
}

template<typename ARRAY_T>
ARRAY_T* BLKC_SizeArray<ARRAY_T>::getDataptr()
{
	return mDataptr;
}

template<typename ARRAY_T>
bool BLKC_SizeArray<ARRAY_T>::isNewArray()
{
	return mIsNewArray;
}

template<typename ARRAY_T>
void BLKC_SizeArray<ARRAY_T>::setDataptr(ARRAY_T* dataptr , short s_datasize )
{
	mDataptr = dataptr;
	calcDataSize(s_datasize);
}
template<typename ARRAY_T> 
void BLKC_SizeArray<ARRAY_T>::calcDataSize(short s_datasize)
{

	mSize = ( mDataptr == NULL )?0:s_datasize;
}

template<typename ARRAY_T>
void BLKC_SizeArray<ARRAY_T>::newArray(ARRAY_T*& array, short size)
{
	array = new ARRAY_T[size];
	setDataptr(array, size);
	mIsNewArray = true;
}

template<typename ARRAY_T>
void BLKC_SizeArray<ARRAY_T>::deleteArray()
{
	if( mIsNewArray )
	{
		mIsNewArray = false;
		if( mDataptr != NULL )
		{
			delete [] mDataptr;
			mDataptr = NULL;
			mSize = 0;
		}
	}
}

class BLKC_SpecificConversion
{
private:
	char mID;
	void* mAddrptr;

public:
	BLKC_SpecificConversion(){}
	void setAddrptr(char c_id, void* vp_addrptr);
	void* getAddrptr(char* c_id);
};

#endif //#if !defined(__BLKC_MARSHALPARAMATERWRAPPER_H__)
