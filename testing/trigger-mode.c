/* SPDX-License-Identifier: GPL-2.0-or-later */
#include <assert.h>
#include "trigger_mode.h"

static bool accepted(uint64_t wanted, uint64_t actual, unsigned int privilege, bool virtualized)
{
	uint64_t mask = riscv_trigger_mode_ro0(privilege, virtualized);
	return (wanted & ~mask) == (actual & ~mask);
}

int main(void)
{
	const uint64_t modes = CSR_MCONTROL6_M | CSR_MCONTROL6_S | CSR_MCONTROL6_U |
		CSR_MCONTROL6_VS | CSR_MCONTROL6_VU;
	assert(accepted(modes, modes, PRV_M, false));
	assert(!accepted(modes, CSR_MCONTROL6_M, PRV_M, false));
	assert(accepted(modes, modes & ~CSR_MCONTROL6_M, PRV_S, false));
	assert(!accepted(modes, CSR_MCONTROL6_S, PRV_S, false));
	assert(!accepted(modes, CSR_MCONTROL6_S | CSR_MCONTROL6_U, PRV_S, false));
	assert(accepted(modes, CSR_MCONTROL6_S | CSR_MCONTROL6_U, PRV_S, true));
	assert(!accepted(modes, CSR_MCONTROL6_S, PRV_S, true));
	assert(accepted(modes, CSR_MCONTROL6_U, PRV_U, false));
	assert(accepted(modes, CSR_MCONTROL6_U, PRV_U, true));
	assert(!accepted(modes, 0, PRV_U, false));
	assert(!accepted(modes | CSR_MCONTROL6_EXECUTE, CSR_MCONTROL6_U, PRV_U, true));
	return 0;
}
