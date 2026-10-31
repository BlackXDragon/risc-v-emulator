#pragma once

#include <cassert>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdio>

namespace riscv_emulator {

class Registers {
public:
	Registers() {}

	void set(uint32_t index, uint32_t value) {
		assert(index < 32);
		if (index == 0) {
			return; // x0 is always zero in RISC-V
		}
		registers[index] = value;
	}

	uint32_t get(uint32_t index) const {
		assert(index < 32);
		return registers[index];
	}

	uint32_t get_pc() const {
		return pc;
	}

	void set_pc(uint32_t value) {
		pc = value;
	}

	void reset(uint32_t entry_point = 0) {
		registers.fill(0);
		pc = entry_point;
	}

	void dump() const {
		for (int i = 0; i < registers.size(); ++i) {
			printf("x%02d: 0x%08X\n", i, registers[i]);
		}
		printf("PC: 0x%08X\n", pc);
	}
private:
	std::array<uint32_t, 32> registers = {0};
	uint32_t pc = 0;
};

} // namespace riscv_emulator