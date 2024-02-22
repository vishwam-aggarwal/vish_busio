#include "vish_busio.h"

#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9

vish_busio::vish_busio()
{
    stdio_init_all();
    vish_i2cdev myI2C;

    myI2C.begin(0x40, I2C_PORT, 400*1000, I2C_SDA, I2C_SCL, false);

    uint8_t Data[2];
    uint8_t reg = 0x00;    

    // Read Config register
    myI2C.read(&reg, &Data[0], 2);
    uint16_t configReg = (int16_t)((Data[0] << 8) | Data[1]);

}