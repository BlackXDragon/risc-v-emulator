#include "cpu.hpp"

namespace riscv_emulator {

CPU::CPU(Memory* memory) : memory(memory) {
	registers.reset();
	working_memory = new Memory(*memory);
}

CPU::~CPU() {
	delete working_memory;
}

void CPU::reset() {
	registers.reset();
	delete working_memory;
	working_memory = new Memory(*memory);
}

void CPU::step() {
	uint32_t pc = registers.get_pc();
	uint32_t instruction = working_memory->read32(pc);
	printf("PC: 0x%08X, Instruction: 0x%08X\n", pc, instruction);

	uint32_t next_pc = pc + 4;
	uint32_t opcode = instruction & 0x7F;
	switch (opcode) {
		case 0x33: { // R-type
			uint32_t rd = (instruction >> 7) & 0x1F;
			uint32_t funct3 = (instruction >> 12) & 0x7;
			uint32_t rs1 = (instruction >> 15) & 0x1F;
			uint32_t rs2 = (instruction >> 20) & 0x1F;
			uint32_t funct7 = (instruction >> 25) & 0x7F;
			if (funct3 == 0x0 && funct7 == 0x00) { // ADD
				uint32_t result = registers.get(rs1) + registers.get(rs2);
				registers.set(rd, result);
				printf("ADD x%d, x%d, x%d\n", rd, rs1, rs2);
			} else {
				printf("Unknown R-type instruction: funct3=0x%X, funct7=0x%X\n", funct3, funct7);
			}
			break;
		}
		default:
			printf("Unknown instruction with opcode: 0x%X\n", opcode);
			break;
	}

	registers.set_pc(next_pc);
}

void CPU::run(uint32_t max_steps) {
	for (uint32_t i = 0; i < max_steps; ++i) {
		step();
	}
}
}