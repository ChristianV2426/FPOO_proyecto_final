/*
  Archivo: Barca.h

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-07-15
  Fecha de última modificación: 2022-08-08

  Licencia: GNU-GPL
*/

/**
  CLASE: Barca

  INTENCIÓN: con esta clase se espera modelar una barca que transporte a los individuos de una orilla a la otra.
  Cada barca tiene una restricción de espacio, y por ello solo puede transportar dos individuos al tiempo.
  Además, cada barca se puede mover unicamente si hay un robot en ella que la maneje.
  Como es un lugar, conserva las características y funcionalidades de los lugares. 


  RELACIONES:
  -Es un lugar.
  -Como es un lugar, contiene (por herencia) un nombre que lo identifica. 
  -Como es un lugar, conoce (por herencia) a los individuos que están en el espacio de la barca en cada momento. 
  -Como es un lugar, conoce (por herencia) a los lugares vecinos con los que colinda. 
*/

#ifndef BARCA_H
#define BARCA_H

#include <string>

#include "Lugar.h"
using namespace std;

class Barca : public Lugar
{
  public:
  /**
    @brief Función constructora del objeto barca. Inicializa el nombre de la barca usando el constructor de la clase lugar (herencia). 
    @param nombreDeLaBarca string que representa el nombre de la barca.
  */
  Barca(string nombreDeLaBarca);

  /**
    @brief Función destructura del objeto barca. No hace nada por ahora.
  */
  virtual ~Barca();

  /**
    @brief Función que se encarga de ingresar un nuevo individuo a este lugar. Particularmente la barca tiene una restricción de espacio: solamente caben un máximo de dos individuos.
    @param nuevoIndividuo puntero a objeto de tipo individuo, que representa un nuevo individuo que ingresa a este lugar.
    @returns booleano. Retona true si el lugar tiene espacio y acepta al nuevo individuo. Retorna false si no hay espacio para aceptar al nuevo individuo en este lugar.
  */
  virtual bool aceptarIndividuo(Individuo *nuevoIndividuo);
};

#else
class Barca;
#endif