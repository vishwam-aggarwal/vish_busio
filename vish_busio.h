#ifndef _VISH_BUSIO_H
#define _VISH_BUSIO_H

#include "vish_i2cdev.h"

typedef enum ByteOrder:bool {
  LSBFIRST = false, /// (Default)
  MSBFIRST = true, ///
}ByteOrder;

/*!
 * @brief The class which defines a device register (a location to read/write
 * data from)
 */
class vish_BusIO_Register {
public:
  vish_BusIO_Register();

  void begin(vish_i2cdev* INA260_I2C, uint32_t reg, uint8_t width = 1, ByteOrder byteorder = LSBFIRST,
              uint8_t reg_len = 1, ByteOrder reg_byteorder = LSBFIRST);
  uint32_t read(void);
  bool write(uint32_t value, uint8_t numbytes = 1);

  //uint8_t width(void);

  void setWidth(uint8_t width);
  void setAddress(uint16_t address);
  void setAddressWidth(uint16_t address_width);

private:
    vish_i2cdev* _INA260_I2C;
    uint32_t _reg;
    uint8_t _width, _reg_len;
    ByteOrder _byteorder, _reg_byteorder;
};

/*!
 * @brief The class which defines a slice of bits from within a device register
 * (a location to read/write data from)
 */
class vish_BusIO_RegisterBits {
public:
  vish_BusIO_RegisterBits(vish_BusIO_Register *reg, uint8_t bits,
                              uint8_t shift);
  bool write(uint32_t value);
  uint32_t read(void);

private:
  vish_BusIO_Register* _register;
  uint8_t _bits, _shift;
};

#endif // _VISH_BUSIO_H