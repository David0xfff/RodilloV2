# Proyecto de Control con Arduino Nano, Sensor IR, Encoder Rotativo y Pantalla LCD

Este proyecto utiliza un Arduino Nano, un sensor infrarrojo, un encoder rotativo y una pantalla LCD I2C para realizar tareas de control y monitoreo con funcionalidades adicionales como almacenamiento en EEPROM.

## Hardware Utilizado

### 1. **Microcontrolador**
- **Arduino Nano**: Se utiliza como el núcleo del proyecto para leer sensores, manejar la pantalla LCD y realizar cálculos.

### 2. **Sensor Infrarrojo (E18-D80NK)**
- Configuración:
  - Marrón → Positivo
  - Negro → Señal (Conectado a D5)
  - Azul → Negativo
- Ajuste:
  - El tornillo se ajusta en sentido antihorario para reducir la distancia de detección.

### 3. **Encoder Rotativo (KY-040)**
- Conexiones:
  - SW → D3
  - DT → D2
  - CLK → D5

### 4. **Pantalla LCD I2C (16x2)**
- Conexiones:
  - SCL → A5
  - SDA → A4

## Funcionalidades

### 1. **Contador con Encoder Rotativo**
- Permite incrementar o decrementar un valor en pantalla según el giro del encoder.
- Incluye un botón en el encoder para activar funciones adicionales.

### 2. **Detección con Sensor Infrarrojo**
- Detecta la presencia de un objeto y muestra un estado en la pantalla.

### 3. **Almacenamiento de Estado**
- El valor actual del contador se guarda en la memoria EEPROM, garantizando que persista después de un reinicio.

### 4. **Pantalla Personalizada**
- Dígitos personalizados para mostrar valores en la pantalla LCD de manera gráfica.
- Caracteres definidos en el código para crear gráficos personalizados.

## Código Principal

El código realiza las siguientes tareas:
1. Configuración inicial de pines y dispositivos.
2. Manejo de interrupciones para detectar giros en el encoder rotativo.
3. Actualización de valores en la pantalla LCD en tiempo real.
4. Detección de eventos mediante el sensor infrarrojo.
5. Almacenamiento de valores en EEPROM para su persistencia.

## Estructura del Código

### 1. **Configuración**
La función `setup()` inicializa la pantalla LCD, los pines y los valores almacenados en la EEPROM.

### 2. **Loop Principal**
El bucle `loop()` realiza las siguientes tareas:
- Detectar cambios en el valor del contador.
- Leer el estado del botón del encoder y del sensor infrarrojo.
- Actualizar la pantalla LCD.

### 3. **Interrupciones**
Se utiliza la función `encoder()` para manejar los pulsos del encoder rotativo y ajustar el contador de manera precisa.

### 4. **Funciones Personalizadas**
- `compocicion()`: Actualiza la pantalla LCD con el valor actual del contador.
- `printNumber(value, col)`: Dibuja números personalizados en la pantalla LCD.
