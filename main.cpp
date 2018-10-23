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
#include "MAX32620SDT.h"

/* Serial */
#define BAUDRATE        9600
Serial g_Serial_Pc(USBTX, USBRX, BAUDRATE);

/* PMIC */
#define I2C_ADDR_PMIC   0x90
I2C PMIC(I2C2_SDA, I2C2_SCL);
MAX77650 max77650(&PMIC, I2C_ADDR_PMIC);

/* VDDIOH */
#define VDDIOH_1P8      0
#define VDDIOH_3P3      1
MAX32620SDT max32620sdt;

/* DigitalOut */
DigitalOut g_DO_LedRed(LED_RED, 1);



void pmic_test(void) {
    g_Serial_Pc.printf("[%s] Start\n", __FUNCTION__);

    /* Init register */
    if(max77650.init() == MAX77650_ERROR) {
        g_Serial_Pc.printf("[%s] Error initializing MAX77650\n", __FUNCTION__);
    }

    /* Read initial value of register */
    char data_init = 0x00;
    max77650.readReg(MAX77650::REG_CNFG_CHG_A, &data_init);              
    g_Serial_Pc.printf("[%s] REG_CNFG_CHG_A (Current value) = 0x%X\n", __FUNCTION__, data_init);
    wait(1);

    /* Write a value to register */
    char data = 0x0A;        // Set value you want
    max77650.writeReg(MAX77650::REG_CNFG_CHG_A, data);
    max77650.readReg(MAX77650::REG_CNFG_CHG_A, &data);
    g_Serial_Pc.printf("[%s] REG_CNFG_CHG_A (After changing value you want) = 0x%X\n", __FUNCTION__, data);
    wait(1);

    /* Reset */
    max77650.writeReg(MAX77650::REG_CNFG_CHG_A, data_init);
    max77650.readReg(MAX77650::REG_CNFG_CHG_A, &data_init);
    g_Serial_Pc.printf("[%s] REG_CNFG_CHG_A (Reset register to initial value) = 0x%X\n", __FUNCTION__, data_init);
    wait(1);
}

void vddioh_test(bool vddioh_level) {
    g_Serial_Pc.printf("[%s] Start\n", __FUNCTION__);

    /* Init port */
    if(max32620sdt.init() == MAX32620SDT_ERROR) {
        g_Serial_Pc.printf("[%s] Error initializing MAX32620SDT\n", __FUNCTION__);
    }

    /* Set VDDIOH of this port */
    if(vddioh_level) {
        max32620sdt.set_vddioh(LED_RED, MAX32620SDT::VIO_3V3);
    }
    else {
        max32620sdt.set_vddioh(LED_RED, MAX32620SDT::VIO_1V8);
    }
    wait(1);
    g_Serial_Pc.printf("[%s] Check LED_RED(= GPIO0) whether high level is 1.8V or 3.3V\n", __FUNCTION__);
}

int main(void) {
    g_Serial_Pc.printf("< Sigma Delta Technologies Inc. >\n\r");

    pmic_test();
    vddioh_test(VDDIOH_3P3);    // You can set a parameter of this function to VDDIOH_1P8 or VDDIOH_3P3.
    
    while (true) {
        g_Serial_Pc.printf("Led Toggle\n");
        g_DO_LedRed = !g_DO_LedRed;
        wait(1);
    }
}
