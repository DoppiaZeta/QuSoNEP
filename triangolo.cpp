#include "triangolo.h"

Triangolo::Triangolo() {
   immagine = GLOBAL::TRIANGOLO;
}

void Triangolo::disegna(int profondita) const {
   disegnaPoligono(profondita);
}
