/*Se implementa un programa que ejemplifica el uso de 
dos interrupciones externas, en donde al presionar alguno de los 
pulsadores, la velocidad en que la secuencia de encendido y 
apagado de los leds conectados, disminuye o aumenta hasta llegar
a un tope. El pulsador izquierdo disminuye la velocidad y el 
derecho la aumenta, se deben presionar varias veces para ir 
notando los cambios. El programa inicialmente esta con la 
velocidad mínima. */

//Variable global que controla la velocidad
long int tiempo_espera = 1000; 
// Constantes de los tiempos de espera máxima, mínima y cuanto aumenta
//Las constantes son los valores en milisegundos que espera el delay
//entre cada encendido y apagado de los leds
const int maxima = 20;
const int minima = 1000;
const int aumenta = 70;
const int disminuye =70;

// Array con los números de los pines donde están conectados
// los LEDs, almacenados para que inicien desde la izquierda
int leds[5] = {12, 11, 10, 9, 8};


void setup() {
  // Se inicializan los pines de los LEDs como salida y en estado bajo
  for (int i = 0; i < 5; i++)
  {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  // Se asigna la velocidad mínima
  tiempo_espera = minima;

  /* Se configuran los pines de interrupciones para que
  detecten un cambio de bajo a alto*/
  attachInterrupt(digitalPinToInterrupt(2), velocidadMenos, RISING);//Interrupción que disminuye la velocidad del led
  attachInterrupt(digitalPinToInterrupt(3), velocidadMas, RISING);//Interrupción que aumenta la velocidad del led

}

void loop() {
  // Este primer bucle recorre el array de izquierda a derecha
  //Y muestra el resultado en los leds de la misma forma
  
  for (int i = 0; i < 5; i++)
  {
    // Solo para el segundo pin y consecutivos se apaga el pin anterior
    // En el caso de 0 no hace falta ya que por defecto está apagado
    if (i > 0) //Se validan los rangos del array con los leds
    {
      digitalWrite(leds[i - 1], LOW); // Apaga el LED a la izquierda
    }

    
    digitalWrite(leds[i], HIGH); // Enciende el LED actual

    
    delay(tiempo_espera); // Espera el tiempo que marca la velocidad
  }

  //Apaga el último LED encendido, el ultimo elemento del array
  digitalWrite(leds[4], LOW);

  // Recorre el array en sentido inverso, de derecha a izquierda
  for (int i = 4; i >= 0; i--)
  {
    // En el primer caso como ya está apagado el LED no hace nada
    if (i < 4) //Controla los rangos del array
    {
      digitalWrite(leds[i + 1], LOW); // Apaga el LED a la derecha
    }
    digitalWrite(leds[i], HIGH); //Enciende el LED actual

    delay(tiempo_espera); // Espera el tiempo marcado por la velocidad
  }

  // Apaga el último LED encendido, el elemento 0 del array
  digitalWrite(leds[0], LOW);

}

// ISR pin 2, disminuye la velocidad
void velocidadMenos()
{  
  //Aumenta el valor establecido para que la velocidad sea
  //mayor y espere mas, por lo que la espera aumenta
  tiempo_espera += disminuye;

  // Si llega a la velocidad mínima no disminuye más
  if (tiempo_espera > minima)
  {
    tiempo_espera = minima;
  }
}

// ISR pin 3, aumenta la velocidad
void velocidadMas()
{
  //Disminuye el valor establecido para que la velocidad sea
  //menor y espere menos, por lo que la velocidad aumenta
  tiempo_espera -= aumenta; 

  // Si llega a la velocidad máxima no aumenta más
  if (tiempo_espera < maxima)
  {
    tiempo_espera = maxima;
  }
}