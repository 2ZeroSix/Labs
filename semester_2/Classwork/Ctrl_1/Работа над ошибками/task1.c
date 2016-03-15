#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encode_table[256];

void init_encode_table() {
	static char flag = 1;
	if (flag) {
		int i;
		for (i = 0; i < 256; i++) {
			encode_table[i] = 16;
		}
		for(i = '0'; i <= '9'; i++) {
			encode_table[i] = i - '0';
		}
		encode_table['*'] = 0b1010;
		encode_table['#'] = 0b1011;
		encode_table['a'] = 0b1100;
		encode_table['b'] = 0b1101;
		encode_table['c'] = 0b1110;
		flag = 0;
	}
}

void encode() {
	int c;
	char odd = 0;
	init_encode_table();
	while(((c = getchar()) != EOF) && (c != '\n')) {
		if(encode_table[(unsigned char)c] != 16){
		printf("%X", encode_table[(unsigned char)c]);
		}
		else {
			printf("\nERROR: %c %d\n", c, c);
			return;
		}
		odd = (odd) ? 0 : 1;
	}
	if(odd) {
		printf("%X", 0b1111);
	}
}


char decode_table[256];

void init_decode_table(){
	static char flag = 1;
	if (flag) {
		int i;
		for (i = 0; i < 256; i++) {
			decode_table[i] = 0;
		}
		for(i = '0'; i <= '9'; i++) {
			decode_table[i] = i;
		}
		decode_table['A'] = '*';
		decode_table['B'] = '#';
		decode_table['C'] = 'a';
		decode_table['D'] = 'b';
		decode_table['E'] = 'c';
		decode_table['F'] = 'f';
		flag = 0;
	}
}

void decode() {
	int c;
	init_decode_table();
	while(((c = getchar()) != EOF) && (c != '\n')) {
		unsigned char buf = toupper(c);
		if (decode_table[buf]) {
			if(decode_table[buf] != 'f') {
				putc(decode_table[buf], stdout);
			}
			else {
				return;
			}
		}
		else {
			printf("\nERROR: %c %d", decode_table[buf], decode_table[buf]);
			return;
		}
	}
}

int main(int argc, char const *argv[]) {
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