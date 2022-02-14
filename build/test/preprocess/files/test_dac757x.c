#include "src/dac757x.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


static dac757x_dev_t dac757x_device = {0};

static dac757x_return_code_t desired_read_ret = DAC757x_RET_OK;



int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len);

int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len);

void usr_delay_us(uint32_t period);



void setUp(void)

{

    dac757x_device.intf.delay_us = usr_delay_us;

    dac757x_device.intf.read = usr_i2c_read;

    dac757x_device.intf.write = usr_i2c_write;

    dac757x_device.intf.i2c_addr = 0x01;

}



void tearDown(void)

{

}



int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len) {

    dac757x_return_code_t ret = DAC757x_RET_OK;









    return ret;

}



int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len) {

    dac757x_return_code_t ret = DAC757x_RET_OK;



    switch( desired_read_ret ) {

        case DAC757x_RET_OK:

            ret = DAC757x_RET_OK;

            break;



        case DAC757x_RET_TIMEOUT:

            ret = DAC757x_RET_OK;

            break;



        case DAC757x_RET_ERROR:

            ret = DAC757x_RET_ERROR;

            break;



        default:

            break;

    }



    return ret;

}



void usr_delay_us(uint32_t period) {



}





void test_dac757x_writeChannel_AllValid(void) {



    for(uint8_t i = DAC757x_OUTPUT_CH_1; i < DAC757x_OUTPUT_CH__MAX__; i++) {

        dac757x_return_code_t ret = dac757x_writeChannel(&dac757x_device, i, 0x0000);

        UnityAssertEqualNumber((UNITY_INT)((DAC757x_RET_OK)), (UNITY_INT)((ret)), (

       ((void *)0)

       ), (UNITY_UINT)(64), UNITY_DISPLAY_STYLE_INT);

    }

}



void test_dac757x_writeChannel_NullDevice(void) {



    dac757x_return_code_t ret = dac757x_writeChannel(

                                                    ((void *)0)

                                                        , DAC757x_OUTPUT_CH_1, 0x0000);



    UnityAssertEqualNumber((UNITY_INT)((DAC757x_RET_NULL_PTR)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(72), UNITY_DISPLAY_STYLE_INT);

}



void test_dac757x_writeChannel_InvalidChannel(void) {



    dac757x_return_code_t ret = dac757x_writeChannel(&dac757x_device, DAC757x_OUTPUT_CH__MAX__, 0x0000);



    UnityAssertEqualNumber((UNITY_INT)((DAC757x_RET_INV_PARAM)), (UNITY_INT)((ret)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

}
