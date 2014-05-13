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

	__asm {
		MOV   EAX, a
		MOV   EBX, b
		MOV   ECX, [plus_int]
		ADD   EAX, EBX
		CMOVC ECX, [plus_bigint]
		PUSH  EBX
		PUSH  EAX
		CALL  ECX
		POP   EBX
		POP   EBX
	};
}

void test_straight(unsigned a) {
	unsigned int b = 1;
	int overflow = 0;
	if (a > UINT_MAX - b)
		overflow = 1;
	res = overflow? plus_bigint(a, b) : plus_int(a, b);
}

int main() {

	const int Tests = 100000000;

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