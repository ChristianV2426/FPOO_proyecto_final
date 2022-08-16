/*
  Archivo: Orilla.h

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-07-15
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

/**
  CLASE: Orilla

  INTENCIÓN: con esta clase se esperan modelar las orillas del río.
  Como es un lugar, conserva las características y funcionalidades de los lugares. 

  RELACIONES:
  -Es un lugar.
  -Como es un lugar, contiene (por herencia) un nombre que lo identifica. 
  -Como es un lugar, conoce (por herencia) a los individuos que están en la orilla en cada momento. 
  -Como es un lugar, conoce (por herencia) a los lugares vecinos con los que colinda. 
*/

#ifndef ORILLA_H
#define ORILLA_H

#include <string>

#include "Lugar.h"
using namespace std;

class Orilla : public Lugar
{
  public:
  /**
    @brief Función constructora del objeto orilla. Inicializa el nombre de la orilla usando el constructor de la clase lugar (herencia). 
    @param nombreDeLaOrilla string que representa el nombre de la orilla.
  */
  Orilla(string nombreDeLaOrilla);

  /**
    @brief Función destructura del objeto orilla. No hace nada por ahora.
  */
  virtual ~Orilla();
};

#else
class Orilla;
#endif