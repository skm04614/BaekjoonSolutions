#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>

class BigNum
{
	char sign;
	char num[10010];
	int digits;

public:
	BigNum()
		: BigNum{ "0" }
	{
	}

	BigNum(const BigNum& other)
		: sign{ other.sign },
		digits{ other.digits }
	{
		for (int i = 0; i < sizeof(num); i++)
		{
			num[i] = other.num[i];
		}
	}

	BigNum& operator=(const BigNum& other) = delete;

	BigNum(const char* val)
		: digits{ 0 }, sign{ 1 }
	{
		for (int i = 0; i < sizeof(num) - 1; i++)
		{
			num[i] = '0';
		}
		num[sizeof(num) - 1] = 0;

		if (*val == '-')
		{
			val++;
			sign = -1;
		}

		while (*val)
		{
			digits++;
			val++;
		}

		for (int i = 0; i < digits; i++)
		{
			num[i] = *(--val);
		}
	}

	BigNum operator+(const BigNum& other) const
	{
		BigNum result;
		int max_digits = digits > other.digits ? digits : other.digits;

		int carry = 0;
		int sum = 0;
		for (int i = 0; i < max_digits; i++)
		{
			sum = (sign * (num[i] - '0')) + (other.sign * (other.num[i] - '0')) + carry;
			if (sum < 0)
			{
				carry = 0;
				while (sum < 0)
				{
					sum += 10;
					carry -= 1;
				}
			}
			else
			{
				carry = sum / 10;
			}
			result.num[i] = (sum % 10) + '0';

			if (result.num[i] > '0')
			{
				result.digits = i + 1;
			}

		}

		if (carry < 0)
		{
			result.sign = -1;
			result.digits = 1;

			int sum2 = 0;
			int carry2 = 1;
			for (int i = 0; i < max_digits; i++)
			{
				sum2 = (carry2 + 9) - (result.num[i] - '0');
				carry2 = sum2 / 10;
				result.num[i] = (sum2 % 10) + '0';

				if (result.num[i] > '0')
				{
					result.digits = i + 1;
				}
			}

			carry++;
			if (carry < 0)
			{
				result.num[max_digits] = -1 * carry + '0';
				result.digits = max_digits + 1;
			}
		}
		else
		{
			result.num[max_digits] = carry + '0';
			if (carry > 0)
			{
				result.digits = max_digits + 1;
			}
		}

		return result;
	}

	void print() const
	{
		if (sign < 0)
		{
			printf("-");
		}

		for (int i = digits - 1; i >= 0; i--)
		{
			printf("%c", num[i]);
		}
	}
};

char A[10010];
char B[10010];

int main(void)
{
	scanf("%s %s", A, B);
	BigNum nA{ A };
	BigNum nB{ B };

	BigNum nC = nA + nB;
	nC.print();

	return 0;
}