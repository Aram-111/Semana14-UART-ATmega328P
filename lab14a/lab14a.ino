// Lab 14a: Reto 2 (115200 baudios con U2X0) + Reto 3 (funciones auxiliares)

// Envía un solo carácter por UART
void uart_tx(char c) {
  // Esperar hasta que el buffer de transmisión esté vacío (UDRE0 = 1)
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

// Envía una cadena de texto completa usando uart_tx
void uart_print(const char *str) {
  while (*str != '\0') {
    uart_tx(*str);
    str++;
  }
}

void setup() {
  // 1. Activar doble velocidad (U2X0 = 1) para minimizar error en 115200 baudios
  // Fórmula con U2X0=1: UBRR0 = (16,000,000 / (8 * 115200)) - 1 = 16.36 ≈ 16
  UCSR0A |= (1 << U2X0);
  UBRR0 = 16;

  // 2. Habilitar TX y RX
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);

  // 3. Formato 8N1 (8 bits de datos, sin paridad, 1 stop bit)
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void loop() {
  uart_print("Hola desde el ATmega328P a 115200!\r\n");
  delay(1000);
}