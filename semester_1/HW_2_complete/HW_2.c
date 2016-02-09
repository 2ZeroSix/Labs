#include "ende64.h"

void main(int argc, char **argv)
{
	int check[sizecheck] = { 0 };
	FILE *in, *out;
	if (checkmode(argc, argv, &in, &out, check))
	{
		if (check[mode] == encode)
		{
			encoder(in, out);
		}
		else
		{
			check[decode] = decoder(in, out, check[ignore]);
		}
		fclose(in);
		fclose(out);
	}
	output(check, argc, argv);
	return;
}