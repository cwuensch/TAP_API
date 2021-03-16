#include "tap.h"

#define ABS(x)	(((x)>0)?(x):(-(x)))

void DrawLine( word rgn, int Ax, int Ay, int Bx, int By, int Color )
{
	int dX = ABS(Bx-Ax);	// store the change in X and Y of the line endpoints
	int dY = ABS(By-Ay);

	int CurrentX = Ax;		// store the starting point (just point A)
	int CurrentY = Ay;

	int Xincr, Yincr;
	if (Ax > Bx) { Xincr=-1; } else { Xincr=1; }	// which direction in X?
	if (Ay > By) { Yincr=-1; } else { Yincr=1; }	// which direction in Y?

	if (dX >= dY)	// if X is the independent variable
	{
		int dPr 	= dY<<1;						// amount to increment decision if right is chosen (always)
		int dPru	= dPr - (dX<<1);				// amount to increment decision if up is chosen
		int P		= dPr - dX; 					// decision variable start value

		for (; dX>=0; dX--) 						// process each point in the line one at a time (just use dX)
		{
			TAP_Osd_PutPixel( rgn, CurrentX, CurrentY, Color);	  // plot the pixel
			if (P > 0)								// is the pixel going right AND up?
			{
				CurrentX+=Xincr;					// increment independent variable
				CurrentY+=Yincr;					// increment dependent variable
				P+=dPru;							// increment decision (for up)
			}
			else									// is the pixel just going right?
			{
				CurrentX+=Xincr;					// increment independent variable
				P+=dPr; 							// increment decision (for right)
			}
		}
	}
	else			// if Y is the independent variable
	{
		int dPr 	= dX<<1;						// amount to increment decision if right is chosen (always)
		int dPru	= dPr - (dY<<1);					// amount to increment decision if up is chosen
		int P		= dPr - dY; 					// decision variable start value

		for (; dY>=0; dY--) 						// process each point in the line one at a time (just use dY)
		{

			TAP_Osd_PutPixel( rgn, CurrentX, CurrentY, Color);	  // plot the pixel
			if (P > 0)								// is the pixel going up AND right?
			{
				CurrentX+=Xincr;					// increment dependent variable
				CurrentY+=Yincr;					// increment independent variable
				P+=dPru;							// increment decision (for up)
			}
			else									// is the pixel just going up?
			{
				CurrentY+=Yincr;					// increment independent variable
				P+=dPr; 							// increment decision (for right)
			}
		}
	}
}
