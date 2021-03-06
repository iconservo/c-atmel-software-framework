/**
 * \file
 *
 * \brief AT30TSE75X driver
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <at30tse75x.h>
#include <asf.h>

#ifdef __cplusplus
extern "C" {
#endif

uint8_t resolution = AT30TSE_CONFIG_RES_9_bit;

/**
 * \brief Configures the TWHIS master to be used with the AT30TSE75X device.
 */
void at30tse_init(void)
{	
	twihs_options_t opt;

	/* Enable the peripheral clock for TWIHS */
	pmc_enable_periph_clk(BOARD_AT30TSE_ID_TWIHS);

	/* Configure the options of TWI driver */
	opt.master_clk = sysclk_get_cpu_hz();
	opt.speed      = TWIHS_CLK;

	if (twihs_master_init(BOARD_AT30TSE_TWIHS, &opt) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}
}

/**
 * \brief Writes the EEPROM with data provided.
 *
 * \param[out] *data Pointer to the data buffer.
 * \param[in]  length Number of data bytes.
 * \param[in]  word_addr Word address of the EEPROM.
 * \param[in]  page Page number of the EEPROM.
 */
void at30tse_eeprom_write(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page)
{
	/* ACK polling for consecutive writing not implemented! */
	uint8_t buffer[17];
	/* Byte addr in page (0-15) */
	buffer[0] = word_addr & 0x0F;
	/* 4 lower bits of page addr in EEPROM	 */
	buffer[0] |= (0x0F & page) << 4;

	/* Copy data to be sent */
	for (uint8_t i=1; i<17; i++){
		buffer[i] = data[i-1];
	}

	twihs_packet_t packet_tx;

	/* Configure the data packet to be transmitted */
	packet_tx.chip        = AT30TSE758_EEPROM_TWI_ADDR;
	packet_tx.addr[0]     = ((0x30 & page) >> 4);
	packet_tx.addr[1]     = buffer[0];
	packet_tx.addr_length = 2;
	packet_tx.buffer      = buffer;
	packet_tx.length      = length+1;
	
	/* Send test pattern to EEPROM */
	if (twihs_master_write(BOARD_AT30TSE_TWIHS, &packet_tx) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}
}

/**
 * \brief Reads data from the EEPROM.
 *
 * \param[out] *data Pointer to the data buffer.
 * \param[in]  length Number of data bytes.
 * \param[in]  word_addr Word address of the EEPROM.
 * \param[in]  page Page number of the EEPROM.
 */
void at30tse_eeprom_read(uint8_t *data, uint8_t length, uint8_t word_addr, uint8_t page)
{
	/* ACK polling for consecutive reading not implemented! */
	uint8_t buffer[1];
	/* Byte addr in page (0-15) */
	buffer[0] = word_addr & 0x0F;
	/* 4 lower bits of page addr in EEPROM */
	buffer[0] |= (0x0F & page) << 4;
	
	twihs_packet_t packet_rx;
	
	/* Configure the data packet to be received */
	packet_rx.chip        = AT30TSE758_EEPROM_TWI_ADDR;
	packet_rx.addr[0]     = ((0x30 & page) >> 4);
	packet_rx.addr[1]     = buffer[0];
	packet_rx.addr_length = 2;
	packet_rx.buffer      = data;
	packet_rx.length      = length;
	
	/* Get memory from EEPROM*/
	if (twihs_master_read(BOARD_AT30TSE_TWIHS, &packet_rx) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}
}

/**
 * \brief Sets the register pointer with specified reg value.
 *
 * \param[in] reg Register value of the pointer register.
 * \param[in] reg_type Register type being pointed by pointer register.
 */
void at30tse_set_register_pointer(uint8_t reg, uint8_t reg_type)
{
	uint8_t reg_addr = {reg | reg_type};
	twihs_packet_t packet_tx;

	/* Configure the data packet to be transmitted */
	packet_tx.chip        = AT30TSE_TEMPERATURE_TWI_ADDR;
	packet_tx.addr[0]     = reg_addr;
	packet_tx.addr_length = 1;
	packet_tx.buffer      = &reg_addr;
	packet_tx.length      = 1;
	
	/* Send test pattern to EEPROM */
	if (twihs_master_write(BOARD_AT30TSE_TWIHS, &packet_tx) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}
}

/**
 * \brief Reads the value from the register reg.
 *
 * \param[in] reg Register to read.
 * \param[in] reg_type Type of the register (Volatile or Non-volatile).
 * \param[in] reg_size Register size.
 *
 * \return Register value.
 */
uint16_t at30tse_read_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size)
{
	uint8_t buffer[2];
	uint8_t reg_addr = reg | reg_type;

	twihs_packet_t packet_rx;
	
	/* Configure the data packet to be received */
	packet_rx.chip        = AT30TSE_TEMPERATURE_TWI_ADDR;
	packet_rx.addr[0]     = reg_addr;
	packet_rx.addr_length = 1;
	packet_rx.buffer      = buffer;
	packet_rx.length      = reg_size;

	/* Get memory from EEPROM*/
	if (twihs_master_read(BOARD_AT30TSE_TWIHS, &packet_rx) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}

	return (buffer[0] << 8) | buffer[1];
}

/**
 * \brief Writes the specified register reg with the reg_value passed
 *
 * \param[in] reg Register to write.
 * \param[in] reg_type Type of the register (Volatile or Non-volatile).
 * \param[in] reg_size Register size.
 * \param[in] reg_value Value to be written to reg.
 */
void at30tse_write_register(uint8_t reg, uint8_t reg_type, uint8_t reg_size, uint16_t reg_value)
{
	uint8_t data[2];
	uint8_t reg_addr = reg | reg_type;
	data[0] = 0x00FF & (reg_value >> 8);
	data[1] = 0x00FF & reg_value;

	twihs_packet_t packet_tx;

	/* Configure the data packet to be transmitted */
	packet_tx.chip        = AT30TSE_TEMPERATURE_TWI_ADDR;
	packet_tx.addr[0]     = reg_addr;
	packet_tx.addr_length = 1;
	packet_tx.buffer      = data;
	packet_tx.length      = reg_size;

	/* Send test pattern to EEPROM */
	if (twihs_master_write(BOARD_AT30TSE_TWIHS, &packet_tx) != TWIHS_SUCCESS) {
		while (1) {
			/* Capture error */
		}
	}
}

/**
 * \brief Writes the configuration register reg with the value passed
 *
 * \param[in] value Register value to be written.
 */
void at30tse_write_config_register(uint16_t value)
{
	uint16_t cur_reg_val = 0;
	cur_reg_val = at30tse_read_register(AT30TSE_CONFIG_REG, AT30TSE_VOLATILE_REG, 2);	
	cur_reg_val = ((cur_reg_val & (~(AT30TSE_CONFIG_R1 | AT30TSE_CONFIG_R0))) | value);
	at30tse_write_register(AT30TSE_CONFIG_REG,
							AT30TSE_VOLATILE_REG,
							AT30TSE_CONFIG_REG_SIZE,
							cur_reg_val);

	resolution = ( value >> AT30TSE_CONFIG_RES_Pos ) & ( AT30TSE_CONFIG_RES_Msk >> AT30TSE_CONFIG_RES_Pos);

}

/**
 * \brief Reads the temperature value.
 *
 * \return Temperature data.
 */
double at30tse_read_temperature()
{
	/* Read the 16-bit temperature register. */
	uint16_t data = at30tse_read_register(AT30TSE_TEMPERATURE_REG,
											AT30TSE_VOLATILE_REG,
											AT30TSE_TEMPERATURE_REG_SIZE);

	double temperature = 0;
	int8_t sign = 1;

	/*Check if negative and clear sign bit. */
	if (data & (1 << 15)){
		sign *= -1;
		data &= ~(1 << 15);
	}

	/* Convert to temperature  */
	switch (resolution){
		case AT30TSE_CONFIG_RES_9_bit:
			data = (data >> 7);
			temperature = data * sign * 0.5;
			break;
		case AT30TSE_CONFIG_RES_10_bit:
			data = (data >> 6);
			temperature = data * sign * 0.25;
			break;
		case AT30TSE_CONFIG_RES_11_bit:
			data = (data >> 5);
			temperature = data * sign * 0.125;
			break;
		case AT30TSE_CONFIG_RES_12_bit:
			data = (data >> 4);
			temperature = data * sign * 0.0625;
			break;
		default:
			break;
	}
	return temperature;
}

#ifdef __cplusplus
}
#endif
