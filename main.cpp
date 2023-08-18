// данная программа решает квадратное уравнение вида ax^2 + bx + c = 0 в действительных числах

#include <stdio.h>
#include <math.h>
#define EPS 1.0e-15

int LinearEquation(double b, double c);                                        // случай линейного уравнения
int QuadraticEquation(double a, double b, double c, double* x1, double* x2);   // случай квадратного уравнения
double discriminant(double a, double b, double c);                             // нахождение дискриминанта
double FirstRoot(double D, double a, double b);                                // первый корень
double SecondRoot(double D, double a, double b);                               // второй корень
int input(double* a, double* b, double* c);                                    // ввод и проверка коэффициентов
void output(int NumberOfRoots, double x1, double x2);                          // вывод корней

int main(int argc, char** argv) {
    double a = 1, b = 2, c = 1;                                                // a, b, c - коэффициенты квадратного уравнения вида ax^2 + bx + c = 0
    double x1 = -1, x2 = 0;                                                    // x1 и x2 - корни уравнения
    int NumberOfRoots = 0;                                                     // количество корней квадратного уравнения

    printf("Let us solve the quadratic equation!\n");
    printf("Please, type the coefficients: ");
    if (!input(&a, &b, &c)) {                                                  // ввод и проверка коэффициентов
        printf("Please, check the input type");
        return 0;
    }

    if (fabs(a) < EPS) {                                                       // случай линейного уравнения
        LinearEquation(b, c);
        return 0;
    }

    NumberOfRoots = QuadraticEquation(a, b, c, &x1, &x2);                      // случай квадратного уравнения
    output(NumberOfRoots, x1, x2);
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

int QuadraticEquation(double a, double b, double c, double* x1, double* x2){
    double D = discriminant(a, b, c);
    if (D < 0) return 0;
    else if (D < EPS) {
        *x1 = - b / (2 * a);
        return 1;
    }
    else {
        *x1 = FirstRoot(D, a, b);
        *x2 = SecondRoot(D, a, b);
        return 2;
    }
}

int input(double* a, double* b, double* c) {
    if (scanf("%lf", a) != 1) return 0;
    if (scanf("%lf", b) != 1) return 0;
    if (scanf("%lf", c) != 1) return 0;
    return 1;
}

void output(int NumberOfRoots, double x1, double x2) {
    if (NumberOfRoots == 0)
        printf("Cannot be solved for real numbers");
    else if (NumberOfRoots == 1)
        printf("The only root is %lf", x1);
    else
        printf("The quadratic equation has two roots:\nx1 = %lf and x2 = %lf", x1, x2);
    return;
}
