#include <iostream>
#include <string>
#include <typeinfo>

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
		template <typename T, typename W> void sub(T b, W c);
		template <typename T> void div(T b, T c);
		template <typename T> void assign(T b);
		void out();
};

		void Math::out()
		{
			std::cout << this->value << std::endl;
		}
		
		template <typename T, typename W>
		void Math::sub(T b, W c)
		{
			int checkB, checkC = 0;
			if(typeid(b).name() == "i")
			{

			}
		}

		template <>
		void Math::sub<int>(int b, int c)
		{
			this->value = b - c;
		}

		template <typename T>
		void Math::div(T b, T c)
		{
			if (c.value == 0)
			{
				throw; //should throw an exception instead
			}
			this->value = b.value/c.value;
		}

		template <>
		void Math::div<int>(int b, int c) //needs to be able to mix and match int and object
		{
			if(c == 0)
			{
				throw; //should throw an exception instead
			}

			this->value = b/c;	
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
	int myint = 12;

	// a.sub(b, c);
	std::cout << "Testing SUB of objects: " << "\n";
	a.out();

	std::cout << "Type is: " << typeid(b).name() << std::endl;

	// a.sub(b, 12);
	// std::cout << "Testing SUB of mixed types: " << "\n";
	// a.out();

	// a.sub(23, 1);
	std::cout << "Testing SUB of ints: " << "\n";
	a.out();

	return 0;
}