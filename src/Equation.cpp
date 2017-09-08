#include "Equation.h"



Equation::Equation(std::string start)
{

    equation = start;
}
Equation::Equation()
{


}
Equation::~Equation()
{
    //dtor
}
double Equation::convertToDouble(void)
{
    double result = equation[0] - '0';
    for (int i = 2; i <= equation.length() - 1; i += 2)
    {
        if (equation[i - 1] == '+')
            result += equation[i] - '0';
        if (equation[i - 1] == '-')
            result -= equation[i] - '0';
        if (equation[i - 1] == '*')
            result *= equation[i] - '0';
        if (equation[i - 1] == '/')
            result /= equation[i] - '0';

    }
    return result;
}


double Equation::get_fitness()
{
    return fitness;
}


std::string Equation::get_equation(void)
{
    return equation;
}


void Equation::set_fitness(double value, int goal)
{
    double dGoal = double(goal);
    if (abs(value - dGoal) != 0)
        fitness =  1.0 / abs(value - dGoal);
    else
        fitness = 2.0;
}

/// If (current/max > rand) survive

void Equation::generate(int digits)
{
    int max = (2*digits);
    max -= 1;
    char tmp[max];
    //std::cout << max << "\n";
    for (int i = 0; i < max; i ++)
    {

        if (i % 2 == 0)
        {

            int digit = rand() % 9 + 1;
            tmp[i] = digit + '0';
        }
        else
        {

            int sign = rand() % 4;
            if (sign == 0)
                tmp[i] = '+';
            if (sign == 1)
                tmp[i] = '-';
            if (sign == 2)
                tmp[i] = '*';
            if (sign == 3)
                tmp[i] = '/';
        }

    }
    equation = tmp;

}
