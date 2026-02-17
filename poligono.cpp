#include "poligono.h"

Poligono::Poligono() {
   immagine = GLOBAL::POLIGONO;
}

void Poligono::disegna(int profondita) const {
   disegnaPoligono(profondita);
}
