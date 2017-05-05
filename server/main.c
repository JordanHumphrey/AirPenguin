#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 6666

typedef struct              s_packet {
    uint16_t        port;
    char            name[20];
}			    s_packet;

int         error(const char *str) {
    perror(str);
    return 1;
}

int             main(int ac, char **av) {
    struct      sockaddr_in si_server, si_client;
    int         sock, recv_len, broadcast;
    s_packet    packet;
    socklen_t   slen;

    broadcast = 1;
    slen = sizeof(si_client);
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        return error("socket");
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
            &broadcast, sizeof(broadcast));
    memset((char *) &si_server, 0, sizeof(si_server));
    si_server.sin_family = AF_INET;
    si_server.sin_port = htons(PORT);
    si_server.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr*)&si_server, sizeof(si_server)) == -1)
        return error("bind");

    while (1) {
        memset((char*) &si_client, 0, sizeof(si_client));
        memset(&packet, 0, sizeof(s_packet));
        if ((recv_len = recvfrom(sock, &packet, sizeof(s_packet), 0, (struct sockaddr *) &si_client, &slen)) == -1)
            return error("recvfrom");
        if (packet.port != 0) {
            printf("%s:%d", inet_ntoa(si_client.sin_addr), packet.port);
            fflush(stdout);
            return 0;
        } else {
            memset(&packet, 0, sizeof(s_packet));
            strcat(packet.name, "TESTONE");
            if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*) &si_client, slen) == -1)
                return error("sendto");
        }
    }
    return 0;
}
