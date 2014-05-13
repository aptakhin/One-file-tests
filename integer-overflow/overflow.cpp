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

int main() {
	const int Tests = 300000000;

	auto start = std::chrono::system_clock::now();
	for (int i = Tests; i; --i) {
		unsigned int b = 1;

		__asm {
			MOV   EAX, i
			MOV   EBX, b
			MOV   ECX, [plus_int]
			ADD   EAX, EBX
			CMOVC ECX, [plus_bigint]
			CLC
			PUSH  EBX
			PUSH  EAX
			CALL  ECX
			POP   EBX
			POP   EBX
		};
	}

	res = 0;
	auto mid = std::chrono::system_clock::now();
	for (int i = Tests; i; --i) {
		unsigned int b = 1;
		int overflow = 0;
		if (i > UINT_MAX - b)
			overflow = 1;
		res = overflow? plus_bigint(i, b) : plus_int(i, b);
	}
	auto end = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count() << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count()   << std::endl;
	std::cout << res << std::endl;
	return 0;
}