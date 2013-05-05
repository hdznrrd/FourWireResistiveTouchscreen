// FourWireResistiveTouchscreen Library
// (c) 2013 hadez@shackspace.de

#ifndef _FourWireResistiveTouchscreen_h_
#define _FourWireResistiveTouchscreen_h_


class FourWireResistiveTouchscreen
{
  public:
	struct Measurement
	{
		unsigned int x;
		unsigned int y;
		unsigned int pressure;
	};

    FourWireResistiveTouchscreen(int pinX1, int pinX2, int pinY1, int pinY2);
    void getPosition(Measurement& m);
  private:
    int _pX1;
    int _pX2;
    int _pY1;
    int _pY2;
		
};

#endif
