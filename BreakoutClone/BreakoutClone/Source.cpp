#include <iostream>
//declare initial int "x" to 0
int x = 0;
int main()
{
	//prints hello world to make sure the code runs
	std::cout << "Hello World" << std::endl;
	// adds a condition so if "x" is under 100 continue to loop
	while (x < 100)
	{
		//increase "x" by 1
		x++;
		//if condition for if "x" is equal to either 3 or 5 continue down the line of if statement
		if (x % 3 == 0 || x % 5 == 0)
		{
			//if "x" is equal to a multiple of 3 then type fizz then proceed
			if (x % 3 == 0)
			{
				std::cout << "Fizz";
			}
			//if "x" is equal to a multiple of 5 then type buzz and end line
			if (x % 5 == 0)
			{
				std::cout << "Buzz" << std::endl;
			}
			//otherwise end line
			else
			{
				std::cout << std::endl;
			}
		}
		//if the answer is not a multiple of 3 or 5 print "x"
		else
		{
			std::cout << x << std::endl;
		}
	}
	return 0;
}