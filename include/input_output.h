/**
 * @file input_output.h
 *
 * @author SeveraTheDuck
 *
 * @brief Input and output functions for quadratic equation solver
 *
 * @date 2024-06-27
 *
 * @copyright GNU GPL v.3
 */



#pragma once



#include "quadratic_equation.h"



#include <ctype.h>
#include <stdio.h>



//------------------------------------------------------------------------------
// Input and output interface
//------------------------------------------------------------------------------

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
ReadCoefs (void);


/**
 * @brief Prints output of the quadratic equation
 *
 * @param equation Pointer to the struct with equation
 *
 * @details Prints number of roots and their values (for valid roots)
 * If the equation was not solved, prints error message
 */
void
PrintRoots (const quadratic_equation* const equation);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
