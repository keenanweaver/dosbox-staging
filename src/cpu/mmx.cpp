/*
 *  Copyright (C) 2024-2024  The DOSBox Staging Team
 *  Copyright (C) 2002-2021  The DOSBox Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "dosbox.h"

#include "cpu.h"
#include "fpu.h"
#include "mem.h"
#include "mmx.h"

#if C_MMX

#ifndef C_FPU
#error "MMX emulation requires FPU!"
#endif

MMX_reg* reg_mmx[8] = {
        &fpu.p_regs[0].reg_mmx,
        &fpu.p_regs[1].reg_mmx,
        &fpu.p_regs[2].reg_mmx,
        &fpu.p_regs[3].reg_mmx,
        &fpu.p_regs[4].reg_mmx,
        &fpu.p_regs[5].reg_mmx,
        &fpu.p_regs[6].reg_mmx,
        &fpu.p_regs[7].reg_mmx,
};

MMX_reg* lookupRMregMM[256] = {
        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],

        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],

        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],

        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[0], reg_mmx[0], reg_mmx[0], reg_mmx[0],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[1], reg_mmx[1], reg_mmx[1], reg_mmx[1],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[2], reg_mmx[2], reg_mmx[2], reg_mmx[2],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[3], reg_mmx[3], reg_mmx[3], reg_mmx[3],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[4], reg_mmx[4], reg_mmx[4], reg_mmx[4],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[5], reg_mmx[5], reg_mmx[5], reg_mmx[5],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[6], reg_mmx[6], reg_mmx[6], reg_mmx[6],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],
        reg_mmx[7], reg_mmx[7], reg_mmx[7], reg_mmx[7],
};

int8_t SaturateWordSToByteS(int16_t value)
{
	if (value < -128) {
		return -128;
	}
	if (value > 127) {
		return 127;
	}
	return static_cast<int8_t>(value);
}

int16_t SaturateDwordSToWordS(int32_t value)
{
	if (value < -32768) {
		return -32768;
	}
	if (value > 32767) {
		return 32767;
	}
	return static_cast<int16_t>(value);
}

uint8_t SaturateWordSToByteU(int16_t value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 255) {
		return 255;
	}
	return static_cast<uint8_t>(value);
}

uint16_t SaturateDwordSToWordU(int32_t value)
{
	if (value < 0) {
		return 0;
	}
	if (value > 65535) {
		return 65535;
	}
	return static_cast<uint16_t>(value);
}

void setFPUTagEmpty()
{
	FPU_SetCW(0x37F);
	fpu.sw      = 0;
	TOP         = FPU_GET_TOP();
	fpu.tags[0] = TAG_Empty;
	fpu.tags[1] = TAG_Empty;
	fpu.tags[2] = TAG_Empty;
	fpu.tags[3] = TAG_Empty;
	fpu.tags[4] = TAG_Empty;
	fpu.tags[5] = TAG_Empty;
	fpu.tags[6] = TAG_Empty;
	fpu.tags[7] = TAG_Empty;
	fpu.tags[8] = TAG_Valid; // is only used by us
}

#endif