// данная программа решает квадратное уравнение вида ax^2 + bx + c = 0 в действительных числах

#include <stdio.h>
#include <math.h>

const double EPS = 1.0e-9;
const int SS_INF_ROOTS = 3;

int LinearEquation(double b, double c, double* x1);                            // linear equation case
int QuadraticEquation(double a, double b, double c, double* x1, double* x2);   // square equation case
double discriminant(double a, double b, double c);                             // find discriminant
double FirstRoot(double sqrt_D, double a, double b);                           // first root
double SecondRoot(double sqrt_D, double a, double b);                          // second root
int input(double* a, double* b, double* c);                                    // input coefficients
void output(int NumberOfRoots, double x1, double x2);                          // output roots

int main(int argc, char** argv)
{
    double a = nan, b = nan, c = nan;                                          // a, b, c - square equation sort of ax^2 + bx + c = 0
    double x1 = -1, x2 = 0;                                                    // x1 & x2 - roots of the equation
    int NumberOfRoots = 0;                                                     // number of roots

    printf("Let us solve the quadratic equation!\n");
    printf("Please, type the coefficients: ");
    if (!input(&a, &b, &c))                                                    // input and check coefficients
    {
        printf("Please, check the input type");
        return 1;
    }

    if (fabs(a) < EPS)                                                         // linear equation case
    {
        NumberOfRoots = LinearEquation(b, c, &x1);
    }
    else
    {
        NumberOfRoots = QuadraticEquation(a, b, c, &x1, &x2);                  // square equation case
    }

    output(NumberOfRoots, x1, x2);
    return 0;
}

double discriminant(double a, double b, double c)
{
    return b * b - 4 * a * c;
}

double FirstRoot(double sqrt_D, double a, double b)
{
    return (-b + sqrt_D) / (2 * a);
}

double SecondRoot(double sqrt_D, double a, double b)
{
    return (-b - sqrt_D) / (2 * a);
}

int LinearEquation(double b, double c, double* x1)
{
    if (fabs(b) < EPS && fabs(c) >= EPS)                                       // no roots
    {
        return 0;
    }
    else if (fabs(b) < EPS)                                                    // inf roots
    {
        return SS_INF_ROOTS;
    }
    else                                                                       // one root
    {
        *x1 = - b / c;
        return 1;
    }
}

int QuadraticEquation(double a, double b, double c, double* x1, double* x2)
{
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    double D = discriminant(a, b, c);                                          // no roots
    if (D <= -EPS)
    {
        return 0;
    }
    else if (D < EPS)                                                          // one root
    {
        *x1 = - b / (2 * a);
        return 1;
    }
    else                                                                       // two roots
    {
        sqrt_D = sqrt(D);
        *x1 = FirstRoot(sqrt_D, a, b);
        *x2 = SecondRoot(sqrt_D, a, b);
        return 2;
    }
}

int input(double* a, double* b, double* c)
{
    if (scanf("%lf", a) != 1) return 0;
    if (scanf("%lf", b) != 1) return 0;
    if (scanf("%lf", c) != 1) return 0;

    assert(std::isfinite(*a));
    assert(std::isfinite(*b));
    assert(std::isfinite(*c));

    assert(std::isnan(*a));
    assert(std::isnan(*b));
    assert(std::isnan(*c));

    return 1;
}

void output(int NumberOfRoots, double x1, double x2)
{
    switch(NumberOfRoots)
    {
        case 0:
            printf("Cannot be solved");
            break;
        case 1:
            printf("The only root is %lf", x1);
            break;
        case 2:
            printf("The quadratic equation has two roots:\nx1 = %lf and x2 = %lf", x1, x2);
            break;
        case SS_INF_ROOTS:
            printf("Infinite number of roots");
            break;
        default:
            printf("Something went wrong");
            break;
    }
    return;
}
