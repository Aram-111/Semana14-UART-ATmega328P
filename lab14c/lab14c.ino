// Lab 14c: Protocolo simple UART + GPIO (LED) + ADC (Temperatura interna)
#include <stdlib.h> // Necesaria para itoa()

void uart_tx(char c) {
  while (!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
}

void uart_print(const char *str) {
  while (*str != '\0') {
    uart_tx(*str);
    str++;
  }
}

// Bono +5%: Leer el sensor de temperatura interno del ATmega328P
int leer_temperatura_adc() {
  // Referencia interna de 1.1V (REFS1=1, REFS0=1) y canal 8: sensor interno (MUX3=1)
  ADMUX = (1 << REFS1) | (1 << REFS0) | (1 << MUX3);
  delay(10); // Breve espera para estabilizar el voltaje de referencia

  // Habilitar ADC (ADEN), iniciar conversión (ADSC) y prescaler 128 (ADPS2:0 en 1)
  ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Esperar a que termine la conversión (cuando ADSC vuelva a 0)
  while (ADCSRA & (1 << ADSC));

  return ADC; // Devuelve el valor crudo de 10 bits (0 - 1023)
}

void setup() {
  UCSR0A = 0;                               // Velocidad normal (U2X0 = 0)
  UBRR0 = 103;                              // 9600 baudios
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);     // Habilitar TX y RX
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // Formato 8N1

  // Configurar PB5 (pin 13) como salida para el LED
  DDRB |= (1 << PB5);
}

void loop() {
  // 1. RECIBIR: Esperar a que llegue un carácter por UART
  while (!(UCSR0A & (1 << RXC0)));
  char c = UDR0;

  // Ignorar saltos de línea del Monitor Serie para que no disparen el '?'
  if (c == '\r' || c == '\n') return;

  // 2. PROCESAR y 3. RESPONDER
  if (c == '1') {
    PORTB |= (1 << PB5);    // Encender LED (pin 13)
    uart_print("A\r\n");    // Confirmación: Encendido
  } 
  else if (c == '0') {
    PORTB &= ~(1 << PB5);   // Apagar LED (pin 13)
    uart_print("B\r\n");    // Confirmación: Apagado
  } 
  else if (c == '2') {      // Reto 1: Parpadeo 3 veces
    for (int i = 0; i < 3; i++) {
      PORTB |= (1 << PB5);
      delay(500);
      PORTB &= ~(1 << PB5);
      delay(500);
    }
    uart_print("C\r\n");    // Confirmación: Parpadeo terminado
  } 
  else if (c == 'T' || c == 't') { // Reto 2 (Bono +5%): Temperatura
    int valor_adc = leer_temperatura_adc();
    char buffer[10];
    itoa(valor_adc, buffer, 10); // Convertir entero a texto base 10
    uart_print("Temp ADC: ");
    uart_print(buffer);
    uart_print("\r\n");
  } 
  else {
    uart_print("?\r\n");    // Comando desconocido
  }
}