#include "cpu.hpp"

int main() {
	riscv_emulator::Memory memory(1024); // 1KB of memory

	// Write an ADD instruction to memory at address 0
	// ADD x3, x1, x2 (opcode: 0x33, funct3: 0x0, funct7: 0x00)
	uint32_t add_instruction = (0x00 << 25) | (2 << 20) | (1 << 15) | (0x0 << 12) | (3 << 7) | 0x33;
	memory.write32(0, add_instruction);
	
	riscv_emulator::CPU cpu(&memory);
	printf("Initial state of registers:\n");
	cpu.registers.dump();
	printf("\n");

	// Set x1 to 5 and x2 to 10
	cpu.registers.set(1, 5);
	cpu.registers.set(2, 10);
	printf("State of registers after setting x1 and x2:\n");
	cpu.registers.dump();
	printf("\n");

	cpu.run(1); // Run one instruction
	
	// Dump the registers to see the result
	printf("State of registers after executing ADD instruction:\n");
	cpu.registers.dump();
	printf("\n");

	return 0;
}