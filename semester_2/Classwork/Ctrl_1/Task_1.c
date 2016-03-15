#include <stdio.h>
#include <string.h>

void print4(unsigned char code) {
	static  unsigned char buf = 0;
	static char flag;
	if(code >= 15) {
		if(flag) {
			buf = (buf << 4) | 0b1111;
			printf("%c", buf);
			buf = 0;
			flag = 0;
		}
	}
	else {
		if(flag) {
			buf = (buf << 4) | code;
			putc(buf, stdout);
			buf = 0;
			flag = 0;
		}
		else {
			flag = 1;
			buf = code;
		}
	}
}

void encode() {
	int c;
	while(((c = getchar()) != EOF) && (c != '\n')) {
		if((c >= '0') && (c <= '9')) {
			print4(c - '0');
		}
		else {
			switch(c) {
				case '*':
					print4(0b1010);
					break;
				case '#':
					print4(0b1011);
					break;
				case 'a':
					print4(0b1100);
					break;
				case 'b':
					print4(0b1101);
					break;
				case 'c':
					print4(0b1110);
					break;
				default:
					printf("\nERROR\n");
					return;
			}
		}
	}
	print4(0b1111);
}
static char decode_table[15] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#', 'a', 'b', 'c'};


void decode() {
	int c;
	while(((c = getchar()) != EOF) && (c != '\n')) {
		unsigned char buf = c;
		if ((buf >> 4) < 15) {
			putc(decode_table[buf >> 4], stdout);
		}
		else {
			return;
		}
		if ((buf & 0b1111) < 15) {
			putc(decode_table[buf&0b1111], stdout);
		}
		else {
			return;
		}
	}
}

int main(int argc, char** argv) {
	if (argc == 2) {
		if(strlen(argv[1]) == 1) {
			switch(argv[1][0]) {
				case 'e':
					encode();
					break;
				case 'd':
					decode();
					break;
				default:
				break;
			}
		}
	}
	return 0;
}