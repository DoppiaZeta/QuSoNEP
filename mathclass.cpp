#include "mathclass.h"

const double MathClass::PI(3.141592653589793238462643383279502884197169399);


double MathClass::radToDeg(double degree) {
   return (180.0 / PI) * degree;
}


double MathClass::degToRad(double radiants) {
   return (PI / 180.0) * radiants;
}


double MathClass::degACosine(double cosine) {
   return radToDeg(acos(cosine));
}


double MathClass::degASine(double sine) {
   return radToDeg(asin(sine));
}


double MathClass::degATangent(double tangent) {
   return radToDeg(atan(tangent));
}


double MathClass::degCosine(double degree) {
   return cos(degToRad(degree));
}


double MathClass::degSine(double degree) {
   return sin(degToRad(degree));
}


double MathClass::degTangent(double degree) {
   return tan(degToRad(degree));
}
