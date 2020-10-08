// ===============================================================================================================
// ===============================================================================================================
// Am Anfang ein paar Bytes Platz lassen. Haben ist besser als brauchen.
const int settingStart = 10;
const int settingOffset = sizeof(setting_t) + 10;

const int slotValueEpsilon = 20; // 

// Anzahl der Settings ist durch den EEPROM-Speicher begrenzt....
const byte settingItemMax = 5;

// Versionsnummer der Settingdaten. Bei Änderungen im Struct einfach hochzählen
const byte settingVersion = 5;

// ===============================================================================================================
// ===============================================================================================================
void eepromRead(int addr, void* output, int length) {
  uint8_t* src;
  uint8_t* dst;
  src = (uint8_t*)addr;
  dst = (uint8_t*)output;
  for (uint16_t i = 0; i < length; i++) {
    *dst++ = EEPROM.read((int)src++);
  }
}

// ===============================================================================================================
// ===============================================================================================================
void eepromWrite(int addr, void* input, int length) {
  uint8_t* src;
  uint8_t* dst;
  src = (uint8_t*)input;
  dst = (uint8_t*)addr;
  for (uint16_t i = 0; i < length; i++) {
    EEPROM.write((int)dst++, *src++);
  }
}

// ===============================================================================================================
// ===============================================================================================================
int slotToEEPROM(byte slot) {
  return settingStart + slot * settingOffset;
}

// ===============================================================================================================
// ===============================================================================================================
byte findSettingSlot(int value) {
  byte slot = 0;

  do {
    int e = slotToEEPROM(slot);
    int slotvalue = EEPROM.read(e + 2) + (EEPROM.read(e + 3) << 8);
    if (abs(slotvalue - value) <= slotValueEpsilon) {
      return slot;
    }

    slot++;
  } while (slot < settingItemMax);

  return 255;
}

// ===============================================================================================================
// ===============================================================================================================
byte findEmptySlot(void) {
  byte slot = 0;

  do {
    int e = slotToEEPROM(slot);
    byte id1 = EEPROM.read(e);
    byte id2 = EEPROM.read(e + 1);
    // Serial.println("id1: " + String(id1));
    // Serial.println("id2: " + String(id2));

    if (id1 != (id2 ^ 0xff)) {
      return slot;
    }
    slot++;
  } while (slot < settingItemMax);

  return 255;
}

// ===============================================================================================================
// ===============================================================================================================
void eraseAlleSlots(void) {
  for (int slot = 0; slot < settingItemMax; slot++) {
    int e = slotToEEPROM(slot);
    EEPROM.write(e, 0);
    EEPROM.write(e + 1, 0);
  }
}

// ===============================================================================================================
// ===============================================================================================================
byte SaveSettings(struct setting_t settings) {
  byte slot = findSettingSlot(settings.teiler);

  if (slot == 255) {
    slot = findEmptySlot();
  }

  settings.id1 = settingVersion;
  settings.id2 = settingVersion ^ 0xff;

  Serial.println("Speichern in Slot: " + String(slot));

  int e = slotToEEPROM(slot);
  eepromWrite(e, &settings, sizeof(setting_t));

  return slot;
}

// ===============================================================================================================
// ===============================================================================================================
byte LoadSettings(struct setting_t &settings) {
  byte slot = findSettingSlot(settings.teiler);

  if (slot == 255) {
    return 255;
  }

  Serial.println("Laden aus Slot: " + String(slot));

  int e = slotToEEPROM(slot);
  eepromRead(e, &settings, sizeof(setting_t));

  return slot;
}

// ===============================================================================================================
// ===============================================================================================================
void test(void) {
  Serial.println("----------------------------------");
  eraseAlleSlots();

  Serial.println("Leer: "+String(findEmptySlot()));

  setting_t s;

  s.teiler = 120;
  s.buzzeatdeltatemp=42;
  SaveSettings(s);
  Serial.println("120 Speicherslot: "+String(findSettingSlot(s.teiler)));

  s.teiler = 1220;
  s.buzzeatdeltatemp=142;
  SaveSettings(s);
  Serial.println("1220 Speicherslot: "+String(findSettingSlot(s.teiler)));

  s.teiler = 120;
  Serial.println("120 Leseslot: "+String(findSettingSlot(s.teiler)));
  LoadSettings(s);
  Serial.println("120 Value: "+String(s.buzzeatdeltatemp));

  s.teiler = 1220;
  Serial.println("1220 Leseslot: "+String(findSettingSlot(s.teiler)));
  LoadSettings(s);
  Serial.println("1220 Value: "+String(s.buzzeatdeltatemp));
}
