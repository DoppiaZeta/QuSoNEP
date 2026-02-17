#ifndef MATHCLASS_H
#define MATHCLASS_H

#include <math.h>

/*
  Classe MathClass
  sono funzioni matematiche con i gradi invece che con i radianti
*/

class MathClass{
   public:
      // math mathods with degree (no radiants)
      static double degSine(double degree);
      static double degCosine(double degree);
      static double degTangent(double degree);
      static double degASine(double sine);
      static double degACosine(double cosine);
      static double degATangent(double tangent);
      static double degToRad(double degree);
      static double radToDeg(double radiants);

      static const double PI;
};

#endif // MATHCLASS_H
