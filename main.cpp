#include <stdio.h>
#include <math.h>

double LinearEquation(double b, double c);         // случай линейного уравнения
double discriminant(double a, double b, double c); // нахождение дискриминанта
double FirstRoot(double D, double a, double b);    // первый корень
double SecondRoot(double D, double a, double b);   // второй корень

int main(void) {
    double a, b, c;                                // a, b, c - коэффициенты квадратного уравнения вида ax^2 + bx + c = 0
    double D, x1, x2;                              // D - дискриминант уравнения, x1 и x2 - корни

    printf("Let us solve the quadratic equation!\n");
    printf("Please, type the coefficients: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a == 0) {
        if (b == 0 && c != 0)
            printf("Cannot be solved");
        else if (b == 0)
            printf("Any real number");
        else {
            x1 = LinearEquation(b, c);
            printf("The linear equation has the only root: %lf", x1);
        }
        return 0;
    }

    D = discriminant(a, b, c);
    if (D < 0) printf("Cannot be solved for real numbers.");
    else if (D == 0) {
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

double LinearEquation(double b, double c) {
    return -c / b;
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
