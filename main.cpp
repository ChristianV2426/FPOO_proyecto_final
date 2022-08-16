/*
  Archivo: main.cpp

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-08-04
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

/**
  HISTORIA: Este programa implementa un juego de lógica.
  En el juego hay 4 individuos: un robot, un zorro, un conejo y una lechuga.
  El juego consiste en transportar todos los individuos de la orilla izquierda de un río hasta la orilla derecha, usando una barca. 

  Hay ciertas restricciones pare el transporte de los individuos:
  -Hay una sola barca y esta unicamente se mueve cuando el robot está en ella. Además, en la barca solo cabe otro individuo además del robot.
  -Hay algunos individuos que se comen a otros si el robot no está presente para imperdirlo. Por eso no se deben dejar solos al zorro y al conejo, o al conejo y a la lechuga.
  -Si un individuo intenta saltar a la barca y la barca no está allí, entonces se cae al agua y el juego termina. 

  Para jugar, el jugador puede dar ordenes usando el teclado de la siguiente manera:
  -Pulsar B para que la barca se mueva de orilla.
  -Pulsar R para que el robot salte de o hacía la barca.
  -Pulsar Z para que el zorro salte de o hacía la barca. 
  -Pulsar C para que el conejo salte de o hacía la barca.
  -Pulsar L para que la lechuga salte de o hacía la barca. 

  Después de cada orden el jugador verá en pantalla el estado del juego. Por ejemplo, al empezar el juego el estado será:
  | IZQUIERDA      | BARCA          |                | DERECHA        |
  | Robot          |                |                |                |
  | Zorro          |                |                |                |
  | Conejo         |                |                |                |
  | Lechuga        |                |                |                |

  El estado final al que se debe llegar es:
  | IZQUIERDA      |                | BARCA          | DERECHA        |
  |                |                |                | Robot          |
  |                |                |                | Zorro          |
  |                |                |                | Conejo         |
  |                |                |                | Lechuga        |
*/

#include "Jugador.h"
#include "Lugar.h"
#include "Orilla.h"
#include "Barca.h" 
#include "Individuo.h"

#include <vector>
#include <string>

int main()
{
//--------------------------- INICIALIZACIÓN DE INDIVIDUOS

  Individuo *robot = new Individuo("Robot", "R");
  Individuo *zorro = new Individuo("Zorro", "Z");
  Individuo *conejo = new Individuo("Conejo", "C");
  Individuo *lechuga = new Individuo("Lechuga", "L");

  zorro->nuevaPresa(conejo);
  conejo->nuevaPresa(lechuga);

  vector <Individuo *> individuosDelJuego = {robot, zorro, conejo, lechuga};

//---------------------------


//--------------------------- INICIALIZACIÓN DE LUGARES

  Lugar *orillaIzquierda = new Orilla("Orilla Izquierda");
  Lugar *barca = new Barca("Barca");
  Lugar *orillaDerecha = new Orilla("Orilla Derecha");

  orillaIzquierda->nuevoVecinoInmediato(barca);
  orillaDerecha->nuevoVecinoAlternativo(barca);

  vector <Lugar *> lugaresDelJuego = {orillaIzquierda, barca, orillaDerecha};

  for (int posicion = 0; posicion < individuosDelJuego.size(); posicion++)
    orillaIzquierda->aceptarIndividuo(individuosDelJuego.at(posicion)); // Todos los individuos inician en la orilla izquierda

//---------------------------


//--------------------------- INICIALIZACIÓN DEL JUEGO

  Jugador jugador;

  for (int posicion = 0; posicion < lugaresDelJuego.size(); posicion++)
  {
    jugador.nuevoLugar(lugaresDelJuego.at(posicion));
    lugaresDelJuego.at(posicion) = nullptr;
  }

  for (int posicion = 0; posicion < individuosDelJuego.size(); posicion++)
  {
    jugador.nuevoIndividuo(individuosDelJuego.at(posicion));
    individuosDelJuego.at(posicion) = nullptr;
  }

  // // Descomentar para verificar lugares, vecinos e individuos antes de iniciar el juego:
  // jugador.cualesSonLosLugaresYSusVecinos();
  // jugador.individuosEnCadaLugar();

//--------------------------- 


//--------------------------- EJECUCIÓN DEL JUEGO

  jugador.jugar();

//--------------------------- 

  return 0;
}