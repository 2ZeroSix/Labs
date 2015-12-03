#include "ende64.h"

static unsigned char b64symb[64] = {
'A','B','C','D','E',
'F','G','H','I','J',
'K','L','M','N','O',
'P','Q','R','S','T',
'U','V','W','X','Y',
'Z','a','b','c','d',
'e','f','g','h','i',
'j','k','l','m','n',
'o','p','q','r','s',
't','u','v','w','x',
'y','z','0','1','2',
'3','4','5','6','7',
'8','9','+','/'};

static unsigned char b64numb[255];

//fill array b64numb
void b64num()
{
	static int check = 0;
	int i;
	// printf("b64num\n");
	if (check != 0)
		return;
	for(i = 0; i < 256; i++)
		b64numb[i] = 64;
	for(i = (unsigned char)'A'; i <= (unsigned char)'Z'; i++)
		b64numb[i] = i - (unsigned char)'A';
	for(i = (unsigned char)'a'; i <= (unsigned char)'z'; i++)
		b64numb[i] = i - (unsigned char)'a' + 26;
	for(i = (unsigned char)'0'; i <= (unsigned char)'9'; i++)
		b64numb[i] = i - (unsigned char)'0' + 52;
	b64numb[(unsigned char)'+'] = 62;		
	b64numb[(unsigned char)'/'] = 63;
	check++;
	// for(i = 0; i < 256; i++)
		// printf("%c: %d\n", (signed char)i, b64numb[i]);
	return;
}

void encoder(FILE *in, FILE *out)
{
	unsigned char c[3], b64[5] = { 0 }, count, i;
	printf("encode\n");
	while (count = fread(c, sizeof(char), 3, in))
	{
		for(i = count; i < 3; i++)
			c[i] = 0;
		b64[0] = b64symb[(c[0] >> 2) & 0x3f];
		b64[1] = b64symb[((c[0] << 4) | (c[1] >> 4)) & 0x3f];
		b64[2] = b64symb[((c[1] << 2) | (c[2] >> 6)) & 0x3f];
		b64[3] = b64symb[c[2] & 0x3f];
		for (i = count + 1; i < 4; i++)
			b64[i] = '=';
		fprintf(out, "%s", b64);
	}
	printf("encoded\n");
	return;
}


char decoder(FILE *in, FILE *out, int im)
{
	unsigned char c[3], b64[4], i, count = 3;
	long long j = 0;
	printf("decode\n");
	b64num();
	while(((signed char)(b64[0] = getc(in))) != EOF)
	{
		for (i = 0; i < 4; i++)
		{
			if (i > 0)
				b64[i] = getc(in);
			if((b64[i] != '=') && (count == 3))
			{
				while((b64numb[b64[i]] > 0x3f) && (im == 1) && ((signed char)b64[i] != EOF))
					{
						// printf("%d\n", b64[i]);
						b64[i] = getc(in);
					}
				if (b64numb[b64[i]] > 0x3f)
				{
					printf("code: %s\nsymbol num(0,...,255): %d\ncount of symbols before error: %lld\n", ((signed char)b64[i] == EOF) ? "EOF" : ">0x3f", b64[i], i + j);
					return 0;
				}
				b64[i] = b64numb[b64[i]];
			}
			else if ((i > 1) && (b64[i] == '='))
			{
				count = (count == 3) ? i - 1 : 1;
				b64[i] = 0;
			}
			else
			{
				printf("wrong2\n");
				return 0;
			}
		}
		if (count < 3)
			if (getc(in) != EOF)
			{
				printf("wrong3\n");
				return 0;
			}
		c[0] = (b64[0] << 2) | (b64[1] >> 4);
		c[1] = (b64[1] << 4) | (b64[2] >> 2);
		c[2] = (b64[2] << 6) | (b64[3]);
		fwrite(c, sizeof(char), count, out);
		j+=4;
	}
	printf("decoded\n");
	return 1;
}

int checkmode(int argc, char *argv[], FILE **in, FILE **out, int *check)
{
	int checkall = ((argc != 5) && (argc != 4)) ? 0 : 1, i;
	for(i = 0; i < 4; i++)
		check[i] = 0;
	check[4] = 1;
	i = 1;
	if (argc == 5)
		{
		if (strcmp(argv[i], "-i") == 0)
			check[0] = 1;
		checkall *= check[0];
		i++;
		}
	if (argc > i)
	{
		if (strcmp(argv[i], "-e") == 0)
			check[1] = 1;
		if (strcmp(argv[i], "-d") == 0)
			check[1] = 2;
		i++;
	}
	checkall *= check[1];
	if (argc > i)
	{
		if (*in = fopen(argv[i], (check[1] == 1) ? "rb" : "r"))
			check[2] = 1;
		i++;
	}
	checkall *= check[2];
	if (argc > i)
	{
		if (*out = fopen(argv[i], (check[1] == 1) ? "w" : "wb"))
			check[3] = 1;
	}
	checkall *= check[3];
	return checkall;
}

void output(int *check, int argc, char *argv[])
{
	static char *outcode[8] = {
	"wrong ignore mode:",
	"wrong encode/decode mode:",
	"wrong input file:",
	"wrong output file:",
	"wrong symbols in input file",
	"wrong count of args",
	"COMPLETE\nResult in output file",
	"ERROR\nInterface: <ignore mode> <decode/encode mode> <input file> <output file>\nIgnore modes:\n- <-i> - ignore nonBase64 symbols while decoding\n- empty - not ignore nonBase64 symbols\nDecode/encode modes:\n- <-d> - decode\n- <-e> - encode\nInput file\nOutput file\n"};
	int i = (argc == 5) ? 0 : 1, j = (argc == 5) ? 1 : 0, checkall = 1;
	for (i; i < sizecheck; i++)
	{
		if (check[i] == 0)
			printf("%s %s\n", outcode[i], (argc > (i + j)) ? argv[i + j] : "<none>");
		checkall *= check[i];
	}
	if ((argc != 4) && (argc != 5))
		printf("%s %d\n", outcode[i], argc);
	i++;
	if (checkall)
	{
		printf("%s\n", outcode[i]);
	}
	else
	{
		printf("%s\n", outcode[i + 1]);
	}
	return;
}