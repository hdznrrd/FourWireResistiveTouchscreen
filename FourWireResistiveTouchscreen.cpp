// (c) 2013 hadez@shackspace.de
// released as-is without warranty under GPL
#include "FourWireResistiveTouchscreen.h"
#include "Arduino.h"

#define DOFF 14 // offset for analog pins when accessing them via digitalRead/Write


FourWireResistiveTouchscreen::FourWireResistiveTouchscreen(int pinX1, int pinX2, int pinY1, int pinY2)
{
  _pX1 = pinX1;
  _pX2 = pinX2;
  _pY1 = pinY1;
  _pY2 = pinY2;
}

void FourWireResistiveTouchscreen::getPosition(FourWireResistiveTouchscreen::Measurement& m)
{
	unsigned int x1=0;
	unsigned int x2=0;
	unsigned int y1=0;
	unsigned int y2=0;
	unsigned int p=0;

  // Read the X coordinate
  pinMode( _pX2 + DOFF, INPUT ); 
  pinMode( _pX1 + DOFF, INPUT ); 
  pinMode( _pY1 + DOFF, OUTPUT );
  pinMode( _pY2 + DOFF, OUTPUT );
  digitalWrite( _pY1 + DOFF, LOW ); 
  digitalWrite( _pY2 + DOFF, HIGH );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );
  x1 += analogRead( _pX2 );

	// Read X coordinates w/ reversed polarity
  digitalWrite( _pY1 + DOFF, HIGH );
  digitalWrite( _pY2 + DOFF, LOW ); 
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );
  x2 += 1024-analogRead( _pX2 );


  // Read the Y coordinate
  pinMode( _pY1 + DOFF, INPUT ); 
  pinMode( _pY2 + DOFF, INPUT ); 
  pinMode( _pX2 + DOFF, OUTPUT );
  pinMode( _pX1 + DOFF, OUTPUT );
  digitalWrite( _pX2 + DOFF, LOW ); 
  digitalWrite( _pX1 + DOFF, HIGH );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );
  y1 += analogRead( _pY1 );

	// Read Y coordinates w/ reversed polarity
  digitalWrite( _pX2 + DOFF, HIGH );
  digitalWrite( _pX1 + DOFF, LOW ); 
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );
  y2 += 1024-analogRead( _pY1 );

	// Read pressure
  pinMode( _pX2 + DOFF, OUTPUT ); 
  pinMode( _pX1 + DOFF, OUTPUT ); 
  pinMode( _pY1 + DOFF, OUTPUT );
  pinMode( _pY2 + DOFF, INPUT );
  digitalWrite( _pX1 + DOFF, HIGH );
  digitalWrite( _pX2 + DOFF, HIGH );
  digitalWrite( _pY1 + DOFF, LOW );
  digitalWrite( _pY2 + DOFF, LOW );
  p += analogRead( _pY2 );
  p += analogRead( _pY2 );

  pinMode( _pY1 + DOFF, INPUT );
  pinMode( _pY2 + DOFF, OUTPUT );
  digitalWrite( _pY2 + DOFF, LOW );
  p += analogRead( _pY1 );
  p += analogRead( _pY1 );

  pinMode( _pY1 + DOFF, OUTPUT );
  pinMode( _pY2 + DOFF, OUTPUT );
  pinMode( _pX2 + DOFF, OUTPUT ); 
  pinMode( _pX1 + DOFF, INPUT ); 
  digitalWrite( _pY1 + DOFF, HIGH );
  digitalWrite( _pY2 + DOFF, HIGH );
  digitalWrite( _pX2 + DOFF, LOW );
  p += analogRead( _pX1 );
  p += analogRead( _pX1 );

  pinMode( _pX1 + DOFF, OUTPUT );
  pinMode( _pX2 + DOFF, INPUT );
  digitalWrite( _pX1 + DOFF, LOW );
  p += analogRead( _pX2 );
  p += analogRead( _pX2 );

	// average of forward and backward measurement
	unsigned int xVal = (x1+x2)>>1;
	unsigned int yVal = (y1+y2)>>1;

	// prefer values measured on the high-voltage end for accuracy
	// if we're in the middle of the range, use averaging
/*
	if(xVal < 1024/3) { xVal = x2; }
	else if(xVal > 1024-(1024/3)) { xVal = x1; }

	if(yVal < 1024/3) { yVal = y2; }
	else if(yVal > 1024-(1024/3)) { yVal = y1; }
*/

	m.x = xVal;
	m.y = xVal;
	m.pressure = p;
}
