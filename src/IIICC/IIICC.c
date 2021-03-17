/* Copyright 2020 kbjunky
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "IIICC.h"

#define HIGH 0b11111111
#define LOW 0

static i2c_status_t last_err = 0;
bool i2c_initialized = false;

void i2c_initialize(void){
    dprint("I2C init start\n");
     
    if(!i2c_initialized) {
        i2c_init();
        i2c_initialized = true;
        
    }

    //1st device
    //set A as outputs
    i2c_write8(I2CA_ADDRESS, IODIRA, LOW);
    //seems like A pull ups also needed
    i2c_write8(I2CA_ADDRESS, GPPUA, HIGH);
    //set B pull ups ON
    i2c_write8(I2CA_ADDRESS, GPPUB, HIGH);

    if(i2c_last_error()) {
        dprint("Unable to setup right side!\n");
    }else {
        dprint("Right side OK!\n");
    } 
    
    //2nd device
    i2c_write8(I2CB_ADDRESS, IODIRA, LOW);
    //seems like A pull ups also needed
    i2c_write8(I2CB_ADDRESS, GPPUA, HIGH);
    //set B pull ups ON
    i2c_write8(I2CB_ADDRESS, GPPUB, HIGH);
    if(i2c_last_error()) {
        dprint("Unable to setup left side!\n");
    }else {
        dprint("Left side OK!\n");
    }  

#ifdef MACROPAD_ENABLE
    //3rd device - macropad
    i2c_write8(I2CM_ADDRESS, IODIRA, LOW);
    //seems like A pull ups also needed
    i2c_write8(I2CM_ADDRESS, GPPUA, HIGH);
    //set B pull ups ON
    i2c_write8(I2CM_ADDRESS, GPPUB, HIGH);
    if(i2c_last_error()) {
        dprint("Unable to setup macropad!\n");
    }else {
        dprint("Macropad OK!\n");
    }  
#endif
    
}

bool isI2C_initialized() {
    return i2c_initialized;
}

uint8_t i2c_read8(uint8_t addr, uint8_t reg) {
    uint8_t data = 0;
    last_err = i2c_start(addr, I2C_TIMEOUT); if(last_err) goto end;
    last_err = i2c_readReg(addr, reg, &data, sizeof(data), I2C_TIMEOUT); if(last_err) goto end;    
    end:
        i2c_stop();
    return ~data;

}

void i2c_write8(uint8_t addr, uint8_t reg, uint8_t data) {
    last_err = i2c_start(addr, I2C_TIMEOUT); if(last_err) goto end;
    last_err = i2c_writeReg(addr, reg, &data, sizeof(data), I2C_TIMEOUT); if(last_err) goto end;
    end:
        i2c_stop();
}

void i2c_select_row(uint8_t row_index) {
    uint8_t row_mask = ~(1 << row_index);
    i2c_write8(I2CA_ADDRESS, GPIOA, row_mask);
}

void i2c_select_row_on(uint8_t addr, uint8_t row_index) {
    uint8_t row_mask = ~(1 << row_index);
    i2c_write8(addr, GPIOA, row_mask);
} 

i2c_status_t i2c_last_error(void) {
    return last_err;
}
