// Canevas manipulation GenSig avec menu
// C. HUBER  09/02/2015
// Fichier Generateur.C
// Gestion  du générateur

// Prévu pour signal de 40 echantillons

// Migration sur PIC32 30.04.2014 C. Huber


#include "Generateur.h"
#include "DefMenuGen.h"
#include "Mc32gestSpiDac.h"
#include "math.h"
#include "driver/tmr/drv_tmr_static.h"

// T.P. 2016 100 echantillons
#define MAX_ECH 100

// Valeurs initiaux pour le générateur
// SignalSinus, SignalTriangle, SignalDentDeScie, SignalCarre
#define INIT_FREQ                  100
#define INIT_FORM          SignalCarre
#define INIT_AMPLITUDE           30000
#define INIT_OFFSET              -25000
#define DEFAULT_OFFSET           32767
/*----------------------------------------*/
#define MAX_VAL                  65535
#define MIN_VAL                      0
/*----------------------------------------*/

#define F_SYS                 80000000
#define PRESCALER                    1

// Variables globales
uint16_t SignalValues[MAX_ECH] = {0};

// Initialisation du  générateur
void  GENSIG_Initialize(S_ParamGen *pParam)
{
    // Fréquence par défaut = 20
    pParam -> Frequence = INIT_FREQ;
    // Forme du signal par défaut = Sinus
    pParam -> Forme = INIT_FORM;
    // Amplitude par défaut = 0;
    pParam -> Amplitude = INIT_AMPLITUDE;
    // Offset par défaut = 0
    pParam -> Offset = INIT_OFFSET;
}
  

// Mise à jour de la periode d'échantillonage
void  GENSIG_UpdatePeriode(S_ParamGen *pParam)
{
    // Variable locale
    uint16_t Val_Periode = 0;
    
    Val_Periode = F_SYS/(pParam -> Frequence * MAX_ECH * PRESCALER);
    PLIB_TMR_Period16BitSet(TMR_ID_3, Val_Periode);
}

// Mise à jour du signal (forme, amplitude, offset)
void  GENSIG_UpdateSignal(S_ParamGen *pParam)
{
    // Variables locales
    uint8_t i = 0;
    int32_t pointValue = (DEFAULT_OFFSET - pParam -> Amplitude + pParam -> Offset);
    //uint8_t stepVal = 0;
    
    for(i=0; i<MAX_ECH; i++)
    {
        //val[1] = val[0]; 
        switch(pParam -> Forme)
        {
            case SignalSinus:
                pointValue = pParam -> Amplitude * sin((float)2 * M_PI * i/(float)MAX_ECH) + 0.5 + DEFAULT_OFFSET + pParam -> Offset;
                if(pointValue > MAX_VAL)
                {
                    pointValue = MAX_VAL;
                }
                else if(pointValue < MIN_VAL)
                {
                    pointValue = MIN_VAL;
                }
                SignalValues[i] = pointValue;
                break;
            case SignalTriangle:
                SignalValues[i] = pointValue;
                if(i < (MAX_ECH / 2) - 1)
                {
                    pointValue = pointValue + ((float)pParam -> Amplitude * (float)2 + (float)1) / (float)(MAX_ECH/2) + 0.5 + pParam -> Offset ;
                }
                else
                {
                    pointValue = pointValue - ((float)pParam -> Amplitude * (float)2 + (float)1) / (float)(MAX_ECH/2) + 0.5 + pParam -> Offset ;
                }
                if(pointValue > MAX_VAL)
                {
                    pointValue = MAX_VAL;
                }
                else if(pointValue < MIN_VAL)
                {
                    pointValue = MIN_VAL;
                }
                break;
            case SignalDentDeScie:
                SignalValues[i] = pointValue;
                pointValue = pointValue + ((float)pParam -> Amplitude * (float)2 + (float)1) / (float)MAX_ECH + 0.5 + pParam -> Offset;
                if(pointValue > MAX_VAL)
                {
                    pointValue = MAX_VAL;
                }
                else if(pointValue < MIN_VAL)
                {
                    pointValue = MIN_VAL;
                }
                break;
            case SignalCarre:
                if(i < (MAX_ECH / 2))
                {
                    pointValue = pParam -> Amplitude + 1 + DEFAULT_OFFSET + pParam -> Offset;
                }
                else
                {
                    pointValue = -pParam -> Amplitude + DEFAULT_OFFSET + pParam -> Offset;
                }
                if(pointValue > MAX_VAL)
                {
                    pointValue = MAX_VAL;
                }
                else if(pointValue < MIN_VAL)
                {
                    pointValue = MIN_VAL;
                }
                SignalValues[i] = pointValue;
                break;
            default :
                break;
        }
    }
    // Test pour debug
    i = 10;
}


// Execution du générateur
// Fonction appelée dans Int timer3 (cycle variable variable)

// Version provisoire pour test du DAC à modifier
void  GENSIG_Execute(void)
{
   static uint16_t EchNb = 0;
   const uint16_t Step = 65535 / MAX_ECH;

   //SPI_WriteToDac(0, Step * EchNb );      // sur canal 0
   SPI_WriteToDac(0, SignalValues[EchNb]);      // sur canal 0
   EchNb++;
   EchNb = EchNb % MAX_ECH;
}
