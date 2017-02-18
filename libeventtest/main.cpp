#include <stdio.h>
#include <assert.h>
#include <WinSock2.h>
#include <windows.h>
#include "UseLog.h"
#include "UseLibevent.h"
#include "Rpcdata.h"

#pragma comment(lib, "ws2_32.lib")

struct event g_ev;
struct timeval g_tb;

void time_cb(evutil_socket_t fd, short flag, void* args)
{
    logd("test!");
    event_add(&g_ev, &g_tb);
}
int main1(int argc, char** argv)
{
    WORD dwWord;
    WSADATA data;
    dwWord = MAKEWORD(2,2);
    WSAStartup(dwWord, &data);
    struct event_base* base = event_base_new();
    event_set(&g_ev, -1, NULL, time_cb, NULL);
    g_tb.tv_sec = 1;
    g_tb.tv_usec = 0;
    event_base_set(base, &g_ev);
    event_add(&g_ev, &g_tb);
    event_base_dispatch(base);

    getchar();
    return 0;
}
EVRPC_HEADER(Message, RpcRequestInfo, RpcReplyInfo)
EVRPC_GENERATE(Message, RpcRequestInfo, RpcReplyInfo)
static int need_input_hook = 0;
static int need_output_hook = 0;
static event_base* g_base = NULL;
static void
MessageCb(EVRPC_STRUCT(Message)* rpc, void *arg)
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
    EVTAG_GET(request, a, &a);
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
http_setup(ev_uint16_t *pport)
{
    struct evhttp *myhttp;
    ev_uint16_t port;
    struct evhttp_bound_socket *sock;
    g_base = event_base_new();
    myhttp = evhttp_new(g_base);
    if (!myhttp)
        logd( "Could not start web server");

    /* Try a few different ports */
    sock = evhttp_bind_socket_with_handle(myhttp, "127.0.0.1", 0);
    if (!sock)
        logd( "Couldn't open web port");

    port = regress_get_socket_port(evhttp_bound_socket_get_fd(sock));
    
    *pport = port;
    return (myhttp);
}
int main(int argc, char** argv)
{
    WORD dwWord;
    WSADATA data;
    dwWord = MAKEWORD(2,2);
    WSAStartup(dwWord, &data);
    //struct event_base* base = event_base_new();
    uint16_t port = 0;
    struct evhttp* http = http_setup(&port);
    logd("bind port on %d", port);
    struct evrpc_base* rpc_base = evrpc_init(http);
    
    EVRPC_REGISTER(rpc_base, Message, RpcRequestInfo, RpcReplyInfo, MessageCb, NULL);
    event_base_dispatch(g_base);
    getchar();
    return 0;
}
static void
    rpc_postrequest_done(struct evhttp_request *req, void *arg)
{
    struct RpcReplyInfo* kill_reply = NULL;
    if (req->response_code != HTTP_OK) {
        fprintf(stderr, "FAILED (response code)\n");
        exit(1);
    }
    logd("rpc_postrequest_done run!");
    kill_reply = RpcReplyInfo_new();

    if ((RpcReplyInfo_unmarshal(kill_reply, req->input_buffer)) == -1) {
        fprintf(stderr, "FAILED (unmarshal)\n");
        exit(1);
    }
    ev_uint32_t b = 0;
    char* p = NULL;
    EVTAG_GET(kill_reply, b,&b);
    EVTAG_GET(kill_reply, p, &p);
    logd("recv b=%d p=%s",b,p );
    RpcReplyInfo_free(kill_reply);
   // event_loopexit(base);
}
int main3(int argc, char** argv)
{
    WORD dwWord;
    WSADATA data;
    dwWord = MAKEWORD(2,2);
    WSAStartup(dwWord, &data);
    ev_uint16_t port = 0;
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;
	struct RpcRequestInfo *msg;
    struct event_base* base = event_base_new();
    struct evdns_base* dns_base = evdns_base_new(base, EVDNS_BASE_INITIALIZE_NAMESERVERS | EVDNS_BASE_DISABLE_WHEN_INACTIVE);
	evcon = evhttp_connection_base_new(base, dns_base, "127.0.0.1", atoi(argv[1])); //evhttp_connection_new("127.0.0.1", 5546);
    //evhttp_connection_connect_(evcon);
    evcon->timeout.tv_sec = 10;
	req = evhttp_request_new(rpc_postrequest_done, NULL);
	if (req == NULL) {
		fprintf(stdout, "FAILED\n");
		exit(1);
	}

	/* Add the information that we care about */
	evhttp_add_header(req->output_headers, "Host", "somehost");

	/* set up the basic message */
	msg = RpcRequestInfo_new();
	EVTAG_ASSIGN(msg, a, 100);
    char* test = "tester";
	EVTAG_ASSIGN(msg, p, test);
	RpcRequestInfo_marshal(req->output_buffer, msg);
	RpcRequestInfo_free(msg);
    if (evhttp_make_request(evcon, req,
        EVHTTP_REQ_POST,
        "/.rpc.Message") == -1) {
            fprintf(stdout, "FAILED\n");
            exit(1);
    }

    event_base_dispatch(base);

    getchar();
	evhttp_connection_free(evcon);

end:
    getchar();
    return 0;
}