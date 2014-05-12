#include <iostream>
#include <chrono>

int plus_int(int a, int b) {
	return a + b;
}

int plus_bigint(int a, int b) {
	return 0;
}

typedef int (*Func)(int, int);

unsigned res = 0;

void test_asm(unsigned a) {
	unsigned int b = 1;
	
	const int f = (int) &plus_int;
	const int g = (int) &plus_bigint;

	__asm {
		MOV   EAX, a
		MOV   ECX, f
		ADD   EAX, b
		CMOVC ECX, g
		MOV   f, ECX
		MOV   res, EAX
	};
	auto call = (Func) f;
	call(a, b);

	//char c;
	//__asm {
	//	LAHF      // Copy flags to AH
	//	MOV c, AH
	//	CLC       // Clear carry flag
	//};
	//int overflow = c & 1;
	//std::cout << overflow << std::endl;
}

void test_straight(unsigned a) {
	unsigned int b = 1;
	int overflow = 0;
	if (a > UINT_MAX - b)
		overflow = 1;
	res = overflow? plus_bigint(a, b) : plus_int(a, b);
}

int main() {

	const int Tests = 50000000;

	auto start = std::chrono::system_clock::now();
	for (int i = Tests; i; --i)
		test_asm(i);
	auto mid = std::chrono::system_clock::now();
	for (int i = Tests; i; --i)
		test_straight(i);
	auto end = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count()   << std::endl;
	std::cout << res << std::endl;
	return 0;
}