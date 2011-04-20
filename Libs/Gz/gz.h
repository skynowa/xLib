/*****************************************************************************************************
    File:   gz.h
    Author: Igor
    Date:
    Note:

******************************************************************************************************/


#ifndef GZ_H_
#define GZ_H_
//----------------------------------------------------------------------------------------------------
#include <zlib.h>
#include <inttypes.h>
#include <sys/types.h>
//----------------------------------------------------------------------------------------------------
#define BUFLEN          (64 * 1024)

#define GZIP_MAGIC0     0x1F
#define GZIP_MAGIC1     0x8B
#define GZIP_OMAGIC1    0x9E

#define GZIP_TIMESTAMP  (off_t)4
#define GZIP_ORIGNAME   (off_t)10

#define HEAD_CRC        0x02
#define EXTRA_FIELD     0x04
#define ORIG_NAME       0x08
#define COMMENT         0x10

#define OS_CODE         3    /* Unix */
//----------------------------------------------------------------------------------------------------
off_t gz_compress  (int in, int out, const char *origname);
off_t gz_uncompress(int in, int out, char *pre, size_t prelen, off_t *gsizep);
//----------------------------------------------------------------------------------------------------
#endif
