#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <sys/wait.h>

#include <unistd.h>

#include <arpa/inet.h>

#include <string.h>

#include "RoundTripClient.h"


RoundTripClient::RoundTripClient() {
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
}

void RoundTripClient::setPackageSize(int package_size) {
	this->package_size = package_size;
}

void RoundTripClient::setDstIp(char dst_ip[]) {
	strcpy(this->dst_ip, dst_ip);
}

void RoundTripClient::setDstPort(int dst_port) {
	this->dst_port = dst_port;
}


void RoundTripClient::roundTrip(int round_times) {
	printf("RoungTrip Running...\n");
	struct sockaddr_in their_addr;
	their_addr.sin_family = AF_INET; /* host byte order */
	their_addr.sin_port = htons(this->dst_port); /* short, network byte order */
	their_addr.sin_addr.s_addr = inet_addr(this->dst_ip);
	char *ipaddr = inet_ntoa(their_addr.sin_addr);
	bzero(&(their_addr.sin_zero), 8); /* zero the rest of the struct */

	if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {
		perror("connect");
		exit(1);
	}

	char buf[ARTRIBUTE_PACKAGE_SIZE];
	while (true) {
		// round times-------------------------BEGIN
		bzero(buf, ARTRIBUTE_PACKAGE_SIZE);
		sprintf(buf, "%d", round_times);

		// send 'round_times' to server.
		if (send(sockfd, buf, ARTRIBUTE_PACKAGE_SIZE, 0) == -1) {
			perror("send");
			break;
		}

		int recv_buf_size;
		// receive response for 'round_times' sending.
		if ((recv_buf_size = recv(sockfd, buf, ARTRIBUTE_PACKAGE_SIZE, 0)) == -1) {
			perror("recv");
			break;
		}
		// round times-------------------------END

		// package size-------------------------BEGIN
		bzero(buf, ARTRIBUTE_PACKAGE_SIZE);
		sprintf(buf, "%d", PACKAGE_SIZE);

		// send 'Package size' to server.
		if (send(sockfd, buf, ARTRIBUTE_PACKAGE_SIZE, 0) == -1) {
			perror("send");
			break;
		}

		// receive response for 'Package size' sending.
		if ((recv_buf_size = recv(sockfd, buf, ARTRIBUTE_PACKAGE_SIZE, 0)) == -1) {
			perror("recv");
			break;
		}
		// package size-------------------------END

		// send 'round_times' times test message
		int msg_size;
		char message[PACKAGE_SIZE];
		for (int i = 1; i <= round_times; ++i) {
			printf("Sending package (%d/%d).\n", i, round_times);
			if (send(sockfd, message, PACKAGE_SIZE, 0) == -1) {
				perror("send");
				break;
			}

			if ((msg_size = recv(sockfd, message, PACKAGE_SIZE, 0)) == -1) {
				perror("recv");
				break;
			}

		}
		break;

	}

	close(sockfd);

	printf("RoungTrip Ending...\n");
}
