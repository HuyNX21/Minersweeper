#include "pch.h"
#include "BLKC_CallbackPointerContainer.h"

BLKC_CallbackPointerContainer::BLKC_CallbackPointerContainer()
{
	m_id = 0;
	m_sessionId = 0;
	m_func = NULL;
	m_regist = false;
	m_full_id = 0;
}

BLKC_CallbackPointerContainer::~BLKC_CallbackPointerContainer()
{
}

uint32_t BLKC_CallbackPointerContainer::getCbid()
{
	return m_id;
}

void BLKC_CallbackPointerContainer::setCbid( uint32_t ul_id )
{
	m_id = ul_id;
}

uint32_t BLKC_CallbackPointerContainer::getSessionID()
{
	return m_sessionId;
}

void BLKC_CallbackPointerContainer::setSessionID( uint32_t ul_sessionId )
{
	m_sessionId = ul_sessionId;
}

void* BLKC_CallbackPointerContainer::getFunc()
{
	return m_func;
}

void BLKC_CallbackPointerContainer::setFunc( void* p_func )
{
	m_func = p_func;
}

bool BLKC_CallbackPointerContainer::getRegist()
{
	return m_regist;
}

void BLKC_CallbackPointerContainer::setRegist( bool b_regist )
{
	m_regist = b_regist;
}

uint32_t BLKC_CallbackPointerContainer::getFullCbid()
{
	return m_full_id;
}

void BLKC_CallbackPointerContainer::setFullCbid( uint32_t ul_id )
{
	m_full_id = ul_id;
}
