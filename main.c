#include <stdio.h>
#include <stdlib.h>

// Max length of ip chars plus one null terminator
#define IP_STRLEN 18


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


/**
 * Checks is IPV4 string valid.
 * Does it contains valid IPV4 address.
 */
int is_valid_ipv4 (char *str) {
    int segs = 0;   // Segment count.
    int chcnt = 0;  // Character count within segment.
    int accum = 0;  // Accumulator for segment.

    // Catch NULL pointer.
    if (str == NULL) return 0;

    // Process every character in string.
    while (*str != '\0') {

        // Segment changeover.
        if (*str == '.') {
        	// Must have some digits in segment.
            if (chcnt == 0) return 0;

            // Limit number of segments.
            if (++segs == 4) return 0;

            // Reset segment values and restart loop.
            chcnt = accum = 0;
            str++;
            continue;
        }

       	// Check numeric.
        if ((*str < '0') || (*str > '9')) return 0;

        // Acumulate and check segment (cannot be greather then 255)
        if ((accum = accum * 10 + *str - '0') > 255)
            return 0;

        chcnt++;
        str++;
    }

    /* Check enough segments and enough characters in last segment. */

    if (segs != 3)
        return 0;

    if (chcnt == 0)
        return 0;

    /* Address okay. */

    return 1;
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
	int force_arg_insertion = 0;

	if(argc < 3) {
		force_arg_insertion = 1;
	}
	else {
		// lets check that this what is inserted in correct format
		ip_address = argv[1];
		subnet_mask = argv[2];

		if(is_valid_ipv4(ip_address) == 0 || is_valid_ipv4(subnet_mask) == 0) {
			printf("IP address or subnet mask you inserted are invalid ... Please insert proper ones bellow \n");
			force_arg_insertion = 1;
		}
	}

	if(force_arg_insertion == 1) {
		ip_address = ask_ip_input();
		subnet_mask = ask_subnet_mask_input();
	}

	printf("Inserted ip address %s\n", ip_address);
	printf("Inserted subnet mask %s\n", subnet_mask);
	return 0;
}