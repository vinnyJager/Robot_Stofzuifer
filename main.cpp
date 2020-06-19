/*
                                                      ________________________
                                                     │  Group : 2             │
                                                     │  Class : EMT1V.B       │
                                                     │  Date  : 09/06/2020    │
                                                      ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
*/

#include "mbed.h"
#include "platform/mbed_thread.h"

// Hier worden alle motoren (ledjes) geïnitialiseerd. Er komen 2 motoren, maar beide kunnen voor- en achteruit. Voor worden groene ledjes, achteruit worden rode ledjes.
DigitalOut motorRV(D7);             // Motor rechts (gaat vooruit) wordt geïnitialiseerd.
DigitalOut motorLV(D4);             // Motor links (gaat vooruit)  wordt geïnitialiseerd.
DigitalOut motorRA(D2);             // Motor rechts (gaat achteruit)  wordt geïnitialiseerd.
DigitalOut motorLA(D3);             // Motor links (gaat achteruit) wordt geïnitialiseerd.
DigitalOut Batterij_led(D6);        // Ledje controle accu niveau wordt geïnitialiseerd.

// Hier worden alle sensoren (drukknoppen) geïnitialiseerd. Er komen 5 sensoren verspreid in een halve boog aan de voorkant van de stofzuiger.
InterruptIn SensorL(D8);            // Sensor links.
InterruptIn SensorLV(D9);           // sensor linksvoor.
InterruptIn SensorV(D10);           // Sensor voor.
InterruptIn SensorRV(D11);          // Sensor rechstvoor.
InterruptIn SensorR(D12);           // Sensor rechts.
InterruptIn SensorO(D13);           // Sensor Onder.

int Batterij_niveau = 6;            // Met deze variabele simuleren we het accu niveau.
bool Timer1 = 0;                    // Met deze variabele simuleren we een timer.
bool start_knop = 1;                // Met deze variable simuleren we een startknop.


void sensorLinks() {                // Deze functie wordt geroepen wanneer "sensor links" iets ziet.
                motorLA = 0;        // Hier zorgen we dat de beweging die de robot in de rest van deze functie maakt, niet tegen gesteld is aan een vorige beweging
                motorRV = 0;        // zodat de robot rechts voor en rechts achter niet tegelijkertijd aan kan zijn.

                motorLV = 1;
                motorRA = 1;
                thread_sleep_for(350);       // 35 Graden naar rechts.
}
void sensorLinksVoor() {            // Deze functie wordt geroepen wanneer "sensorLinksVoor" iets ziet.
                motorLA = 0;
                motorRV = 0;

                motorLV = 1;
                motorRA = 1;
                thread_sleep_for(350);       // 35 Graden naar rechts.          
}
void sensorVoor() {                 // Deze functie wordt geroepen wanneer "sensorVoor" iets ziet.
                motorLA = 0;
                motorRV = 0;

                motorLV = 1;
                motorRA = 1;
                thread_sleep_for(1400);       // 150 Graden naar rechts.          
}
void sensorRechtsVoor() {           // Deze functie wordt geroepen wanneer "sensorRechtsVoor" iets ziet.
                motorLV = 0;
                motorRV = 0;

                motorLA = 1;
                motorRV = 1;
                thread_sleep_for(350);        // 35 Graden naar links.          
}
void sensorRechts() {               // Deze functie wordt geroepen wanneer "sensorRechts" iets ziet.
                motorLV = 0;
                motorRV = 0;

                motorLA = 1;
                motorRV = 1;
                thread_sleep_for(350);        // 35 Graden naar links.           

}
void sensorOnder() {                // Deze functie wordt geroepen wanneer "sensorOnder" ziet dat er een afgrond is.
                motorLA = 0;
                motorRV = 0;

                motorLV = 1;
                motorRA = 1;
                thread_sleep_for(1400);        // 150 Graden naar rechts.          
}
void sensor_None() {                // Deze functie wordt geroepen wanneer geen enekele sensor iets ziet, en de robot door kan rijden.
                motorLA = 0;
                motorRA = 0;

                motorLV = 1;
                motorRV = 1;        
}

int main()
{
    while (Batterij_niveau > 5 && (Timer1 == 1 || start_knop == 1)) {         // Wanneer de gesimuleerde timer aan is en batterij percentage boven 5% zit werkt deze while loop.
        if(SensorL==1) {            // Ziet de sensor links naast de robot iets?                                              // En wanneer de gesimuleerde start knop aan is en de batterij boven 5% is werkt de while loop.
            sensorLinks();
        }
        else if (SensorLV == 1) {   // Ziet de sensor links voor de robot iets?
            sensorLinksVoor();
        }
        else if (SensorV == 1) {    // Ziet de sensor voor de robot iets?
            sensorVoor();
        }
        else if (SensorRV == 1) {   // Ziet de sensor rechts voor de robot iets?
            sensorRechtsVoor();
        }
        else if (SensorR == 1) {    // Ziet de sensor rechts naast de robotiets?
            sensorRechts();
        }
        else if (SensorO == 1) {    // Ziet de sensor onder de robot iets?
            sensorOnder();
        }
        else {
            sensor_None();          // Als geen van de sensoren iets zien, wordt deze functie aangeroepen.
        }

    if(Batterij_niveau <= 15) {     // Wanneer het batterij percentage kleiner is dan 15%, gaat het batterij_niveau lampje aan.
        Batterij_led = 1;
        }
    }
if (Batterij_niveau <= 5) {         // Wanneer het percentage van de batterij kleiner is dan 5, gaat het lampje weer aan, terwijl de hoofd while loop uit is.
Batterij_led = 1;
    }
}