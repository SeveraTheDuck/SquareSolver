/**
 * @file quadratic_equation.h
 *
 * @author SeveraTheDuck
 *
 * @brief Header file for quadratic equation solver
 *
 * @date 2024-06-27
 *
 * @copyright GNU GPL v.3
 */



#pragma once



#include <float.h>
#include <math.h>
#include <stdlib.h>



//------------------------------------------------------------------------------
// Quadratic equation solver structs and types
//------------------------------------------------------------------------------

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
 * @details Quadratic equation has this form:
 * \f$ ax^2 + bx + c = 0 \f$
 */
typedef
struct quadratic_equation_coefs
{
    double a;   ///< Coefficient before \f$ x^2 \f$
    double b;   ///< Coefficient before \f$ x \f$
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
    double x1;                                      ///< First  root
    double x2;                                      ///< Second root
    quadratic_equation_roots_number roots_number;   ///< Number of roots
}
quadratic_equation_roots;


/**
 * @brief The main container for quadratic equation
 */
typedef
struct quadratic_equation
{
    quadratic_equation_coefs* coefs;    ///< Coefficients
    quadratic_equation_roots* roots;    ///< Roots
}
quadratic_equation;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Quadratic equation solver interface
//------------------------------------------------------------------------------

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
SolveQuadraticEquation (quadratic_equation_coefs* coefs);


/**
 * @brief Destructor for the equation structure and its children
 *
 * @param equation Pointer to the struct with equation
 *
 * @retval NULL
 *
 * @details Destroys the equation, its coefficients and roots structures
 *
 * @note This function frees the memory allocated for coefficient structure
 */
quadratic_equation*
EndSolver (quadratic_equation* equation);


/**
 * @brief Destructor for the equation structure and its roots
 *
 * @param equation
 *
 * @retval NULL
 *
 * @details Destroys the equation and roots structures
 *
 * @note This function DOES NOT destroy equation coefficients
 * You should free the memory allocated for the coefficients, calling
 * for CoefsDestructor() function
 */
quadratic_equation*
QuadraticEquationDestructor (quadratic_equation* equation);


/**
 * @brief Constructor for the quadratic_equation_coefs structure
 *
 * @param a_coef Coefficient before \f$ x^2 \f$
 * @param b_coef Coefficient before \f$ x \f$
 * @param c_coef Free coefficient
 *
 * @retval pointer to the structure
 * @retval NULL if allocation error occurred
 *
 * @details Allocates memory for the structure and initializes it
 * with given values
 */
quadratic_equation_coefs*
CoefsConstructor (double a_coef,
                  double b_coef,
                  double c_coef);


/**
 * @brief Destructor for the quadratic_equation_coefs structure
 *
 * @param coefs Pointer to the structure
 *
 * @retval NULL
 *
 * @details Frees memory
 */
quadratic_equation_coefs*
CoefsDestructor (quadratic_equation_coefs* coefs);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
