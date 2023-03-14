// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms

#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h" 

//S_ParamGen ParamGen;

S_ParamGen ParamDisplay; //= {SignalSinus, 100, 500, 0};

E_Menu_State Menu_State = Main_Menu;

uint8_t position = 0;

//int8_t wave_signal = 0;

char cursor[4] = {BLANK, BLANK, BLANK, BLANK};

uint8_t selected = FALSE;   //The option is selected or not 

int lcdPosition;

char textSignal[sizeof Menu_State][11]={"Sine Wave  ", "Triangle   ", "Saw Tooth  ", "Square Wave"};

//cursor[position] = NOT_SELECT;

//char form[] = {"Sine Wave"};


// Initialisation du menu et des paramètres
void MENU_Initialize(S_ParamGen *pParam)
{
    lcd_bl_on();
	printf_lcd("  Signal Generator");           
    lcd_gotoxy(1,3);
    printf_lcd("   TP3 MINF 22-23");
    lcd_gotoxy(1,4);
    printf_lcd("    Alex & Einar");

    ParamDisplay.Forme = pParam -> Forme;
    ParamDisplay.Frequence = pParam -> Frequence;
    ParamDisplay.Amplitude = pParam -> Amplitude;
    ParamDisplay.Offset = pParam -> Offset;
}


// Execution du menu, appel cyclique depuis l'application
void MENU_Execute(S_ParamGen *pParam)
{
    //Manage backlight
    if(Pec12.NoActivity == TRUE)
    {
        lcd_bl_off();
    }
    else
    {
        lcd_bl_on();
    }

    switch(Menu_State)
    {
    case Main_Menu:
        {
            if(Pec12.Inc == TRUE && position < 3)
            {
                cursor[position + 1] = (cursor[position], cursor[position]=BLANK);
                position++;
                Pec12ClearPlus();
            }
            else
            {
                Pec12ClearPlus();
            }

            if(Pec12.Dec == TRUE && position > 0)
            {
                cursor[position - 1] = (cursor[position], cursor[position]=BLANK);
                position--;
                Pec12ClearMinus();
            }
            else
            {
                Pec12ClearMinus();
            }

            if(Pec12.OK == TRUE && selected == FALSE)
            {
                selected = TRUE;
                Pec12ClearOK();
            }

            if(selected == TRUE)
            {
                cursor[position] = SELECTED;
                Menu_State = position;

                ParamDisplay.Forme = pParam -> Forme;
                ParamDisplay.Frequence = pParam -> Frequence;
                ParamDisplay.Amplitude = pParam -> Amplitude;
                ParamDisplay.Offset = pParam -> Offset;

                //ParamDisplay = ParamGen;
            }
            else
            {
                cursor[position] = NAVIGATION;
            }

            break;
        }
    case Wave_Menu:
        {
            if(Pec12.Inc == TRUE)
            {
                ParamDisplay.Forme++;
                if(ParamDisplay.Forme > 3){ParamDisplay.Forme = 0;}
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE)
            {
                if(ParamDisplay.Forme == 0){ParamDisplay.Forme = 3;}
                else{ParamDisplay.Forme--;}        
                Pec12ClearMinus();
            }
            if(Pec12.OK == TRUE)
            {
                pParam -> Forme = ParamDisplay.Forme;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearOK();
            }
            else if(Pec12.ESC == TRUE)
            {
                ParamDisplay.Forme = pParam -> Forme;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearESC();
            }
            break;
        }
    case Frequency_Menu:
        {
            if(Pec12.Inc == TRUE)
            {
                ParamDisplay.Frequence += FREQUENCY_INC;
                if(ParamDisplay.Frequence > MAX_FREQUENCY){ParamDisplay.Frequence = MIN_FREQUENCY;}
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE)
            {
                ParamDisplay.Frequence -= FREQUENCY_INC;
                if(ParamDisplay.Frequence < MIN_FREQUENCY){ParamDisplay.Frequence = MAX_FREQUENCY;}
                Pec12ClearMinus();
            }
            if(Pec12.OK == TRUE)
            {
                pParam -> Frequence = ParamDisplay.Frequence;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearOK();
            }
            else if(Pec12.ESC == TRUE)
            {
                ParamDisplay.Frequence = pParam -> Frequence;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearESC();
            }
            break;
        }
    case Amplitude_Menu:
        {
            if(Pec12.Inc == TRUE)
            {
                ParamDisplay.Amplitude += AMPLITUDE_INC;
                if(ParamDisplay.Amplitude > MAX_AMPLITUDE){ParamDisplay.Amplitude = MIN_AMPLITUDE;}
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE)
            {
                ParamDisplay.Amplitude -= AMPLITUDE_INC;
                if(ParamDisplay.Amplitude < MIN_AMPLITUDE){ParamDisplay.Amplitude = MAX_AMPLITUDE;}
                Pec12ClearMinus();
            }
            if(Pec12.OK == TRUE)
            {
                pParam -> Amplitude = ParamDisplay.Amplitude;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearOK();
            }
            else if(Pec12.ESC == TRUE)
            {
                ParamDisplay.Amplitude = pParam -> Amplitude;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearESC();
            }
            break;
        }
        
    case Offset_Menu:
        {
            if(Pec12.Inc == TRUE && ParamDisplay.Offset < MAX_OFFSET)
            {
                ParamDisplay.Offset += OFFSET_INC;
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE && ParamDisplay.Offset > MIN_OFFSET)
            {
                ParamDisplay.Offset -= OFFSET_INC;
                Pec12ClearMinus();
            }
            if(Pec12.OK == TRUE)
            {
                pParam -> Offset = ParamDisplay.Offset;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearOK();
            }
            else if(Pec12.ESC == TRUE)
            {
                ParamDisplay.Offset = pParam -> Offset;
                Menu_State = Main_Menu;
                selected = FALSE;
                Pec12ClearESC();
            }
            break;  
        }
    default:
    break;        
    }

    //Display update
    lcd_gotoxy(1,1);
    printf_lcd("%cShape %c ", cursor[0], SEPARATOR);
    for (lcdPosition = 0; lcdPosition < 11; ++lcdPosition)
    {
        printf_lcd("%c", textSignal[ParamDisplay.Forme][lcdPosition]);
    }
    lcd_gotoxy(1,2);
    printf_lcd("%cFrequ [Hz] %c %-4d", cursor[1], SEPARATOR, ParamDisplay.Frequence);
    lcd_gotoxy(1,3);
    printf_lcd("%cAmpli [mV] %c %-5d", cursor[2], SEPARATOR, ParamDisplay.Amplitude);
    lcd_gotoxy(1,4);
    printf_lcd("%cOffset [mV] %c %-5d", cursor[3], SEPARATOR, ParamDisplay.Offset);
}