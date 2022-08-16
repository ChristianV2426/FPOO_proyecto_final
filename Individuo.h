/*
  Archivo: Individuo.h

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-07-15
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

/**
  CLASE: Individuo

  INTENCIÓN: con esta clase se esperan modelar los actores principales del juego: robot(s), zorro(s), conejo(s), lechuga(s). 
  Cada individuo se caracteriza por conocer a los otros individuos que se puede comer.
  Además, cada individuo realiza un movimiento cuando escucha la instrucción que reconoce como propia (esta instrucción es única para cada individuo). 

  RELACIONES:
  -Cada individuo contiene un nombre que lo identifica. 
  -Cada individuo conoce a los otros individuos que se puede comer.
  -Cada individuo contiene una instrucción (de tipo string) que reconoce como propia y con la cual realiza un movimiento.  
*/

#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
#include <string>
using namespace std;

class Individuo
{
  private:
  string nombreDelIndividuo;
  vector <Individuo*> individuosQuePuedoComer;
  string instruccionPropia;

  public:
  /**
    @brief Función constructora del objeto individuo. Inicializa el nombre de cada individuo, así como la instrucción propia con la que va a realizar movimientos durante el juego. 
    @param nombreDelIndivido string que representa el nombre "genérico" del individuo (por ejemplo, "Robot" o "Conejo").
    @param instruccionPropia string que representa la instrucción que el individuo reconoce como propia y con la que va a realizaer movimientos durante el juego.
  */
  Individuo(string nombreDelIndividuo, string instruccionPropia);

  /**
    @brief Función destructura del objeto individuo. No hace nada por ahora.
  */
  virtual ~Individuo();

  /**
    @brief Función que retorna el nombre del individuo.
    @returns string que representa el nombre del individuo en cuestión. 
  */
  virtual string cualEsElNombreDelIndividuo();

  /**
    @brief Fución que retorna la instrucción propia de cada individuo. 
    @returns string que representa la instrucción propia de cada individuo y con la cual realiza movimientos durante el juego.
  */
  virtual string cualEsLaInstruccionDelIndividuo();

  /**
    @brief Función que retorna un vector con los otros individuos a los que este individuo en particular se puede comer. 
    @returns vector con punteros a objetos de tipo individuo, que representa la lista de individuos a los que este individuo en particular se puede comer. 
  */
  virtual vector <Individuo*> queIndividuosPuedoComer();

  /**
    @brief Función que hace que este individuo en particular reconozca a otro individuo como su potencial presa.  
    @param nuevaPresa puntero a objeto de tipo individuo, que representa al individuo que va a ser una potencial presa para este individuo en particular.
  */
  virtual void nuevaPresa(Individuo *nuevaPresa);

  /**
    @brief Función que verifica si cierta instrucción corresponde a la instrucción de este individuo en particular. 
    @returns booleano. Retorna true si la instrucción ingresada como argumento de la función corresponde a la instrucción propia de este individuo, retorna false en cualquier otro caso.
  */
  virtual bool esEstaTuInstruccion(const string instruccion);
};

#else
class Individuo;
#endif