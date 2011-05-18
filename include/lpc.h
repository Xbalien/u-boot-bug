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

static inline void set_clk(int is_on);
static inline void set_lframe(int is_on);
static inline void set_reset(int is_on);
static inline void set_lad(unsigned char data);
static inline unsigned char get_lad(void);

static unsigned char mem_read(unsigned char addr);
static int mem_write(unsigned char addr, unsigned char data);


