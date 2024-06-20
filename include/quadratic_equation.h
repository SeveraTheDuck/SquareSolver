#pragma once



//-----------------------------------------------------------------------------
// Quadratic equation solver structs and types
//-----------------------------------------------------------------------------

/**
 * @brief Possible roots number for the quadratic equation
 */
typedef
enum quadratic_equation_roots_number
{
    QUADRATIC_EQUATION_NO_ROOTS   = 0,  ///< No roots
    QUADRATIC_EQUATION_ONE_ROOT   = 1,  ///< One root
    QUADRATIC_EQUATION_TWO_ROOTS  = 2,  ///< Two roots
    QUADRATIC_EQUATION_INF_ROOTS  = 3,  ///< Infinite number of roots
    QUADRATIC_EQUATION_NOT_SOLVED = 4   ///< The equation was not solved
}
quadratic_equation_roots_number;


/**
 * @brief A container for quadratic equation coefficients
 *
 * @details Quadratic equation has this form: ax^2 + bx + c = 0
 */
typedef
struct quadratic_equation_coefs
{
    double a;   ///< Coefficient before x^2
    double b;   ///< Coefficient before x
    double c;   ///< Free coefficient
}
quadratic_equation_coefs;


/**
 * @brief A container for quadratic equation roots
 *
 * @see SolveQuadraticEquation() for details about possible values
 */
typedef
struct quadratic_equation_roots
{
    double x1;  ///< First  root
    double x2;  ///< Second root
}
quadratic_equation_roots;


/**
 * @brief The main container for quadratic equation
 */
typedef
struct quadratic_equation
{
    quadratic_equation_coefs* coefs;                ///< Coefficients
    quadratic_equation_roots* roots;                ///< Roots
    quadratic_equation_roots_number roots_number;   ///< Number of roots
}
quadratic_equation;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Quadratic equation solver interface
//-----------------------------------------------------------------------------

/**
 * @brief Reads three coefficients from stdin
 *
 * @retval Pointer to the struct with the coefficients
 * @retval NULL if allocation error occured
 * @retval NULL if bad input  error occured (wrong coefficients number)
 *
 * @details Reads the coefficients and allocates memory for
 * quadratic_equations_coefs structure
 * Returns pointer to the structure upon success and NULL upon error
 */
quadratic_equation_coefs*
ReadQuadraticEquationCoefs (void);


/**
 * @brief Solves the equation with given coefficients
 *
 * @param coefs Pointer to the struct with the coefficients
 *
 * @retval Pointer to the struct with solved equation
 * @retval NULL if allocation error occured
 *
 * @details Solves the quadratic equation with given coefficients
 * Returns pointer to the structure upon success and NULL upon error
 * Possible roots values:
 * 1. The equation has two fractional roots => use their values
 * 2. One root                              => first root used, second is NaN
 * 3. No roots or infinite number           => both roots are set NaN
 */
quadratic_equation*
SolveQuadraticEquation (quadratic_equation_coefs* const coefs);


/**
 * @brief Prints output of quadratic equation
 *
 * @param equation Pointer to the struct with equation
 *
 * @details Prints number of roots and their values (for valid roots)
 * If the equation was not solved, prints error message
 */
void
PrintQuadraticEquationRoots (const quadratic_equation* const equation);


/**
 * @brief Destructor for the equation structure and its children
 *
 * @param equation Pointer to the struct with equation
 *
 * @retval NULL
 *
 * @details Destroys the equation, its coefficients and roots structures
 */
quadratic_equation*
EndQuadraticEquationSolver (quadratic_equation* const equation);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
