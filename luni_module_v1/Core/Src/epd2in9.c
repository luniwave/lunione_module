/**
 *  @filename   :   epd2in9.c
 *  @brief      :   Implements for e-paper library
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 12 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include "epd2in9.h"
#include "main.h"
#include "epdif.h"

int EPD_Init(EPD* epd, const unsigned char* lut) {
	epd->reset_pin = RST_PIN;
	epd->dc_pin = DC_PIN;
	epd->cs_pin = CS_PIN;
	epd->busy_pin = BUSY_PIN;
	epd->width = EPD_WIDTH;
	epd->height = EPD_HEIGHT;
	/* this calls the peripheral hardware interface, see epdif */
	if (EpdInitCallback() != 0) {
		return -1;
	}



	epd->lut = lut;

  EPD_Reset(epd);

  EPD_WaitUntilIdle(epd);
  EPD_SendCommand(epd,SW_RESET); // soft reset
  EPD_WaitUntilIdle(epd);

  EPD_SendCommand(epd, DRIVER_OUTPUT_CONTROL);
  EPD_SendData(epd, 0x27);
  EPD_SendData(epd, 0x01);
  EPD_SendData(epd, 0x00);

  // Entrymode
  EPD_SendCommand(epd, DATA_ENTRY_MODE_SETTING);
  EPD_SendData(epd, 0x03);

  // Curseur de mémoire
  EPD_SetMemoryArea(epd, 0 , 0, EPD_WIDTH-1, EPD_HEIGHT-1);

  // Update mode
  EPD_SendCommand(epd, DISPLAY_UPDATE_CONTROL_1);
  EPD_SendData(epd, 0x00);
  EPD_SendData(epd, 0x80);

  // Set the cursor
  EPD_SetMemoryPointer(epd,0,0);
  EPD_WaitUntilIdle(epd);


  /* EPD hardware init end */
  return 0;



}

/**
 *  @brief: this calls the corresponding function from epdif.h
 *          usually there is no need to change this function
 */
void EPD_DigitalWrite(EPD* epd, int pin, int value) {
  EpdDigitalWriteCallback(pin, value);
}

/**
 *  @brief: this calls the corresponding function from epdif.h
 *          usually there is no need to change this function
 */
int EPD_DigitalRead(EPD* epd, int pin) {
  return EpdDigitalReadCallback(pin);
}

/**
 *  @brief: this calls the corresponding function from epdif.h
 *          usually there is no need to change this function
 */
void EPD_DelayMs(EPD* epd, unsigned int delaytime) {  // 1ms
  EpdDelayMsCallback(delaytime);
}

/**
 *  @brief: basic function for sending commands
 */
void EPD_SendCommand(EPD* epd, unsigned char command) {
  EPD_DigitalWrite(epd, epd->dc_pin, LOW);
  EpdSpiTransferCallback(command);
}

/**
 *  @brief: basic function for sending data
 */
void EPD_SendData(EPD* epd, unsigned char data) {
  EPD_DigitalWrite(epd, epd->dc_pin, HIGH);
  EpdSpiTransferCallback(data);
}

/**
 *  @brief: Wait until the busy_pin goes LOW
 */
void EPD_WaitUntilIdle(EPD* epd) {
  while(EPD_DigitalRead(epd, epd->busy_pin) == HIGH) {      //0: busy, 1: idle
    EPD_DelayMs(epd, 100);
  }      
}

/**
 *  @brief: module reset.
 *          often used to awaken the module in deep sleep,
 *          see EPD::Sleep();
 */
void EPD_Reset(EPD* epd) {
  EPD_DigitalWrite(epd, epd->reset_pin, LOW);                //module reset    
  EPD_DelayMs(epd, 10);
  EPD_DigitalWrite(epd, epd->reset_pin, HIGH);
  EPD_DelayMs(epd, 10);
}

/**
 *  @brief: put an image buffer to the frame memory.
 *          this won't update the display.
 */
void EPD_SetFrameMemory(
  EPD* epd,
  const unsigned char* image_buffer,
  int x,
  int y,
  int image_width,
  int image_height
) {
  int x_end;
  int y_end;

  if (
    image_buffer == NULL ||
    x < 0 || image_width < 0 ||
    y < 0 || image_height < 0
  ) {
    return;
  }
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  x &= 0xF8;
  image_width &= 0xF8;
  if (x + image_width >= epd->width) {
    x_end = epd->width - 1;
  } else {
    x_end = x + image_width - 1;
  }
  if (y + image_height >= epd->height) {
    y_end = epd->height - 1;
  } else {
    y_end = y + image_height - 1;
  }
  EPD_SetMemoryArea(epd, x, y, x_end, y_end);
  EPD_SetMemoryPointer(epd, x, y);
  EPD_SendCommand(epd, WRITE_RAM);
  /* send the image data */
  for (int j = 0; j < y_end - y + 1; j++) {
    for (int i = 0; i < (x_end - x + 1) / 8; i++) {
      EPD_SendData(epd, image_buffer[i + j * (image_width / 8)]);
    }
  }
}

/**
*  @brief: clear the screen for init
*/

void EPD_Clear_Full(EPD* epd){

	// Reset
	EPD_Reset(epd);

	// On met les luts
	EPD_SetLut(epd,epd->lut);

	//
	EPD_SendCommand(epd, OTP_SELECTION);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x40);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);
	EPD_SendData(epd,0x00);

	// Border waveform
	EPD_SendCommand(epd, BORDER_WAVEFORM_CONTROL);
	EPD_SendData(epd,0x80);

	EPD_SendCommand(epd, DISPLAY_UPDATE_CONTROL_2);
	EPD_SendData(epd,0xC0);
	EPD_SendCommand(epd, MASTER_ACTIVATION);

	// Mémoire
	EPD_SetMemoryArea(epd, 0 , 0, EPD_WIDTH-1, EPD_HEIGHT-1);
	EPD_SetMemoryPointer(epd,0,0);

	EPD_2IN9_V2_SendCommand(WRITE_RAM);   //Write Black and White image to RAM
	for(int i=0;i<4736;++i)
	{
		EPD_SendData(epd,0xFF);
	}

	EPD_SendCommand(epd, DISPLAY_UPDATE_CONTROL_2);
	EPD_SendData(epd,0xF7);
	EPD_SendCommand(epd, MASTER_ACTIVATION);

	EPD_WaitUntilIdle(epd);

}



/**
*  @brief: clear the frame memory with the specified color.
*          this won't update the display.
*/
void EPD_ClearFrameMemory(EPD* epd, unsigned char color) {
  EPD_SetMemoryArea(epd, 0, 0, epd->width - 1, epd->height - 1);
  EPD_SetMemoryPointer(epd, 0, 0);
  EPD_SendCommand(epd, WRITE_RAM);
  /* send the color data */
  for (int i = 0; i < epd->width / 8 * epd->height; i++) {
    EPD_SendData(epd, color);
  }
}

/**
*  @brief: update the display
*          there are 2 memory areas embedded in the e-paper display
*          but once this function is called,
*          the the next action of SetFrameMemory or ClearFrame will 
*          set the other memory area.
*/
void EPD_DisplayFrame(EPD* epd) {
  EPD_SendCommand(epd, DISPLAY_UPDATE_CONTROL_2);
  EPD_SendData(epd, 0xC4);
  EPD_SendCommand(epd, MASTER_ACTIVATION);
  EPD_SendCommand(epd, TERMINATE_FRAME_READ_WRITE);
  EPD_WaitUntilIdle(epd);
}

void EPD_Display_full_refresh(EPD* epd) {
  EPD_SendCommand(epd, DISPLAY_UPDATE_CONTROL_2);
  EPD_SendData(epd, 0xF7);
  EPD_SendCommand(epd, MASTER_ACTIVATION);
  EPD_SendCommand(epd, TERMINATE_FRAME_READ_WRITE);
  EPD_WaitUntilIdle(epd);
}

/**
 *  @brief: After this command is transmitted, the chip would enter the 
 *          deep-sleep mode to save power. 
 *          The deep sleep mode would return to standby by hardware reset. 
 *          You can use EPD_Init() to awaken
 */
void EPD_Sleep(EPD* epd) {
  EPD_SendCommand(epd, DEEP_SLEEP_MODE);
  EPD_WaitUntilIdle(epd);
}

/**
 *  @brief: set the look-up tables
 */
static void EPD_SetLut(EPD* epd, const unsigned char* lut) {
  epd->lut = lut;
  EPD_SendCommand(epd, WRITE_LUT_REGISTER);
  /* the length of look-up table is 30 bytes */
  for (int i = 0; i < 30; i++) {
    EPD_SendData(epd, epd->lut[i]);
  } 
}

/**
 *  @brief: private function to specify the memory area for data R/W
 */
static void EPD_SetMemoryArea(EPD* epd, int x_start, int y_start, int x_end, int y_end) {
  EPD_SendCommand(epd, SET_RAM_X_ADDRESS_START_END_POSITION);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  EPD_SendData(epd, (x_start >> 3) & 0xFF);
  EPD_SendData(epd, (x_end >> 3) & 0xFF);
  EPD_SendCommand(epd, SET_RAM_Y_ADDRESS_START_END_POSITION);
  EPD_SendData(epd, y_start & 0xFF);
  EPD_SendData(epd, (y_start >> 8) & 0xFF);
  EPD_SendData(epd, y_end & 0xFF);
  EPD_SendData(epd, (y_end >> 8) & 0xFF);
}

/**
 *  @brief: private function to specify the start point for data R/W
 */
static void EPD_SetMemoryPointer(EPD* epd, int x, int y) {
  EPD_SendCommand(epd, SET_RAM_X_ADDRESS_COUNTER);
  /* x point must be the multiple of 8 or the last 3 bits will be ignored */
  EPD_SendData(epd, (x >> 3) & 0xFF);
  EPD_SendCommand(epd, SET_RAM_Y_ADDRESS_COUNTER);
  EPD_SendData(epd, y & 0xFF);
  EPD_SendData(epd, (y >> 8) & 0xFF);
  EPD_WaitUntilIdle(epd);
}

const unsigned char lut_full_update[] =
{
    0x02, 0x02, 0x01, 0x11, 0x12, 0x12, 0x22, 0x22, 
    0x66, 0x69, 0x69, 0x59, 0x58, 0x99, 0x99, 0x88, 
    0x00, 0x00, 0x00, 0x00, 0xF8, 0xB4, 0x13, 0x51, 
    0x35, 0x51, 0x51, 0x19, 0x01, 0x00
};

const unsigned char lut_partial_update[] =
{
    0x10, 0x18, 0x18, 0x08, 0x18, 0x18, 0x08, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x13, 0x14, 0x44, 0x12, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* END OF FILE */


