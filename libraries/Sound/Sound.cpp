#include "Sound.h"


const char SIMPSONS[] PROGMEM = "The Simpsons:d=8,o=5,b=200:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";
const char INDIANA_JONES[] PROGMEM = "Indiana:d=16,o=5,b=250:e,8p,8f,8g,8p,1c6,8p.,d,8p,8e,1f,p.,g,8p,8a,8b,8p,1f6,p,a,8p,8b,2c6,2d6,2e6,e,8p,8f,8g,8p,1c6,p,d6,8p,8e6,1f.6,g,8p,8g,e.6,8p,d6,8p,8g,e.6,8p,d6,8p,8g,f.6,8p,e6,8p,8d6,2c6";
const char TAKE_ON_ME[] PROGMEM = "TakeOnMe:d=4,o=4,b=160:8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5,8f#5,8e5,8f#5,8f#5,8f#5,8d5,8p,8b,8p,8e5,8p,8e5,8p,8e5,8g#5,8g#5,8a5,8b5,8a5,8a5,8a5,8e5,8p,8d5,8p,8f#5,8p,8f#5,8p,8f#5,8e5,8e5";
const char LOONEY_TUNES[] PROGMEM = "Looney:d=4,o=5,b=140:32p,c6,8f6,8e6,8d6,8c6,a.,8c6,8f6,8e6,8d6,8d#6,e.6,8e6,8e6,8c6,8d6,8c6,8e6,8c6,8d6,8a,8c6,8g,8a#,8a,8f";
const char TWENTYEST_CENT_FOX[] PROGMEM = "20thCenFox:d=16,o=5,b=140:b,8p,b,b,2b,p,c6,32p,b,32p,c6,32p,b,32p,c6,32p,b,8p,b,b,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,b,32p,g#,32p,a,32p,b,8p,b,b,2b,4p,8e,8g#,8b,1c#6,8f#,8a,8c#6,1e6,8a,8c#6,8e6,1e6,8b,8g#,8a,2b";
const char JAMES_BOND[] PROGMEM = "Bond:d=4,o=5,b=80:32p,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d#6,16d#6,16c#6,32d#6,32d#6,16d#6,8d#6,16c#6,16c#6,16c#6,16c#6,32e6,32e6,16e6,8e6,16d#6,16d6,16c#6,16c#7,c.7,16g#6,16f#6,g#.6";
const char STAR_WARS[] PROGMEM = "StarWars:d=8,o=5,b=45:32p,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#.6,32f#,32f#,32f#,8b.,8f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32c#6,8b.6,16f#.6,32e6,32d#6,32e6,8c#6";
const char TOP_GUN[] PROGMEM = "TopGun:d=4,o=4,b=31:32p,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,16f,d#,16c#,16g#,16g#,32f#,32f,32f#,32f,16d#,16d#,32c#,32d#,16f,32d#,32f,16f#,32f,32c#,g#";
const char A_TEAM[] PROGMEM = "A-Team:d=8,o=5,b=125:4d#6,a#,2d#6,16p,g#,4a#,4d#.,p,16g,16a#,d#6,a#,f6,2d#6,16p,c#.6,16c6,16a#,g#.,2a#";
const char FLINTSTONES[] PROGMEM = "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.,16a#6,32g6,16f6,16a#.,32f6,32f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,a#,16a6,16d.6,16a#6,32a6,32a6,32g6,32f#6,32a6,8g6,16g6,16c.6,32a6,32a6,32g6,32g6,32f6,32e6,32g6,8f6,16f6,16a#.,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#,16c.6,32d6,32d#6,32f6,16a#6,16c7,8a#.6";
const char SMURFS[] PROGMEM = "Smurfs:d=32,o=5,b=200:4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8f#,p,8a#,p,4g#,4p,g#,p,a#,p,b,p,c6,p,4c#6,16p,4f#6,p,16c#6,p,8d#6,p,8b,p,4g#,16p,4c#6,p,16a#,p,8b,p,8f,p,4f#";
const char MISSION_IMPOSSIBLE[] PROGMEM = "MissionImp:d=16,o=6,b=95:32d,32d#,32d,32d#,32d,32d#,32d,32d#,32d,32d,32d#,32e,32f,32f#,32g,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,g,8p,g,8p,a#,p,c7,p,g,8p,g,8p,f,p,f#,p,a#,g,2d,32p,a#,g,2c#,32p,a#,g,2c,a#5,8c,2p,32p,a#5,g5,2f#,32p,a#5,g5,2f,32p,a#5,g5,2e,d#,8d";
const char WORMS[] PROGMEM = "Worms:d=4,o=6,b=125:8c5,8d5,e5,g5,g5,8f5,8e5,8d.5,16c5,8d5,8e5,d5,16p,8d5,8d.5,16c5,8d5,8e5,2c5,8d.5,16c5,8d5,8e5,d5,8c5,8d5,e5,g5,g5,8f5,8e5,8d.5,16c5,8d5,8e5,d5,16p,8d5,8d.5,16c5,8d5,8e5,2c5,8d.5,16c5,8d5,8e5,d5";
const char PIRATES[] PROGMEM = "Pirates of the Caribbean:d=8,o=6,b=160:8d,8e,2f,8g,8a,g,f,e,f,g,a,g,p,8f,8g,a,p,8g,8f,e,f,e,d,p,8e,8c,d,8p,p,8d,8e,f,p,8e,8f,g,f,g,a,g,f,d";
const char SCHWEIZER_PSALM[] PROGMEM = "CH Hymne:d=4,o=6,b=80:d5,8d5,d5,g5,8g.5,16f_.5,f_5,p,8d.5,8d5,d5,a5,a5,8g5,g5,p,b.5,8b5,8a5,8a5,a.5,8g5,f_5,2e5,c_5,2d5,p,d5,8d5,d5,g5,g5,8f_5,f_5,p,d5,8d5,d5,a5,a5,8g5,g5,p,b.5,8b5,8a5,8a5,a.5,8g5,f_5,2e5,c_5,2d5,p,g5";
const char FINAL_COUNTDOWN[] PROGMEM = "Final Countdown:d=4,o=6,b=125:p,8p,16b,16a,b,e,p,8p,16c7,16b,8c7,8b,a,p,8p,16c7,16b,c7,e,p,8p,16a,16g,8a,8g,8f_,8a,g,8p,16f_,16g,a,8p,16g,16a,8b,8a,8g,8f_,e,c7,2b,p,16b,16c7,16b,16a,1b";
const char BOHEMIAN[] PROGMEM =  "Bohemian Rhapsody:d=4,o=6,b=140:32e,16p,32p,1e,p,8c,8p,d,8e,1e,8d,8e,f,8g,f,e,2d,d,e,f,8g,f,e,d,8p";
const char FUR_ELISE[] PROGMEM =  "Fuer Elise:d=8,o=2,b=125:8e,8d_,8e,8d_,8e,8b5,8d,8c,a5,8p,8c5,8e5,8a5,b5,8p,8e5,8g_5,8b5,c,8p,8e5,8e,8d_,8e,8d_,8e,8b5,8d,8c,a5,8p,8c5,8e5,8a5,b5,8p,8e5,8c,8b5,a5";
const char MY_HEART_WILL[] PROGMEM =  "My Heart will go on:d=4,o=6,b=100:2d,2e,a5,2a,g,8f_,2e,f_,g,2f_,e,d,c_,2d,c_,1b5,1a5,1d,2e,a5,2a,g,8f_,2e,f_,g,2f_,e,d,c_,2d,c_,c_,2d,e,2f_,2e,1d";
const char HARRY_POTTER[] PROGMEM =  "Harry Potter:d=4,o=6,b=100:2p,8p,8b5,8e.,16g,8f_,e,8b,a.,f_.,8e.,16g,8f_,d,8f,2b5,8p,8b5,8e.,16g,8f_,e,8b,d7,8c_7,c7,8g_,8c.7,16b,8a_,f_,8g,b,8g,c7,8b,a_,8f_,8g.,16b,8a_,a_5,8b5,2b,8p";


int notes[] = { 0,
                NOTE_C4, NOTE_CS4, NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_GS4, NOTE_A4, NOTE_AS4, NOTE_B4,
                NOTE_C5, NOTE_CS5, NOTE_D5, NOTE_DS5, NOTE_E5, NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_AS5, NOTE_B5,
                NOTE_C6, NOTE_CS6, NOTE_D6, NOTE_DS6, NOTE_E6, NOTE_F6, NOTE_FS6, NOTE_G6, NOTE_GS6, NOTE_A6, NOTE_AS6, NOTE_B6,
                NOTE_C7, NOTE_CS7, NOTE_D7, NOTE_DS7, NOTE_E7, NOTE_F7, NOTE_FS7, NOTE_G7, NOTE_GS7, NOTE_A7, NOTE_AS7, NOTE_B7
};

void play_rtttl(const char song[])
{
    int i = 0;
    short default_dur = 4;
    short default_oct = 6;
    int bpm = 63;
    int num = 0;
    long wholenote = 0;
    long duration = 0;
    short note = 0;
    short scale = 0;
    static char p[512];
    strcpy_P(p,song);
    noTone(SPEAKER_PIN);

    while(p[i] != ':') {
        i++;    // ignore name
    }
    i++;                     // skip ':'
    // get default duration
    if(p[i] == 'd')
    {
        i++; i++;                // skip "d="
        num = 0;
        while(ischardigit(p[i]))
        {
            num = (num * 10) + (p[i] + 1 - '0');
            i++;
        }
        if(num > 0) default_dur = num;
        i++;                   // skip comma
    }


    // get default octave
    if(p[i] == 'o')
    {
        i++; i++;              // skip "o="
        num = p[i] + 1 - '0';
        if(num >= 3 && num <=7) default_oct = num;
        i++;                   // skip comma
    }


    // get BPM
    if(p[i] == 'b')
    {
        i++;i++;                // skip "b="
        num = 0;
        while(ischardigit(p[i]))
        {
            num = (num * 10) + (p[i++] - '0');
        }
        bpm = num;
        i++;                     // skip colon
    }

    // BPM usually expresses the number of quarter notes per minute
    wholenote = (60 * 1000L / bpm) * 4;  // this is the time for whole note (in milliseconds)


    // now begin note loop
    while(p[i])
    {
        // first, get note duration, if available
        num = 0;
        while(ischardigit(p[i]))
        {
            num = (num * 10) + (p[i++] - '0');
        }

        if(num) duration = wholenote / num;
        else duration = wholenote / default_dur;  // we will need to check if we are a dotted note after

        // now get the note
        note = 0;

        switch(p[i])
        {
            case 'c':
                note = 1;
                break;
            case 'd':
                note = 3;
                break;
            case 'e':
                note = 5;
                break;
            case 'f':
                note = 6;
                break;
            case 'g':
                note = 8;
                break;
            case 'a':
                note = 10;
                break;
            case 'b':
                note = 12;
                break;
            case 'p':
            default:
                note = 0;
        }
        i++;

        // now, get optional '#' sharp
        if(p[i] == '#')
        {
            note++;
            i++;
        }

        // now, get optional '.' dotted note
        if(p[i] == '.')
        {
            duration += duration/2;
            i++;
        }

        // now, get scale
        if(ischardigit(p[i]))
        {
            scale = p[i]- '0';
            i++;;
        }
        else
        {
            scale = default_oct;
        }

        scale += OCTAVE_OFFSET;

        if(p[i] == ',')
            i++;;       // skip comma for next note (or we may be at the end)

        // now play the note

        if(note)
        {
            tone(SPEAKER_PIN, notes[(scale - 4) * 12 + note], duration);
            delay(duration);
            noTone(SPEAKER_PIN);
        }
        else
        {
            delay(duration);
        }
    }
    noTone(SPEAKER_PIN);
}

void playTone(int freq, long duration) {
    //tone(SPEAKER_PIN, freq, duration);
}
