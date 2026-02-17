#include "lineac.h"

Lineac::Lineac() {
   immagine = GLOBAL::LINEAC;
}

void Lineac::disegna(int profondita) const {
   disegnaPoligono(profondita);
}
