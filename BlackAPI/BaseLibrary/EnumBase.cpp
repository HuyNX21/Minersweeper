#include "EnumBase.h"

EnumBase::EnumBase(std::string name)
{
	mName = name;
}

EnumBase::~EnumBase()
{
}


const char* EnumBase::toString()
{
	return mName.c_str();

}