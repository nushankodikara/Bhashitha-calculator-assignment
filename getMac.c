#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_dl.h>

int main() {
    int fd;
    struct ifreq ifr;
    unsigned char *mac;

    // create socket
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) {
        perror("socket error");
        return 1;
    }

    // get MAC address
    strncpy(ifr.ifr_name, "en0", IFNAMSIZ-1);
    ifr.ifr_name[IFNAMSIZ-1] = '\0';
    if (ioctl(fd, SIOCGIFDLADDR, &ifr) < 0) {
        perror("ioctl error");
        return 1;
    }
    struct sockaddr_dl *sdl = (struct sockaddr_dl *)&ifr.ifr_addr;
    mac = (unsigned char*) LLADDR(sdl);

    // print MAC address
    printf("MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    close(fd);
    return 0;
}
