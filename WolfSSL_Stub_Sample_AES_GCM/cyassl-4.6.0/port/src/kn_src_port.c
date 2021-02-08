#include <wolfssl/internal.h>
#include <port/inc/kn_src_port.h>
//#include "_kn_plt_cstd_lib_wrap.h"
#if defined(POC_CDE_BREW)			
#include <AEEstd.h>
#include <AEENetErr.h>
#include <AEENetAddrTypes.h>
#endif

//from internal.c
#if defined(USER_TICKS)
uint32 kn_port_time()
{
#ifndef POC_CDE_BREW
	return KN_TIME(0);
#else
	uint32 ret = 0;
	KN_TIME(&ret);
	return ret;
#endif
}
#endif

#if defined(WOLFSSL_USER_IO) ||  defined(POC_CDE_BREW)
void InitSSL_Ctx_CDE_Port(WOLFSSL_CTX* ctx, WOLFSSL_METHOD* method)
{
    ctx->CBIORecv = KN_IO_EmbedReceive;
    ctx->CBIOSend = KN_IO_EmbedSend;
	#if  defined(CYASSL_DTLS) || defined (WOLFSSL_DTLS)
        if (method->version.major == DTLS_MAJOR
                                    && method->version.minor == DTLS_MINOR) {
            ctx->CBIORecv = KN_IO_EmbedReceiveFrom;
            ctx->CBIOSend = KN_IO_EmbedSendTo;
	#ifdef 	WOLFSSL_DTLS
			ctx->CBIOCookie = NULL;
	#endif		
        }
	#endif
}
#endif

/* Merging from 7.10 branch to 7.10 64-bit branch - Begin */
#if defined(POC_CDE_BREW) || defined(PJ_RTKE) || defined(PJ_THREADX) || defined(PJ_MTK)  /*Kodiak Custom IO APIs*/
#include "_kn_plt_cstd_lib_wrap.h"
#ifndef POC_CDE_BREW
static INLINE int LastError(void)
{
    return KN_OS_GetLastError();
}
#else
static INLINE int LastError(int err)
{
    return -err;
	//return 0;
}
#endif
int KN_IO_EmbedReceive(WOLFSSL *ssl, char *buf, int sz, void *ctx)
{
    int recvd;
    int err;
    KN_SOCK_T sd = *(KN_SOCK_T*)ctx;

#ifdef WOLFSSL_DTLS
    {
        int dtls_timeout = wolfSSL_dtls_get_current_timeout(ssl);
        if (wolfSSL_dtls(ssl)
                     && !wolfSSL_get_using_nonblock(ssl)
                     && dtls_timeout != 0) {
        KN_TIME_VAL timeout;
      	    XMEMSET(&timeout, 0, sizeof(timeout));
		timeout.sec = dtls_timeout;
#ifndef POC_CDE_BREW
            if(KN_Sock_SetSockOpt(sd, kn_SKT_SOL_SOCKET(), kn_SO_RCVTIMEO(),
                                            (char*)&timeout, sizeof(timeout))!=0){
                                            WOLFSSL_MSG("setsockopt rcvtimeo failed");
            }
#endif
        }
    }
#endif

    recvd = KN_Sock_Recv(sd, (char *)buf, sz, ssl->rflags);

    if (recvd < 0) {
#ifndef POC_CDE_BREW
        err = LastError();
#else
		err = LastError(recvd);
#endif

        if (err == kn_SOCK_ERR_WOULDBLOCK() || err == kn_SOCK_ERR_AGAIN()) {
            if (!wolfSSL_dtls(ssl) || wolfSSL_get_using_nonblock(ssl)) {
                WOLFSSL_MSG("    Would block");
		return  WOLFSSL_CBIO_ERR_WANT_READ;//CYASSL_CBIO_ERR_WANT_READ; KSantosh - Cyassl_3_5
            }
            else {
                WOLFSSL_MSG("    Socket timeout");
                return WOLFSSL_CBIO_ERR_TIMEOUT;
            }
        }
        else if (err == kn_SOCK_ERR_CONNRESET()) {
            WOLFSSL_MSG("    Connection reset");
            return WOLFSSL_CBIO_ERR_CONN_RST;
        }
        else if (err == kn_SOCK_ERR_INTR()) {
            WOLFSSL_MSG("    Socket interrupted");
            return WOLFSSL_CBIO_ERR_ISR;
        }
        else if (err == kn_SOCK_ERR_CONNREFUSED()) {
            WOLFSSL_MSG("    Connection refused");
            return WOLFSSL_CBIO_ERR_WANT_READ;
        }
#if 0 /*To be uncommented after mapping is available from vendor & also needs to added in wrap.h*/
        else if (err == kn_SOCK_ERR_CONNABORTED()) {
            WOLFSSL_MSG("    Connection aborted");
            return WOLFSSL_CBIO_ERR_CONN_CLOSE;
        }
#endif
        else {
	 WOLFSSL_MSG("    General error");
            return WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
    else if (recvd == 0) {
        WOLFSSL_MSG("Embed receive connection closed");
        return WOLFSSL_CBIO_ERR_CONN_CLOSE;
    }

    return recvd;
}


int KN_IO_EmbedSend(WOLFSSL* ssl, char *buf, int sz, void *ctx)
{
    KN_SOCK_T sd = *(KN_SOCK_T*)ctx;
    int sent;
    int len = sz;
    int err;

    (void)ssl;
#ifdef POC_CDE_BREW
    sent = KN_Sock_Send(sd, &buf[sz - len], len);
#else
    sent = KN_Sock_Send(sd, &buf[sz - len], len, ssl->wflags);
#endif

    if (sent < 0) {
#ifndef POC_CDE_BREW
        err = LastError();
#else
		err = LastError(sent);
#endif
        WOLFSSL_MSG("Embed Send error");
        if (err == kn_SOCK_ERR_WOULDBLOCK() || err == kn_SOCK_ERR_AGAIN()) {
            WOLFSSL_MSG("    Would Block");
	    return WOLFSSL_CBIO_ERR_WANT_WRITE;
        }
        else if (err == kn_SOCK_ERR_CONNRESET()) {
            WOLFSSL_MSG("    Connection reset");
            return WOLFSSL_CBIO_ERR_CONN_RST;
        }
        else if (err == kn_SOCK_ERR_INTR()) {
            WOLFSSL_MSG("    Socket interrupted");
            return WOLFSSL_CBIO_ERR_ISR;
        }
        else if (err == kn_SOCK_ERR_PIPE()) {
            WOLFSSL_MSG("    Socket EPIPE");
            return WOLFSSL_CBIO_ERR_CONN_CLOSE;
        }
        else {
            WOLFSSL_MSG("    General error");
            return WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
 
    return sent;
}


int KN_IO_EmbedReceiveFrom(WOLFSSL *ssl, char *buf, int sz, void *ctx)
{
    WOLFSSL_DTLS_CTX* dtlsCtx = (WOLFSSL_DTLS_CTX*)ctx;
    int recvd;
    int err;
	enum IOerrors eErrCde = 1;
#ifdef POC_CDE_BREW
	AEESockAddrStorage peer	=	{0};
#else
    KN_SOCK_ADDR_IN peer = {0};
#endif
    KN_SOCKLEN peerSz = KN_SIZEOF(peer);
    KN_SOCK_T sd = (KN_SOCK_T)dtlsCtx->rfd;
    int dtls_timeout = wolfSSL_dtls_get_current_timeout(ssl);
	
    WOLFSSL_ENTER("KN_IO_EmbedReceiveFrom()");
#ifndef POC_CDE_BREW
	if (!wolfSSL_get_using_nonblock(ssl) && dtls_timeout != 0) {
        KN_TIME_VAL timeout;
         XMEMSET(&timeout, 0, sizeof(timeout));
	 timeout.sec = dtls_timeout;
        if(KN_Sock_SetSockOpt(sd, kn_SKT_SOL_SOCKET(), kn_SO_RCVTIMEO(),
                                            (char*)&timeout, KN_SIZEOF(timeout))!=0){
                WOLFSSL_MSG("setsockopt rcvtimeo failed");
		}
    }
#endif
    recvd = KN_Sock_Recvfrom((void*)sd, (char *)buf, sz, ssl->rflags, &peer, &peerSz);

    if (recvd < 0) {
#ifndef POC_CDE_BREW
        err = LastError();
#else
		err = LastError(recvd);
#endif
        WOLFSSL_MSG("KN_IO_EmbedReceiveFrom error");

        if (err == kn_SOCK_ERR_WOULDBLOCK() || err == kn_SOCK_ERR_AGAIN()) {
            if (wolfSSL_get_using_nonblock(ssl)) {
                WOLFSSL_MSG("    Would block");
                eErrCde = WOLFSSL_CBIO_ERR_WANT_READ;
            }
            else {
                WOLFSSL_MSG("    Socket timeout");
                eErrCde = WOLFSSL_CBIO_ERR_TIMEOUT;
            }
        }
        else if (err == kn_SOCK_ERR_CONNRESET()) {
            WOLFSSL_MSG("    Connection reset");
            eErrCde = WOLFSSL_CBIO_ERR_CONN_RST;
        }
        else if (err == kn_SOCK_ERR_INTR()) {
            WOLFSSL_MSG("    Socket interrupted");
            eErrCde = WOLFSSL_CBIO_ERR_ISR;
        }
        else if (err == kn_SOCK_ERR_CONNREFUSED()) {
            WOLFSSL_MSG("    Connection refused");
            eErrCde = WOLFSSL_CBIO_ERR_WANT_READ;
        }
        else {
            WOLFSSL_MSG("    General error");
            eErrCde = WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
    else {
        if (dtlsCtx != NULL
                && dtlsCtx->peer.sz > 0
                && peerSz != (KN_SOCKLEN)dtlsCtx->peer.sz
                && KN_MEMCMP(&peer, dtlsCtx->peer.sa, peerSz) != 0) {
            WOLFSSL_MSG("    Ignored packet from invalid peer");
            eErrCde = WOLFSSL_CBIO_ERR_WANT_READ;
        }
    }
	if (eErrCde != 1)
		return eErrCde;
	else
		return recvd;
}


int KN_IO_EmbedSendTo(WOLFSSL* ssl, char *buf, int sz, void *ctx)
{
    WOLFSSL_DTLS_CTX* dtlsCtx = (WOLFSSL_DTLS_CTX*)ctx;
    KN_SOCK_T sd = (KN_SOCK_T)dtlsCtx->rfd;
    int sent;
    int len = sz;
    int err;

    (void)ssl;
	
    WOLFSSL_ENTER("KN_IO_EmbedSendTo()");
	sent = KN_Sock_Sendto(sd, &buf[sz - len], len, ssl->wflags,
                                            (KN_SOCK_ADDR_IN*)dtlsCtx->peer.sa, (KN_SOCKLEN)dtlsCtx->peer.sz);

    if (sent < 0) {
#ifndef POC_CDE_BREW
        err = LastError();
#else
		err = LastError(sent);
#endif
        WOLFSSL_MSG("Embed Send To error");

        if (err == kn_SOCK_ERR_WOULDBLOCK() || err == kn_SOCK_ERR_AGAIN()) {
            WOLFSSL_MSG("    Would Block");
            return WOLFSSL_CBIO_ERR_WANT_WRITE;
        }
        else if (err == kn_SOCK_ERR_CONNRESET()) {
            WOLFSSL_MSG("    Connection reset");
            return WOLFSSL_CBIO_ERR_CONN_RST;
        }
        else if (err == kn_SOCK_ERR_INTR()) {
            WOLFSSL_MSG("    Socket interrupted");
            return WOLFSSL_CBIO_ERR_ISR;
        }
        else if (err == kn_SOCK_ERR_PIPE()) {
            WOLFSSL_MSG("    Socket EPIPE");
            return WOLFSSL_CBIO_ERR_CONN_CLOSE;
        }
        else {
            WOLFSSL_MSG("    General error");
            return WOLFSSL_CBIO_ERR_GENERAL;
        }
    }
 
    return sent;
}

/*KSantosh - Cyassl_3_5 */
/* Check the use of below function */
#if 0
int EmbedGenerateCookie(CYASSL* ssl, byte *buf, int sz, void *ctx)
{
    int sd = ssl->wfd;
    KN_SOCK_ADDR_IN peer;
    KN_SOCKLEN peerSz = KN_SIZEOF(peer);
    int cookieSrcSz = 0;
    Sha sha;
    byte cookieSrc[KN_SIZEOF(struct __KN_IN_ADDR) + KN_SIZEOF(int)];
 

   if( KN_Sock_Getpeername(sd, &peer, &peerSz)!=0){
        WOLFSSL_MSG("getpeername failed in EmbedGenerateCookie");
        return GEN_COOKIE_E;
   	}
    if (peer.iFamily == kn_SOCK_FAMILY_AFINET()) {
        KN_SOCK_ADDR_IN *s = (KN_SOCK_ADDR_IN*)&peer;

        cookieSrcSz = sizeof(struct __KN_IN_ADDR) + sizeof(s->iPort);
        XMEMCPY(cookieSrc, &s->iPort, sizeof(s->iPort));
        XMEMCPY(cookieSrc + sizeof(s->iPort),
                                     &s->sAddr, sizeof(struct __KN_IN_ADDR));
    }

    InitSha(&sha);
    ShaUpdate(&sha, cookieSrc, cookieSrcSz);

    if (sz < SHA_DIGEST_SIZE) {
        byte digest[SHA_DIGEST_SIZE];
        ShaFinal(&sha, digest);
        XMEMCPY(buf, digest, sz);
        return sz;
    }

    ShaFinal(&sha, buf);

    return SHA_DIGEST_SIZE;
}
#endif //#if 0

#endif  //#if defined(PJ_RTKE) || defined(PJ_THREADX) || defined(PJ_MTK)