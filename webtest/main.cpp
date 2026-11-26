#include <cstdio>
#include <cstdlib>
#include <thread>
#include <atomic>
#include <wasm_simd128.h>

int main() {
  printf("Pointer size: %zu bytes (8 = Memory64 is on)\n", sizeof(void*));
  std::atomic<int> n{0};
  std::thread t([&] { n = 42; });
  t.join();
  printf("Thread test: %s\n", n == 42 ? "OK" : "FAILED");
  v128_t c = wasm_i32x4_add(wasm_i32x4_splat(1), wasm_i32x4_splat(2));
  printf("SIMD test: %s\n", wasm_i32x4_extract_lane(c, 0) == 3 ? "OK" : "FAILED");
  size_t big = 5ull << 30;
  char* p = (char*)malloc(big);
  if (p) { p[big - 1] = 7; printf("5 GB memory test: OK\n"); }
  else   { printf("5 GB memory test: FAILED\n"); }
  return 0;
}
