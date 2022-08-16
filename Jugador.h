/*
  Archivo: Jugador.h

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-07-15
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

/**
  CLASE: Jugador

  INTENCIÓN: con esta clase se espera modelar al jugador que controla el juego. 
  El jugador es quien da las ordenes a los individuos para moverlos de una orilla a la otra usando la barca, intentando respetar al mismo tiempo las reglas del juego.
  Además, el jugador se encarga de mostrar en pantalla el estado del juego después de cada movimiento y es quien informa cuando se pierde o se gana en el juego. 

  RELACIONES:
  -El jugador conoce a todos los individuos del juego (robot(s), zorro(s), conejo(s), lechuga(s)). 
  -El jugador conoce a todos los lugares del juego (las dos orillas y la barca).   
*/

#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Individuo.h"
#include "Lugar.h"
#include "Barca.h"
#include "Orilla.h"
using namespace std;

class Jugador
{
  private:
  vector <Lugar*> todosLosLugares;
  vector <Individuo*> todosLosIndividuos;

  public:
  /**
    @brief Función constructora del objeto jugador. Se encarga de crear el objeto. No inicializa parametros. 
  */
  Jugador();

  /**
    @brief Función destructura del objeto jugador.
    Se encarga de devolver la memoria que se reservó para crear los objetos dinámicos que conoce el jugador y de los cuales tiene la propiedad temporal al momento de la destrucción.
  */
  virtual ~Jugador();

  /**
    @brief Función que se encarga de ingresar un nuevo lugar a la lista de lugares del juego. 
    @param nuevoLugar puntero a objeto de tipo lugar, que representa un nuevo lugar que hará parte del juego.
  */
  virtual void nuevoLugar(Lugar *nuevoLugar);

  /**
    @brief Función que se encarga de ingresar un nuevo individuo a la lista de individuos del juego.
    @param nuevoIndividuo puntero a objeto de tipo individuo, que representa un nuevo individuo que hará parte del juego.
  */
  virtual void nuevoIndividuo(Individuo *nuevoIndividuo);

  /**
    @brief Función que imprime en pantalla un mensaje informativo donde se listan cada uno de los lugares que hacen parte del juego
    junto con sus vecinos inmediato y alternativo al momento de llamar la función. 
  */
  virtual void cualesSonLosLugaresYSusVecinos();

  /**
    @brief Función que imprime en pantalla un mensaje informativo donde se listan cada uno de los lugares que hacen parte del juego
    junto con los individuos que están en ese lugar al momento de llamar la función. 
  */
  virtual void individuosEnCadaLugar();

  /**
    @brief Función auxiliar que se encarga de imprimir en pantalla el mensaje ingresado como parámetro, usando un alineado a la izquierda de 15 espacios.
    Los mensajes que se van a imprimir en pantalla usando esta función pretenden informar el estado actual del juego, por lo que al inicio del mensaje se agrega una línea como esta | 
    para simular las divisiones de espacio entre las orillas, la barca y el agua del río. 
    @param mensajeAImprimir string que contiene el dato que se va a imprimir en pantalla para representar la ubicación de los individuos en los lugares del juego después de cada movimiento. 
  */
  virtual void alinearEnPantalla(const string mensajeAImprimir);

  /**
    @brief Función que se encarga de imprimir en pantalla los lugares del juego junto con los individuos que están en cada lugar al momento de llamar la función.
    Esta función ayuda a tener una idea visual de cómo es el estado del juego después de cada movimiento.
  */
  virtual void imprimirEstadoActualDelJuego(const vector <string> &individuosEnOrillaIzquierda, const vector <string> &individuosEnBarca, const vector <string> &individuosEnOrillaDerecha, const bool barcaEnLaOrillaIzquierda);

  /**
    @brief Función que se encarga de imprimir en pantalla las instrucciones del juego.
  */
  virtual void imprimirInstrucciones();

  /**
    @brief Función que se encarga de verificar la convivencia de los individuos en todos los lugares del juego.
    En otras palabras, esta función verifica después de un movimiento si en alguno de los lugares, alguno de los individuos se come a otro. 
    @returns booleano. Retorna true si en algún lugar del juego un individuo se comió a su presa. Retorna false si hay buena convicencia en todos los lugares.
  */
  virtual bool hayConflictoEnAlgunLugar();

  /**
    @brief Función que se encarga de verificar en cada turno si el jugador ganó el juego.
    Es decir, esta función verifica si se logró el cometido de transportar todos individuos del juego hasta la orilla derecha. 
    @returns booleano. Retorna true si el jugador ganó el juego. Retorna false si aun no se han logrado las condiciones para ganar. 
  */
  virtual bool seTrasladaronTodosLosIndividuos();

  /**
    @brief Función que se encarga de iniciar, controlar y terminar el juego.
    Esta función se encarga de dirigir globalmente el transcurso del juego dependiendo de las decisiones que ingresa el jugador mediante el teclado.
    El flujo del juego va de la siguiente manera:

    -Inicialmente se imprime por una única vez las reglas del juego. 
    -Después se ingresa a un bucle que no termina hasta que el jugador pierda, se rinda o gane. 
    -Dentro del bucle se empieza por imprimir en pantalla el estado del juego en ese momento.
    -Después se verifican las condiciones de pérdida o ganancia del juego. 
    -A continuación se le pide al jugador que ingrese mediante el teclado la instrucción que desea realizar. 
    -Como paso siguiente se ejecuta el algoritmo propio de la instrucción ingresada. 
    -Se reinicia el ciclo. 
  */
  virtual void jugar();
};

#else
class Jugador;
#endif