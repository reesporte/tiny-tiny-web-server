/*
 * lets see if i can make a web server
 * */

#include "utils.h"

int main(int argc, char **argv){
	int listenfd, connfd, port;
	unsigned int clientlen;
	struct sockaddr_in clientaddr;


	/* Check command line args */
	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);

	fprintf(stdout, "web server started on port %d\n", port);
	listenfd = open_listenfd(port);

	while (1) {

		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
		fprintf(stdout, "server got a request\n");
		serve_static(connfd);
		fprintf(stdout, "server responded to request\n");
		
		close(connfd);

	}

	return 0;
}
