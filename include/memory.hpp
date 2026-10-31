#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdio>

namespace riscv_emulator {

class Memory {
public:
	Memory(uint64_t size) : size_(size), data(new uint8_t[size]) {}

	~Memory() {
		delete[] data;
	}

	Memory(const Memory& other) {
		size_ = other.size_;
		data = new uint8_t[size_];
		std::copy(other.data, other.data + size_, data);
	}

	Memory& operator=(const Memory& other) {
		if (this != &other) {
			delete[] data;
			size_ = other.size_;
			data = new uint8_t[size_];
			std::copy(other.data, other.data + size_, data);
		}
		return *this;
	}

	uint8_t read8(uint32_t address) const {
		assert(address < size_);
		return data[address];
	}

	uint16_t read16(uint32_t address) const {
		assert(size_ > 1);
		assert(address < size_ - 1);
		return static_cast<uint16_t>(data[address]) | (static_cast<uint16_t>(data[address + 1]) << 8);
	}

	uint32_t read32(uint32_t address) const {
		assert(size_ > 3);
		assert(address < size_ - 3);
		return static_cast<uint32_t>(data[address]) |
		       (static_cast<uint32_t>(data[address + 1]) << 8) |
		       (static_cast<uint32_t>(data[address + 2]) << 16) |
		       (static_cast<uint32_t>(data[address + 3]) << 24);
	}

	void write8(uint32_t address, uint8_t value) {
		assert(address < size_);
		data[address] = value;
	}

	void write16(uint32_t address, uint16_t value) {
		assert(size_ > 1);
		assert(address < size_ - 1);
		data[address] = static_cast<uint8_t>(value & 0xFF);
		data[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	}

	void write32(uint32_t address, uint32_t value) {
		assert(size_ > 3);
		assert(address < size_ - 3);
		data[address] = static_cast<uint8_t>(value & 0xFF);
		data[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		data[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		data[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	}
private:
	uint64_t size_;
	uint8_t* data;
};

} // namespace riscv_emulator