#include "ende64.h"

void main(int argc, char **argv)
{
	int check[sizecheck] = { 0 };
	FILE *in, *out;
	if (checkmode(argc, argv, &in, &out, check))
	{
		if (check[2] == 'e')
		{
			encoder(in, out);
		}
		else
		{
			decoder(in, out, check[0]);
		}
		fclose(in);
		fclose(out);
	}
	output(check, argc, argv);
	return;
}