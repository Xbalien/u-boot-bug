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

#define LPC_START		0x0
#define LPC_CYC_MEMREAD		0x4
#define LPC_CYC_MEMWRITE	0x6
#define LPC_CYC_IOREAD		0x0
#define LPC_CYC_IOWRITE		0x2

#define LPC_SYNC_READY		0x0
#define LPC_SYNC_SWAIT		0x5
#define LPC_SYNC_LWAIT		0x6
#define LPC_SYNC_ERROR		0xA

void lpc_init(void);
inline void lpc_set_clk(int is_on);
inline void lpc_set_lframe(int is_on);
inline void lpc_set_reset(int is_on);
inline void lpc_set_lad(unsigned char data);
inline unsigned char lpc_get_lad(void);

unsigned char lpc_mem_read(unsigned int addr);
int lpc_mem_write(unsigned int addr, unsigned char data);
unsigned char lpc_io_read(unsigned short addr);
int lpc_io_write(unsigned short addr, unsigned char data);

