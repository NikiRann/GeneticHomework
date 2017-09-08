#ifndef EQUATION_H
#define EQUATION_H
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <cmath>


class Equation
{
    public:
        Equation(std::string);
        Equation();
        virtual ~Equation();
        double get_fitness(void);
        void set_fitness(double, int);
        void generate(int);
        double convertToDouble(void);
        std::string get_equation(void);
    protected:
    private:
        std::string equation;
        double fitness;
};

#endif // EQUATION_H
