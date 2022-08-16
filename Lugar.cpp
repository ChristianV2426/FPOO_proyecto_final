/*
  Archivo: Lugar.cpp

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-08-04
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

#include "Lugar.h"

Lugar::Lugar(string nombreDelLugar) : nombreDelLugar(nombreDelLugar)
{
  vecinoInmediato = nullptr;
  vecinoAlternativo = nullptr;
}

Lugar::~Lugar()
{
}

string Lugar::cualEsElNombreDelLugar()
{
  return nombreDelLugar;
}

string Lugar::cualEsTuVecinoInmediato()
{
  if (not vecinoInmediato)
    return "Agua";

  return vecinoInmediato->cualEsElNombreDelLugar();
}

string Lugar::cualEsTuVecinoAlternativo()
{
  if (not vecinoAlternativo)
    return "Agua";

  return vecinoAlternativo->cualEsElNombreDelLugar();
}

vector <string> Lugar::cualesIndividuosEstanEnEsteLugar()
{
  vector <string> nombresDeLosIndividuosEnEsteLugar;

  for (int posicion = 0; posicion < individuosEnEsteLugar.size(); posicion++)
    nombresDeLosIndividuosEnEsteLugar.push_back(individuosEnEsteLugar.at(posicion)->cualEsElNombreDelIndividuo());

  return nombresDeLosIndividuosEnEsteLugar;
}

int Lugar::cuantosIndividuosHayEnEsteLugar()
{
  return individuosEnEsteLugar.size();
}

void Lugar::nuevoVecinoInmediato(Lugar *nuevoVecinoInmediato)
{
  if (this->vecinoInmediato == nuevoVecinoInmediato)
    return;

  else if (this->vecinoInmediato)
  {
    delete this->vecinoInmediato;
    this->vecinoInmediato = nullptr;
  }

  else
  {
    this->vecinoInmediato = nuevoVecinoInmediato;
    nuevoVecinoInmediato->nuevoVecinoInmediato(this);
  }
}

void Lugar::nuevoVecinoAlternativo(Lugar *nuevoVecinoAlternativo)
{
  if (this->vecinoAlternativo == nuevoVecinoAlternativo)
    return;

  else if (this->vecinoAlternativo)
  {
    delete this->vecinoAlternativo;
    this->vecinoAlternativo = nullptr;
  }

  else
  {
    this->vecinoAlternativo = nuevoVecinoAlternativo;
    nuevoVecinoAlternativo->nuevoVecinoAlternativo(this);
  }
}

void Lugar::intercambiarVecinos()
{
  Lugar *vecinoTemporal = this->vecinoInmediato;

  this->vecinoInmediato = this->vecinoAlternativo;
  this->vecinoAlternativo = vecinoTemporal;

  vecinoTemporal = nullptr;
}

bool Lugar::aceptarIndividuo(Individuo *nuevoIndividuo)
{
  individuosEnEsteLugar.push_back(nuevoIndividuo);
  return true;
}

bool Lugar::estaEsteIndividuo(const string nombreDelIndividuo)
{
  vector <string> nombresDeLosIndividuosEnEsteLugar = cualesIndividuosEstanEnEsteLugar();

  for (int posicion = 0; posicion < nombresDeLosIndividuosEnEsteLugar.size(); posicion++)
    if (nombresDeLosIndividuosEnEsteLugar.at(posicion) == nombreDelIndividuo)
      return true;

  return false;
}

bool Lugar::estaAlgunoDeEstosIndividuos(const vector <Individuo*> individuosEnPeligro, int &posicionDelIndividuoEnPeligro)
{
  for (int posicionIndividuosEnPeligro = 0; posicionIndividuosEnPeligro < individuosEnPeligro.size(); posicionIndividuosEnPeligro++)
    for (int posicionIndividuosEnEsteLugar = 0; posicionIndividuosEnEsteLugar < individuosEnEsteLugar.size(); posicionIndividuosEnEsteLugar++)
      if (individuosEnPeligro.at(posicionIndividuosEnPeligro)->cualEsElNombreDelIndividuo() == individuosEnEsteLugar.at(posicionIndividuosEnEsteLugar)->cualEsElNombreDelIndividuo())
      {
        posicionDelIndividuoEnPeligro = posicionIndividuosEnEsteLugar;
        return true;
      }
  return false;
}

bool Lugar::estanTodosEstosIndividuos(const vector <Individuo*> individuosAVerificar)
{
  for (int posicionIndividuosAVerificar = 0; posicionIndividuosAVerificar < individuosAVerificar.size(); posicionIndividuosAVerificar++)
  {
    bool elIndividuoEsta = false;

    for (int posicionIndividuosEnEsteLugar = 0; posicionIndividuosEnEsteLugar < individuosEnEsteLugar.size(); posicionIndividuosEnEsteLugar++)
      if (individuosAVerificar.at(posicionIndividuosAVerificar) == individuosEnEsteLugar.at(posicionIndividuosEnEsteLugar))
      {
        elIndividuoEsta = true;
        break;
      }

    if(not elIndividuoEsta)
      return false;
  }

  return true;      
}

void Lugar::realizarMovimiento(const string instruccion, bool &movimientoRealizado, bool &elJugadorHaPerdido)
{
  for (int posicion = 0; posicion < individuosEnEsteLugar.size(); posicion++)
  {
    if (individuosEnEsteLugar.at(posicion)->esEstaTuInstruccion(instruccion))
    {
      if (not vecinoInmediato) // Si el vecino inmediato es nullptr (agua), el individuo se cae al río y pierde.
      {
        elJugadorHaPerdido = true;
        individuosEnEsteLugar.at(posicion) = nullptr;
        individuosEnEsteLugar.erase(individuosEnEsteLugar.begin() + posicion);
        return;
      }

      if (vecinoInmediato->aceptarIndividuo( individuosEnEsteLugar.at(posicion) ))
      {
        individuosEnEsteLugar.at(posicion) = nullptr;
        individuosEnEsteLugar.erase(individuosEnEsteLugar.begin() + posicion);
      }

      movimientoRealizado = true;
      return;
    }
  }
}

bool Lugar::hayConflictoEnEsteLugar() // Por conflicto, entender que un individuo se come a otro. 
{
  if (estaEsteIndividuo("Robot")) // Nunca van a haber conflictos si hay un robot presente.
    return false;

  for (int posicion = 0; posicion < individuosEnEsteLugar.size(); posicion++)
  {
    vector <Individuo *> individuosEnPeligro = individuosEnEsteLugar.at(posicion)->queIndividuosPuedoComer(); 
    int posicionDelIndividuoEnPeligro = -1; 

    if(estaAlgunoDeEstosIndividuos(individuosEnPeligro, posicionDelIndividuoEnPeligro))
    {
      individuosEnEsteLugar.at(posicionDelIndividuoEnPeligro) = nullptr;
      individuosEnEsteLugar.erase(individuosEnEsteLugar.begin() + posicionDelIndividuoEnPeligro);
      return true;
    }
  }

  return false;
}