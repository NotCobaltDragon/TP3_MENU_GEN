#ifndef MenuGen_h
#define MenuGen_h

// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  03.02.2016
// Fichier MenuGen.h
// Gestion du menu  du générateur
// Traitement cyclique à 1 ms du Pec12


#include <stdbool.h>
#include <stdint.h>
#include "DefMenuGen.h"
#include "Mc32DriverLcd.h"

#include "GesPec12.h" //not shure

//Separation caracter between option and value "Frequ [Hz] X 1000"
#define SEPARATOR 246	// =>
//#define SEPARATOR 61	// = (Specification sheet)


// -----Cursor for navigation-----
#define NAVIGATION 199	// ->
//#define NAVIGATION 42	// * (Specification sheet)

#define SELECTED 251	// ->| 
//#define SELECTED 63	// ? (Specification sheet)

#define BLANK 32	//Blank caracter

typedef enum{Main_Menu, Wave_Menu, Frequency_Menu, Ampliture_Menu, Offset_Menu}E_Menu_State;

S_Pec12_Descriptor Pec12;

void MENU_Initialize(S_ParamGen *pParam);


void MENU_Execute(S_ParamGen *pParam);

#endif




  
   







