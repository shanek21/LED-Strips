void GBtoRB()
{
  if (potTime < 4500)
  {
    if (light < lightThreshold)
    {
      turnGreenBlue();
      potValue = analogRead(potPin);
      potTime = map(potValue, 0, 1025, 10, 5000);
      delay(potTime);
      light = analogRead(photoPin);
    }
    else
    {
      light = analogRead(photoPin);
      turnOff();
      delay(time);
    }
    if (light < lightThreshold)
    {
      turnRedBlue();
      potValue = analogRead(potPin);
      potTime = map(potValue, 0, 1025, 10, 5000);
      //Serial.println(potTime);
      delay(potTime);
      light = analogRead(photoPin);
    }
    else
    {
      light = analogRead(photoPin);
      turnOff();
      delay(time);
    }
  }
  else
  {
    turnWhite();
  }
}
