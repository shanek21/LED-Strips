#include <IRremote.h>

int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results))
  {
    String currentValue = String(results.value, HEX);
    Serial.println(currentValue);
    irrecv.resume(); // Receive the next value
  }
  delay(100);
}
