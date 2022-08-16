/*
  Archivo: Barca.cpp

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-08-04
  Fecha de última modificación: 2022-08-08

  Licencia: GNU-GPL
*/

#include "Barca.h"

Barca::Barca(string nombreDeLaBarca) : Lugar(nombreDeLaBarca)
{
}

Barca::~Barca()
{
}

bool Barca::aceptarIndividuo(Individuo *nuevoIndividuo)
{
  if (cuantosIndividuosHayEnEsteLugar() == 2)
    return false;

  return Lugar::aceptarIndividuo(nuevoIndividuo);
}