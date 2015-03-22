void rainbow()
{
  fade(red, redgreen);
  if (!powerOn)
  {
    return;
  }
  fade(redgreen, green);
  if (!powerOn)
  {
    return;
  }
  fade(green, greenblue);
  if (!powerOn)
  {
    return;
  }
  fade(greenblue, blue);
  if (!powerOn)
  {
    return;
  }
  fade(blue, bluered);
  if (!powerOn)
  {
    return;
  }
  fade(bluered, red);
  if (!powerOn)
  {
    return;
  }
}
