#include "netinet/in.h"

#include <unistd.h>
#include <errno.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sockaddr SA;

int open_listenfd(int port);

ssize_t rio_writen(int fd, char *usrbuf, size_t n);

void serve_static(int fd);