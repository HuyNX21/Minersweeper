#ifndef __CLASS_BLKC_CALLBACKPOINTERCONTAINER_H_
#define __CLASS_BLKC_CALLBACKPOINTERCONTAINER_H_

#include <stdint.h>

class BLKC_CallbackPointerContainer
{
	private:
		uint32_t m_id;
		uint32_t m_sessionId;
		void* m_func;
		bool m_regist;
		uint32_t m_full_id;

	public:
		BLKC_CallbackPointerContainer();
		~BLKC_CallbackPointerContainer();

		uint32_t getCbid();
		void setCbid( uint32_t ul_id );

		uint32_t getSessionID();
		void setSessionID( uint32_t ul_sessionId );

		void* getFunc();
		void setFunc( void* p_func );

		bool getRegist();
		void setRegist( bool b_regist );

		uint32_t getFullCbid();
		void setFullCbid( uint32_t ul_id );
};

#endif // #ifndef __CLASS_BLKC_CALLBACKPOINTERCONTAINER_H_
