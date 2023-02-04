//Tobias Medina
//pek

#ifndef _PEK__RANDOM__H__
#define _PEK__RANDOM__H__

#include <PEK/pek.h>
#include <string>

_PEK_BEGIN

class Random
{

private:
	std::string _Seed = "0";

	std::string xorString(char x, char y) const 
	{
		if (x != y)
			return "1";
		return "0";
	}

	std::string LFSR(std::string base) const 
	{
		base.pop_back();
		std::string base1 = xorString(base[base.size() - 1], base[base.size() - 2]) + base;
		return base1;
	}

	/* generates a very large pseudo-random binary number */
	std::string generate()
	{
		_Seed = LFSR(_Seed);
		std::string end = _Seed;
		_Seed = LFSR(_Seed);
		end += _Seed;
		_Seed = LFSR(_Seed);
		end += _Seed;
		_Seed = LFSR(_Seed);
		end += _Seed;


		return end;
	}


	/* converts a single digit to character (no recommended)*/
	int toint(char x) const
	{
		for (int i = 0; i < 10; i++) {
			if (x == std::to_string(i)[0])
			{
				return i;
			}
		}

		return '1';
	}

	/* generates a long number (recommended)*/
	inline long generatel()
	{
		return atol(generate().c_str());
	}

	/*
	Adds all the characters of a binary number
	example: 101010111 = 1+0+1+0+1+0+1+1+1
	(recommended)
	*/
	std::string sum_c()
	{
		int result = 0;
		for (int i = 0; i < _Seed.length(); i++)
		{
			result += this->toint(generate()[i]);
		}

		return std::to_string(result);
	}

public:

	Random(const int _seed)
	{
		int _Seed = _seed;
		std::string bin = "";
		_Seed *= 4;

		if (_Seed > 0) 
		{
			while (_Seed > 0) 
			{
				if (_Seed % 2 == 0) 
				{
					bin = "0" + bin;
				}

				else 
				{
					bin = "1" + bin;
				}
				_Seed = (int)_Seed / 2;
			}
		}

		else if (_Seed == 0 || _Seed == 1 || _Seed == 2 || _Seed == 3) 
		{
			bin = "1010";
		}
		
		else
		{
			bin = "101010101101111";
		}

		this->_Seed = bin;
		srand((unsigned int) atoi(this->_Seed.c_str()));
	}

	Random()
	{
		this->_Seed = "10101101";
	}

	/* generates a pseudo-random number (recommended) */
	inline long double next()
	{
		return ((atoi(sum_c().c_str()) * 48432 / 432) * rand() * 3.14159265358979323846264338327950288 * 2.71828182845904523536028747135266250);
	}

	/* generates a pseudo-random number with a minimum value and a maximum value (recommended) */
	int next(int minValue, int maxValue)
	{
		if (minValue > maxValue) return 0;

		return minValue + ((int) next() + rand()) % (maxValue + 1 - minValue);
	}
};

_PEK_END
#endif