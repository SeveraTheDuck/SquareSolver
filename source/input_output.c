/**
 * @file input_output.c
 *
 * @author SeveraTheDuck
 *
 * @brief Input and output functions implementation
 *
 * @date 2024-06-27
 *
 * @copyright GNU GPL v.3
 */



#include "input_output.h"



//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------

/// @brief Messages for input
const char* const INPUT_GREETINGS_MESSAGE = "Please, enter coefficients:";
const char* const INPUT_A_COEF_MESSAGE    = "a_coef:";
const char* const INPUT_B_COEF_MESSAGE    = "b_coef:";
const char* const INPUT_C_COEF_MESSAGE    = "c_coef:";
const char* const INPUT_CHECK_MESSAGE     = "Is it your equation? [Y]es [N]o";
const char* const BAD_INPUT_MESSAGE       = "Please, try again";

/// @brief Symbol to read to agree with input
const unsigned char INPUT_CHECK_SUCCESS = 'Y';

/// @brief Messages for output
const char* const OUTPUT_NOT_SOLVED_MESSAGE   = "The equation was not solved";
const char* const OUTPUT_ROOTS_NUMBER_MESSAGE = "Number of roots:";
const char* const OUTPUT_ONLY_ROOT_MESSAGE    = "The only root:";
const char* const OUTPUT_FIRST_ROOT_MESSAGE   = "First root:";
const char* const OUTPUT_SECOND_ROOT_MESSAGE  = "Second root:";
const char* const OUTPUT_NO_ROOTS_MESSAGE     = "No roots";
const char* const OUTPUT_INF_ROOTS_MESSAGE    = "Infinite number of roots";

/**
 * @brief Enumeration for input read status
 */
typedef
enum input_status
{
    BAD_INPUT = 0,  ///< invalid input
    SUCCESS   = 1   ///< ok input
}
input_status;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

/**
 * @brief Reads one coefficient from stdin
 *
 * @param input_message The message to print about the coefficient
 *
 * @retval The coefficient
 *
 * @details If scanf() error occured, asks to enter the coefficient again
 */
static double
ReadOneCoef (const char* input_message);


/**
 * @brief Prints your equation and asks whether it is correct ot not
 *
 * @param a_coef Coefficient before \f$ x^2 \f$
 * @param b_coef Coefficient before \f$ x \f$
 * @param c_coef Free coefficient
 *
 * @return input_status
 */
static input_status
CheckCoefs (double a_coef,
            double b_coef,
            double c_coef);


/**
 * @brief Prints error message if the equation was not solved
 *
 * @details This scenario may occure if you try
 * to change number of roots manualy
 */
static inline void
PrintNotSolvedError (void);


/**
 * @brief Prints message for no roots case
 */
static inline void
PrintNoRootsCase (void);


/**
 * @brief Prints message for one root case and the root
 *
 * @param root The root of the equation
 */
static inline void
PrintOneRootCase (double root);


/**
 * @brief Prints message for one root case and the roots
 *
 * @param root1 The first  root of the equation
 * @param root2 The second root of the equation
 */
static inline void
PrintTwoRootsCase (double root1,
                   double root2);


/**
 * @brief Prints message for infinite number of roots case
 *
 * @details Obviously, the function doesn't print roots :)
 */
static inline void
PrintInfRootsCase (void);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Input and output interface implementation
//------------------------------------------------------------------------------

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
PrintRoots (const quadratic_equation* equation)
{
    if (equation == NULL) return;

    const quadratic_equation_roots* roots = equation->roots;
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
        #if __STDC_VERSION__ >= 202300L
            [[fallthrough]];
        #endif

        default:
            PrintNotSolvedError ();
            break;
    }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Static functions implementation
//------------------------------------------------------------------------------

static double
ReadOneCoef (const char* input_message)
{
    input_status status = BAD_INPUT;
    double coef = 0.0;

    while (status == BAD_INPUT)
    {
        if (input_message != NULL) puts (input_message);

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
PrintOneRootCase (double root)
{
    printf ("%s 1\n%s %lf\n",
        OUTPUT_ROOTS_NUMBER_MESSAGE, OUTPUT_ONLY_ROOT_MESSAGE, root);
}


static inline void
PrintTwoRootsCase (double root1,
                   double root2)
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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
