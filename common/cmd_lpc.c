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
#include <command.h>
#include <lpc.h>

static void pulse_clk_out(int delay)
{
	udelay(delay);
	set_clk(0);
	udelay(delay);
	set_clk(1);
}

static void pulse_clk_in(int delay)
{
	udelay(delay);
	set_clk(1);
	udelay(delay);
	set_clk(0);
}

static unsigned char lpc_mem_read(unsigned int addr)
{
	unsigned char data;
	/* START */
	set_clk(1);
	set_lframe(0);
	set_lad(LPC_START);
	pulse_clk_out(2);


	/* Cycle Type */
	set_clk(1);
	set_lframe(1);
	set_lad(LPC_CYC_MEMREAD);
	pulse_clk_out(2);

	/* Address */

	set_lad(0xf & (addr >> 28));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 24));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 20));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 16));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* TAR */

	set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	set_clk(0);
	while (get_lad() != LPC_SYNC_READY)
		pulse_clk_in(2);
	return 0;

	/* Data */
	pulse_clk_in(2);
	data = get_lad();
	pulse_clk_in(2);
	data |= get_lad() << 4;

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

static int lpc_mem_write(unsigned char addr, unsigned char data)
{
	/* START */
	set_clk(1);
	set_lframe(0);
	set_lad(LPC_START);
	pulse_clk_out(2);

	/* Cycle Type */
	set_lframe(1);
	set_lad(LPC_CYC_MEMREAD);
	pulse_clk_out(2);

	/* Address */

	set_lad(0xf & (addr >> 28));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 24));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 20));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 16));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* Data */

	set_lad(0xf & (data >> 0));
	pulse_clk_out(2);
	set_lad(0xf & (data >> 4));
	pulse_clk_out(2);
	/* TAR */

	set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	set_clk(0);
	while (get_lad() != LPC_SYNC_READY)
		pulse_clk_in(2);
	return 0;

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

int do_lpc (cmd_tbl_t *cmdtp, int flag, int argc, char* const argv[])
{
	switch (argc) {
	case 2:
		if (strcmp(argv[1], "mem_read") == 0) {
			return 0;
		}
	case 3:
		if (strcmp(argv[1], "mem_write") == 0) {
			return 0;
		}

	default:
		return cmd_usage(cmdtp);
	}
}

U_BOOT_CMD(
	lpc, 3, 0, do_lpc,
	"LPC Subsystem",
	"mem_read addr\n"
	"mem_write addr data\n");
