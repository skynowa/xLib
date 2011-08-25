/**
 * \file  CxGz.cpp
 * \brief gz
 */


#include <xLib/Compress/Linux/CxGz.h>

#if defined(xOS_WIN)

#elif defined(xOS_LINUX)
    //-lz
#endif


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxGz
CxGz::CxGz() {

}
//---------------------------------------------------------------------------
//DONE: ~CxGz
/*virtual*/
CxGz::~CxGz() {

}
//---------------------------------------------------------------------------
//DONE: bCompress ()
BOOL
CxGz::bCompress(INT iFileIn, INT iFileOut, const std::tstring &csOriginName) {
    /*DEBUG*/xASSERT_RET(- 1   != iFileIn,              FALSE);
    /*DEBUG*/xASSERT_RET(- 1   != iFileOut,             FALSE);
    /*DEBUG*/xASSERT_RET(false == csOriginName.empty(), FALSE);

    off_t liRes = _liCompress(iFileIn, iFileOut, csOriginName.c_str());
    /*DEBUG*/xASSERT_RET(liRes > 0, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUncompress ()
BOOL
CxGz::bUncompress(INT iFileIn, INT iFileOut) {
    /*DEBUG*/xASSERT_RET(- 1   != iFileIn,  FALSE);
    /*DEBUG*/xASSERT_RET(- 1   != iFileOut, FALSE);

    off_t liRes = _liUncompress(iFileIn, iFileOut, NULL, 0, NULL);
    /*DEBUG*/xASSERT_RET(- 1 != liRes, FALSE);

    return TRUE;
}
//----------------------------------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//----------------------------------------------------------------------------------------------------
//DONE: _liCompress
off_t
CxGz::_liCompress(int iFileIn, int iFileOut, const char *pcszOriginName) {
    static int numflag = 6;        /* gzip -1..-9 value */

    z_stream   z       = {0};
    char      *outbufp = NULL;
    char      *inbufp  = NULL;
    off_t      in_tot  = 0;
    off_t      out_tot = 0;
    ssize_t    in_size = 0;
    int        i       = 0;
    int        error   = 0;
    uLong      crc     = 0;


    outbufp = (char *)malloc(BUFLEN);
    inbufp  = (char *)malloc(BUFLEN);
    if (outbufp == NULL || inbufp == NULL) {
        //maybe_err("malloc failed");
        goto out;
    }

    memset(&z, 0, sizeof z);
    z.zalloc = Z_NULL;
    z.zfree  = Z_NULL;
    z.opaque = 0;

    i = snprintf(outbufp, BUFLEN,
                 "%c%c%c%c%c%c%c%c%c%c%s",
                 GZIP_MAGIC0, GZIP_MAGIC1, Z_DEFLATED,
                 *pcszOriginName ? ORIG_NAME : 0,
                 0, 0, 0, 0,
                 0, OS_CODE, pcszOriginName);
    if (i >= BUFLEN) {
        /* this need PATH_MAX > BUFLEN ... */
        //maybe_err("snprintf");
        in_tot = - 1;

        goto out;
    }

    if (*pcszOriginName) {
        i++;
    }

    z.next_out  = (unsigned char *)outbufp + i;
    z.avail_out = BUFLEN - i;

    error = deflateInit2(&z, numflag, Z_DEFLATED, (-MAX_WBITS), 8, Z_DEFAULT_STRATEGY);
    if (error != Z_OK) {
        //maybe_warnx("deflateInit2 failed");
        in_tot = -1;

        goto out;
    }

    crc = crc32(0L, Z_NULL, 0);
    for (;;) {
        if (z.avail_out == 0) {
            if (write(iFileOut, outbufp, BUFLEN) != BUFLEN) {
                //maybe_warn("write");
                out_tot = -1;

                goto out;
            }

            out_tot += BUFLEN;
            z.next_out  = (unsigned char *)outbufp;
            z.avail_out = BUFLEN;
        }

        if (z.avail_in == 0) {
            in_size = read(iFileIn, inbufp, BUFLEN);
            if (in_size < 0) {
                //maybe_warn("read");
                in_tot = -1;

                goto out;
            }

            if (in_size == 0) {
                break;
            }

            crc = crc32(crc, (const Bytef *)inbufp, (unsigned)in_size);

            in_tot += in_size;
            z.next_in  = (unsigned char *)inbufp;
            z.avail_in = in_size;
        }

        error = deflate(&z, Z_NO_FLUSH);
        if (Z_OK != error && Z_STREAM_END != error) {
            //maybe_warnx("deflate failed");
            in_tot = -1;

            goto out;
        }
    }

    /* clean up */
    for (;;) {
        size_t len;
        ssize_t w;

        error = deflate(&z, Z_FINISH);
        if (error != Z_OK && error != Z_STREAM_END) {
            //maybe_warnx("deflate failed");
            in_tot = -1;

            goto out;
        }

        len = (char *)z.next_out - outbufp;

        w = write(iFileOut, outbufp, len);
        if (w == -1 || (size_t)w != len) {
            //maybe_warn("write");
            out_tot = -1;

            goto out;
        }
        out_tot += len;
        z.next_out  = (unsigned char *)outbufp;
        z.avail_out = BUFLEN;

        if (Z_STREAM_END == error) {
            break;
        }
    }

    if (deflateEnd(&z) != Z_OK) {
        //maybe_warnx("deflateEnd failed");
        in_tot = -1;

        goto out;
    }

    i = snprintf(outbufp, BUFLEN,
                 "%c%c%c%c%c%c%c%c",
                 (int)crc            & 0xff,
                 (int)(crc >> 8)     & 0xff,
                 (int)(crc >> 16)    & 0xff,
                 (int)(crc >> 24)    & 0xff,
                 (int)in_tot         & 0xff,
                 (int)(in_tot >> 8)  & 0xff,
                 (int)(in_tot >> 16) & 0xff,
                 (int)(in_tot >> 24) & 0xff);
    if (i != 8) {
        //maybe_err("snprintf");
    }

    if (write(iFileOut, outbufp, i) != i) {
        //maybe_warn("write");
        in_tot = -1;
    } else {
        out_tot += i;
    }

out:
    if (inbufp != NULL) {
        free(inbufp);
    }

    if (outbufp != NULL) {
        free(outbufp);
    }

    return in_tot;
}
//----------------------------------------------------------------------------------------------------
//DONE: _liUncompress
off_t
CxGz::_liUncompress(INT iFileIn, INT iFileOut, char *pszPre, size_t uiPreLen, off_t *pliGsizep) {
    #define ADVANCE()  { z.next_in ++; z.avail_in --; }

    enum EState {
        GZSTATE_MAGIC0,
        GZSTATE_MAGIC1,
        GZSTATE_METHOD,
        GZSTATE_FLAGS,
        GZSTATE_SKIPPING,
        GZSTATE_EXTRA,
        GZSTATE_EXTRA2,
        GZSTATE_EXTRA3,
        GZSTATE_ORIGNAME,
        GZSTATE_COMMENT,
        GZSTATE_HEAD_CRC1,
        GZSTATE_HEAD_CRC2,
        GZSTATE_INIT,
        GZSTATE_READ,
        GZSTATE_CRC,
        GZSTATE_LEN
    };

    z_stream  z            = {0};
    char     *outbufp      = NULL;
    char     *inbufp       = NULL;
    off_t     out_tot      = -1;
    off_t     in_tot       = 0;
    uint32_t  out_sub_tot  = 0;
    EState    stState      = GZSTATE_MAGIC0;
    int       flags        = 0;
    int       skip_count   = 0;
    int       error        = Z_STREAM_ERROR;
    int       done_reading = 0;
    uLong     crc          = 0;
    ssize_t   wr           = 0;
    int       needmore     = 0;


    outbufp = (char *)malloc(BUFLEN);
    if (NULL == outbufp) {
        //maybe_err("malloc failed");
        goto out2;
    }

    inbufp = (char *)malloc(BUFLEN);
    if (NULL == inbufp) {
        //maybe_err("malloc failed");
        goto out1;
    }

    z.avail_in  = uiPreLen;
    z.next_in   = (unsigned char *)pszPre;
    z.avail_out = BUFLEN;
    z.next_out  = (unsigned char *)outbufp;
    z.zalloc    = NULL;
    z.zfree     = NULL;
    z.opaque    = 0;

    in_tot  = uiPreLen;
    out_tot = 0;

    for (;;) {
        if ((z.avail_in == 0 || needmore) && done_reading == 0) {
            ssize_t in_size;

            if (z.avail_in > 0) {
                memmove(inbufp, z.next_in, z.avail_in);
            }

            z.next_in = (unsigned char *)inbufp;
            in_size = read(iFileIn, z.next_in + z.avail_in, BUFLEN - z.avail_in);
            if (in_size == -1) {
                //maybe_warn("failed to read stdin");
                goto stop_and_fail;
            } else if (in_size == 0) {
                done_reading = 1;
            }

            z.avail_in += in_size;
            needmore = 0;

            in_tot += in_size;
        }

        if (z.avail_in == 0) {
            if (done_reading && stState != GZSTATE_MAGIC0) {
                //maybe_warnx("unexpected end of file");
                goto stop_and_fail;
            }

            goto stop;
        }

        switch (stState) {
            case GZSTATE_MAGIC0:
                if (*z.next_in != GZIP_MAGIC0) {
                    if (in_tot > 0) {
                        //maybe_warnx("trailing garbage ignored");
                        goto stop;
                    }
                    //maybe_warnx("input not gziped (MAGIC0)");
                    goto stop_and_fail;
                }
                ADVANCE();
                xENUM_ENC(EState, stState);
                out_sub_tot = 0;
                crc = crc32(0L, Z_NULL, 0);
                break;

            case GZSTATE_MAGIC1:
                if (*z.next_in != GZIP_MAGIC1 &&
                    *z.next_in != GZIP_OMAGIC1) {
                    //maybe_warnx("input not gziped (MAGIC1)");
                    goto stop_and_fail;
                }
                ADVANCE();
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_METHOD:
                if (*z.next_in != Z_DEFLATED) {
                    //maybe_warnx("unknown compression method");
                    goto stop_and_fail;
                }
                ADVANCE();
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_FLAGS:
                flags = *z.next_in;
                ADVANCE();
                skip_count = 6;
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_SKIPPING:
                if (skip_count > 0) {
                    skip_count--;
                    ADVANCE();
                } else {
                    xENUM_ENC(EState, stState);
                }
                break;

            case GZSTATE_EXTRA:
                if ((flags & EXTRA_FIELD) == 0) {
                    stState = GZSTATE_ORIGNAME;
                    break;
                }
                skip_count = *z.next_in;
                ADVANCE();
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_EXTRA2:
                skip_count |= ((*z.next_in) << 8);
                ADVANCE();
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_EXTRA3:
                if (skip_count > 0) {
                    skip_count--;
                    ADVANCE();
                } else {
                    xENUM_ENC(EState, stState);
                }
                break;

            case GZSTATE_ORIGNAME:
                if ((flags & ORIG_NAME) == 0) {
                    xENUM_ENC(EState, stState);
                    break;
                }
                if (*z.next_in == 0) {
                    xENUM_ENC(EState, stState);
                }
                ADVANCE();
                break;

            case GZSTATE_COMMENT:
                if ((flags & COMMENT) == 0) {
                    xENUM_ENC(EState, stState);
                    break;
                }
                if (*z.next_in == 0) {
                    xENUM_ENC(EState, stState);
                }
                ADVANCE();
                break;

            case GZSTATE_HEAD_CRC1:
                if (flags & HEAD_CRC) {
                    skip_count = 2;
                } else {
                    skip_count = 0;
                }
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_HEAD_CRC2:
                if (skip_count > 0) {
                    skip_count--;
                    ADVANCE();
                } else {
                    xENUM_ENC(EState, stState);
                }
                break;

            case GZSTATE_INIT:
                if (inflateInit2(&z, -MAX_WBITS) != Z_OK) {
                    //maybe_warnx("failed to inflateInit");
                    goto stop_and_fail;
                }
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_READ:
                error = inflate(&z, Z_FINISH);
                switch (error) {
                    /* Z_BUF_ERROR goes with Z_FINISH... */
                    case Z_BUF_ERROR:
                    case Z_STREAM_END:
                    case Z_OK:
                        break;

                    case Z_NEED_DICT:
                        //maybe_warnx("Z_NEED_DICT error");
                        goto stop_and_fail;
                    case Z_DATA_ERROR:
                        //maybe_warnx("data stream error");
                        goto stop_and_fail;
                    case Z_STREAM_ERROR:
                        //maybe_warnx("internal stream error");
                        goto stop_and_fail;
                    case Z_MEM_ERROR:
                        //maybe_warnx("memory allocation error");
                        goto stop_and_fail;

                    //default:
                        //maybe_warn("unknown error from inflate(): %d", error);
                }
                wr = BUFLEN - z.avail_out;

                if (wr != 0) {
                    crc = crc32(crc, (const Bytef *)outbufp, (unsigned)wr);
                    if ( write(iFileOut, outbufp, wr) != wr) {
                        //maybe_warn("error writing to output");
                        goto stop_and_fail;
                    }

                    out_tot += wr;
                    out_sub_tot += wr;
                }

                if (error == Z_STREAM_END) {
                    inflateEnd(&z);
                    xENUM_ENC(EState, stState);
                }

                z.next_out = (unsigned char *)outbufp;
                z.avail_out = BUFLEN;

                break;

            case GZSTATE_CRC:
                {
                    uLong origcrc;

                    if (z.avail_in < 4) {
                        if (!done_reading) {
                            needmore = 1;
                            continue;
                        }
                        //maybe_warnx("truncated input");
                        goto stop_and_fail;
                    }
                    origcrc = ((unsigned)z.next_in[0] & 0xff)       |
                              ((unsigned)z.next_in[1] & 0xff) << 8  |
                              ((unsigned)z.next_in[2] & 0xff) << 16 |
                              ((unsigned)z.next_in[3] & 0xff) << 24;
                    if (origcrc != crc) {
                        //maybe_warnx("invalid compressed data--crc error");
                        goto stop_and_fail;
                    }
                }

                z.avail_in -= 4;
                z.next_in += 4;

                if (!z.avail_in && done_reading) {
                    goto stop;
                }
                xENUM_ENC(EState, stState);
                break;

            case GZSTATE_LEN:
                {
                    uLong origlen;

                    if (z.avail_in < 4) {
                        if (!done_reading) {
                            needmore = 1;
                            continue;
                        }
                        //maybe_warnx("truncated input");
                        goto stop_and_fail;
                    }
                    origlen = ((unsigned)z.next_in[0] & 0xff)       |
                              ((unsigned)z.next_in[1] & 0xff) << 8  |
                              ((unsigned)z.next_in[2] & 0xff) << 16 |
                              ((unsigned)z.next_in[3] & 0xff) << 24;

                    if (origlen != out_sub_tot) {
                        //maybe_warnx("invalid compressed data--length error");
                        goto stop_and_fail;
                    }
                }

                z.avail_in -= 4;
                z.next_in += 4;

                if (error < 0) {
                    //maybe_warnx("decompression error");
                    goto stop_and_fail;
                }

                stState = GZSTATE_MAGIC0;

                break;
        } //switch (stState)

        continue;

stop_and_fail:
        out_tot = -1;

stop:
        break;
    }

    if (stState > GZSTATE_INIT) {
        inflateEnd(&z);
    }

    free(inbufp);

out1:
    free(outbufp);

out2:
    if (pliGsizep) {
        *pliGsizep = in_tot;
    }

    return out_tot;
}
//----------------------------------------------------------------------------------------------------

