#include "utils.h"

int open_listenfd(int port){
    int listenfd, optval=1;
    struct sockaddr_in serveraddr;

    /* create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        return -1;
    }

    /* eliminate "address already in use" error from bind */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)) < 0){
        return -1;
    }

    /* listenfd will be an endpoint for all requests to port on any IP for this host */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);
    if (bind(listenfd, (SA *)&serveraddr, sizeof(serveraddr)) < 0){
        return -1;
    }

    /* make it a listening socket ready to accept requests */
    if (listen(listenfd, 1024) < 0){
        return -1;
    }

    return listenfd;
}

ssize_t rio_writen(int fd, char *usrbuf, size_t n){
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while (nleft > 0) {
        if ((nwritten = write(fd, bufp, nleft)) <= 0) {
            if (errno == EINTR) {  /* Interrupted by sig handler return */
                nwritten = 0; 
            } else {
                return -1;
            }
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}


void serve_static(int fd){
    int srcfd, filesize;
    char *srcp, buf[1024];
    struct stat st;

    stat("index.html", &st);
    filesize = st.st_size;

    /* Send response headers to client */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, "text/html");
    rio_writen(fd, buf, strlen(buf));
    /* Send response body to client */
    srcfd = open("index.html", O_RDONLY, 0);
    srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    close(srcfd);
    rio_writen(fd, srcp, filesize);
    munmap(srcp, filesize);
    
}