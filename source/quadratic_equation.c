/**
 * @file quadratic_equation.c
 *
 * @author SeveraTheDuck
 *
 * @brief Quadratic equation solver implementation
 *
 * @date 2024-06-27
 *
 * @copyright GNU GPL v.3
 *
 */



#include "quadratic_equation.h"



//------------------------------------------------------------------------------
// Doubles comparison
//------------------------------------------------------------------------------

/**
 * @brief Tolerance for double comparison
 */
static const double DOUBLES_CMP_TOLERANCE = DBL_EPSILON;


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
static inline doubles_cmp_status
CompareDoubles (double a,
                double b);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

/**
 * @brief Constructor for quardatic_equation structure
 *
 * @param coefs Coefficients of the equation
 * @param roots Roots of the equation
 *
 * @retval Pointer to quardatic_equation structure
 * @retval NULL if allocation error occurred
 *
 * @details Allocates memory for quardatic_equation structure and
 * initializes its fields with given pointers
 * The function does not copy coefficients or roots structures
 */
static quadratic_equation*
QuadraticEquationConstructor (quadratic_equation_coefs* coefs,
                              quadratic_equation_roots* roots);


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
RootsConstructor (double x1_root,
                  double x2_root,
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
RootsDestructor (quadratic_equation_roots* roots);


/**
 * @brief The function calculates roots of the equation and returns them
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
CalculateRoots (const quadratic_equation_coefs* coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Initializes fields with:
 * x1 = NaN, x2 = NaN, roots_number = QUADRATIC_EQUATION_NO_ROOTS
 */
static inline quadratic_equation_roots*
BothCasesNoRoots (void);


/**************************************
 * @defgroup QuadraticCase
 * @brief Quadratic case functions (a != 0)
 * @{
 **************************************/

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
SolveQuadraticCase (const quadratic_equation_coefs* coefs);


/**
 * @brief Finds discriminant of the quadratic equation
 *
 * @param coefs Coefficients of the quadratic equation
 *
 * @retval Discriminant value
 *
 * @details Formula \f$ D = b^2 - 4 \cdot a \cdot c \f$
 */
static inline double
FindDiscriminant (const quadratic_equation_coefs* coefs);


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
static inline quadratic_equation_roots*
QuadraticCaseOneRoot (const quadratic_equation_coefs* coefs);


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
static inline quadratic_equation_roots*
QuadraticCaseTwoRoots (const quadratic_equation_coefs* coefs,
                       double discriminant);

/**************************************
 * @}
 * End group QuadraticCase
 **************************************/


/**************************************
 * @defgroup QuadraticCase
 * @brief Linear case functions (a == 0)
 * @{
 **************************************/

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
 * LinearCaseOneRoot()  if b != 0
 * LinearCaseInfRoots() if b == 0 && c == 0
 */
static quadratic_equation_roots*
SolveLinearCase (const quadratic_equation_coefs* coefs);


/**
 * @brief Returns quadratic_equation_roots structure with initialized fields
 *
 * @retval Pointer to the structure
 * @retval NULL if allocation error occured
 *
 * @details Initializes fields with:
 * x1 = NaN, x2 = NaN, roots_number = QUADRATIC_EQUATION_INF_ROOTS
 */
static inline quadratic_equation_roots*
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
static inline quadratic_equation_roots*
LinearCaseOneRoot (const quadratic_equation_coefs* coefs);

/**************************************
 * @}
 * End group LinearCase
 **************************************/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Interface functions implementation
//------------------------------------------------------------------------------

quadratic_equation*
SolveQuadraticEquation (quadratic_equation_coefs* coefs)
{
    quadratic_equation_roots* roots = CalculateRoots (coefs);
    if (roots == NULL) return NULL;

    quadratic_equation* equation = QuadraticEquationConstructor (coefs, roots);
    if (equation == NULL) roots = RootsDestructor (roots);

    return equation;
}


quadratic_equation*
EndSolver (quadratic_equation* equation)
{
    if (equation == NULL) return NULL;

    equation->coefs = CoefsDestructor (equation->coefs);

    return QuadraticEquationDestructor (equation);
}


quadratic_equation*
QuadraticEquationDestructor (quadratic_equation* equation)
{
    if (equation == NULL) return NULL;

    equation->roots = RootsDestructor (equation->roots);

    free (equation);
    return NULL;
}


quadratic_equation_coefs*
CoefsConstructor (double a_coef,
                  double b_coef,
                  double c_coef)
{
    quadratic_equation_coefs* coefs =
        malloc (sizeof (quadratic_equation_coefs));
    if (coefs == NULL) return NULL;

    coefs->a = a_coef;
    coefs->b = b_coef;
    coefs->c = c_coef;

    return coefs;
}


quadratic_equation_coefs*
CoefsDestructor (quadratic_equation_coefs* coefs)
{
    free (coefs);
    return NULL;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Static functions implementation
//------------------------------------------------------------------------------

static quadratic_equation*
QuadraticEquationConstructor (quadratic_equation_coefs* coefs,
                              quadratic_equation_roots* roots)
{
    if (coefs == NULL ||
        roots == NULL) return NULL;

    quadratic_equation* equation =
        malloc (sizeof (quadratic_equation));
    if (equation == NULL) return NULL;

    equation->coefs = coefs;
    equation->roots = roots;

    return equation;
}


static quadratic_equation_roots*
RootsConstructor (double x1_root,
                  double x2_root,
                  quadratic_equation_roots_number roots_number)
{
    quadratic_equation_roots* roots =
        malloc (sizeof (quadratic_equation_roots));
    if (roots == NULL) return NULL;

    roots->x1           = x1_root;
    roots->x2           = x2_root;
    roots->roots_number = roots_number;

    return roots;
}


static quadratic_equation_roots*
RootsDestructor (quadratic_equation_roots* roots)
{
    free (roots);
    return NULL;
}


static quadratic_equation_roots*
CalculateRoots (const quadratic_equation_coefs* coefs)
{
    if (coefs == NULL) return NULL;

    if (CompareDoubles (coefs->a, 0) == DOUBLES_CMP_EQUAL)
        return SolveLinearCase (coefs);

    return SolveQuadraticCase (coefs);
}


static inline quadratic_equation_roots*
BothCasesNoRoots (void)
{
    return RootsConstructor (NAN, NAN, QUADRATIC_EQUATION_NO_ROOTS);
}


//-------------------------------------
// Quadratic case

static quadratic_equation_roots*
SolveQuadraticCase (const quadratic_equation_coefs* coefs)
{
    double discriminant = FindDiscriminant (coefs);

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

        case DOUBLES_CMP_UNDEFINED:
            return NULL;

        default:
            return NULL;
    }
}


static inline double
FindDiscriminant (const quadratic_equation_coefs* coefs)
{
    return coefs->b * coefs->b - 4 * coefs->a * coefs->c;
}


static inline quadratic_equation_roots*
QuadraticCaseOneRoot (const quadratic_equation_coefs* coefs)
{
    double x1_root = -coefs->b / 2 / coefs->a;
    return RootsConstructor (x1_root, NAN, QUADRATIC_EQUATION_ONE_ROOT);
}


static inline quadratic_equation_roots*
QuadraticCaseTwoRoots (const quadratic_equation_coefs* coefs,
                       double discriminant)
{
    const double x1_root = (-coefs->b - sqrt (discriminant)) / 2 / coefs->a;
    const double x2_root = (-coefs->b + sqrt (discriminant)) / 2 / coefs->a;
    return RootsConstructor (x1_root, x2_root, QUADRATIC_EQUATION_TWO_ROOTS);
}

//-------------------------------------


//-------------------------------------
// Linear case

static quadratic_equation_roots*
SolveLinearCase (const quadratic_equation_coefs* coefs)
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


static inline quadratic_equation_roots*
LinearCaseInfRoots (void)
{
    return RootsConstructor (NAN, NAN, QUADRATIC_EQUATION_INF_ROOTS);
}


static inline quadratic_equation_roots*
LinearCaseOneRoot (const quadratic_equation_coefs* coefs)
{
    double x1_root = -coefs->c / coefs->b;
    return RootsConstructor (x1_root, NAN, QUADRATIC_EQUATION_ONE_ROOT);
}
//-------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Doubles comparison implementation
//------------------------------------------------------------------------------

static inline doubles_cmp_status
CompareDoubles (double a,
                double b)
{
    if (isnan (a) || isnan (b)) return DOUBLES_CMP_UNDEFINED;

    if (a < b - DOUBLES_CMP_TOLERANCE) return DOUBLES_CMP_LESS;
    if (a > b + DOUBLES_CMP_TOLERANCE) return DOUBLES_CMP_GREATER;
    return DOUBLES_CMP_EQUAL;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
