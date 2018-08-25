#include <stdio.h>

// Flushing the buffer after the fgets (extra characters).
void flush_input() {
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF);
}

/**
 * Main function, which will receive argument as ip address, or
 * if you dont provide argument, you will be ask to insert it during the code
 * execution.
 */
int main(int argc, char **argv) {
	char ip_address[17];
	char subnet_mask[17];

	printf("Insert IP address (decimal dotted notation): ");
	fgets(ip_address, 17, stdin);
	flush_input();

	printf("Insert subnet mask (decimal dotted notation): ");
	fgets(subnet_mask, 17, stdin);
	flush_input();

	printf("Inserted ip address %s\n", ip_address);
	printf("Inserted subnet mask %s\n", subnet_mask);
	return 0;
}