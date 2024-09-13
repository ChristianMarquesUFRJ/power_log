#include <Wire.h>
#include <Adafruit_INA219.h>

#include "logger.h"

Adafruit_INA219 ina219;

void setup(void) 
{
    Serial.begin(115200);

    while (!Serial) {
        delay(1);
    }

    unsigned int init_time = millis();
    do{
        Serial.println(">> Aguardando Terminal: " + String((10000 - (millis() - init_time)),1) + "s");
    } while(millis() - init_time < 10000);

    // ===================================================================
    setup_log();
    // readFile(SD, "/TESTE.txt");
    // writeFile(SD, "/log.txt", "Mensagem 1");
    // appendFile(SD, "/log.txt", "Mensagem 2");
    // appendFile(SD, "/log.txt", "Mensagem 3");
    // readFile(SD, "/log.txt");
    // ===================================================================

    Serial.println("==================");
    Serial.println("=== POWER LOG ====");
    Serial.println("==================");

    if (!ina219.begin()) {
        Serial.println(">> Erro ao conectar com o INA219");
        while (1) { delay(10); }
    }

    Serial.println("==================");
    Serial.println("INICIALIZANDO...  ");
    Serial.println("==================");

    // Serial.println("tempo[ms];tensao[V];corrente[mA];potencia[mW]");
    writeFile(SD, "/datalogger.txt", "tempo[ms];tensao[V];corrente[mA];potencia[mW]\n");
}

void loop(void) {
    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();
    float current_mA = ina219.getCurrent_mA();
    float power_mW = ina219.getPower_mW();
    float load_voltage = busvoltage + (shuntvoltage / 1000);
    static unsigned int start_time_ms = millis();

    String msg = get_message(millis()-start_time_ms, load_voltage, current_mA, power_mW);
    appendFile(SD, "/datalogger.txt", msg);

    delay(1000);
}