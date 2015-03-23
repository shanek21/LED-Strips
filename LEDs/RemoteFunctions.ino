//////////////////////////////////////////////////
//FUNCTIONS FOR READING IR REMOTE BUTTON PRESSES//
//////////////////////////////////////////////////

//Check for all buttons
void checkButtons()
{
  if (irrecv.decode(&results))
  {
    //Define the button value that was pressed
    currentCode = String(results.value, HEX);
    
    //If power button pressed, toggle power
    if (currentCode == power)
    {
      currentCode = "penis";
      Serial.println("Attempting to toggle");
      if (remoteRefresh%2 == 0)
      {
        powerOn = !(powerOn);
        Serial.println("Toggle power!");
        Serial.println(powerOn);
      }
      remoteRefresh++;
    }
    
    //If up button pressed, increase fade speed
    else if (currentCode == up)
    {
      if (remoteRefresh%2 == 0 & remoteDelay > 0)
      {
        remoteDelay --;
        Serial.println("Fade speed increased!");
        Serial.println(remoteDelay);
      }
      remoteRefresh++;
    }
    
    //If down button pressed, decrease fade speed
    else if (currentCode == down)
    {
      if (remoteRefresh%2 == 0 & remoteDelay < 20)
      {
        remoteDelay ++;
        Serial.println("Fade speed decreased!");
        Serial.println(remoteDelay);
      }
      remoteRefresh++;
    }
    
    //If one button pressed, set state
    else if (currentCode == one)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = 1;
        Serial.println("State set to one");
        Serial.println(currentState);
      }
      remoteRefresh++;
    }
    
    //If two button pressed, set state
    else if (currentCode == two)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = 2;
        Serial.println("State set to two");
        Serial.println(currentState);
      }
      remoteRefresh++;
    }
    
    //If three button pressed, set state
    else if (currentCode == three)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = 3;
        Serial.println("State set to three");
        Serial.println(currentState);
      }
      remoteRefresh++;
    }
    
    //Continue looking for button presses
    irrecv.resume();
  }
}
