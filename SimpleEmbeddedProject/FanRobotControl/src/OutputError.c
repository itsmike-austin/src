/* ==========================================================================
 * OutputError:
 *    The OutputError module has a single method:
 *        OutputError: Used to send an error message to syslog
 *
 *        void OutputError(char* pSource):
 *             pSource should be a unique identifier to mark the specific
 *             location where the error occurred for debugging.
 *
 * --------------------------------------------------------------------------
 * (c) 2000 itsinc (mdb)
 *          Updated over time whenever additional errno members have appeared
 * ========================================================================== */

#include "OutputError.h"

void OutputError(char* pSource)
{
  char pErrMsg[256];
  switch( errno ) {
  case E2BIG:
    sprintf(pErrMsg,"%s","%s: E2BIG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EACCES:
    sprintf(pErrMsg,"%s","%s: EACCESS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EADDRINUSE:
    sprintf(pErrMsg,"%s","%s: EADDRINUSE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EADDRNOTAVAIL:
    sprintf(pErrMsg,"%s","%s: EADDRNOTAVAIL");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EAGAIN:
    sprintf(pErrMsg,"%s","%s: EAGAIN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EALREADY:
    sprintf(pErrMsg,"%s","%s: EALREADY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADE:
    sprintf(pErrMsg,"%s","%s: EBADE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADF:
    sprintf(pErrMsg,"%s","%s: EBADF");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADFD:
    sprintf(pErrMsg,"%s","%s: EBADFD");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADMSG:
    sprintf(pErrMsg,"%s","%s: EBADMSG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADR:
    sprintf(pErrMsg,"%s","%s: EBADR");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADRQC:
    sprintf(pErrMsg,"%s","%s: EBADRQC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBADSLT:
    sprintf(pErrMsg,"%s","%s: EBADSLT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EBUSY:
    sprintf(pErrMsg,"%s","%s: EBUSY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECANCELED:
    sprintf(pErrMsg,"%s","%s: ECANCELED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECHILD:
    sprintf(pErrMsg,"%s","%s: ECHILD");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECHRNG:
    sprintf(pErrMsg,"%s","%s: ECHRNG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECOMM:
    sprintf(pErrMsg,"%s","%s: ECOMM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECONNABORTED:
    sprintf(pErrMsg,"%s","%s: ECONNABORTED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECONNREFUSED:
    sprintf(pErrMsg,"%s","%s: ECONNREFUSED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ECONNRESET:
    sprintf(pErrMsg,"%s","%s: ECONNRESET");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EDEADLK:
    sprintf(pErrMsg,"%s","%s: EDEADLK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EDESTADDRREQ:
    sprintf(pErrMsg,"%s","%s: EDESTADDRREQ");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EDOM:
    sprintf(pErrMsg,"%s","%s: EDOM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EDQUOT:
    sprintf(pErrMsg,"%s","%s: EDQUOT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EEXIST:
    sprintf(pErrMsg,"%s","%s: EEXIST");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EFAULT:
    sprintf(pErrMsg,"%s","%s: EFAULT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EFBIG:
    sprintf(pErrMsg,"%s","%s: EFBIG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EHOSTDOWN:
    sprintf(pErrMsg,"%s","%s: EHOSTDOWN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EHOSTUNREACH:
    sprintf(pErrMsg,"%s","%s: EHOSTUNREACH");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EIDRM:
    sprintf(pErrMsg,"%s","%s: EIDRM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EILSEQ:
    sprintf(pErrMsg,"%s","%s: EILSEQ");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EINPROGRESS:
    sprintf(pErrMsg,"%s","%s: EINPROGRESS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EINTR:
    sprintf(pErrMsg,"%s","%s: EINTR");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EINVAL:
    sprintf(pErrMsg,"%s","%s: EINVAL");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EIO:
    sprintf(pErrMsg,"%s","%s: EIO");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EISCONN:
    sprintf(pErrMsg,"%s","%s: EISCONN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EISDIR:
    sprintf(pErrMsg,"%s","%s: EISDIR");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EISNAM:
    sprintf(pErrMsg,"%s","%s: EISNAM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EKEYEXPIRED:
    sprintf(pErrMsg,"%s","%s: EKEYEXPIRED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EKEYREJECTED:
    sprintf(pErrMsg,"%s","%s: EREJECTED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EKEYREVOKED:
    sprintf(pErrMsg,"%s","%s: EKEYREVOKED");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EL2HLT:
    sprintf(pErrMsg,"%s","%s: EL2HLT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EL2NSYNC:
    sprintf(pErrMsg,"%s","%s: EL2NSYNC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EL3HLT:
    sprintf(pErrMsg,"%s","%s: EL3HLT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EL3RST:
    sprintf(pErrMsg,"%s","%s: EL3RST");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELIBACC:
    sprintf(pErrMsg,"%s","%s: ELIBACC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELIBBAD:
    sprintf(pErrMsg,"%s","%s: ELIBBAD");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELIBMAX:
    sprintf(pErrMsg,"%s","%s: ELIBMAX");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELIBSCN:
    sprintf(pErrMsg,"%s","%s: ELIBSCN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELIBEXEC:
    sprintf(pErrMsg,"%s","%s: ELIBEXEC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ELOOP:
    sprintf(pErrMsg,"%s","%s: ELOOP");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EMEDIUMTYPE:
    sprintf(pErrMsg,"%s","%s: EMEDIUMTYPE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EMFILE:
    sprintf(pErrMsg,"%s","%s: EMFILE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EMLINK:
    sprintf(pErrMsg,"%s","%s: EMLINK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EMSGSIZE:
    sprintf(pErrMsg,"%s","%s: EMSGSIZE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EMULTIHOP:
    sprintf(pErrMsg,"%s","%s: EMULTIHOP");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENAMETOOLONG:
    sprintf(pErrMsg,"%s","%s: ENAMETOOLONG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENETDOWN:
    sprintf(pErrMsg,"%s","%s: ENETDOWN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENETRESET:
    sprintf(pErrMsg,"%s","%s: ENETRESET");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENETUNREACH:
    sprintf(pErrMsg,"%s","%s: ENETUNREACH");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENFILE:
    sprintf(pErrMsg,"%s","%s: ENFILE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOBUFS:
    sprintf(pErrMsg,"%s","%s: ENOBUFS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENODATA:
    sprintf(pErrMsg,"%s","%s: ENODATA");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENODEV:
    sprintf(pErrMsg,"%s","%s: ENODEV");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOENT:
    sprintf(pErrMsg,"%s","%s: ENOENT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOEXEC:
    sprintf(pErrMsg,"%s","%s: ENOEXEC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOKEY:
    sprintf(pErrMsg,"%s","%s: ENOKEY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOLCK:
    sprintf(pErrMsg,"%s","%s: ENOLCK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOLINK:
    sprintf(pErrMsg,"%s","%s: ENOLINK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOMEDIUM:
    sprintf(pErrMsg,"%s","%s: ENOMEDIUM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOMEM:
    sprintf(pErrMsg,"%s","%s: ENOMEM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOMSG:
    sprintf(pErrMsg,"%s","%s: ENOMSG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENONET:
    sprintf(pErrMsg,"%s","%s: ENONET");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOPKG:
    sprintf(pErrMsg,"%s","%s: ENOPKG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOPROTOOPT:
    sprintf(pErrMsg,"%s","%s: ENOPROTOOPT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOSPC:
    sprintf(pErrMsg,"%s","%s: ENOSPC");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOSR:
    sprintf(pErrMsg,"%s","%s: ENOSR");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOSYS:
    sprintf(pErrMsg,"%s","%s: ENOSYS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTBLK:
    sprintf(pErrMsg,"%s","%s: ENOTBLK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTCONN:
    sprintf(pErrMsg,"%s","%s: ENOTCONN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTDIR:
    sprintf(pErrMsg,"%s","%s: ENOTDIR");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTEMPTY:
    sprintf(pErrMsg,"%s","%s: ENOTEMPTY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTSOCK:
    sprintf(pErrMsg,"%s","%s: ENOTSOCK");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTSUP:
    sprintf(pErrMsg,"%s","%s: ENOTSUP");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTTY:
    sprintf(pErrMsg,"%s","%s: ENOTTY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENOTUNIQ:
    sprintf(pErrMsg,"%s","%s: ENOTUNIQ");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ENXIO:
    sprintf(pErrMsg,"%s","%s: ENXIO");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EOVERFLOW:
    sprintf(pErrMsg,"%s","%s: EOVERFLOW");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPERM:
    sprintf(pErrMsg,"%s","%s: EPERM");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPFNOSUPPORT:
    sprintf(pErrMsg,"%s","%s: EPFNOSUPPORT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPIPE:
    sprintf(pErrMsg,"%s","%s: EPIPE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPROTO:
    sprintf(pErrMsg,"%s","%s: EPROTO");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPROTONOSUPPORT:
    sprintf(pErrMsg,"%s","%s: EPROTONOSUPPORT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EPROTOTYPE:
    sprintf(pErrMsg,"%s","%s: EPROTOTYPE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ERANGE:
    sprintf(pErrMsg,"%s","%s: ERANGE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EREMCHG:
    sprintf(pErrMsg,"%s","%s: EREMCHG");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EREMOTE:
    sprintf(pErrMsg,"%s","%s: EREMOTE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EREMOTEIO:
    sprintf(pErrMsg,"%s","%s: EREMOTEIO");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ERESTART:
    sprintf(pErrMsg,"%s","%s: ERESTART");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EROFS:
    sprintf(pErrMsg,"%s","%s: EROFS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ESHUTDOWN:
    sprintf(pErrMsg,"%s","%s: ESHUTDOWN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ESPIPE:
    sprintf(pErrMsg,"%s","%s: ESPIPE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

#if 0
  case ESOCKTNOTSUPPORT:
    sprintf(pErrMsg,"%s","%s: ESOCKNOTSUPPORT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;
#endif

  case ESRCH:
    sprintf(pErrMsg,"%s","%s: ESRCH");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ESTALE:
    sprintf(pErrMsg,"%s","%s: ESTALE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ESTRPIPE:
    sprintf(pErrMsg,"%s","%s: ESTRPIPE");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ETIME:
    sprintf(pErrMsg,"%s","%s: ETIME");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ETIMEDOUT:
    sprintf(pErrMsg,"%s","%s: ETIMEDOUT");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case ETXTBSY:
    sprintf(pErrMsg,"%s","%s: ETXTBSY");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EUCLEAN:
    sprintf(pErrMsg,"%s","%s: EUCLEAN");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EUNATCH:
    sprintf(pErrMsg,"%s","%s: EUNATCH");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EUSERS:
    sprintf(pErrMsg,"%s","%s: EUSERS");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EXDEV:
    sprintf(pErrMsg,"%s","%s: EXDEV");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;

  case EXFULL:
    sprintf(pErrMsg,"%s","%s: EXFULL");
    syslog(LOG_DAEMON|LOG_CRIT,"%s",pErrMsg);
    break;
  }

  return;
}
