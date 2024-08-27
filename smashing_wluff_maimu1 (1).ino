// Definir los pines para los LEDs
const int greenLedPin = 11;
const int redLedPin = 12;
const int yellowLedPin = 13;

// Definir el estado de parpadeo
bool blinking = false;

void setup() {
  // Configurar los pines de los LEDs como salida
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);

  // Iniciar la comunicación serial a 9600 bps
  Serial.begin(9600);

  // Mensaje inicial
  Serial.println("Control de luces iniciado.");
  Serial.println("Presiona:");
  Serial.println("1 para encender la luz verde.");
  Serial.println("2 para apagar la luz verde.");
  Serial.println("3 para encender la luz roja.");
  Serial.println("4 para apagar la luz roja.");
  Serial.println("5 para encender la luz amarilla.");
  Serial.println("6 para apagar la luz amarilla.");
  Serial.println("7 para encender todas las luces.");
  Serial.println("8 para apagar todas las luces.");
  Serial.println("9 para activar el modo intermitente.");
}

void loop() {
  // Comprobar si hay datos disponibles en la entrada serial
  if (Serial.available() > 0) {
    // Leer la entrada como un número entero
    int command = Serial.parseInt();
    
    // Ejecutar la acción correspondiente al comando
    switch (command) {
      case 1:
        controlLight(greenLedPin, HIGH, "verde encendida.");
        break;
      case 2:
        controlLight(greenLedPin, LOW, "verde apagada.");
        break;
      case 3:
        controlLight(redLedPin, HIGH, "roja encendida.");
        break;
      case 4:
        controlLight(redLedPin, LOW, "roja apagada.");
        break;
      case 5:
        controlLight(yellowLedPin, HIGH, "amarilla encendida.");
        break;
      case 6:
        controlLight(yellowLedPin, LOW, "amarilla apagada.");
        break;
      case 7:
        controlAllLights(HIGH, "Todas las luces encendidas.");
        break;
      case 8:
        controlAllLights(LOW, "Todas las luces apagadas.");
        break;
      case 9:
        blinking = !blinking;
        if (blinking) {
          Serial.println("Modo intermitente activado.");
        } else {
          Serial.println("Modo intermitente desactivado.");
        }
        break;
      default:
        Serial.println("Comando no reconocido.");
    }
  }

  // Modo intermitente
  if (blinking) {
    controlAllLights(HIGH, "");
    delay(500);
    controlAllLights(LOW, "");
    delay(500);
  }
}

// Función para controlar una luz específica
void controlLight(int ledPin, int state, String message) {
  digitalWrite(ledPin, state);
  Serial.println("Luz " + message);
}

// Función para controlar todas las luces a la vez
void controlAllLights(int state, String message) {
  digitalWrite(greenLedPin, state);
  digitalWrite(redLedPin, state);
  digitalWrite(yellowLedPin, state);
  if (message != "") {
    Serial.println(message);
  }
}