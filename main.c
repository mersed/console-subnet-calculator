#include <stdio.h>

/**
 * Main function, which will receive argument as ip address, or
 * if you dont provide argument, you will be ask to insert it during the code
 * execution.
 */
int main(int argc, char **argv) {
	char ip_address[17];

	printf("Insert IP address (decimal dotted notation): ");
	fgets(ip_address, 17, stdin);

	printf("Inserted ip address %s\n", ip_address);
	return 0;
}