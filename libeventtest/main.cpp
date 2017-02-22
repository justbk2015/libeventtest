#include <stdio.h>
#include <assert.h>
#include <WinSock2.h>
#include <windows.h>
#include "UseLog.h"
#include "../commonlog/include/Thread.h"
#include "UseLibevent.h"
#include "Rpcdata.h"

#pragma comment(lib, "ws2_32.lib")

EVRPC_HEADER(Message, RpcRequestInfo, RpcReplyInfo)
EVRPC_GENERATE(Message, RpcRequestInfo, RpcReplyInfo)
static int need_input_hook = 0;
static int need_output_hook = 0;
static event_base* g_base = NULL;
static void  MessageCb(EVRPC_STRUCT(Message)* rpc, void *arg)
{
    logd("get MessageCb!");
    struct RpcReplyInfo* kill_reply = rpc->reply;

    if (need_input_hook) {
        struct evhttp_request* req = EVRPC_REQUEST_HTTP(rpc);
        const char *header = evhttp_find_header(
            req->input_headers, "X-Hook");
        assert(header);
        assert(strcmp(header, "input") == 0);
    }

    /* we just want to fill in some non-sense */
    struct RpcRequestInfo* request = rpc->request;
    ev_uint32_t a = 0;
    char* p = NULL;
    EVTAG_GET(request, a, &a);
    EVTAG_GET(request, p, &p);
    logd("recv a=%d,p=%s", a, p);
    EVTAG_ASSIGN(kill_reply, b, a + 1);
    EVTAG_ASSIGN(kill_reply, p, "wave around like an idiot");

    /* no reply to the RPC */
    EVRPC_REQUEST_DONE(rpc);
}
int
    regress_get_socket_port(evutil_socket_t fd)
{
    struct sockaddr_storage ss;
    ev_socklen_t socklen = sizeof(ss);
    if (getsockname(fd, (struct sockaddr*)&ss, &socklen) != 0)
        return -1;
    if (ss.ss_family == AF_INET)
        return ntohs( ((struct sockaddr_in*)&ss)->sin_port);
    else if (ss.ss_family == AF_INET6)
        return ntohs( ((struct sockaddr_in6*)&ss)->sin6_port);
    else
        return -1;
}
static struct evhttp *
http_setup(ev_uint16_t port)
{
    struct evhttp *myhttp;
    struct evhttp_bound_socket *sock;
    if (g_base == NULL) 
    {
        g_base = event_base_new();
    }
    
    myhttp = evhttp_new(g_base);
    if (!myhttp)
        logd( "Could not start web server");

    /* Try a few different ports */
    sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", port);
    if (!sock)
        logd( "Couldn't open web port");

    port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));
    return (myhttp);
}
typedef void (*THREAD_CALL_BACK_FUNC)(void*) ;
void back_run(void* _t)
{
    zb::Thread<THREAD_CALL_BACK_FUNC> *pt = static_cast<zb::Thread<THREAD_CALL_BACK_FUNC> *>(_t);
    WORD dwWord;
    WSADATA data;
    dwWord = MAKEWORD(2,2);
    WSAStartup(dwWord, &data);
    //struct event_base* base = event_base_new();
    uint16_t port = 10035;
    struct evhttp* http = http_setup(port);
    logd("bind port on %d", port);
    struct evrpc_base* rpc_base = evrpc_init(http);

    EVRPC_REGISTER(rpc_base, Message, RpcRequestInfo, RpcReplyInfo, MessageCb, NULL);
    event_base_dispatch(g_base);
    logd("break by other thread!");
}
int main(int argc, char** argv)
{
    zb::Thread<THREAD_CALL_BACK_FUNC> t(back_run);
    t.begin();

    getchar();
    timeval tb;
    tb.tv_sec = 1;
    tb.tv_usec = 0;
    event_base_loopexit(g_base, &tb);
    getchar();
    return 0;
}