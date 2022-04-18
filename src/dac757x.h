/*! @file dac757x.h
 * @brief Driver source for the DAC757x 12-Bit, DAC C driver.
 */

#ifndef _DAC757x_H_
#define _DAC757x_H_

#include <stdint.h>
#include <stdbool.h>

#define dac757x_VERSION_MAJOR   0 /*! @brief VERSION MAJOR */
#define dac757x_VERSION_MINOR   1 /*! @brief VERSION MINOR */
#define dac757x_VERSION_PATCH   0 /*! @brief VERSION PATH */
#define DAC757x_MAX_COUNTS      4095 /*! @brief DAC MAX counts */

/*!
 * @brief This function pointer API reads I2C data from the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be read from
 * @param[out] *data: Pointer to the where we should store the read data
 * @param[in] len: Length of data to be read
 *
 * @return The result of reading I2C data
 */
typedef int8_t(*dac757x_read_fptr_t)(const uint8_t busAddr, uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API writes I2C data to the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be written to
 * @param[in] *data: Pointer to the data to be written
 * @param[in] len: Length of data to be written
 *
 * @return The result of writing I2C data
 */
typedef int8_t(*dac757x_write_fptr_t)(const uint8_t busAddr, const uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API delays for the specified time in microseconds.
 *
 * @param[in] period: Duration to be delayed in micro-seconds
 */
typedef void(*dac757x_delay_us_fptr_t)(uint32_t period);

/*!
 * @brief dac757x Return codes for the driver API
 */
typedef enum {
    DAC757x_RET_OK            = 0,          /* OK */
    DAC757x_RET_ERROR         = -1,         /* Error */
    DAC757x_RET_BUSY          = -2,         /* Interface Busy */
    DAC757x_RET_TIMEOUT       = -3,         /* Timeout */
    DAC757x_RET_INV_PARAM     = -4,         /* Invalid Parameter */
    DAC757x_RET_NULL_PTR      = -5,         /* NULL Pointer */
} dac757x_return_code_t;

/*!
 * @brief dac757x Output Channels
 */
typedef enum {
    DAC757x_OUTPUT_CH_1      = 0x01,        /* DAC Output CH 1 */
    DAC757x_OUTPUT_CH_2      = 0x02,        /* DAC Output CH 2 */
    DAC757x_OUTPUT_CH_3      = 0x03,        /* DAC Output CH 3 */
    DAC757x_OUTPUT_CH_4      = 0x04,        /* DAC Output CH 4 */
    DAC757x_OUTPUT_CH__MAX__
} dac757x_output_channel_t;

/*!
 * @brief dac757x HW Interface
 */
typedef struct {
    uint8_t i2c_addr;                       /* Device I2C Address */
    dac757x_read_fptr_t read;               /* User I2C Read Function Pointer */
    dac757x_write_fptr_t write;             /* User I2C Write Function Pointer */
    dac757x_delay_us_fptr_t delay_us;       /* User Micro-Second Delay Function Pointer */
} dac757x_dev_intf_t;

/*!
 * @brief ad5697r Device Instance
 */
typedef struct
{
    dac757x_dev_intf_t intf;            /* Device Hardware Interface */
} dac757x_dev_t;

/*!
 * @brief This function pointer API writes the desired DAC channel with the provided
 * value.
 *
 * @param[in] *dev: Pointer to your dac757x device
 * @param[in] ch: DAC output channel to be written to
 * @param[in] outputVal: 16bit value to write the DAC channel
 *
 * @return The result of writing the DAC channel
 */
dac757x_return_code_t dac757x_writeChannel(dac757x_dev_t *dev, dac757x_output_channel_t ch, uint16_t val);

#endif // _DAC757x_H_