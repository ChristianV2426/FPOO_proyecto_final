/*
  Archivo: Lugar.h

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-07-15
  Fecha de última modificación: 2022-08-08

  Licencia: GNU-GPL
*/

/**
  CLASE: Lugar

  INTENCIÓN: con esta clase se esperan modelar los lugares en los que conviven los individuos. 
  Como hay individuos que no pueden estar solos sin las supervisión de un robot (porque hay unos individuos que se comen a los otros),
  entonces los lugares son los responsables de verificar que haya armonía en su respectivo espacio después de cada movimiento.
  También son responsables de verificar que los individuos que están en su espacio se muevan a un lugar válido, es decir, que ninguno de sus individuos caíga al agua después de un movimiento. 

  RELACIONES:
  -Cada lugar contiene un nombre que lo identifica.
  -Cada lugar conoce a los individuos que están en ese espacio en particular.
  -Cada lugar conoce a los lugares que colindan con él (su vecino inmediato y su vecino alternativo).
*/

#ifndef LUGAR_H
#define LUGAR_H

#include <string>
#include <vector>

#include "Individuo.h"

using namespace std;

class Lugar
{
  private:
  string nombreDelLugar;
  vector <Individuo*> individuosEnEsteLugar;
  Lugar *vecinoInmediato, *vecinoAlternativo;

  public:
  /**
    @brief Función constructora del objeto lugar. Inicializa el nombre del lugar con el string ingresado como parámetro
    y adicionalmente inicializa los vecinos inmediato y alternativo del lugar, definiéndolos como punteros nulos. 
    @param nombreDelLugar string que representa el nombre del lugar.
  */
  Lugar(string nombreDelLugar);

  /**
    @brief Función destructura del objeto lugar. No hace nada por ahora.
  */
  virtual ~Lugar();

  /**
    @brief Función que retorna el nombre del lugar.
    @returns string que representa el nombre del lugar en cuestión. 
  */
  virtual string cualEsElNombreDelLugar();

  /**
    @brief Función que retorna el nombre del vecino inmediato.
    @returns string que representa el nombre del vecino inmediato.
  */
  virtual string cualEsTuVecinoInmediato();

  /**
    @brief Función que retorna el nombre del vecino alternativo.
    @returns string que representa el nombre del vecino alternativo.
  */
  virtual string cualEsTuVecinoAlternativo();

  /**
    @brief Función que retorna una lista con los nombres de todos los individuos que están en este lugar al momento de ejecutar la función.
    @returns vector de strings, que representa la lista de los nombres de todos los individuos que están en este lugar al momento de llamar la función.
  */
  virtual vector <string> cualesIndividuosEstanEnEsteLugar();

  /**
    @brief Función que retorna el número total de individuos que están en este lugar.
    @returns entero que representa el número total de individuos que están en este lugar. 
  */
  virtual int cuantosIndividuosHayEnEsteLugar();

  /**
    @brief Función que define un nuevo vecino inmediato para este lugar. Además hace que este lugar en particular se convierta en el vecino inmediato del lugar pasado como parámetro.
    @param nuevoVecinoInmediato puntero a objeto de tipo lugar, que representa el nuevo vecino inmediato.
  */
  virtual void nuevoVecinoInmediato(Lugar *nuevoVecinoInmediato);

  /**
    @brief Función que define un nuevo vecino alternativo para este lugar. Además hace que este lugar en particular se convierta en el vecino alternativo del lugar pasado como parámetro.
    @param nuevoVecinoAlternativo puntero a objeto de tipo lugar, que representa el nuevo vecino alternativo.
  */
  virtual void nuevoVecinoAlternativo(Lugar *nuevoVecinoAlternativo);

  /**
    @brief Función que intercambia el vecino inmediato (de este lugar) por el vecino alternativo (de este lugar) y viceversa.
  */
  virtual void intercambiarVecinos();

  /**
    @brief Función que se encarga de ingresar un nuevo individuo a este lugar.
    @param nuevoIndividuo puntero a objeto de tipo individuo, que representa un nuevo individuo que ingresa a este lugar.
    @returns booleano. Retona true si el lugar tiene espacio y acepta al nuevo individuo. Retorna false si no hay espacio para aceptar al nuevo individuo en este lugar.
  */
  virtual bool aceptarIndividuo(Individuo *nuevoIndividuo);

  /**
    @brief Función que se encarga de verificar la presencia de un individuo en este lugar. Utiliza el nombre del individuo (string) como dato de verificación.
    @param nombreDelIndividuo string que representa el nombre del individuo del que se quiere verificar su presencia en este lugar.
    @returns booleano. Retorna true si el individuo a verificar efectivamente se encuentra en este lugar. Retorna false en cualquier otro caso.
  */
  virtual bool estaEsteIndividuo(const string nombreDelIndividuo);

  /**
    @brief Función que se encarga de verificar la presencia de algunos individuos en este lugar. Utiliza una lista (vector) de individuos como dato de verificación.
    @param individuosEnPeligro vector de punteros a objetos de tipo individuo, que representa la lista de individuos cuya presencia se quiere verificar en este lugar.
    @param posicionDelIndividuoEnPeligro entero auxiliar que se pasa como referencia para poder modificarse más allá de su ámbito original. "Devuelve" la posición del primer individuo (de la lista de individuos a verificar) que efectivamente se encuentra en este lugar. 
    @returns booleano. Retorna true si al menos uno de los individuos a verificar se encuentra en este lugar. Retorna false si ninguno de los individuos a verificar se encuentra en este lugar.
  */
  virtual bool estaAlgunoDeEstosIndividuos(const vector <Individuo*> individuosEnPeligro, int &posicionDelIndividuoEnPeligro);

  /**
    @brief Función que se encarga de verificar la presencia de una lista completa de individuos en este lugar.
    @param individuosAVerificar vector de punteros a objetos de tipo individuo, que representa la lista de individuos cuya presencia se quiere verificar en este lugar. 
    @returns booleano. Retorna true si todos los individuos a verificar se encuentra en este lugar. Retorna false si hay al menos 1 individuo de la lista a verificar que no se encuentra en este lugar.
  */
  virtual bool estanTodosEstosIndividuos(const vector <Individuo*> individuosAVerificar);

  /**
    @brief Función se encarga de verificar si la instrucción ingresada como parámetro corresponde a la instrucción propia de alguno de los individuos del lugar.
    En caso de que así sea, la función se encarga de mover al individuo instruido desde este lugar hasta el lugar vecino inmediato, siempre que se cumplan las condiciones del juego.
    Por ejemplo, si el vecino inmediato es la barca y la barca ya está ocupada por dos indiviudos, entonces individuo no se puede mover y se queda en este lugar. 
    @param instruccion string que representa la instrucción ingresada por el jugador. Se espera verificar si alguno de los individuos de este lugar responde a esta instrucción.
    @param movimientoRealizado booleano que se pasa como referencia para poder modificarse más allá de su ámbito original. "Retorna" true cuando el individuo que responde a la instrucción se encuentra en este lugar. "Retorna" false en cualquier otro caso.
    @param elJugadorHaPerdido booleano que se pasa como referencia para poder modificarse más allá de su ámbito original. "Retorna" true cuando se cumplen las condiciones para ordenar el movimiento de un individuo pero el vecino inmediato del lugar es el agua, lo que quiere decir que el individuo en cuestión salta al río y se ahoga.
  */
  virtual void realizarMovimiento(const string instruccion, bool &movimientoRealizado, bool &elJugadorHaPerdido);

  /**
    @brief Función que se encarga de verificar la convivencia de los individuos en este lugar.
    En otras palabras, esta función verifica si después de un movimiento, alguno de los individuos de este lugar se come a otro.
    @returns booelano. Retorna true si hay al menos un individuo que se come a otro en este lugar. Retorna false si hay convivencia entre todos los individuos en este lugar.
  */
  virtual bool hayConflictoEnEsteLugar();

};

#else
class Lugar;
#endif