#ifndef __ENUMBASE_H_
#define __ENUMBASE_H_

#include <string>

class EnumBase
{
	
	public :
		EnumBase(std::string name);
		
		virtual ~EnumBase();

		const char* toString();
		
	private :
		std::string mName;
		
	
};

#endif	// #ifndef __ENUMBASE_H_

