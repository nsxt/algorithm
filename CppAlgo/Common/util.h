#pragma once

namespace nsxtalgo {

	template<class T>
	void swap(T& a, T& b) noexcept
	{
		T t = a;
		a = b;
		b = t;
	}

}