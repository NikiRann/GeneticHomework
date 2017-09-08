#include <iostream>
#include <Equation.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.3



const int N = 100; /// Number of equations we are gonna try

int number, k; /// Wanted number and the number of digits in the equation

Equation equations[N + 1];

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
int RandU(int nMin, int nMax)
{
    return nMin + (int)((double)rand() / (RAND_MAX+1) * (nMax-nMin+1));
}
std::string Roulette(double total_fitness, Equation* Population)
{
    //generate a random number between 0 & total fitness count
    double Slice = fRand(0, total_fitness);

    //go through the chromosones adding up the fitness so far
    double FitnessSoFar = 0.0;

    for (int i=0; i < N; i++)
    {
        FitnessSoFar += Population[i].get_fitness();

        //if the fitness so far > random number return the chromo at this point
        if (FitnessSoFar >= Slice)

            return Population[i].get_equation();
    }

    return "";
}


std::string Mutate(std::string input)
{
    std::string c = input;
    for (int i=0; i < c.length(); i++)
    {
        double r = fRand(0, 1);
        //std::cout << r << " ";
        if (r < MUTATION_RATE)
        {
            if (c[i] >= '0' && c[i] <= '9')
            {
                int gnum = rand() % 10;
                char digit = gnum + '0';
                c[i] = digit;
            }
            else
            {
                int sign = rand() % 4;
                if (sign == 0)
                    c[i] = '+';
                if (sign == 1)
                    c[i] = '-';
                if (sign == 2)
                    c[i] = '*';
                if (sign == 3)
                    c[i] = '/';
            }
        }
    }
    return c;
}

void Crossover(std::string &offspring1, std::string &offspring2)
{
  //dependent on the crossover rate
  double k = rand();
  if (k < CROSSOVER_RATE)
  {
    //create a random crossover point
    int crossover = RandU(0, (k*2 - 1));
    //crossover *= 2;
    std::string t1 = offspring1.substr(0, crossover) + offspring2.substr(crossover, (2*k - 1));
    std::string t2 = offspring2.substr(0, crossover) + offspring1.substr(crossover, (2*k - 1));

    offspring1 = t1; offspring2 = t2;
  }
}

void initiliazeEquations()
{
    Equation pusher;

    for (int i = 0; i < N; i ++)
    {

        pusher.generate(k);
        equations[i] = pusher;
    }
}

int main()
{
    std::cin >> number >> k;

    srand(time(NULL));

    initiliazeEquations();



    bool found = false;
    int generations = 0;
    while (!found)
    {
        generations ++;
        double totalfitness = 0.0;
        for (int i = 0; i < N; i ++)
        {
            equations[i].set_fitness(equations[i].convertToDouble(), number);
            totalfitness += equations[i].get_fitness();
        }

        for (int i = 0; i < N; i ++)
        {
            if (equations[i].get_fitness() == 2.0)
            {
                int countedDigits = 2;
                std::cout << "Generations: " << generations << " Equation: ";
                for (int p = 0; p < equations[i].get_equation().length(); p ++)
                {
                    std::cout << equations[i].get_equation()[p];
                    if (equations[i].get_equation()[p] > '0' && equations[i].get_equation()[p] < '9')
                        countedDigits ++;
                    if (countedDigits == k)
                        break;
                }
                std::cout << "\n";
                found = true;
            }
        }
        Equation temp[N + 1];
        int currentPopulation = 0;
        while (currentPopulation < N)
        {

            std::string offspring1 = Roulette(totalfitness, equations);
            std::string offspring2 = Roulette(totalfitness, equations);

            Crossover(offspring1, offspring2);
            //std::cout << offspring1 << "\n";
            offspring1 = Mutate(offspring1);
            //std::cout << offspring1 << "\n";
            offspring2 = Mutate(offspring2);
            temp[currentPopulation++] = Equation(offspring1);
            temp[currentPopulation++] = Equation(offspring2);
        }
        for (int i = 0; i < N; i ++)
            equations[i] = temp[i];

        //system("pause");
    }

    return 0;
}
