#include "logger.h"

void setup_log(){
    
    SPI.begin(sck, miso, mosi, cs);
    if (!SD.begin(cs)) {
        Serial.println("Card Mount Failed");
        return;
    }

    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE) {
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if (cardType == CARD_MMC) {
        Serial.println("MMC");
    } else if (cardType == CARD_SD) {
        Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("Tamanho SD Card: %lluMB\n", cardSize);

}

void readFile(fs::FS &fs, const char *path) {
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("\n======================");
    Serial.print("Leitura de arquivo: ");
    Serial.println("\n======================");
    while (file.available()) {
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.println(">>> ESCRITA: " + String(path) + " | Mensagem: '" + String(message) + "'");
    File file = fs.open(path, FILE_WRITE);
    
    if (!file) {
        Serial.println("['" + String(path) + "']: Erro ao tentar abrir o arquivo!");
        return;
    }

    if (file.print(message))
        Serial.println("CRIANDO ARQUIVO '" + String(path) + "' COM A MENSAGEM: " + String(message));
    else
        Serial.println("['" + String(path) + "']: Erro de escrita no arquivo!");
    file.close();
}

void appendFile(fs::FS &fs, const char *path, String message) {
    File file = fs.open(path, FILE_APPEND);
    
    if (!file) {
        Serial.println("['" + String(path) + "']: Erro ao tentar abrir o arquivo!");
        return;
    }

    if (file.print(message))
        Serial.println("INSERINDO DADOS EM '" + String(path) + "': " + String(message));
    else
        Serial.println("['" + String(path) + "']: Erro de anexar no arquivo!");
    file.close();
}

String get_message(unsigned long time, float voltage, float current, float power){
    String msg_str = String(time) + ";" + String(voltage, 2) + ";" + String(current, 2) + ";" + String(power, 2) + "\n";
    return msg_str;
}