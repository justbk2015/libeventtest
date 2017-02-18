#include <stdio.h>
#include <assert.h>
#include <WinSock2.h>
#include <windows.h>
#include "../libeventtest/UseLibevent.h"
#include "../libeventtest/Rpcdata.h"
#include "UseLog.h"
#pragma comment(lib, "ws2_32.lib")
EVRPC_HEADER(Message, RpcRequestInfo, RpcReplyInfo)
EVRPC_GENERATE(Message, RpcRequestInfo, RpcReplyInfo)
static int need_input_hook = 0;
static int need_output_hook = 0;
static event_base* g_base = NULL;
static void rpc_postrequest_done(struct evhttp_request *req, void *arg)
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
int main(int argc, char** argv)
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
    //struct evdns_base* dns_base = evdns_base_new(base, EVDNS_BASE_INITIALIZE_NAMESERVERS | EVDNS_BASE_DISABLE_WHEN_INACTIVE);
    evcon = evhttp_connection_base_new(base, NULL, "127.0.0.1", 10035); //evhttp_connection_new("127.0.0.1", 5546);
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