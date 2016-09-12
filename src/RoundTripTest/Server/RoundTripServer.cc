
#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#include <string.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <sys/wait.h>

#include <arpa/inet.h>

#include <unistd.h>

#include "RoundTripServer.h"

RoundTripServer::RoundTripServer() {
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}
}

void RoundTripServer::setListenerPort(int listener_port) {
	struct sockaddr_in my_addr;
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(listener_port);
	my_addr.sin_addr.s_addr = INADDR_ANY;
//	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


	if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
		perror("bind");
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}
}

void RoundTripServer::start() {

	printf("Server is Running...\n");

	struct sockaddr_in their_addr;
	unsigned int sin_size;
	int new_fd;
	while(true) { /* main accept() loop */
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
		if (!fork()) { /* this is the child process */
			int round_times = 0;
			int recv_buf_size;
			char buf[ARTRIBUTE_PACKAGE_SIZE];

			int package_size;

			// receive first message with 'round_times'
			if ( (recv_buf_size = recv(new_fd, buf, ARTRIBUTE_PACKAGE_SIZE, 0)) == -1) perror("receive");
			else {
				printf("[ RECEIVE MESSAGE (round_times) : %s ]\n", buf);

				// parse the message and get the variable 'round_times'.
				if (sscanf(buf, "%d", &round_times) == EOF) {
					perror("sscanf");
				}

				if (send(new_fd, buf, ARTRIBUTE_PACKAGE_SIZE, 0) == -1) perror("send");
			}

			// receive second message with 'package size'
			if ( (recv_buf_size = recv(new_fd, buf, ARTRIBUTE_PACKAGE_SIZE, 0)) == -1) perror("receive");
			else {
				printf("[ RECEIVE MESSAGE (package_size): %s ]\n", buf);

				// parse the message and get the variable 'round_times'.
				if (sscanf(buf, "%d", &package_size) == EOF) {
					perror("sscanf");
				}

				if (send(new_fd, buf, ARTRIBUTE_PACKAGE_SIZE, 0) == -1) perror("send");
			}


			int msg_size;
			char message[package_size];
			// receive the rest message times 'round_times'
			for (int i = 1; i <= round_times; ++i) {
				if ( (msg_size = recv(new_fd, message, package_size, 0)) == -1) {
					perror("receive");
					break;	// if error occurs, close the socket and exit the child process
				}
				else {
					// printf("RECEIVE MESSAGE %d: %s\n", round_times, message);
					printf("Received message(%d/%d) size : %dB.\n", i, round_times, msg_size);
					if (send(new_fd, message, package_size, 0) == -1) {
						perror("send");
						break;
					}
				}
			}

			close(new_fd);
			exit(0);
		}
//		close(new_fd); /* parent doesn't need this */
		while(waitpid(-1,NULL,WNOHANG) > 0); /* clean up child processes */
	}

	printf("Server is over...\n");

}

