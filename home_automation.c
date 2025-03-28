#include <IRremote.h>

const int RECV_PIN = 11; // Pin connected to the IR receiver module
const int RELAY_PIN = 7; // Digital pin connected to the relay control

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the IR receiver
  pinMode(RELAY_PIN, OUTPUT); // Set relay pin as output
}

void loop()
{
  if (irrecv.decode(&results))
  {
    unsigned int value = results.value;
    Serial.println(value, HEX); // Print the HEX value of the button pressed

    // Example: Control relay based on specific remote button
    if (value == 0xFF30CF) // Replace with your remote's button code
    {
      digitalWrite(RELAY_PIN, HIGH); // Turn relay on
    }
    else if (value == 0xFF18E7)
    {
      digitalWrite(RELAY_PIN, LOW); // Turn relay off
    }

    irrecv.resume(); // Receive the next value
  }
}

