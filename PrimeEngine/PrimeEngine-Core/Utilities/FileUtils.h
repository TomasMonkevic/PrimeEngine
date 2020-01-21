#pragma once

#include <string>
#include <memory>
#include <DllExport.h>

namespace PrimeEngine {

	struct ByteArray {
		ByteArray() : ByteArray(0) {}
		ByteArray(size_t s) : size(s), data(size ? new uint8_t[size] : nullptr) {}

		size_t size;
		std::unique_ptr<uint8_t[]> data;
	};

	PRIMEENGINEAPI std::string ReadFileString(const char* path);
	PRIMEENGINEAPI ByteArray ReadFileBytes(const char* path);

}