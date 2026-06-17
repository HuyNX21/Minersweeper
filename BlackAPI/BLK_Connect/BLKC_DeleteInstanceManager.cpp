#include "pch.h"
#include "BLKC_DeleteInstanceManager.h"

BLKC_DeleteInstanceManager::BLKC_DeleteInstanceManager()
{
}

BLKC_DeleteInstanceManager::~BLKC_DeleteInstanceManager()
{
}

void BLKC_DeleteInstanceManager::registInstanceMap( uint32_t InstanceID, BLKC_DeleteInstance* p_Instance )
{
	mIdAndInstanceTbl.insert( pair<uint32_t, BLKC_DeleteInstance*>( InstanceID, p_Instance ) );

	mInstanceOrder.push_back( InstanceID );
}

void BLKC_DeleteInstanceManager::deleteInstanceMap( uint32_t InstanceID )
{
	if( mIdAndInstanceTbl.empty() ){
		return;
	}

	BLKC_DeleteInstance* object = findInstance( InstanceID );
	if( object != NULL ){
		delete object;
		mIdAndInstanceTbl.erase( InstanceID );
		mInstanceOrder.remove( InstanceID );
	}
}

void BLKC_DeleteInstanceManager::destoryAllInstance()
{
	if( mIdAndInstanceTbl.empty() ){
		return;
	}

	list<uint32_t>::reverse_iterator rit = mInstanceOrder.rbegin();
	while( rit != mInstanceOrder.rend() )
	{
		BLKC_DeleteInstance* object = findInstance( *rit );
		if( object != NULL ){
			object->destoryInstance();
			delete object;
		}
		++rit;
	}

	mIdAndInstanceTbl.clear();
	mInstanceOrder.clear();
}

BLKC_DeleteInstance*  BLKC_DeleteInstanceManager::findInstance( uint32_t InstanceID )
{
	BLKC_DeleteInstance* object = NULL;

	map<uint32_t, BLKC_DeleteInstance*>::iterator it = mIdAndInstanceTbl.find( InstanceID );
	map<uint32_t, BLKC_DeleteInstance*>::iterator it_end = mIdAndInstanceTbl.end();
	if( it != it_end ){
		object = (*it).second;
	}
	return object;
}

void BLKC_DeleteInstanceManager::dump_deleteInsTbl( int mode )
{
	if ( mode == 1 ) {
		map<uint32_t, BLKC_DeleteInstance*>::iterator it = mIdAndInstanceTbl.begin();
		while( it != mIdAndInstanceTbl.end() ) {
			BLKC_DeleteInstance* object = (*it).second;
			object->outputLog( (*it).first );
			++it;
		}
	}
}
