//////////////////////////////////////////////////
//FUNCTIONS FOR READING IR REMOTE BUTTON PRESSES//
//////////////////////////////////////////////////

//Check for all buttons
void checkButtons()
{
  //If IR remote input is detected
  if (irrecv.decode(&results))
  {
    //Define the button value that was pressed
    currentCode = String(results.value, HEX);
    
    //If power button pressed, toggle power
    if (currentCode == POWER)
    {
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
    else if (currentCode == UP)
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
    else if (currentCode == DOWN)
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
    else if (currentCode == ONE)
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
    else if (currentCode == TWO)
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
    else if (currentCode == THREE)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = 3;
        Serial.println("State set to three");
        Serial.println(currentState);
      }
      remoteRefresh++;
    }
    
    //If four button pressed, set state
    else if (currentCode == FOUR)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = 4;
        Serial.println("State set to four");
        Serial.println(currentState);
      }
      remoteRefresh++;
    }
    
    //If the play button is pressed... well... just don't press it
    else if (currentCode == REWIND)
    {
      if (remoteRefresh%2 == 0)
      {
        gameState = "red";
      }
      remoteRefresh++;
    }
    
    //If the play button is pressed... well... just don't press it
    else if (currentCode == PLAY)
    {
      if (remoteRefresh%2 == 0)
      {
        currentState = easterState;
        gameState = "green";
      }
      remoteRefresh++;
    }
    
    //If the fastforward button is pressed... well... just don't press it
    else if (currentCode == FASTFORWARD)
    {
      if (remoteRefresh%2 == 0)
      {
        gameState = "blue";
      }
      remoteRefresh++;
    }
    
    //Continue looking for button presses
    irrecv.resume();
  }
}

//Hmm... I'm not sure what this does...
void buttonsCheck()
{
  //If IR remote input is detected
  if (irrecv.decode(&results))
  {
    //Define the button value that was pressed
    currentCode = String(results.value, HEX);
  }
  //Continue looking for button presses
  irrecv.resume();
}
