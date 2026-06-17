
#include "pch.h"

#include "BLKC_Common.h"
#include "BLKC_PortNumberGetter.h"



string BLKC_PortNumberGetter::mThisServerSocketFile;
string BLKC_PortNumberGetter::mThatServerSocketFile;

PORT_NUM_T BLKC_PortNumberGetter::getThisServerPortNumber()
{
	return CLIENT_SERVER_PORT;
}

PORT_NUM_T BLKC_PortNumberGetter::getThatServerPortNumber()
{
	return SERVER_SERVER_PORT;
}

const char* BLKC_PortNumberGetter::createThisServerSocketFile()
{
	makeSocketDirectory();

	mThisServerSocketFile.clear();
	mThisServerSocketFile = SOCKET_FILE_PATH;

	mThisServerSocketFile += SOCKET_FILE_CLIENT;
	return mThisServerSocketFile.c_str();
	
}

const char* BLKC_PortNumberGetter::createThatServerSocketFile()
{
	makeSocketDirectory();
	
	mThatServerSocketFile.clear();
	mThatServerSocketFile = SOCKET_FILE_PATH;

	mThatServerSocketFile += SOCKET_FILE_SERVER;
	return mThatServerSocketFile.c_str();
}

int BLKC_PortNumberGetter::mkdir_p(const char *path, mode_t mode)
{
    char tmp[1024];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);

    if (len > 1 && tmp[len - 1] == '/')
        tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            if (mkdir(tmp, mode) == -1) {
                if (errno != EEXIST) {
                    LOG_ERROR("mkdir('%s') failed: %s", tmp, strerror(errno));
                    return -1;
                }
            }
            *p = '/';
        }
    }

    if (mkdir(tmp, mode) == -1) {
        if (errno != EEXIST) {
            LOG_ERROR("mkdir('%s') failed: %s", tmp, strerror(errno));
            return -1;
        }
    }

    return 0;
}

void BLKC_PortNumberGetter::makeSocketDirectory()
{	
	int result = mkdir_p( SOCKET_FILE_PATH, S_IRWXU | S_IRWXG | S_IRWXO );

	if(result == 0){
		int32_t ret = chmod(  SOCKET_FILE_PATH,  S_IRUSR | S_IWUSR | S_IXUSR | S_IROTH | S_IWOTH | S_IXOTH );
		if( (ret == -1) && (errno != EPERM) ){
			LOG_ERROR("Error chmod folder socket - error : %s", strerror(errno));
			abort();
		}

        sync();

        return;
	}

	if(errno == EEXIST){
		LOG_ERROR("Error mkdir folder EEXIST");
		return;
	}

	LOG_ERROR("Error mkdir folder socket - error : (%d) %s", result, strerror(errno));
	
	abort();
}

