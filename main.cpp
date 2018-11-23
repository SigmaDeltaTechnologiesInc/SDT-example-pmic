/* SDT-example-pmic
 * 
 * Copyright (c) 2018 Sigma Delta Technologies Inc.
 * 
 * MIT License
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "mbed.h"
#include "MAX77650.h"

/* Serial */
#define BAUDRATE        9600
Serial serial_pc(USBTX, USBRX, BAUDRATE);

/* DigitalOut */
#define LED_ON          0
#define LED_OFF         1
DigitalOut do_ledBlue(LED_BLUE, LED_OFF);

/* PMIC(MAX77650) */
I2C i2c_pmic(I2C2_SDA, I2C2_SCL);
MAX77650 max77650(i2c_pmic);



int main(void) {
    serial_pc.printf("< Sigma Delta Technologies Inc. >\n\r");

    // Turn off Low-Dropout Linear Regulator (LDO); unused on MAX32620FTHR platform
    max77650.disableLDO();
    max77650.setEN_LDO(0x04);   // Disable
    // max77650.setEN_LDO(0x06);   // Enable
    int enLDO = max77650.getEN_LDO();
    serial_pc.printf("EN_LDO = 0x%x\n", enLDO);
    
    // Configure PMIC LED's to cycle between colors
    int chipID = max77650.getChipID();
    serial_pc.printf("CID = 0x%x\n", chipID);

    while(true) {
        serial_pc.printf("LED Toggle\n");
        do_ledBlue = !do_ledBlue;
        wait(1);                // 1sec
    }
}
