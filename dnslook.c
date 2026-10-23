#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
     		printf("usage: dnslook [DOMAIN NAME] --ipv4/--ipv6\n");
        	return 1;
    	}

    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        	printf("syntax: dnslook [DOMAIN] --[ipv4/ipv6]\n"
               		"examples (after adding dnslook to system $PATH):\n"
               		"    dnslook google.com --ipv4\n"
               		"    dnslook gentoo.org --ipv6\n"
               		"errors:\n"
               		"    NXDOMAIN - non-existent domain\n");
        	return 0;
    	}

	if (argc < 3) {
		printf("usage: dnslook [DOMAIN NAME] --ipv4/--ipv6\n");
		return 1;
	}

	if (argc == 3 && strcmp(argv[2], "--ipv4") == 0) {
		char *domain = argv[1];
		struct addrinfo hints, *res;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_DGRAM;
		int domain_ip = getaddrinfo(domain, NULL, &hints, &res);
		if (domain_ip != 0) {
			printf("dnslook: NXDOMAIN\n");
			return 1;
		}
		struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
		char ipv4str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(ipv4->sin_addr), ipv4str, sizeof(ipv4str));
		printf("%s:\n", domain);
		printf("	IPV4: %s\n", ipv4str);
		freeaddrinfo(res);
		return 0;
	}

	if (argc == 3 && strcmp(argv[2], "--ipv6") == 0) {
		char *domain = argv[1];
		struct addrinfo hints, *res;
		memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_INET6;
		hints.ai_socktype = SOCK_DGRAM;
		int domain_ip = getaddrinfo(domain, NULL, &hints, &res);
		if (domain_ip != 0) {
			printf("dnslook: NXDOMAIN\n");
			return 1;
		}
		struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
		char ipv6str[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &(ipv6->sin6_addr), ipv6str, sizeof(ipv6str));
		printf("%s\n", domain);
		printf("	IPV6: %s\n", ipv6str);
		freeaddrinfo(res);
		return 0;
	}
	
	if (argc == 3 && strcmp(argv[2], "--ipv4") != 0 || strcmp(argv[2], "--ipv6") != 0) {
		printf("usage: dnslook [DOMAIN NAME] --ipv4/--ipv6\n");
		return 1;
	}
}
