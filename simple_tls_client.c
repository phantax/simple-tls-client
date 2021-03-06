#include<stdio.h>       //printf
#include<string.h>      //strlen
#include<sys/socket.h>  //socket
#include<arpa/inet.h>   //inet_addr

#define HOST "172.217.22.3"
#define PORT 443

int check(const uint8_t* data, uint32_t size) {

    int sock;
    struct sockaddr_in server;
    char reply[16*1024];
     
    //Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr(HOST);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    //Connect to remote server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return -1;
    }
     
    puts("Connected\n");
         
    //Send some data
    if( send(sock, data, size, 0) < 0)
    {
        puts("Send failed");
        return -1;
    }
     
    //Receive a reply from the server
    int n = recv(sock, reply, sizeof(reply), 0);
    if(n < 0)
    {
        puts("recv failed");
        return -1;
    }
     
    close(sock);


    int retval = 0;

    if (n >= 7) {
        if (reply[0] == 0x16) {
            /* >> handshake */
            retval = 0;
        } else if (reply[0] == 0x15) { 
            /* >> alert */
            retval = reply[6];
            if (retval == 0) {
                retval = 256;
            }
        }        
    }

    for (size_t i = 0; i < n; i++) {
        printf("%.02X ", (uint8_t)reply[i]);
    }
    printf("\n");

    return retval;
}


int main(int argc , char *argv[]) {

    uint8_t data[] = {
        0x16, 0x03, 0x01, 0x01, 0x2c, 0x01, 0x00, 0x01, 0x28, 0x03, 0x03, 0x40,
        0xc7, 0x0e, 0x24, 0x30, 0x01, 0xb9, 0x6d, 0x8c, 0x63, 0x68, 0x77, 0x38,
        0x69, 0x64, 0x32, 0xd3, 0xe6, 0xf9, 0x49, 0x10, 0x7a, 0xab, 0xad, 0x84,
        0x50, 0xcd, 0xff, 0xd6, 0xa2, 0x66, 0xe4, 0x00, 0x00, 0x92, 0xc0, 0x30,
        0xc0, 0x2c, 0xc0, 0x28, 0xc0, 0x24, 0xc0, 0x14, 0xc0, 0x0a, 0x00, 0xa3,
        0x00, 0x9f, 0x00, 0x6b, 0x00, 0x6a, 0x00, 0x39, 0x00, 0x38, 0x00, 0x88,
        0x00, 0x87, 0xc0, 0x32, 0xc0, 0x2e, 0xc0, 0x2a, 0xc0, 0x26, 0xc0, 0x0f,
        0xc0, 0x05, 0x00, 0x9d, 0x00, 0x3d, 0x00, 0x35, 0x00, 0x84, 0xc0, 0x2f,
        0xc0, 0x2b, 0xc0, 0x27, 0xc0, 0x23, 0xc0, 0x13, 0xc0, 0x09, 0x00, 0xa2,
        0x00, 0x9e, 0x00, 0x67, 0x00, 0x40, 0x00, 0x33, 0x00, 0x32, 0x00, 0x9a,
        0x00, 0x99, 0x00, 0x45, 0x00, 0x44, 0xc0, 0x31, 0xc0, 0x2d, 0xc0, 0x29,
        0xc0, 0x25, 0xc0, 0x0e, 0xc0, 0x04, 0x00, 0x9c, 0x00, 0x3c, 0x00, 0x2f,
        0x00, 0x96, 0x00, 0x41, 0xc0, 0x11, 0xc0, 0x07, 0xc0, 0x0c, 0xc0, 0x02,
        0x00, 0x05, 0x00, 0x04, 0xc0, 0x12, 0xc0, 0x08, 0x00, 0x16, 0x00, 0x13,
        0xc0, 0x0d, 0xc0, 0x03, 0x00, 0x0a, 0x00, 0x15, 0x00, 0x12, 0x00, 0x09,
        0x00, 0x14, 0x00, 0x11, 0x00, 0x08, 0x00, 0x06, 0x00, 0x03, 0x00, 0xff,
        0x01, 0x00, 0x00, 0x6d, 0x00, 0x0b, 0x00, 0x04, 0x03, 0x00, 0x01, 0x02,
        0x00, 0x0a, 0x00, 0x34, 0x00, 0x32, 0x00, 0x0e, 0x00, 0x0d, 0x00, 0x19,
        0x00, 0x0b, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x09, 0x00, 0x0a, 0x00, 0x16,
        0x00, 0x17, 0x00, 0x08, 0x00, 0x06, 0x00, 0x07, 0x00, 0x14, 0x00, 0x15,
        0x00, 0x04, 0x00, 0x05, 0x00, 0x12, 0x00, 0x13, 0x00, 0x01, 0x00, 0x02,
        0x00, 0x03, 0x00, 0x0f, 0x00, 0x10, 0x00, 0x11, 0x00, 0x23, 0x00, 0x00,
        0x00, 0x0d, 0x00, 0x20, 0x00, 0x1e, 0x06, 0x01, 0x06, 0x02, 0x06, 0x03,
        0x05, 0x01, 0x05, 0x02, 0x05, 0x03, 0x04, 0x01, 0x04, 0x02, 0x04, 0x03,
        0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03,
        0x00, 0x0f, 0x00, 0x01, 0x01 };

    return check(data, sizeof(data));
}

