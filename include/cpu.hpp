#pragma once

#include "registers.hpp"
#include "memory.hpp"
#include <cstdint>

namespace riscv_emulator {

class CPU {
public:
	CPU(Memory* memory);
	~CPU();
	
	void reset();
	
	void step();

	void run(uint32_t max_steps = 1);
	Registers registers; // TODO: Make this private after testing
private:
	Memory* memory;
	Memory* working_memory;
};

} // namespace riscv_emulator