#include "input_output.h"



//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------

const char* const INPUT_GREETINGS_MESSAGE = "Please, enter coefficients:";
const char* const INPUT_A_COEF_MESSAGE    = "a_coef:";
const char* const INPUT_B_COEF_MESSAGE    = "b_coef:";
const char* const INPUT_C_COEF_MESSAGE    = "c_coef:";
const char* const INPUT_CHECK_MESSAGE     = "Is it your equation? [Y]es [N]o";
const char* const BAD_INPUT_MESSAGE       = "Please, try again";

const unsigned char INPUT_CHECK_SUCCESS = 'Y';

const char* const OUTPUT_NOT_SOLVED_MESSAGE   = "The equation was not solved";
const char* const OUTPUT_ROOTS_NUMBER_MESSAGE = "Number of roots:";
const char* const OUTPUT_ONLY_ROOT_MESSAGE    = "The only root:";
const char* const OUTPUT_FIRST_ROOT_MESSAGE   = "First root:";
const char* const OUTPUT_SECOND_ROOT_MESSAGE  = "Second root:";
const char* const OUTPUT_NO_ROOTS_MESSAGE     = "No roots";
const char* const OUTPUT_INF_ROOTS_MESSAGE    = "Infinite number of roots";

typedef
enum input_status
{
    BAD_INPUT = 0,  ///< invalid input
    SUCCESS   = 1   ///< ok input
}
input_status;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Static functions
//-----------------------------------------------------------------------------

static double
ReadOneCoef (const char* const restrict input_message);


static input_status
CheckCoefs (double a_coef,
            double b_coef,
            double c_coef);


static inline void
PrintNotSolvedError (void);


static inline void
PrintNoRootsCase (void);


static inline void
PrintOneRootCase (const double root);


static inline void
PrintTwoRootsCase (const double root1, const double root2);


static inline void
PrintInfRootsCase (void);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Input and output interface implementation
//-----------------------------------------------------------------------------

quadratic_equation_coefs*
ReadCoefs (void)
{
    input_status status = BAD_INPUT;
    double a_coef = 0.0;
    double b_coef = 0.0;
    double c_coef = 0.0;

    while (status == BAD_INPUT)
    {
        puts (INPUT_GREETINGS_MESSAGE);

        a_coef = ReadOneCoef (INPUT_A_COEF_MESSAGE);
        b_coef = ReadOneCoef (INPUT_B_COEF_MESSAGE);
        c_coef = ReadOneCoef (INPUT_C_COEF_MESSAGE);

        status = CheckCoefs (a_coef, b_coef, c_coef);

        if (status == BAD_INPUT) puts (BAD_INPUT_MESSAGE);
    }

    return CoefsConstructor (a_coef, b_coef, c_coef);
}


void
PrintRoots (const quadratic_equation* const equation)
{
    if (equation == NULL) return;

    const quadratic_equation_roots* const roots = equation->roots;
    if (roots == NULL) return;

    switch (roots->roots_number)
    {
        case QUADRATIC_EQUATION_NO_ROOTS:
            PrintNoRootsCase ();
            break;

        case QUADRATIC_EQUATION_ONE_ROOT:
            PrintOneRootCase (roots->x1);
            break;

        case QUADRATIC_EQUATION_TWO_ROOTS:
            PrintTwoRootsCase (roots->x1, roots->x2);
            break;

        case QUADRATIC_EQUATION_INF_ROOTS:
            PrintInfRootsCase ();
            break;

        case QUADRATIC_EQUATION_NOT_SOLVED:
            PrintNotSolvedError ();
            break;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Static functions implementation
//-----------------------------------------------------------------------------

static double
ReadOneCoef (const char* const restrict input_message)
{
    input_status status = BAD_INPUT;
    double coef = 0.0;

    while (status == BAD_INPUT)
    {
        input_message != NULL && puts (input_message);

        if (scanf ("%lf", &coef) == 1) status = SUCCESS;
        else puts (BAD_INPUT_MESSAGE);
    }

    return coef;
}


static input_status
CheckCoefs (double a_coef,
            double b_coef,
            double c_coef)
{
    unsigned char answer = 0;

    printf ("%s\n%lfx^2 + %lfx + %lf = 0\n",
        INPUT_CHECK_MESSAGE, a_coef, b_coef, c_coef);

    do answer = getchar ();
    while (answer == '\n');

    if (toupper (answer) == INPUT_CHECK_SUCCESS)
        return SUCCESS;

    return BAD_INPUT;
}


static inline void
PrintNotSolvedError (void)
{
    puts (OUTPUT_NOT_SOLVED_MESSAGE);
}


static inline void
PrintNoRootsCase (void)
{
    puts (OUTPUT_ROOTS_NUMBER_MESSAGE);
    puts (OUTPUT_NO_ROOTS_MESSAGE);
}


static inline void
PrintOneRootCase (const double root)
{
    printf ("%s 1\n%s %lf\n",
        OUTPUT_ROOTS_NUMBER_MESSAGE, OUTPUT_ONLY_ROOT_MESSAGE, root);
}


static inline void
PrintTwoRootsCase (const double root1, const double root2)
{
    printf ("%s 2\n%s %lf\n%s %lf\n",
        OUTPUT_ROOTS_NUMBER_MESSAGE,
        OUTPUT_FIRST_ROOT_MESSAGE,  root1,
        OUTPUT_SECOND_ROOT_MESSAGE, root2);
}


static inline void
PrintInfRootsCase (void)
{
    puts (OUTPUT_ROOTS_NUMBER_MESSAGE);
    puts (OUTPUT_INF_ROOTS_MESSAGE);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------