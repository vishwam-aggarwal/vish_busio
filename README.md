Serial Protocol Bus implementations (I2c, SPI) for Raspberry Pico

Loosely based on the the adafruit busio library for Arduino.

Only I2C implemeneted, plan to add SPI when I get using an SPI device.

This uses a lower level repo, one must run:

  git submodule update --recursive

to load the nested repo
