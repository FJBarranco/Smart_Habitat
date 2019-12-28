void Touch() {

	
		//=================================================== Touch Functions  ====================================

		// ================================================ GUI Setup =====================================================================================================================================================
		TSPoint p = ts.getPoint();


		//pinMode(XP, OUTPUT);
		pinMode(XM, OUTPUT);
		pinMode(YP, OUTPUT);
		//pinMode(YM, OUTPUT);

		// minimum pressure we consider 'valid' - pressure of 0 means no pressing!
		if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
		{

			// scale from 0->1023 to tft.width
			p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
			p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);

			/*  Display Touch coordinates and pressure to the Serial console  */ // (Test Only)
			/*Serial.print("p.x = ");
			Serial.print(p.x);
			Serial.print("  |  p.y = ");
			Serial.print(p.y);
			Serial.print("  |  Pressure = ");
			Serial.println(p.z);*/
		}



		//==========================================================================================================================================

		//======================================================== Main Menue Touch =========================================================

		//  Debug Mode  - RIGHT & LEFT EDGE & TOP & BOTTOM EDGE
		if (p.y > 183 && p.y < 328 && p.x > 88 && p.x < 192) // Button 1
		{

			DebugMode(); // Open Debug Mode Page

		}

		if (p.y > 22 && p.y < 164 && p.x > 88 && p.x < 192) // Button 2
		{

			Orchid(); // Open Orchid Mode

		}

		if (p.y > 183 && p.y < 328 && p.x > 250 && p.x < 350) // Button 3
		{

			ChickenEgg(); // Open Chicken Egg Mode

		}
	}

