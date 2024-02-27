#include "vish_busio.h"

vish_BusIO_Register::vish_BusIO_Register(
    vish_i2cdev* INA260_I2C, uint32_t reg,
    uint8_t width,
    ByteOrder byteorder,
    uint8_t reg_len,
    ByteOrder reg_byteorder)
    {
    _INA260_I2C = INA260_I2C;
    _reg = reg;
    _width = width;
    _byteorder = byteorder;
    _reg_len = reg_len;
    _reg_byteorder = reg_byteorder;   
}

uint32_t vish_BusIO_Register::read(void)
{
    uint8_t tempReg[_reg_len];
    for(auto i=0; i<_reg_len; i++)
    {
        tempReg[i - _reg_byteorder*(2*i - _reg_len + 1)] = uint8_t(_reg >> i*8) & 0xFF;
    }
    uint8_t _dat[_width] = {0};
    uint32_t readData;
    _INA260_I2C->read(&tempReg[0], &_dat[0], _width, _reg_len);

    readData = 0;
    for(auto i=0; i<_width; i++)
    {
        readData |= _dat[i - _byteorder*(2*i - _width + 1)]<<i*8;
    }

    readData = readData;

    return readData;
}

bool vish_BusIO_Register::write(uint32_t value, uint8_t numbytes)
{
    if (numbytes > _width)
    {
        return 0;
    }
    uint8_t tempReg[_reg_len];
    for(auto i=0; i<_reg_len; i++)
    {
        tempReg[i - _reg_byteorder*(2*i - _reg_len + 1)] = uint8_t(_reg >> i*8) & 0xFF;
    }
    uint8_t _dat[numbytes];
    for(auto i=0; i<numbytes; i++)
    {
        _dat[i - _byteorder*(2*i - numbytes + 1)] = uint8_t(value >> i*8) & 0xFF;
    }    
    _INA260_I2C->write(&tempReg[0], &_dat[0], _width, _reg_len);

    return 1;
}

/*!
 *    @brief  The width of the register data, helpful for doing calculations
 *    @returns The data width used when initializing the register
 */
uint8_t vish_BusIO_Register::width(void) { return _width; }

vish_BusIO_RegisterBits::vish_BusIO_RegisterBits(vish_BusIO_Register *reg, uint8_t bits, uint8_t shift)
{
    _reg = reg;
    _bits = bits;
    _shift = shift;

}

/*!
 *    @brief  Read 4 bytes of data from the register
 *    @return  data The 4 bytes to read
 */
uint32_t vish_BusIO_RegisterBits::read()
{
    uint32_t readData = _reg->read();
    readData >>= _shift;
    return readData & ((1 << (_bits)) - 1);
}

/*!
 *    @brief  Write 4 bytes of data to the register
 *    @param  value The 4 bytes to write
 *    @return True on successful write (only really useful for I2C as SPI is
 * uncheckable)
 */
bool vish_BusIO_RegisterBits::write(uint32_t value)
{
    uint32_t readData = _reg->read();

    // mask off the data before writing
    uint32_t mask = (1 << (_bits)) - 1;
    value &= mask;

    mask <<= _shift;
    readData &= ~mask;          // remove the current data at that spot
    readData |= value << _shift; // and add in the new data

    return _reg->write(readData, _reg->width());
}