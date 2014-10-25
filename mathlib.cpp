//mathlib.cpp
#include "mathlib.h"
const double PI_HALBE = 1.570796327;
const double E  = 2.718281829;
double frac(double x) // Nachkommateil von x
{
    if (x >= 0.0)
        return (x - floor(x));
    return (ceil(x) - x);
}
/*
FUNCTION arccot;
BEGIN
  arccot := Pi_Halbe - ArcTan(x);
END;

*/
double arccot(double x) // ArcusCotangens
{
    return PI_HALBE - atan(x);
}

/*FUNCTION arctanh;
BEGIN
  IF ABS(x) < 1.0 THEN
    arctanh := 0.5 * ln((1 + x) / (1 - x))
  ELSE
    LaufzeitFehler := TRUE
END;
*/
double arctanh(double x) // Arcus Tangens Hyperb.
{
    return 0.5 * log((1.0 + x) / (1.0 - x));
}

