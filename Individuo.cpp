/*
  Archivo: Individuo.cpp

  Autores:
  -> Christian Vargas <vargas.christian@correounivalle.edu.co>

  Fecha de creación: 2022-08-04
  Fecha de última modificación: 2022-08-06

  Licencia: GNU-GPL
*/

#include "Individuo.h"

Individuo::Individuo(string nombreDelIndividuo, string instruccionPropia) : nombreDelIndividuo(nombreDelIndividuo), instruccionPropia(instruccionPropia)
{
}

Individuo::~Individuo()
{
}

string Individuo::cualEsElNombreDelIndividuo()
{
  return nombreDelIndividuo;
}

string Individuo::cualEsLaInstruccionDelIndividuo()
{
  return instruccionPropia;
}

vector <Individuo*> Individuo::queIndividuosPuedoComer()
{
  return individuosQuePuedoComer;
}

void Individuo::nuevaPresa(Individuo *nuevaPresa)
{
  individuosQuePuedoComer.push_back(nuevaPresa);
}

bool Individuo::esEstaTuInstruccion(const string instruccion)
{
  return instruccionPropia == instruccion;
}