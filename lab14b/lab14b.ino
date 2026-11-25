// Lab 14b: UART RX — Eco en mayúsculas + Comando 'q' para salir

// Función auxiliar para enviar un carácter
void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

// Función auxiliar para enviar una cadena de texto
void uart_print(const char *str) {
  while (*str != '\0') {
    uart_tx(*str);
    str++;
  }
}

void setup() {
  UCSR0A = 0;                               // Velocidad normal (U2X0 = 0)
  UBRR0 = 103;                              // 9600 baudios a 16 MHz
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);     // Habilitar TX y RX
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // Formato 8N1
}

void loop() {
  // 1. Esperar a que llegue un dato completo por RX (bandera RXC0 = 1)
  while (!(UCSR0A & (1 << RXC0)));

  // 2. Leer el carácter recibido desde el registro de datos UDR0
  char c = UDR0;

  // Reto 2: Si es 'q' (o 'Q'), mostrar "Adios" y bloquear el programa
  if (c == 'q' || c == 'Q') {
    uart_print("Adios\r\n");
    while (1); // Bucle infinito: deja de hacer eco hasta reiniciar el Arduino
  }

  // Reto 1: Si es letra minúscula ('a' - 'z'), convertir a mayúscula
  if (c >= 'a' && c <= 'z') {
    c = c - 32; // En ASCII, la diferencia entre minúscula y mayúscula es 32
  }

  // 3. Hacer eco devolviendo el carácter
  uart_tx(c);
}