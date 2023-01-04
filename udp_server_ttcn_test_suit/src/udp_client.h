#ifndef _UDP_CLIENT_H
#define _UDP_CLIENT_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int fd; 
	struct sockaddr_in srvAddr;
} udp_client_ctx_t;

bool udp_client_init(const char * host, int port, udp_client_ctx_t *ctx);
bool udp_client_deinit(udp_client_ctx_t *ctx);
bool udp_client_send(const udp_client_ctx_t *ctx, const char *message);
bool udp_client_rcv(const udp_client_ctx_t *ctx, char *message, size_t *msgLen);

#ifdef __cplusplus
}
#endif

#endif
