// Tp3  manipulation MenuGen avec PEC12
// C. HUBER  10/02/2015 pour SLO2 2014-2015
// Fichier MenuGen.c
// Gestion du menu  du générateur
// Traitement cyclique à 10 ms

#include <stdint.h>                   
#include <stdbool.h>
#include "MenuGen.h"

int rotary_value; //test value for 

//E_Cursor_State Cursor_State = 2;

S_ParamGen ParamGen;

E_Menu_State Menu_State;

uint8_t position = 0;

int8_t wave_signal = 0;

char cursor[4] = {BLANK, BLANK, BLANK, BLANK};

uint8_t selected = FALSE;

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

    if(Pec12.OK == TRUE && selected == FALSE)
    {
        selected = TRUE;
        Pec12ClearOK();
    }

    if(selected == TRUE)
    {
        cursor[position] = SELECTED;
    }
    else
    {
        cursor[position] = NAVIGATION;
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

            break;
        }
    case Wave_Menu:
        {
            if(Pec12.Inc == TRUE)
            {
                wave_signal++;
                if(wave_signal > 4){wave_signal = 0;}
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE)
            {
                wave_signal--;
                if(wave_signal < 0){wave_signal = 4;}
                Pec12ClearMinus();
            }
            break;
        }
    /*case Frequency_Menu:
        {
            if(Pec12.Inc == TRUE)
            {
                "frequency"+20;
                if("frequency" > 2000){"frequency" = 0}
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE)
            {
                "frequency"-20;
                if("frequency" < 0){"frequency" = 2000}
                Pec12ClearMinus();
            }
            break;
        }
    case Amplitude_Menu:
        {
            if(Pec12.Inc == TRUE && position < 10000)
            {
                cursor[position + 1] = (cursor[position], cursor[position]=BLANK);
                position+100;
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE && position > 0)
            {
                cursor[position - 1] = (cursor[position], cursor[position]=BLANK);
                position-100;
                Pec12ClearMinus();
            }
            break;
        }
        
    case Offset_Menu:
        {
            if(Pec12.Inc == TRUE && position < 5000)
            {
                cursor[position + 1] = (cursor[position], cursor[position]=BLANK);
                position+100;
                Pec12ClearPlus();
            }
            else if(Pec12.Dec == TRUE && position > -5000)
            {
                cursor[position - 1] = (cursor[position], cursor[position]=BLANK);
                position-100;
                Pec12ClearMinus();
            }
            break;  
        }*/
        
    }

    

    

    /*switch(main_menu)
    {
    case NOT_SELECT:
        switch

    case WAVEFORM:

    case FREQUENCY:

    }*/

    //Display update
    lcd_gotoxy(1,1);
    printf_lcd("%cShape %c Sine Wave", cursor[0], SEPARATOR);
    lcd_gotoxy(1,2);
    printf_lcd("%cFrequ [Hz] %c  ", cursor[1], SEPARATOR);
    lcd_gotoxy(1,3);
    printf_lcd("%cAmpli [mV] %c  ", cursor[2], SEPARATOR);
    lcd_gotoxy(1,4);
    printf_lcd("%cOffset [mV] %c", cursor[3], SEPARATOR);
}