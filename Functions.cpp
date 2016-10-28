#include <iostream>

class Math
{
	private:
		int value = 0;
	public:
		Math(int a = 0)
		{
			value = a;
		};
		~Math(){};
		template <typename T> int sub(T b, T c);
		template <typename T> int div(T b, T c);
		template <typename T> void assign(T b);

};
		
		template <typename T>
		int Math::sub(T b, T c)
		{
			return b.value - c.value;
		}

		template <>
		int Math::sub<int>(int b, int c)
		{
			return b - c;
		}

		template <typename T>
		int Math::div(T b, T c)
		{
			if (c.value == 0)
			{
				throw; //should throw an exception instead
			}
			return b.value/c.value;
		}

		template <>
		int Math::div<int>(int b, int c)
		{
			if(c == 0)
			{
				throw; //should throw an exception instead
			}

			return b/c;	
		}

		template <typename T>
		void Math::assign(T b) //need to detect if parameter is object or primitive
		{
			this->value = b.value;
		}


int main()
{
	Math a;
	Math b(23);
	Math c(1);

	int d = a.sub(b, c);
	int e = a.sub(23, 1);
	std::cout << "Testing SUB of objects: " << d << "\n";
	std::cout << "Testing SUB of ints: " << e << "\n";

	return 0;
}