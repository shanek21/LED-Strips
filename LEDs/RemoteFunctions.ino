//////////////////////////////////////////////////
//FUNCTIONS FOR READING IR REMOTE BUTTON PRESSES//
//////////////////////////////////////////////////


//Check if the power button was pressed
void checkPower()
{
  //If the IR receiver sees a button press, set 'current code' to the button code
  if (irrecv.decode(&results))
  {
    currentCode = String(results.value, HEX);
    //If power button pressed, toggle power
    if (currentCode == power & !recentPress)
    {
      powerOn = !(powerOn);
      recentPress = true;
      Serial.println("Toggle power!");
      Serial.println(powerOn);
    }
    //Continue looking for button presses
    irrecv.resume();
  }
}


//Check if the up button was pressed
void checkUp()
{
  //If the IR receiver sees a button press, set 'current code' to the button code
  if (irrecv.decode(&results))
  {
    currentCode = String(results.value, HEX);
    //If up button pressed, increase delay
    if (currentCode == up & !recentPress)
    {
      remoteDelay ++;
      recentPress = true;
      Serial.println("Remote delay increased!");
      Serial.println(remoteDelay);
    }    
    //Continue looking for button presses
    irrecv.resume();
  }
}


//Check if the down button was pressed
void checkDown()
{
  //If the IR receiver sees a button press, set 'current code' to the button code
  if (irrecv.decode(&results))
  {
    currentCode = String(results.value, HEX);
    //If down button pressed, decrease delay
    if (currentCode == down & !recentPress)
    {
      remoteDelay --;
      recentPress = true;
      Serial.println("Remote delay decreased!");
      Serial.println(remoteDelay);
      if (remoteDelay <= 0)
      {
        remoteDelay = 0;
      }
    }    
    //Continue looking for button presses
    irrecv.resume();
  }
}
