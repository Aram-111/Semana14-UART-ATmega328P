# Laboratorio Semana 14: UART en el ATmega328P

* **Curso:** Lenguajes de Interfaz (SCC-1014)
* **Unidad:** 4 — Programación de Dispositivos
* **Alumno(s):** Aram Gutierrez Alcantar - Andrés Gustavo Soto Torres
* **Fecha:** 27 de noviembre
* **Hardware:** Arduino Uno (ATmega328P), LED externo + resistencia de 220 Ω

## Archivos y Videos de Demostración

* **`lab14a.ino`** — Configuración de registros UART (`UBRR0`, `UCSR0B`, `UCSR0C`) y transmisión TX a 9600 y 115200 baudios (`U2X0 = 1`) con funciones auxiliares (`uart_tx`, `uart_print`).
  * **Video Lab 14a:** https://drive.google.com/file/d/1pOfNuGsuGnSRmfiBBYs7KdTzf3Tvo9ah/view?usp=sharing

* **`lab14b.ino`** — Recepción por polling (`RXC0`), eco convertido a mayúsculas y comando `'q'` de salida.
  * **Video Lab 14b:** https://drive.google.com/file/d/15RBVFM9RIoKLTNnjnKwjEOds3i3NNBwQ/view?usp=sharing

* **`lab14c.ino`** — Protocolo de control del LED en pin 13 (`'1'` enciende/`'A'`, `'0'` apaga/`'B'`, `'2'` parpadea 3 veces/`'C'`, `'T'` lectura de temperatura interna por ADC, otro carácter/`'?'`).
  * **Video Lab 14c:** https://drive.google.com/file/d/1a2cWDiFIZtvJSCbgbdgajRWt9SVL_1bc/view?usp=sharing

## Declaración de uso de IA
Declaro que he utilizado IA (Gemini) como apoyo para resolver dudas sobre los registros del UART y del ADC del ATmega328P, depurar detalles de comunicación en el Monitor Serie y estructurar los retos de las tres sesiones. Todo el código ha sido probado, depurado y comprendido.

**Prompts principales utilizados:**
1. *"¿Cómo calcular el valor de UBRR0 con el bit U2X0 activado para lograr 115200 baudios sin error en el ATmega328P?"*
2. *"¿Cómo convertir caracteres recibidos por UART de minúsculas a mayúsculas en C usando sus valores ASCII?"*
3. *"¿Por qué el Monitor Serie me devuelve '?' extra al presionar Enter y cómo ignorar los caracteres \r y \n?"*
4. *"¿Qué bits de ADMUX y ADCSRA debo configurar para leer el sensor de temperatura interno del Arduino Uno y convertir el resultado a texto con itoa?"*
