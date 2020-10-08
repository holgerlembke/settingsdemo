// Das sind eigentlich nicht Demodaten...
struct setting_t {
  // BEGINN
  // Verwaltungsdaten für die Settings-Slots, nix ändern, da direkter EEPROM-Zugriff
  byte id1;
  byte id2;
  // spezifischer Kennungswert für diese settings
  int teiler; 
  //ENDE

  // hier beginnt der bereich mit den eigentlichen Daten
  float aktivtemperaturziel = 150.0;

  // wenn Griff in die Aufnahme gelegt wird
  float sleeptemp = 100;         // R1  Absenktemperatur beim Schlafen in Aufnahme
  int sleeperiod = 30;           // R2  Sekunden bis zum Schlafen
  int turnoffperiod = 120;       // R3  Sekunden bis zum Ausschalten
  int stayoffonpoweron = 1;      // R4  1==wenn bei Einschalten in Aufnahme, dann ausgeschaltet bleiben
  int displayinfahrenheit;       // R5  1==fahrenhheit
  int displaymittelwert = 0;     // R6  1==mittelwertbildung der Anzeige
  int usedeepsleeping = 1;       // R7  1==Prozessor wird abgestellt, aufwachen über Ablageschalter
  int useannoyingbuzzer = 1;     // R8  Buzzer....
  int buzzeatdeltatemp = 20;     // R9  bei aktivtemperaturziel-buzzeatdeltatemp wird gebuzzed. 0 schaltet ab. 0..150
  float py2 = 300.0;             // R10 Kalibrierungsendwert für die Geradengleichung.

  int schalterAufwachDelta = 10;
  
};
