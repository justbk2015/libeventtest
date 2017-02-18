/*
 * Automatically generated from G:/code/c/libeventest/libeventtest/libeventtest/Rpcdata.rpc
 */

#ifndef EVENT_RPCOUT_G__CODE_C_LIBEVENTEST_LIBEVENTTEST_LIBEVENTTEST_RPCDATA_RPC_
#define EVENT_RPCOUT_G__CODE_C_LIBEVENTEST_LIBEVENTTEST_LIBEVENTTEST_RPCDATA_RPC_

#include <event2/util.h> /* for ev_uint*_t */
#include <event2/rpc.h>


struct RpcRequestInfo;
struct RpcReplyInfo;

/* Tag definition for RpcRequestInfo */
enum rpcrequestinfo_ {
  RPCREQUESTINFO_A=1,
  RPCREQUESTINFO_P=2,
  RPCREQUESTINFO_MAX_TAGS
};

/* Structure declaration for RpcRequestInfo */
struct RpcRequestInfo_access_ {
  int (*a_assign)(struct RpcRequestInfo *, const ev_uint32_t);
  int (*a_get)(struct RpcRequestInfo *, ev_uint32_t *);
  int (*p_assign)(struct RpcRequestInfo *, const char *);
  int (*p_get)(struct RpcRequestInfo *, char * *);
};

struct RpcRequestInfo {
  struct RpcRequestInfo_access_ *base;

  ev_uint32_t a_data;
  char *p_data;

  ev_uint8_t a_set;
  ev_uint8_t p_set;
};

struct RpcRequestInfo *RpcRequestInfo_new(void);
struct RpcRequestInfo *RpcRequestInfo_new_with_arg(void *);
void RpcRequestInfo_free(struct RpcRequestInfo *);
void RpcRequestInfo_clear(struct RpcRequestInfo *);
void RpcRequestInfo_marshal(struct evbuffer *, const struct RpcRequestInfo *);
int RpcRequestInfo_unmarshal(struct RpcRequestInfo *, struct evbuffer *);
int RpcRequestInfo_complete(struct RpcRequestInfo *);
void evtag_marshal_RpcRequestInfo(struct evbuffer *, ev_uint32_t,
    const struct RpcRequestInfo *);
int evtag_unmarshal_RpcRequestInfo(struct evbuffer *, ev_uint32_t,
    struct RpcRequestInfo *);
int RpcRequestInfo_a_assign(struct RpcRequestInfo *, const ev_uint32_t);
int RpcRequestInfo_a_get(struct RpcRequestInfo *, ev_uint32_t *);
int RpcRequestInfo_p_assign(struct RpcRequestInfo *, const char *);
int RpcRequestInfo_p_get(struct RpcRequestInfo *, char * *);
/* --- RpcRequestInfo done --- */

/* Tag definition for RpcReplyInfo */
enum rpcreplyinfo_ {
  RPCREPLYINFO_B=1,
  RPCREPLYINFO_P=2,
  RPCREPLYINFO_MAX_TAGS
};

/* Structure declaration for RpcReplyInfo */
struct RpcReplyInfo_access_ {
  int (*b_assign)(struct RpcReplyInfo *, const ev_uint32_t);
  int (*b_get)(struct RpcReplyInfo *, ev_uint32_t *);
  int (*p_assign)(struct RpcReplyInfo *, const char *);
  int (*p_get)(struct RpcReplyInfo *, char * *);
};

struct RpcReplyInfo {
  struct RpcReplyInfo_access_ *base;

  ev_uint32_t b_data;
  char *p_data;

  ev_uint8_t b_set;
  ev_uint8_t p_set;
};

struct RpcReplyInfo *RpcReplyInfo_new(void);
struct RpcReplyInfo *RpcReplyInfo_new_with_arg(void *);
void RpcReplyInfo_free(struct RpcReplyInfo *);
void RpcReplyInfo_clear(struct RpcReplyInfo *);
void RpcReplyInfo_marshal(struct evbuffer *, const struct RpcReplyInfo *);
int RpcReplyInfo_unmarshal(struct RpcReplyInfo *, struct evbuffer *);
int RpcReplyInfo_complete(struct RpcReplyInfo *);
void evtag_marshal_RpcReplyInfo(struct evbuffer *, ev_uint32_t,
    const struct RpcReplyInfo *);
int evtag_unmarshal_RpcReplyInfo(struct evbuffer *, ev_uint32_t,
    struct RpcReplyInfo *);
int RpcReplyInfo_b_assign(struct RpcReplyInfo *, const ev_uint32_t);
int RpcReplyInfo_b_get(struct RpcReplyInfo *, ev_uint32_t *);
int RpcReplyInfo_p_assign(struct RpcReplyInfo *, const char *);
int RpcReplyInfo_p_get(struct RpcReplyInfo *, char * *);
/* --- RpcReplyInfo done --- */

#endif  /* EVENT_RPCOUT_G__CODE_C_LIBEVENTEST_LIBEVENTTEST_LIBEVENTTEST_RPCDATA_RPC_ */
