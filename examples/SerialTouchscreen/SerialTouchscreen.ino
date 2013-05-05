#include <FourWireResistiveTouchscreen.h>

FourWireResistiveTouchscreen ts(3, 1, 0, 2);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  
  int coordssum[3] = {0,0,0};
  FourWireResistiveTouchscreen::Measurement m = {0,0,0};
  
  // discard one
  ts.getPosition(m);
  
  // ensure that we have 4 successfull samples with finger-down state
  byte samples = 4;
  while(samples > 0)
  {
    ts.getPosition(m);
    
    if(m.pressure > 300)
    {
      coordssum[0] += m.x;
      coordssum[1] += m.y;
      coordssum[2] += m.pressure;
    }
    else
    {
      // finger was lifted, start over 
      return;
    }
    
    --samples;
  }
  
  // report x,y,pressure
  Serial.print(coordssum[0]/4);
  Serial.print(",");
  Serial.print(coordssum[1]/4);
  Serial.print(",");
  Serial.println(coordssum[2]/4);
}
