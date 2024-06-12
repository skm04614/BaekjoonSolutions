#include <cstdio>

int main(void)
{
	char str[110]{};
	char buf[110]{};
	for (;;)
	{
		fgets(str, sizeof(str), stdin);
		if (*str == '.')
		{
			break;
		}

		char* pbuf = buf;
		for (char* pstr = str; *pstr; pstr++)
		{
			if (*pstr == '(' || *pstr == '[')
			{
				*pbuf++ = *pstr;
			}
			else if (*pstr == ')')
			{
				if (pbuf <= buf || *(pbuf - 1) != '(')
				{
					pbuf = nullptr;
					break;
				}
				pbuf--;
			}
			else if (*pstr == ']')
			{
				if (pbuf <= buf || *(pbuf - 1) != '[')
				{
					pbuf = nullptr;
					break;
				}
				pbuf--;
			}
		}
		printf("%s\n", pbuf == buf ? "yes" : "no");
	}

	return 0;
}