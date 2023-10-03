#include <array>
#include <benchmark/benchmark.h>
#include <iostream>
#include <random>
#include <vector>

template <typename T, std::size_t N, T... I>
constexpr auto create_array_impl(std::integer_sequence<T, I...>) {
  return std::array<T, N>{{I...}};
}

template <typename T, std::size_t N> constexpr auto create_array() {
  return create_array_impl<T, N>(std::make_integer_sequence<T, N>{});
}

template <typename T>
static int binary_search(const T *data, int len, const T &x) {
  int lo = 0, hi = len - 1, mid;
  while (lo <= hi) {
    mid = (lo + hi) >> 1;
    if (data[mid] == x) {
      return mid;
    } else if (data[mid] < x) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return -1;
}

template <typename T>
static int lower_bound_v1(const T *data, int len, const T &x) {
  if (!len || x > data[len - 1])
    return len;

  const T *base = data;
  while (len > 1) {
    int half = (len >> 1);
    if (base[half - 1] < x) {
      base += half;
      len -= half;
    } else {
      len -= half;
    }
  }

  return base - data;
}

template <typename T>
static int binary_search_v1(const T *data, int len, const T &x) {
  int i = lower_bound_v1(data, len, x);
  return (i == len || data[i] != x) ? -1 : i;
}

template <typename T>
static int lower_bound_v2(const T *data, int len, const T &x) {
  if (!len || x > data[len - 1])
    return len;

  const T *base = data;
  while (len > 1) {
    int half = (len >> 1);
    base += half * (base[half - 1] < x);
    len -= half;
  }

  return base - data;
}

template <typename T>
static int binary_search_v2(const T *data, int len, const T &x) {
  int i = lower_bound_v2(data, len, x);
  return (i == len || data[i] != x) ? -1 : i;
}

template <typename T>
static int lower_bound_v3(const T *data, int len, const T &x) {
  if (!len || x > data[len - 1])
    return len;

  const T *base = data;
  while (len > 1) {
    int half = (len >> 1);
    __builtin_prefetch(base + (half >> 1) - 1);
    __builtin_prefetch(base + half + (half >> 1) - 1);
    base += half * (base[half - 1] < x);
    len -= half;
  }

  return base - data;
}

template <typename T>
static int binary_search_v3(const T *data, int len, const T &x) {
  int i = lower_bound_v3(data, len, x);
  return (i == len || data[i] != x) ? -1 : i;
}

using BinarySearcher = int (*)(const int *, int, const int &);

auto arr_2m = create_array<int, 1 << 21>();
std::array<BinarySearcher, 4> binary_searchers{
    binary_search<int>, binary_search_v1<int>, binary_search_v2<int>,
    binary_search_v3<int>};

static void BM_binary_search(benchmark::State &state) {
  std::random_device rd;
  std::mt19937 gen(rd());
  auto binary_search = binary_searchers[state.range(0)];
  auto len = state.range(1);
  std::uniform_int_distribution<int> dist(-1024, len << 1);
  std::vector<int> arr(state.range(1));
  std::iota(arr.begin(), arr.end(), 0);

  int sum = 0;
  for (auto _ : state) {
    int x = dist(gen);
    sum += binary_search(arr.data(), arr.size(), x);
  }
  benchmark::DoNotOptimize(sum);
}

BENCHMARK(BM_binary_search)
    ->Args({0, 1 << 8})
    ->Args({0, 1 << 12})
    ->Args({0, 1 << 16})
    ->Args({0, 1 << 22})
    ->Args({0, 1 << 26})
    ->Args({1, 1 << 8})
    ->Args({1, 1 << 12})
    ->Args({1, 1 << 16})
    ->Args({1, 1 << 22})
    ->Args({1, 1 << 26})
    ->Args({2, 1 << 8})
    ->Args({2, 1 << 12})
    ->Args({2, 1 << 16})
    ->Args({2, 1 << 22})
    ->Args({2, 1 << 26})
    ->Args({3, 1 << 8})
    ->Args({3, 1 << 12})
    ->Args({3, 1 << 16})
    ->Args({3, 1 << 22})
    ->Args({3, 1 << 26});

int main(int argc, char **argv) {
  auto arr = create_array<int, (1 << 5)>();
  std::cout << arr.size() << std::endl;
  std::vector<int> nums{1, 3, 5, 7, 9, 10};

  for (int i = -1; i < 13; ++i) {
    int a = binary_search(nums.data(), nums.size(), i);
    int b = binary_search_v1(nums.data(), nums.size(), i);
    int c = binary_search_v2(nums.data(), nums.size(), i);
    int d = binary_search_v3(nums.data(), nums.size(), i);
    assert(a == b && b == c && c == d);
  }

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}
