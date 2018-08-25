#include <stdio.h>
#include <stdlib.h>

#define IP_STRLEN 17


/**
 * Manualy implemented function for reading line as replacment for fgets.
 * Most importantly, this function will avoid limitations related with the
 * fgets, and will clear the buffer after the line is read (and if we have)
 * more characters inserted then its initially planed.
 */
int readln(char s[], int maxlen) {
	char ch;
	int i = 0;
	int char_remain = 1;

	while(char_remain) {
		ch = getchar();
		if((ch == '\n') || (ch == EOF)) {
			char_remain = 0;
		}
		else if (i < maxlen - 1) {
			s[i] = ch;
			i++;
		}
	}
	s[i] = '\0';
	return i;
}


char * ask_ip_input() {
	char *ip_address = malloc(IP_STRLEN * sizeof(char));
	printf("Insert IP address (decimal dotted notation): ");
	readln(ip_address, IP_STRLEN);
	return ip_address;
}


char * ask_subnet_mask_input() {
	char *subnet_mask = malloc(IP_STRLEN * sizeof(char));
	printf("Insert subnet mask (decimal dotted notation): ");
	readln(subnet_mask, IP_STRLEN);
	return subnet_mask;
}



/**
 * Main function, which will receive argument as ip address, or
 * if you dont provide argument, you will be ask to insert it during the code
 * execution.
 */
int main(int argc, char **argv) {
	char *ip_address;
	char *subnet_mask;

	ip_address = ask_ip_input();
	subnet_mask = ask_subnet_mask_input();

	printf("Inserted ip address %s\n", ip_address);
	printf("Inserted subnet mask %s\n", subnet_mask);
	return 0;
}