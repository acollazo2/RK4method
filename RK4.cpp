#include <cmath>
#include <iostream>
#include <format>
#include <map>



double yp(double x, double y)
{
	return -0.00003 * (y-288.03) * (y-961.97);
}


void printResult(std::map<double, double> map)
{
	static int count = 0;
	count++;

	if (count == 1)
	{
		std::cout << std::format("|{:^8}|{:^8}|", "xn", "yn") << std::endl;
		std::cout << std::string(19, '-') << std::endl;
	}

	for (const auto& x : map)
	{
		std::cout << std::format("|{:^8.2f}|{:^8.4f}|", x.first, x.second) << std::endl;
	}
}


void RK4(double starting_x, double starting_y, double final_x, double step, double (*func)(double, double))
{
	double current_x = starting_x;
	double current_y = starting_y;
	int iterations = std::round((final_x - starting_x)/step);
	std::map<double, double> output_data;

	for (int i = 0; i < iterations+1; i++)
	{
		output_data.insert({current_x, current_y});

		double k1 = func(current_x, current_y);
		double k2 = func(current_x + 0.5*step, current_y + 0.5*step*k1);
		double k3 = func(current_x + 0.5*step, current_y + 0.5*step*k2);
		double k4 = func(current_x + step, current_y + step*k3);

		current_y += (step/6) * (k1 + 2*k2 + 2*k3 + k4);

		current_x += step;
	}

	printResult(output_data);

}

int main()
{
	RK4(45, 375.02, 65, 4, &yp);
}