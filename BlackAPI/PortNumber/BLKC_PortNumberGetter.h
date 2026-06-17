
#ifndef __BLKC_PORTNUMBERGETTER_H_
#define __BLKC_PORTNUMBERGETTER_H_

#include "BLKC_PortNumber.h"

#include <string>

class BLKC_PortNumberGetter
{
	public :
		static PORT_NUM_T getThisServerPortNumber();
		static PORT_NUM_T getThatServerPortNumber();

        static const char* createThisServerSocketFile();

		static const char* createThatServerSocketFile();

	private :
		static void makeSocketDirectory();
		static int mkdir_p(const char *path, mode_t mode);

		static std::string mThisServerSocketFile;
		static std::string mThatServerSocketFile;
};

#endif
