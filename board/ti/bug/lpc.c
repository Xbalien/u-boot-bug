/*
 * Copyright (c) 2011 Bug Labs, Inc.
 * Matt Isaacs <izzy@buglabs.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#include <common.h>
#include <asm/arch/gpio.h>
#include <lpc.h>

#define LPC_CLK_GPIO		53
#define LPC_LFRAME_GPIO		54
#define LPC_RESET_GPIO		59
#define LPC_LAD3_GPIO		58
#define LPC_LAD2_GPIO		57
#define LPC_LAD1_GPIO		56
#define LPC_LAD0_GPIO		55

static inline void set_clk(int is_on)
{
	omap_set_gpio_dataout(LPC_CLK_GPIO, is_on);
}

static inline void set_lframe(int is_on)
{
	omap_set_gpio_dataout(LPC_LFRAME_GPIO, is_on);
}

static inline void set_reset(int is_on)
{
	omap_set_gpio_dataout(LPC_RESET_GPIO, is_on);
}

static inline void set_lad(unsigned char data)
{
	omap_set_gpio_dataout(LPC_LAD0_GPIO, (0x1 & data));
	omap_set_gpio_dataout(LPC_LAD1_GPIO, ((0x2 & data) >> 1));
	omap_set_gpio_dataout(LPC_LAD2_GPIO, ((0x4 & data) >> 2));
	omap_set_gpio_dataout(LPC_LAD3_GPIO, ((0x8 & data) >> 3));
}

static inline unsigned char get_lad(void)
{
	unsigned char data = 0;

	data = omap_get_gpio_datain(LPC_LAD0_GPIO);
	data = omap_get_gpio_datain(LPC_LAD1_GPIO) << 1;
	data = omap_get_gpio_datain(LPC_LAD2_GPIO) << 2;
	data = omap_get_gpio_datain(LPC_LAD3_GPIO) << 3;
	return 0;
}
