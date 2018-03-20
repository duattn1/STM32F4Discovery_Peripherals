/* mbed PCF8574 Library, for driving the I2C I/O Expander
 * Copyright (c) 2008-2010, cstyles, sford
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

//#include "mbed.h"

#ifndef MBED_PCF8574_H
#define MBED_PCF8574_H

/** Interface to the popular PCF8574 I2C 8 Bit IO expander */
class PCF8574 {
public:
    /** Create an instance of the PCF8574 connected to specfied I2C pins, with the specified address.
     *
     * @param sda The I2C data pin
     * @param scl The I2C clock pin
     * @param address The I2C address for this PCF8574
     */
    PCF8574(PinName sda, PinName scl, int address);

    /** Read the IO pin level
     *
     * @return The byte read
     */
    int read();
    
    /** Write to the IO pins
     * 
     * @param data The 8 bits to write to the IO port
     */
    void write(int data);

private:
    I2C _i2c;
    int _address;
};

#endif
