#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<netdb.h>
#include<netinet/in.h>

#include<string.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc,char * argv[])
{
    int socketfd , portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    if (argc <3)
    {
        fprintf(stderr, "usage %s hostname port\n",argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);

    /* step 1. Create a socket with the socket() system call */
    socketfd = socket(AF_INET,SOCK_STREAM,0);

    if (socketfd<0)
    {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);

    if (server == NULL){
        error("ERROR, no such host\n");
    }

    ///* Set N bytes of S to 0.  */
    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // # define	h_addr	h_addr_list[0] /* Address, for backward compatibility.*/
    ///* Copy N bytes of SRC to DEST (like memmove, but args reversed).  */
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    /*step 2. Connect the socket to the address of the server using the connect() system cal*/
    if (connect(socketfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        error("ERROR connecting");
    }

    /*
     Now ask for a message form the user ,this message will be read by server
    */
   
    printf("Please enter eth message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);

    /* step 3. Send and receive data */
    /* Send message to the server */

    n = write(socketfd,buffer,strlen(buffer));

    if ( n < 0 ){
        error("ERROR wirting to socket");
    }

    /* Now read server response */
    bzero(buffer,256);
    n = read(socketfd, buffer ,255);

    if(n<0){
        error("ERROR reading from socket");
    }

    printf("Echo from server: %s\n", buffer);

    close(socketfd);

    return 0;
}