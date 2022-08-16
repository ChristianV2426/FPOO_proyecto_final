/*
  Archivo: Jugador.cpp

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-08-04
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

#include "Jugador.h"

Jugador::Jugador()
{
}

Jugador::~Jugador()
{
  for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
  {
    if (todosLosLugares.at(posicion))
    {
      delete todosLosLugares.at(posicion);
      todosLosLugares.at(posicion) = nullptr;
    }
  }
  todosLosLugares.clear();

  for (int posicion = 0; posicion < todosLosIndividuos.size(); posicion++)
  {
    if (todosLosIndividuos.at(posicion))
    {
      delete todosLosIndividuos.at(posicion);
      todosLosIndividuos.at(posicion) = nullptr;
    }
  }
  todosLosIndividuos.clear();
}

void Jugador::nuevoLugar(Lugar *nuevoLugar)
{
  todosLosLugares.push_back(nuevoLugar);
}

void Jugador::nuevoIndividuo(Individuo *nuevoIndividuo)
{
  todosLosIndividuos.push_back(nuevoIndividuo); 
}

void Jugador::cualesSonLosLugaresYSusVecinos()
{
  string mensaje = "";

  for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
  {
    mensaje += "El vecino inmediato de " + todosLosLugares.at(posicion)->cualEsElNombreDelLugar() + " es: " + todosLosLugares.at(posicion)->cualEsTuVecinoInmediato() + "\n";
    mensaje += "El vecino alternativo de " + todosLosLugares.at(posicion)->cualEsElNombreDelLugar() + " es: " + todosLosLugares.at(posicion)->cualEsTuVecinoAlternativo() + "\n\n";
  }

  cout << mensaje;
}

void Jugador::individuosEnCadaLugar()
{
  string mensaje = "";

  for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
  {
    mensaje += "En " + todosLosLugares.at(posicion)->cualEsElNombreDelLugar() + " están: \n";

    vector <string> todosLosIndividuosEnEsteLugar = todosLosLugares.at(posicion)->cualesIndividuosEstanEnEsteLugar();

    for (int posicion = 0; posicion < todosLosIndividuosEnEsteLugar.size(); posicion++)
      mensaje += todosLosIndividuosEnEsteLugar.at(posicion) + "\n";

    mensaje += "\n";
  }

  cout << mensaje;
}

void Jugador::alinearEnPantalla(const string mensajeAImprimir)
{
  if (mensajeAImprimir == "\n" or mensajeAImprimir == "endl")
    cout << "| " << "\n"; 

  else
    cout << left << "| " << setw(15) << mensajeAImprimir;
}

void Jugador::imprimirEstadoActualDelJuego(const vector <string> &individuosEnOrillaIzquierda, const vector <string> &individuosEnBarca, const vector <string> &individuosEnOrillaDerecha, const bool laBarcaEstaEnLaOrillaIzquierda)
{
  int totalIndividuosEnOrillaIzquierda = individuosEnOrillaIzquierda.size();
  int totalIndividuosEnBarca = individuosEnBarca.size();
  int totalIndividuosEnOrillaDerecha = individuosEnOrillaDerecha.size();

  int maximoIndividuosEnUnLugar = max(totalIndividuosEnOrillaIzquierda, totalIndividuosEnBarca);
  maximoIndividuosEnUnLugar = max(maximoIndividuosEnUnLugar, totalIndividuosEnOrillaDerecha);


  //--------------------------- IMPRESIÓN DEL ENCABEZADO

  cout << "\n";
  alinearEnPantalla("IZQUIERDA");

  if (laBarcaEstaEnLaOrillaIzquierda)
  {
    alinearEnPantalla("BARCA");
    alinearEnPantalla("");
  }
  else
  {
    alinearEnPantalla("");
    alinearEnPantalla("BARCA");
  }

  alinearEnPantalla("DERECHA");
  alinearEnPantalla("\n");

  //--------------------------- 


  //--------------------------- IMPRESIÓN DEL CUERPO

  for (int contador = 0; contador < maximoIndividuosEnUnLugar; contador++)
  {
    if (contador < totalIndividuosEnOrillaIzquierda)
      alinearEnPantalla(individuosEnOrillaIzquierda.at(contador));
    else
      alinearEnPantalla("");


    if (laBarcaEstaEnLaOrillaIzquierda and contador < totalIndividuosEnBarca)
    {
      alinearEnPantalla(individuosEnBarca.at(contador));
      alinearEnPantalla("");
    }
    else if (not laBarcaEstaEnLaOrillaIzquierda and contador < totalIndividuosEnBarca)
    {
      alinearEnPantalla("");
      alinearEnPantalla(individuosEnBarca.at(contador));
    }
    else
    {
      alinearEnPantalla("");
      alinearEnPantalla("");
    }


    if (contador < totalIndividuosEnOrillaDerecha)
    {
      alinearEnPantalla(individuosEnOrillaDerecha.at(contador));
      alinearEnPantalla("\n");
    }
    else
    {
      alinearEnPantalla("");
      alinearEnPantalla("\n");
    }
  }

  //---------------------------
}

void Jugador::imprimirInstrucciones()
{
  cout << "Eres un robot y tu misión es llevar a todos los individuos hasta la otra orilla del río usando una barca." << endl;;
  cout << "¡Cuidado!: No puedes dejar solos al zorro y al conejo, o al conejo y a la lechuga, porque el primero devoraría al segundo." << endl;
  cout << "En la barca solo caben dos individuos y uno de ellos debes ser tú (robot), para poder pilotearla." << endl << endl;
  cout << "Las órdenes que puedes dar son:" << endl;
  cout << "Q para rendirte. \nI para ver las instrucciones. \nB para mover la barca. \nR para mover el robot. \nZ para mover el zorro. \nC para mover el conejo. \nL para mover la lechuga." << endl << endl;
  cout << "¡Buena suerte!" << endl;
}

bool Jugador::hayConflictoEnAlgunLugar() // Por conflicto, entender que un individuo se come a otro. 
{
  for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
    if(todosLosLugares.at(posicion)->hayConflictoEnEsteLugar())
      return true;

  return false;
}

bool Jugador::seTrasladaronTodosLosIndividuos()
{
  if(todosLosLugares.at(2)->estanTodosEstosIndividuos(todosLosIndividuos)) // ¿Se han movido todos los individuos a la orilla derecha?
    return true;

  else
    return false;
}

void Jugador::jugar()
{
  imprimirInstrucciones();

  bool elJugadorHaPerdido = false;

  while (true)
  {
    //--------------------------- IMPRESIÓN DEL ESTADO ACTUAL DEL JUEGO

    vector <string> individuosEnOrillaIzquierda = todosLosLugares.at(0)->cualesIndividuosEstanEnEsteLugar();
    vector <string> individuosEnBarca = todosLosLugares.at(1)->cualesIndividuosEstanEnEsteLugar();
    vector <string> individuosEnOrillaDerecha = todosLosLugares.at(2)->cualesIndividuosEstanEnEsteLugar();

    bool laBarcaEstaEnLaOrillaIzquierda = (todosLosLugares.at(0)->cualEsTuVecinoInmediato() == "Barca");

    imprimirEstadoActualDelJuego(individuosEnOrillaIzquierda, individuosEnBarca, individuosEnOrillaDerecha, laBarcaEstaEnLaOrillaIzquierda);

    //----------------------------------------------------------------------


    //--------------------------- VERIFICACIÓN: ¿PERDIÓ O GANÓ EL JUGADOR?

    if(elJugadorHaPerdido)
    {
      cout << "PERDISTE" << endl;
      break;
    }

    if(seTrasladaronTodosLosIndividuos())
    {
      cout << "GANASTE" << endl;
      break;
    }

    //----------------------------------------------------------------------


    //--------------------------- ¿QUÉ QUIERE HACER EL USARIO?

    string instruccion = "";
    cout << "¿Qué deseas hacer?: "; 
    getline(cin, instruccion);

    //----------------------------------------------------------------------


    //--------------------------- EJECUCIÓN DE LA INSTRUCCIÓN DEL USUARIO

    if (instruccion == "Q")
    {
      elJugadorHaPerdido = true;
      cout << "TE RENDISTE" << endl;
      cout << "PERDISTE" << endl;
      break;
    }


    else if(instruccion == "I")
    {
      imprimirInstrucciones();
      continue;
    }


    else if (instruccion == "B")
    {
      if (todosLosLugares.at(1)->estaEsteIndividuo("Robot")) // Debe haber un robot en la barca para que esta se pueda mover.
        for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
          todosLosLugares.at(posicion)->intercambiarVecinos();
      continue;
    }


    else if(instruccion.at(0) == 'R' or instruccion.at(0) == 'Z' or instruccion.at(0) == 'C' or instruccion.at(0) == 'L')
    {
      bool movimientoRealizado = false;

      for (int posicion = 0; posicion < todosLosLugares.size(); posicion++)
      {
        todosLosLugares.at(posicion)->realizarMovimiento(instruccion, movimientoRealizado, elJugadorHaPerdido);
        if(elJugadorHaPerdido or movimientoRealizado)
          break;
      }

      if(movimientoRealizado)
        elJugadorHaPerdido = hayConflictoEnAlgunLugar(); // Después del movimiento realizado, ¿algún individuo se come a otro?

      continue;
    }

    else
      continue;

    //----------------------------------------------------------------------
  }
}