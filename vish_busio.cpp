#include "vish_busio.h"

vish_BusIO_Register::vish_BusIO_Register(vish_i2cdev* INA260_I2C, uint32_t reg, uint8_t width,
                                        bool byteorder, uint8_t reg_len, bool reg_byteorder) {
    _INA260_I2C = INA260_I2C;
    _reg_len = reg_len;
    _reg_byteorder = reg_byteorder;
    _byteorder = byteorder;
    _width = width; // BUG! BUG! BUG! BUG! BUG! BUG! BUG!

    if (_reg_byteorder) {
        _reg[0] = reg >> 24;
        _reg[1] = (reg >> 16) & 0xFF;
        _reg[2] = (reg >> 8) & 0xFF;
        _reg[3] = reg & 0xFF;
    }
    else
    {
        _reg[4] = reg >> 24;
        _reg[3] = (reg >> 16) & 0xFF;
        _reg[2] = (reg >> 8) & 0xFF;
        _reg[1] = reg & 0xFF;
    }

}

uint32_t vish_BusIO_Register::read(void)
{
    uint8_t dbg = 0x00;
    uint8_t dbg1[2];
    uint8_t _dat[_width];
    uint32_t readData;
    //_INA260_I2C->read(&_reg[0], &_dat[0], _width, _reg_len);
    if(_byteorder)
        readData = (int32_t) ((_dat[0]<<24) |   (_dat[1]<<16)   |   (_dat[2] << 8)  |   _dat[3]);
    else
        readData = (int32_t) ((_dat[3]<<24) |   (_dat[2]<<16)   |   (_dat[1] << 8)  |   _dat[0]);

    _INA260_I2C->read(&dbg, &dbg1[0], _width, _reg_len);
    readData = int16_t((dbg1[0]<<8) | (dbg1[1]));

    return readData;

}