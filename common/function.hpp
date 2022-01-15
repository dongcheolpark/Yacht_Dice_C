#pragma once

#include <iostream>
#include <list>
#include <memory>
#include <string>

namespace ydc {
	template<typename ... Args>
	std::string format_string(const std::string& format, Args ... args)
	{
		size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		std::unique_ptr<char[]> buffer(new char[size]);
		snprintf(buffer.get(), size, format.c_str(), args ...);
		return std::string(buffer.get(), buffer.get() + size - 1);
	}
	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}
}