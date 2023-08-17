#include <stdio.h>
#include <math.h>
#define EPS 1.0e-15

int LinearEquation(double b, double c);         // случай линейного уравнения
double discriminant(double a, double b, double c); // нахождение дискриминанта
double FirstRoot(double D, double a, double b);    // первый корень
double SecondRoot(double D, double a, double b);   // второй корень

int main(void) {
    double a, b, c;                                // a, b, c - коэффициенты квадратного уравнения вида ax^2 + bx + c = 0
    double D, x1, x2;                              // D - дискриминант уравнения, x1 и x2 - корни

    printf("Let us solve the quadratic equation!\n");
    printf("Please, type the coefficients: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (fabs(a) < EPS) {                           // случай линейного уравнения
        LinearEquation(b, c);
        return 0;
    }

    D = discriminant(a, b, c);
    if (D < 0) printf("Cannot be solved for real numbers.");
    else if (D < EPS) {
        x1 = FirstRoot(D, a, b);
        printf("The only root is %lf", x1);
    }
    else {
        x1 = FirstRoot(D, a, b);
        x2 = SecondRoot(D, a, b);
        printf("The equation has two roots: %lf and %lf", x1, x2);
    }
    return 0;
}

int LinearEquation(double b, double c) {
    if (fabs(b) < EPS && fabs(c) >= EPS)
            printf("Cannot be solved");
        else if (fabs(b) < EPS)
            printf("Any real number");
        else {
            printf("The linear equation has the only root: %lf", -c / b);
        }
    return 0;
}

double discriminant(double a, double b, double c) {
    return b * b - 4 * a * c;
}

double FirstRoot(double D, double a, double b) {
    return (-b + sqrt(D)) / 2 / a;
}

double SecondRoot(double D, double a, double b) {
    return (-b - sqrt(D)) / 2 / a;
}
