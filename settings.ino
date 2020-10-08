#include <EEPROM.h>

/*
   2020-10-08
 
   # Programm zum Testen von multiplen Settings

   ## Motivation:

   Zur Spitzenerkennung ist im Stecker von meinem Lötdings deie eine Hälfte eines
   Spannungsteilers, am analogen Eingang die andere Hälfte. Über den Spannungswert als
   "Index" werden die individuellen Spitzendaten in einer dynamischen Struktur (genannt Slot)
   im EEPROM abgelegt.

   Der "Indexwert" benötigt ein gewisse Toleranz (wg. Messunsicherheit). 
   
   Diese Sammlung soll ein beispielhaftes Vorgehen zeigen.
   
   Das Serial.print-Zeugs ist nicht ideal (Speicherverbrauch, Varspace statt Codespace, 
   Heapfragmentierung).
*/

void setup() {
  Serial.begin(115200);

  test();
}

void loop() {
  delay(1000);
}
