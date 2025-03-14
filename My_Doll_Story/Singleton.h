#pragma once
template <typename T>
class Singleton {
public:
	static T* GetInst()
	{
		static T instance;
		return &instance;
	}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

protected:
	Singleton() {}
	virtual ~Singleton() {}
};