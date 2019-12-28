void  HomeMenu() {           //  main menu for all settings 
	

	pinMode(13, OUTPUT);
	tft.reset();


	// ====================================================== Reset the TFT Display ========================================================


	tft.begin(0x9341);                          // The address of your Display
	tft.setRotation(LCDROTATION);               // Need for the Mega, please changed for your choice or rotation initial
	tft.fillScreen(BLACK);
	delay(500);
		
	// =========================================================== GUI =====================================================================


		/*  Button 1 - Horizontal, Vertical, Width, Height, Color  */
		tft.setTextSize(3);
		tft.setTextColor(WHITE);
		tft.drawRect(20, 55, 210, 70, GREY);   //
		tft.drawRect(21, 56, 208, 68, GREY);
		tft.setCursor(40, 80);
		tft.println("Debug Mode");

		/*  Button 2 - Horizontal, Vertical, Width, Height, Color  */
		tft.setTextSize(3);
		tft.setTextColor(WHITE);
		tft.drawRect(250, 55, 210, 70, GREY);
		tft.drawRect(251, 56, 208, 68, GREY);
		tft.setCursor(290, 80);
		tft.println("Orchid");

		/*  Button 3 - Horizontal, Vertical, Width, Height, Color  */
		tft.setTextSize(3);
		tft.setTextColor(WHITE);
		tft.drawRect(20, 155, 210, 70, GREY);   //
		tft.drawRect(21, 156, 208, 68, GREY);
		tft.setCursor(29, 180);
		tft.println("Chicken Egg");

		//=============================================================

		

}

