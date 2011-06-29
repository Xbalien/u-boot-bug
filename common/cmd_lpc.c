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

#define mdelay(n)	udelay((n)*100000)

void pulse_clk_out(int delay)
{
	/* delay = delay * 100000; */
	udelay(delay);
	lpc_set_clk(0);
	udelay(delay);
	lpc_set_clk(1);
}

void pulse_clk_in(int delay)
{
	/* delay = delay * 100000; */
	udelay(delay);
	lpc_set_clk(1);
	udelay(delay);
	lpc_set_clk(0);
}

unsigned char lpc_mem_read(unsigned int addr)
{
	unsigned char data;
	int count = 0;

	lpc_init();
	/* START */
	lpc_set_clk(1);
	lpc_set_lframe(0);
	lpc_set_lad(LPC_START);
	pulse_clk_out(2);


	/* Cycle Type */
	lpc_set_clk(1);
	lpc_set_lframe(1);
	lpc_set_lad(LPC_CYC_MEMREAD);
	pulse_clk_out(2);

	/* Address */

	lpc_set_lad(0xf & (addr >> 28));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 24));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 20));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 16));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* TAR */

	lpc_set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	lpc_set_clk(0);
	while (lpc_get_lad() != LPC_SYNC_READY || (count < 20)) {
		pulse_clk_in(2);
		count++;
	}

	if (count >= 20)
		printf("%s: No Sync detected.\n", __FUNCTION__);
	/* Data */
	pulse_clk_in(2);
	data = lpc_get_lad();
	pulse_clk_in(2);
	data |= lpc_get_lad() << 4;

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

int lpc_mem_write(unsigned int addr, unsigned char data)
{
	int count = 0;

	lpc_init();
	/* START */
	lpc_set_clk(1);
	lpc_set_lframe(0);
	lpc_set_lad(LPC_START);
	pulse_clk_out(2);

	/* Cycle Type */
	lpc_set_lframe(1);
	lpc_set_lad(LPC_CYC_MEMREAD);
	pulse_clk_out(2);

	/* Address */

	lpc_set_lad(0xf & (addr >> 28));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 24));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 20));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 16));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* Data */

	lpc_set_lad(0xf & (data >> 0));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (data >> 4));
	pulse_clk_out(2);
	/* TAR */

	lpc_set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	lpc_set_clk(0);
	while ((lpc_get_lad() != LPC_SYNC_READY) || (count < 20)) {
		pulse_clk_in(2);
		count++;
	}

	if (count >= 20)
		printf("%s: No Sync detected.\n", __FUNCTION__);

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

unsigned char lpc_io_read(unsigned short addr)
{
	unsigned char data;
	int count = 0;

	lpc_init();
	/* START */
	lpc_set_clk(1);
	lpc_set_lframe(0);
	lpc_set_lad(LPC_START);
	pulse_clk_out(2);


	/* Cycle Type */
	lpc_set_clk(1);
	lpc_set_lframe(1);
	lpc_set_lad(LPC_CYC_IOREAD);
	pulse_clk_out(2);

	/* Address */

	lpc_set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* TAR */

	lpc_set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	lpc_set_clk(0);
	while (lpc_get_lad() != LPC_SYNC_READY || (count < 20)) {
		pulse_clk_in(2);
		count++;
	}

	if (count >= 20)
		printf("%s: No Sync detected.\n", __FUNCTION__);

	/* Data */
	pulse_clk_in(2);
	data = lpc_get_lad();
	pulse_clk_in(2);
	data |= lpc_get_lad() << 4;

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

int lpc_io_write(unsigned short addr, unsigned char data)
{
	int count = 0;

	lpc_init();
	/* START */
	lpc_set_clk(1);
	lpc_set_lframe(0);
	lpc_set_lad(LPC_START);
	pulse_clk_out(2);

	/* Cycle Type */
	lpc_set_lframe(1);
	lpc_set_lad(LPC_CYC_IOREAD);
	pulse_clk_out(2);

	/* Address */

	lpc_set_lad(0xf & (addr >> 12));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 8));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 4));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (addr >> 0));
	pulse_clk_out(2);

	/* Data */

	lpc_set_lad(0xf & (data >> 0));
	pulse_clk_out(2);
	lpc_set_lad(0xf & (data >> 4));
	pulse_clk_out(2);
	/* TAR */

	lpc_set_lad(0xf);
	pulse_clk_out(2);
	pulse_clk_out(2);

	/* Sync */

	udelay(2);
	lpc_set_clk(0);
	while ((lpc_get_lad() != LPC_SYNC_READY) || (count < 20)) {
		pulse_clk_in(2);
		count++;
	}

	if (count >= 20)
		printf("%s: No Sync detected.\n", __FUNCTION__);

	/* TAR */
	pulse_clk_in(2);
	pulse_clk_in(2);

	return data;
}

int do_lpc (cmd_tbl_t *cmdtp, int flag, int argc, char* const argv[])
{
	unsigned int mem_addr;
	unsigned short io_addr;
	unsigned char data;

	/* printf("argc: %d\n", argc); */

	if (argc < 2)
		return cmd_usage(cmdtp);
	if (argc == 3) {
		if (strcmp(argv[1], "mem_read") == 0) {
			printf("mem_read\n");
			mem_addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			data = lpc_mem_read(mem_addr);
			printf("LPC mem_read: 0x%x\n",data);
			return 0;
		}
		else if (strcmp(argv[1], "io_read") == 0) {
			printf("io_read\n");
			io_addr = (unsigned short)simple_strtoul(argv[2], NULL, 16);
			data = lpc_io_read(io_addr);
			printf("LPC io_read: 0x%x\n",data);
			return 0;
		}
		else
			return cmd_usage(cmdtp);
	}
	if (argc == 4) {
		if (strcmp(argv[1], "mem_write") == 0) {
			printf("mem_write\n");
			mem_addr = (unsigned int)simple_strtoul(argv[2], NULL, 16);
			data = (unsigned char)(0xf & simple_strtoul(argv[3], NULL, 16));
			data = lpc_mem_write(mem_addr, data);
			printf("LPC mem_write: 0x%x\n",data);
			return 0;
		}
		else if (strcmp(argv[1], "io_write") == 0) {
			printf("io_write\n");
			io_addr = (unsigned short)simple_strtoul(argv[2], NULL, 16);
			data = (unsigned char)(0xf & simple_strtoul(argv[3], NULL, 16));
			data = lpc_io_write(io_addr, data);
			printf("LPC io_write: 0x%x\n",data);
			return 0;
		}
		else
			return cmd_usage(cmdtp);
	}
}

U_BOOT_CMD(
	lpc, 4, 0, do_lpc,
	"LPC Subsystem",
	"mem_read addr\n"
	"lpc mem_write addr data\n"
	"lpc io_read addr\n"
	"lpc io_write addr data\n");
