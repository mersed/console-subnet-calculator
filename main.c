#include <stdio.h>
#include <stdlib.h>

// Max length of ip chars plus one null terminator
#define IP_STRLEN 18


int to_binary(int decimal_number) {
	if(decimal_number < 2)
		return decimal_number;

	return to_binary(decimal_number / 2) * 10 + decimal_number % 2;
}	


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


char * get_subnet_id(char *ip_address, char *subnet_mask) {
	char *subnet_id = malloc(IP_STRLEN * sizeof(char));
	return subnet_id;
}

/*
char * get_broadcast_address(char *ip_address, char *mask) {
	char *subnet_id = malloc(IP_STRLEN * sizeof(char));
	return subnet_id;
}
*/


/**
 * Main function, which will receive argument as ip address, or
 * if you dont provide argument, you will be ask to insert it during the code
 * execution.
 */
int main(int argc, char **argv) {
	char *ip_address;
	char *subnet_mask;
	char *subnet_id;
	int force_arg_insertion = 0;
	int test = 5;
	int converted;

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

	while(force_arg_insertion == 1) {
		ip_address = ask_ip_input();
		subnet_mask = ask_subnet_mask_input();

		if(!(is_valid_ipv4(ip_address) == 0) && !(is_valid_ipv4(subnet_mask) == 0)) {
			force_arg_insertion = 0;
		}
		else {
			printf("IP address or subnet mask you inserted are invalid ... Please try again.\n");
		}
	}

	printf("Inserted ip address %s\n", ip_address);
	printf("Inserted subnet mask %s\n", subnet_mask);
	printf("-----------------------------------------\n");

	subnet_id = get_subnet_id(ip_address, subnet_mask);
	printf("Subnet id is: %s\n", subnet_id);

	converted = to_binary(test);
	printf("The decimal number %d is converted to binary %d\n", test, converted);

	return 0;
}




/*
int convert_binary(int a,int b,int c,int d);
int *  convert_binary1(int a);
main() {
	int i,j;	//loop index
	int ip[4];	// array to store ip seperated by "."
	int binary[32]; //store ip in binary
	int *bin;
	char *piece;
	char input[20];

	printf("\nEnter ip address:");
	scanf("%s",input);             //read ip as string

	piece = strtok(input,".");   //split . seperated ip , first call to the function strtok will return first piece in the string, subsequent calls to the function with null as first parameter will return subsequent pieces
	i=0;
	
	do {
		ip[i++]=atoi(piece);		// atoi(string) converts string to integer, store pieced string into integer array
		piece=strtok(NULL,".");		// this is subsequent call
	} while(piece && i<4);

	for(j=0;j<4;j++)  // loop through ips e.g 192.168.0.1  first loop will process ip[0] which has 192 stored
	{
		bin = convert_binary1( ip[j] );	//convert integer to binary , stored in integer array
		for(i=0;i<8;i++)
		{
			binary[j*8+i]=bin[i];   // store converted binary into correct position in 32 binary array
		}
	}

	for(i=0;i<32;i++)
	{
		if(i>0 && (i)%8==0) printf(".");   //print a "." after printing 8 digits
		printf("%d",binary[i]);		//print binary values of given ip saved in this int array
	}
	printf("\n");
}

//takes an integer as input
//returns binary stored in integer array
int * convert_binary1(int a) {
	int i,j,k,l;
	int *num=(int *)malloc(sizeof(int)*8);  //allocating memory of 8 integers
	for(i=0;i<=7;i++) {
		num[7-i]=a%2;
		a=a/2;
	}
	return num;
}

int convert_binary(int a,int b, int c, int d) {
	int i,j,k,l;
	int num[10];
	for(i=0;i<=7;i++) {
		num[i]=a%2;
		a=a/2;
	}
	//return(num);
	for(i=7;i>=0;i--) {
		printf("%d", num[i]);
	}
	printf(".");
	
	for(j=0;j<=7;j++) {
		num[j]=b%2;
		b=b/2;
	}

	for(j=7;j>=0;j--) {
		printf("%d", num[j]);
	}
	printf(".");

	for(k=0;k<=7;k++) {
		num[k]=c%2;
		c=c/2;
	}

	for(k=7;k>=0;k--) {
		printf("%d", num[k]);
	}
	printf(".");

	for(l=0;l<=7;l++) {
		num[l]=d%2;
		d=d/2;
	}
	for(l=7;l>=0;l--){ 
		printf("%d", num[l]);
	}
}
*/





