#include "quadratic_equation.h"

/*
    TODO: inline CompareDoubles(), FindDiscriminant() and case functions
*/

//-----------------------------------------------------------------------------
// Doubles comparison
//-----------------------------------------------------------------------------

/**
 * @brief Possible results for doubles comparison
 */
typedef
enum doubles_cmp_status
{
    DOUBLES_CMP_LESS      = -1,     ///< first is less than second
    DOUBLES_CMP_EQUAL     =  0,     ///< first is equal to second
    DOUBLES_CMP_GREATER   =  1,     ///< first is greater than second
    DOUBLES_CMP_UNDEFINED =  2      ///< NaN input
}
doubles_cmp_status;


/**
 * @brief Compares two doubles
 *
 * @param a First  double to compare
 * @param b Second double to compare
 *
 * @retval Status @see doubles_cmp_status
 */
static doubles_cmp_status
CompareDoubles (const double a,
                const double b);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Static functions
//-----------------------------------------------------------------------------

/**
 * @brief Constructor for quardatic_equation structure
 *
 * @param coefs Coefficients of the equation
 * @param roots Roots of the equation
 *
 * @retval Pointer to quardatic_equation structure
 * @retval NULL if allocation error occurred
 * @retval NULL if bad input  error occurred (NaN coefficients)
 *
 * @details Allocates memory for quardatic_equation structure and
 * initializes its fields with given pointers
 * The function does not copy coefficients structure
 */
static quadratic_equation*
QuadraticEquationConstructor (quadratic_equation_coefs* const coefs,
                              quadratic_equation_roots* const roots);


/**
 * @brief Constructor for quardatic_equation_roots structure
 *
 * @param x1_root First  root
 * @param x2_root Second root
 * @param roots_number Number of roots of the equation
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Allocates memory for quardatic_equation_roots structure and
 * initializes its fields with given roots and number values
 */
static quadratic_equation_roots*
RootsConstructor (const double x1_root,
                  const double x2_root,
                  quadratic_equation_roots_number roots_number);


/**
 * @brief Destructor for the quardatic_equation_roots structure
 *
 * @param roots Pointer to the structure
 *
 * @retval NULL
 *
 * @details Frees allocated memory, returns NULL
 */
static quadratic_equation_roots*
RootsDestructor (quadratic_equation_roots* const roots);


/**
 * @brief The function finds roots of the equation and returns them
 *
 * @param coefs Coefficients of the equation
 *
 * @retval Pointer to the roots structure
 * @retval NULL if allocation error occured
 * @retval NULL if bad input  error occured (NaN coefficients)
 *
 * @details If a_coef == 0 calls for SolveQuadraticCase() function
 * Otherwise, calls for SolveLinearCase() function
 */
static quadratic_equation_roots*
FindRoots (const quadratic_equation_coefs* const coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Initializes fields with:
 * x1 = NaN, x2 = NaN, roots_number = QUADRATIC_EQUATION_NO_ROOTS
 */
static quadratic_equation_roots*
BothCasesNoRoots (void);


//-------------------------------------
// Quadratic case (a_coef != 0)

/**
 * @brief Finds the roots of the quadratic equation (a_coef != 0)
 *
 * @param coefs Coefficients of the quadratic equation
 *
 * @retval Pointer to the roots structure
 * @retval NULL if allocation error occured
 * @retval NULL if bad input  error occured
 *
 * @details Finds the discriminant (D) and calls for:
 * BothCasesNoRoots()      if D <  0
 * QuadraticCaseOneRoot()  if D == 0
 * QuadraticCaseTwoRoots() if D >  0
 * Returns NULL if D is NaN (bad input)
 */
static quadratic_equation_roots*
SolveQuadraticCase (const quadratic_equation_coefs* const coefs);


/**
 * @brief Finds discriminant of the quadratic equation
 *
 * @param coefs Coefficients of the quadratic equation
 *
 * @retval Discriminant value
 */
static double
FindDiscriminant (const quadratic_equation_coefs* const coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Finds the only root value in the quadratic case
 * and initializes fields with:
 * x1 = value, x2 = NaN, roots_number = QUADRATIC_EQUATION_ONE_ROOT
 */
static quadratic_equation_roots*
QuadraticCaseOneRoot (const quadratic_equation_coefs* const coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Finds both roots values in quadratic case
 * and initializes fields with:
 * x1 = value1, x2 = value2, roots_number = QUADRATIC_EQUATION_TWO_ROOTS
 */
static quadratic_equation_roots*
QuadraticCaseTwoRoots (const quadratic_equation_coefs* const coefs,
                       const double discriminant);
//-------------------------------------


//-------------------------------------
// Linear case (a_coef == 0)

/**
 * @brief Finds the roots of the linear equation (a_coef != 0)
 *
 * @param coefs Coefficients of the equation
 *
 * @retval Pointer to the roots structure
 * @retval NULL if allocation error occured
 * @retval NULL if bad input  error occured
 *
 * @details Calls for functions:
 * BothCasesNoRoots()   if b == 0 && c != 0
 * LiearCaseOneRoot()   if b != 0
 * LiearCaseInfRoots()  if b == 0 && c == 0
 */
static quadratic_equation_roots*
SolveLinearCase (const quadratic_equation_coefs* const coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Initializes fields with:
 * x1 = NaN, x2 = NaN, roots_number = QUADRATIC_EQUATION_INF_ROOTS
 */
static quadratic_equation_roots*
LinearCaseInfRoots (void);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Finds the only root in linear case
 * and initializes fields with:
 * x1 = value, x2 = NaN, roots_number = QUADRATIC_EQUATION_ONE_ROOT
 */
static quadratic_equation_roots*
LinearCaseOneRoot (const quadratic_equation_coefs* const coefs);
//-------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Interface functions implementation
//-----------------------------------------------------------------------------

quadratic_equation*
SolveQuadraticEquation (quadratic_equation_coefs* const coefs)
{
    if (coefs == NULL) return NULL;

    quadratic_equation_roots* roots = FindRoots (coefs);
    if (roots == NULL) return NULL;

    quadratic_equation* const equation =
        QuadraticEquationConstructor (coefs, roots);

    if (equation == NULL)
        roots = RootsDestructor (roots);

    return equation;
}


quadratic_equation*
QuadraticEquationDestructor (quadratic_equation* const equation)
{
    if (equation == NULL) return NULL;

    equation->coefs = CoefsDestructor (equation->coefs);
    equation->roots = RootsDestructor (equation->roots);

    free (equation);
    return NULL;
}


quadratic_equation_coefs*
CoefsConstructor (const double a_coef,
                  const double b_coef,
                  const double c_coef)
{
    quadratic_equation_coefs* const coefs =
        malloc (sizeof (quadratic_equation_coefs));
    if (coefs == NULL) return NULL;

    coefs->a = a_coef;
    coefs->b = b_coef;
    coefs->c = c_coef;

    return coefs;
}


quadratic_equation_coefs*
CoefsDestructor (quadratic_equation_coefs* const coefs)
{
    free (coefs);
    return NULL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Static functions implementation
//-----------------------------------------------------------------------------

static quadratic_equation*
QuadraticEquationConstructor (quadratic_equation_coefs* const coefs,
                              quadratic_equation_roots* const roots)
{
    if (coefs == NULL ||
        roots == NULL) return NULL;

    quadratic_equation* const equation =
        malloc (sizeof (quadratic_equation));
    if (equation == NULL) return NULL;

    equation->coefs = coefs;
    equation->roots = roots;

    return equation;
}


static quadratic_equation_roots*
RootsConstructor (const double x1_root,
                  const double x2_root,
                  quadratic_equation_roots_number roots_number)
{
    quadratic_equation_roots* const roots =
        malloc (sizeof (quadratic_equation_roots));
    if (roots == NULL) return NULL;

    roots->x1           = x1_root;
    roots->x2           = x2_root;
    roots->roots_number = roots_number;

    return roots;
}


static quadratic_equation_roots*
RootsDestructor (quadratic_equation_roots* const roots)
{
    free (roots);
    return NULL;
}


static quadratic_equation_roots*
FindRoots (const quadratic_equation_coefs* const coefs)
{
    if (coefs == NULL) return NULL;

    if (CompareDoubles (coefs->a, 0) == DOUBLES_CMP_EQUAL)
        return SolveLinearCase (coefs);

    return SolveQuadraticCase (coefs);
}


static quadratic_equation_roots*
BothCasesNoRoots (void)
{
    return RootsConstructor (NAN, NAN, QUADRATIC_EQUATION_NO_ROOTS);
}


//-------------------------------------
// Quadratic case
static quadratic_equation_roots*
SolveQuadraticCase (const quadratic_equation_coefs* const coefs)
{
    const double discriminant = FindDiscriminant (coefs);

    doubles_cmp_status discriminant_cmp_status =
        CompareDoubles (discriminant, 0);

    switch (discriminant_cmp_status)
    {
        case DOUBLES_CMP_LESS:
            return BothCasesNoRoots ();

        case DOUBLES_CMP_EQUAL:
            return QuadraticCaseOneRoot (coefs);

        case DOUBLES_CMP_GREATER:
            return QuadraticCaseTwoRoots (coefs, discriminant);

        default:
            return NULL;
    }
}


static double
FindDiscriminant (const quadratic_equation_coefs* const coefs)
{
    return coefs->b * coefs->b - 4 * coefs->a * coefs->c;
}


static quadratic_equation_roots*
QuadraticCaseOneRoot (const quadratic_equation_coefs* const coefs)
{
    const double x1_root = -coefs->b / 2 / coefs->a;
    return RootsConstructor (x1_root, NAN, QUADRATIC_EQUATION_ONE_ROOT);
}


static quadratic_equation_roots*
QuadraticCaseTwoRoots (const quadratic_equation_coefs* const coefs,
                       const double discriminant)
{
    const double x1_root = (-coefs->b - sqrt (discriminant)) / 2 / coefs->a;
    const double x2_root = (-coefs->b + sqrt (discriminant)) / 2 / coefs->a;
    return RootsConstructor (x1_root, x2_root, QUADRATIC_EQUATION_TWO_ROOTS);
}
//-------------------------------------


//-------------------------------------
// Linear case
static quadratic_equation_roots*
SolveLinearCase (const quadratic_equation_coefs* const coefs)
{
    doubles_cmp_status b_cmp_status = CompareDoubles (coefs->b, 0);
    doubles_cmp_status c_cmp_status = CompareDoubles (coefs->c, 0);

    if (b_cmp_status == DOUBLES_CMP_EQUAL &&
        c_cmp_status == DOUBLES_CMP_EQUAL)
        return LinearCaseInfRoots ();

    else if (b_cmp_status == DOUBLES_CMP_EQUAL &&
             c_cmp_status != DOUBLES_CMP_EQUAL)
        return BothCasesNoRoots ();

    return LinearCaseOneRoot (coefs);
}


static quadratic_equation_roots*
LinearCaseInfRoots (void)
{
    return RootsConstructor (NAN, NAN, QUADRATIC_EQUATION_INF_ROOTS);
}


static quadratic_equation_roots*
LinearCaseOneRoot (const quadratic_equation_coefs* const coefs)
{
    const double x1_root = -coefs->c / coefs->b;
    return RootsConstructor (x1_root, NAN, QUADRATIC_EQUATION_ONE_ROOT);
}
//-------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Doubles comparison implementation
//-----------------------------------------------------------------------------

static doubles_cmp_status
CompareDoubles (const double a,
                const double b)
{
    if (isnan (a) || isnan (b)) return DOUBLES_CMP_UNDEFINED;

    if (a < b - DBL_EPSILON) return DOUBLES_CMP_LESS;
    if (a > b + DBL_EPSILON) return DOUBLES_CMP_GREATER;
    return DOUBLES_CMP_EQUAL;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
