/*! @file dac757x.c
 * @brief Driver source for the DAC757x 12-Bit, DAC C driver.
 */

#include <stdint.h>
#include <stddef.h>
#include "dac757x.h"

typedef enum {
    DAC757x_PD_NORM = 0x00,
    DAC757x_PD_OFF = 0x01,
    DAC757x_PD__MAX__
} dac757x_power_down_t;

/*!
 * @brief DAC757x Control Byte Contents
 */
typedef union {
    struct {
        uint8_t PD      : 1;
        uint8_t SEL     : 2;
        uint8_t RSVD0   : 1;
        uint8_t LOAD    : 2;
        uint8_t RSVD1   : 2;
    } bits;
    uint8_t byte;
} dac757x_control_byte_t;

/*!
 * @brief This API writes the desired DAC value to the specified channel
 */
dac757x_return_code_t dac757x_writeChannel(dac757x_dev_t *dev, dac757x_output_channel_t ch, uint16_t val) {
    dac757x_control_byte_t ctrl = {0x00};
    uint8_t msg_buff[3] = {0xFF};

    if(NULL == dev) {
        return DAC757x_RET_NULL_PTR;
    }
    else if((ch >= DAC757x_OUTPUT_CH__MAX__) || (val > DAC757x_MAX_COUNTS)) {
        return DAC757x_RET_INV_PARAM;
    }

    ctrl.bits.LOAD = 0x01;
    ctrl.bits.PD = DAC757x_PD_NORM;
    ctrl.bits.SEL = ch;

    msg_buff[0] = ctrl.byte;
    msg_buff[1] = (uint8_t)(val >> 4);
    msg_buff[2] = (uint8_t)(val << 8);

    return dev->intf.write(dev->intf.i2c_addr, msg_buff, sizeof(msg_buff));
}