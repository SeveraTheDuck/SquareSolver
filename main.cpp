#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <iostream>

const double EPS = 1.0e-9;

enum class TypeOfRoots
{
    SS_NO_ROOTS = 0,
    SS_ONE_ROOT = 1,
    SS_TWO_ROOTS = 2,
    SS_INF_ROOTS = 3
};

TypeOfRoots SolveLinearEquation(double b, double c, double* x1);                            // linear equation case
TypeOfRoots SolveQuadraticEquation(double a, double b, double c, double* x1, double* x2);   // square equation case
double FindDiscriminant(double a, double b, double c);                                      // find discriminant
double FindFirstRoot(double sqrt_D, double a, double b);                                    // first root
double FindSecondRoot(double sqrt_D, double a, double b);                                   // second root
bool GetInput(double* a, double* b, double* c);                                             // input coefficients
void PrintOutput(TypeOfRoots number_of_roots, double x1, double x2);                        // output roots

int main(int argc, char** argv)
{
    double a = 1, b = 2, c = 1;                                                             // a, b, c - square equation sort of ax^2 + bx + c = 0
    double x1 = -1, x2 = 0;                                                                 // x1 & x2 - roots of the equation
    TypeOfRoots number_of_roots = TypeOfRoots::SS_NO_ROOTS;

    printf("Let us solve the quadratic equation!\n");
    printf("Please, type the coefficients: ");
    if (!GetInput(&a, &b, &c))                                                              // input and check coefficients
    {
        printf("Please, check the input type");
        return 1;
    }

    if (fabs(a) < EPS)                                                                      // linear equation case
    {
        number_of_roots = SolveLinearEquation(b, c, &x1);
    }
    else
    {
        number_of_roots = SolveQuadraticEquation(a, b, c, &x1, &x2);                        // square equation case
    }

    PrintOutput(number_of_roots, x1, x2);
    return 0;
}

double FindDiscriminant(double a, double b, double c)
{
    return b * b - 4 * a * c;
}

double FindFirstRoot(double sqrt_D, double a, double b)
{
    return (-b + sqrt_D) / (2 * a);
}

double FindSecondRoot(double sqrt_D, double a, double b)
{
    return (-b - sqrt_D) / (2 * a);
}

TypeOfRoots SolveLinearEquation(double b, double c, double* x1)
{
    assert(x1 != NULL);

    if (fabs(b) < EPS && fabs(c) >= EPS)                                       // no roots
    {
        return TypeOfRoots::SS_NO_ROOTS;
    }
    else if (fabs(b) < EPS)                                                    // inf roots
    {
        return TypeOfRoots::SS_INF_ROOTS;
    }
    else                                                                       // one root
    {
        *x1 = - c / b;
        return TypeOfRoots::SS_ONE_ROOT;
    }
}

TypeOfRoots SolveQuadraticEquation(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    double D = FindDiscriminant(a, b, c);                                          // no roots
    if (D <= -EPS)
    {
        return TypeOfRoots::SS_NO_ROOTS;
    }
    else if (D < EPS)                                                          // one root
    {
        *x1 = - b / (2 * a);
        return TypeOfRoots::SS_ONE_ROOT;
    }
    else                                                                       // two roots
    {
        double sqrt_D = sqrt(D);
        *x1 = FindFirstRoot(sqrt_D, a, b);
        *x2 = FindSecondRoot(sqrt_D, a, b);
        return TypeOfRoots::SS_TWO_ROOTS;
    }
}

bool GetInput(double* a, double* b, double* c)
{
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(a != b);
    assert(a != c);
    assert(b != c);

    if (scanf("%lf", a) != 1) return false;
    if (scanf("%lf", b) != 1) return false;
    if (scanf("%lf", c) != 1) return false;

    assert(std::isfinite(*a));
    assert(std::isfinite(*b));
    assert(std::isfinite(*c));

    assert(!isnan(*a));
    assert(!isnan(*b));
    assert(!isnan(*c));

    return true;
}

void PrintOutput(TypeOfRoots number_of_roots, double x1, double x2)
{
    switch(number_of_roots)
    {
        case TypeOfRoots::SS_NO_ROOTS:
            printf("Cannot be solved");
            break;
        case TypeOfRoots::SS_ONE_ROOT:
            printf("The only root is %lf", x1);
            break;
        case TypeOfRoots::SS_TWO_ROOTS:
            printf("The quadratic equation has two roots:\nx1 = %lf and x2 = %lf", x1, x2);
            break;
        case TypeOfRoots::SS_INF_ROOTS:
            printf("Infinite number of roots");
            break;
        default:
            printf("Something went wrong");
            break;
    }
    return;
}
