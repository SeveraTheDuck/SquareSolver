#include "quadratic_equation.h"
#include "input_output.h"



#include <assert.h>



int main (void)
{
    quadratic_equation_coefs* coefs = ReadCoefs ();
    assert (coefs);

    quadratic_equation* equation = SolveQuadraticEquation (coefs);
    assert (equation);

    PrintRoots (equation);

    equation = EndSolver (equation);

    return 0;
}
