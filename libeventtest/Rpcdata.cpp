/*
 * Automatically generated from G:/code/c/libeventest/libeventtest/libeventtest/Rpcdata.rpc
 * by event_rpcgen.py/0.1.  DO NOT EDIT THIS FILE.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <event2/event-config.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/tag.h>
#include "UseLog.h"

#if defined(EVENT____func__) && !defined(__func__)
#define __func__ EVENT____func__
#endif


#include "Rpcdata.h"

void event_warn(const char *fmt, ...);
void event_warnx(const char *fmt, ...);


/*
 * Implementation of RpcRequestInfo
 */

static struct RpcRequestInfo_access_ RpcRequestInfo_base__ = {
  RpcRequestInfo_a_assign,
  RpcRequestInfo_a_get,
  RpcRequestInfo_p_assign,
  RpcRequestInfo_p_get,
};

struct RpcRequestInfo *
RpcRequestInfo_new(void)
{
  return RpcRequestInfo_new_with_arg(NULL);
}

struct RpcRequestInfo *
RpcRequestInfo_new_with_arg(void *unused)
{
  struct RpcRequestInfo *tmp;
  if ((tmp = (RpcRequestInfo*)malloc(sizeof(struct RpcRequestInfo))) == NULL) {
    logd("%s: malloc", __func__);
    return (NULL);
  }
  tmp->base = &RpcRequestInfo_base__;

  tmp->a_data = 0;
  tmp->a_set = 0;

  tmp->p_data = NULL;
  tmp->p_set = 0;

  return (tmp);
}



int
RpcRequestInfo_a_assign(struct RpcRequestInfo *msg, const ev_uint32_t value)
{
  msg->a_set = 1;
  msg->a_data = value;
  return (0);
}

int
RpcRequestInfo_p_assign(struct RpcRequestInfo *msg,
    const char * value)
{
  if (msg->p_data != NULL)
    free(msg->p_data);
  if ((msg->p_data = strdup(value)) == NULL)
    return (-1);
  msg->p_set = 1;
  return (0);
}

int
RpcRequestInfo_a_get(struct RpcRequestInfo *msg, ev_uint32_t *value)
{
  if (msg->a_set != 1)
    return (-1);
  *value = msg->a_data;
  return (0);
}

int
RpcRequestInfo_p_get(struct RpcRequestInfo *msg, char * *value)
{
  if (msg->p_set != 1)
    return (-1);
  *value = msg->p_data;
  return (0);
}

void
RpcRequestInfo_clear(struct RpcRequestInfo *tmp)
{
  tmp->a_set = 0;
  if (tmp->p_set == 1) {
    free(tmp->p_data);
    tmp->p_data = NULL;
    tmp->p_set = 0;
  }
}

void
RpcRequestInfo_free(struct RpcRequestInfo *tmp)
{
  if (tmp->p_data != NULL)
      free (tmp->p_data);
  free(tmp);
}

void
RpcRequestInfo_marshal(struct evbuffer *evbuf, const struct RpcRequestInfo *tmp){
  evtag_marshal_int(evbuf, RPCREQUESTINFO_A, tmp->a_data);
  evtag_marshal_string(evbuf, RPCREQUESTINFO_P, tmp->p_data);
}

int
RpcRequestInfo_unmarshal(struct RpcRequestInfo *tmp,  struct evbuffer *evbuf)
{
  ev_uint32_t tag;
  while (evbuffer_get_length(evbuf) > 0) {
    if (evtag_peek(evbuf, &tag) == -1)
      return (-1);
    switch (tag) {

      case RPCREQUESTINFO_A:

        if (tmp->a_set)
          return (-1);
        if (evtag_unmarshal_int(evbuf, RPCREQUESTINFO_A, &tmp->a_data) == -1) {
          logd("%s: failed to unmarshal a", __func__);
          return (-1);
        }
        tmp->a_set = 1;
        break;

      case RPCREQUESTINFO_P:

        if (tmp->p_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, RPCREQUESTINFO_P, &tmp->p_data) == -1) {
          logd("%s: failed to unmarshal p", __func__);
          return (-1);
        }
        tmp->p_set = 1;
        break;

      default:
        return -1;
    }
  }

  if (RpcRequestInfo_complete(tmp) == -1)
    return (-1);
  return (0);
}

int
RpcRequestInfo_complete(struct RpcRequestInfo *msg)
{
  if (!msg->a_set)
    return (-1);
  if (!msg->p_set)
    return (-1);
  return (0);
}

int
evtag_unmarshal_RpcRequestInfo(struct evbuffer *evbuf, ev_uint32_t need_tag, struct RpcRequestInfo *msg)
{
  ev_uint32_t tag;
  int res = -1;

  struct evbuffer *tmp = evbuffer_new();

  if (evtag_unmarshal(evbuf, &tag, tmp) == -1 || tag != need_tag)
    goto error;

  if (RpcRequestInfo_unmarshal(msg, tmp) == -1)
    goto error;

  res = 0;

 error:
  evbuffer_free(tmp);
  return (res);
}

void
evtag_marshal_RpcRequestInfo(struct evbuffer *evbuf, ev_uint32_t tag, const struct RpcRequestInfo *msg)
{
  struct evbuffer *buf_ = evbuffer_new();
  assert(buf_ != NULL);
  RpcRequestInfo_marshal(buf_, msg);
  evtag_marshal_buffer(evbuf, tag, buf_);
   evbuffer_free(buf_);
}

/*
 * Implementation of RpcReplyInfo
 */

static struct RpcReplyInfo_access_ RpcReplyInfo_base__ = {
  RpcReplyInfo_b_assign,
  RpcReplyInfo_b_get,
  RpcReplyInfo_p_assign,
  RpcReplyInfo_p_get,
};

struct RpcReplyInfo *
RpcReplyInfo_new(void)
{
  return RpcReplyInfo_new_with_arg(NULL);
}

struct RpcReplyInfo *
RpcReplyInfo_new_with_arg(void *unused)
{
  struct RpcReplyInfo *tmp;
  if ((tmp = (RpcReplyInfo*)malloc(sizeof(struct RpcReplyInfo))) == NULL) {
    logd("%s: malloc", __func__);
    return (NULL);
  }
  tmp->base = &RpcReplyInfo_base__;

  tmp->b_data = 0;
  tmp->b_set = 0;

  tmp->p_data = NULL;
  tmp->p_set = 0;

  return (tmp);
}



int
RpcReplyInfo_b_assign(struct RpcReplyInfo *msg, const ev_uint32_t value)
{
  msg->b_set = 1;
  msg->b_data = value;
  return (0);
}

int
RpcReplyInfo_p_assign(struct RpcReplyInfo *msg,
    const char * value)
{
  if (msg->p_data != NULL)
    free(msg->p_data);
  if ((msg->p_data = strdup(value)) == NULL)
    return (-1);
  msg->p_set = 1;
  return (0);
}

int
RpcReplyInfo_b_get(struct RpcReplyInfo *msg, ev_uint32_t *value)
{
  if (msg->b_set != 1)
    return (-1);
  *value = msg->b_data;
  return (0);
}

int
RpcReplyInfo_p_get(struct RpcReplyInfo *msg, char * *value)
{
  if (msg->p_set != 1)
    return (-1);
  *value = msg->p_data;
  return (0);
}

void
RpcReplyInfo_clear(struct RpcReplyInfo *tmp)
{
  tmp->b_set = 0;
  if (tmp->p_set == 1) {
    free(tmp->p_data);
    tmp->p_data = NULL;
    tmp->p_set = 0;
  }
}

void
RpcReplyInfo_free(struct RpcReplyInfo *tmp)
{
  if (tmp->p_data != NULL)
      free (tmp->p_data);
  free(tmp);
}

void
RpcReplyInfo_marshal(struct evbuffer *evbuf, const struct RpcReplyInfo *tmp){
  evtag_marshal_int(evbuf, RPCREPLYINFO_B, tmp->b_data);
  evtag_marshal_string(evbuf, RPCREPLYINFO_P, tmp->p_data);
}

int
RpcReplyInfo_unmarshal(struct RpcReplyInfo *tmp,  struct evbuffer *evbuf)
{
  ev_uint32_t tag;
  while (evbuffer_get_length(evbuf) > 0) {
    if (evtag_peek(evbuf, &tag) == -1)
      return (-1);
    switch (tag) {

      case RPCREPLYINFO_B:

        if (tmp->b_set)
          return (-1);
        if (evtag_unmarshal_int(evbuf, RPCREPLYINFO_B, &tmp->b_data) == -1) {
          logd("%s: failed to unmarshal b", __func__);
          return (-1);
        }
        tmp->b_set = 1;
        break;

      case RPCREPLYINFO_P:

        if (tmp->p_set)
          return (-1);
        if (evtag_unmarshal_string(evbuf, RPCREPLYINFO_P, &tmp->p_data) == -1) {
          logd("%s: failed to unmarshal p", __func__);
          return (-1);
        }
        tmp->p_set = 1;
        break;

      default:
        return -1;
    }
  }

  if (RpcReplyInfo_complete(tmp) == -1)
    return (-1);
  return (0);
}

int
RpcReplyInfo_complete(struct RpcReplyInfo *msg)
{
  if (!msg->b_set)
    return (-1);
  if (!msg->p_set)
    return (-1);
  return (0);
}

int
evtag_unmarshal_RpcReplyInfo(struct evbuffer *evbuf, ev_uint32_t need_tag, struct RpcReplyInfo *msg)
{
  ev_uint32_t tag;
  int res = -1;

  struct evbuffer *tmp = evbuffer_new();

  if (evtag_unmarshal(evbuf, &tag, tmp) == -1 || tag != need_tag)
    goto error;

  if (RpcReplyInfo_unmarshal(msg, tmp) == -1)
    goto error;

  res = 0;

 error:
  evbuffer_free(tmp);
  return (res);
}

void
evtag_marshal_RpcReplyInfo(struct evbuffer *evbuf, ev_uint32_t tag, const struct RpcReplyInfo *msg)
{
  struct evbuffer *buf_ = evbuffer_new();
  assert(buf_ != NULL);
  RpcReplyInfo_marshal(buf_, msg);
  evtag_marshal_buffer(evbuf, tag, buf_);
   evbuffer_free(buf_);
}

