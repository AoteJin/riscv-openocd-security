/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef OPENOCD_TARGET_RISCV_TRIGGER_MODE_H
#define OPENOCD_TARGET_RISCV_TRIGGER_MODE_H

#include <stdbool.h>
#include <stdint.h>
#include "encoding.h"
#include "debug_defines.h"

static inline uint64_t riscv_trigger_mode_ro0(unsigned int privilege, bool virtualized)
{
	if (privilege == PRV_U)
		return CSR_MCONTROL6_M | CSR_MCONTROL6_S | CSR_MCONTROL6_VS | CSR_MCONTROL6_VU;
	if (privilege == PRV_S)
		return CSR_MCONTROL6_M | (virtualized ? CSR_MCONTROL6_VS | CSR_MCONTROL6_VU : 0);
	return 0;
}

#endif
