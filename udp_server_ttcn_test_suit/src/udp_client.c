#include <sys/types.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include "udp_client.h"

bool udp_client_init(const char * host, int port, udp_client_ctx_t *ctx)
{
	if (host == NULL || ctx == NULL || port <= 0)
	{
		return false;
	}
	struct hostent *hp;
	if ((hp = gethostbyname(host)) == NULL)
	{
		return false;
	}

	bzero(&ctx->srvAddr, sizeof(ctx->srvAddr));
	bcopy(hp->h_addr, &ctx->srvAddr.sin_addr, hp->h_length);
	ctx->srvAddr.sin_family = hp->h_addrtype;
	ctx->srvAddr.sin_port = htons(port);

	if ((ctx->fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return false;
	}
	return true;
}

bool udp_client_deinit(udp_client_ctx_t *ctx)
{
	if (ctx == NULL)
	{
		return false;
	}
	close(ctx->fd);
	ctx->fd = -1;
	bzero(&ctx->srvAddr, sizeof(ctx->srvAddr));
	return true;
}

bool udp_client_send(const udp_client_ctx_t *ctx, const char *message)
{
	if (ctx == NULL || message == NULL)
	{
		return false;
	}
	if (sendto(ctx->fd, message, strlen(message), MSG_CONFIRM, (const struct sockaddr *)&ctx->srvAddr, sizeof(ctx->srvAddr)) < 0 )
	{
		return false;
	}
	return true;
}

bool udp_client_rcv(const udp_client_ctx_t *ctx, char *message, size_t *msgLen)
{
	if (ctx == NULL || message == NULL || msgLen == NULL || *msgLen == 0)
	{
		return false;
	}
	int received;
	struct sockaddr_in srvAddr;
	memset(message, 0, *msgLen);
	if ((received = recvfrom(ctx->fd, message, *msgLen, MSG_WAITALL, (struct sockaddr *)&srvAddr, (socklen_t*)msgLen)) < 0)
	{
		return false;		
	}
	if ( memcmp(&ctx->srvAddr.sin_addr, &srvAddr.sin_addr, sizeof(srvAddr.sin_addr)) != 0)
	{
		return false;
	}
	return true; 
}
