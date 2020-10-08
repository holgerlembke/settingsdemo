# Programm zum Testen von multiplen Settings

## Motivation:

Zur Spitzenerkennung ist im Stecker von meinem L�tdings deie eine H�lfte eines
Spannungsteilers, am analogen Eingang die andere H�lfte. �ber den Spannungswert als
"Index" werden die individuellen Spitzendaten in einer dynamischen Struktur (genannt Slot)
im EEPROM abgelegt.

Der "Indexwert" ben�tigt ein gewisse Toleranz (wg. Messunsicherheit). 

Diese Sammlung soll ein beispielhaftes Vorgehen zeigen.

Das Serial.print-Zeugs ist nicht ideal (Speicherverbrauch, Varspace statt Codespace, 
Heapfragmentierung).
