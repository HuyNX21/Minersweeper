
#ifndef	__CLASS_OBSERVABLEEXECUTOR_H_
#define	__CLASS_OBSERVABLEEXECUTOR_H_

#include <map>
#include <stdint.h>

#include "BLKC_Common.h"
#include "ObservableClassBase.h"

class BLKC_ProxyManager;
class BLKC_ReceiveThreadContext;

class ObservableExecutor
{
	public :
		ObservableExecutor();

		virtual ~ObservableExecutor();

		void exec( BLKC_ProxyManager& proxy_manager, BLKS_COMMONID* type_id, void *pt, void *object_pt, BLKC_ReceiveThreadContext* context );

		static void notifyProxyRcvThFatalCallBack( ushort us_TaskDetailCode, uint64_t ull_NewDetailCode );

	private :
		void buildObservableClassTbl();
	
		typedef std::map<uint32_t, ObservableClassBase*> EXECUTOR_TBL;

		class ObservableClassTbl : public EXECUTOR_TBL
		{
			
			public :
			
				ObservableClassTbl() {}
				~ObservableClassTbl() {}
			
				class Initializer
				{
					public:
						Initializer( EXECUTOR_TBL::mapped_type& reference )
						: mReference( reference )
						{
						}
					
						~Initializer()
						{
						}
					
						template <typename OBSERVABLE_T>
						void operator=( OBSERVABLE_T* pObservableClass )
						{
							typename OBSERVABLE_T::FUNC_CONTAINER::OBSERVER_T* data = NULL;
							mReference = static_cast<EXECUTOR_TBL::mapped_type>( pObservableClass );
							mReference->setObserverType( &typeid(data) );
						}
					
					private:
						EXECUTOR_TBL::mapped_type&	mReference;
				};
				
				Initializer operator[]( const EXECUTOR_TBL::key_type& k )
				{
					return Initializer( EXECUTOR_TBL::operator[](k) );
				}
		};

		ObservableClassTbl mObservableClassTbl;

	
};	// class ObservableExecutor


#endif	//#ifndef	__CLASS_OBSERVABLEEXECUTOR_H_


