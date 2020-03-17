#include <benchmark/benchmark.h>

class CacheLargArray : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& state)
  {

  }

  void TearDown(const ::benchmark::State& state)
  {

  }

  static constexpr size_t largArraySize = 32 * 1024 * 1024;
  int largArray[largArraySize];
};

BENCHMARK_DEFINE_F(CacheLargArray, IterateAndMultiplayOverLargArrayWithStep)(benchmark::State& state)
{
    size_t step = state.range(0);
    for (auto _ : state)
      for (size_t i = 0; i < largArraySize; i+= step) largArray[i] *= 3;
}

BENCHMARK_REGISTER_F(CacheLargArray, IterateAndMultiplayOverLargArrayWithStep)->DenseRange(1, 32);

BENCHMARK_DEFINE_F(CacheLargArray, IterateReverseAndMultiplayOverLargArrayWithStep)(benchmark::State& state)
{
    size_t step = state.range(0);
    for (auto _ : state)
      for (int i = largArraySize - 1; i >= 0; i-= step) largArray[i] *= 3;
}

BENCHMARK_REGISTER_F(CacheLargArray, IterateReverseAndMultiplayOverLargArrayWithStep)->DenseRange(1, 32);

class CacheLargArrayWithLookup : public benchmark::Fixture {
public:
  CacheLargArrayWithLookup() : benchmark::Fixture()
  {
      std::vector<size_t> randomIndex;
      std::vector<size_t> normalIndex;

      normalIndex.resize(largArraySize);
      std::generate(std::begin(normalIndex),std::end(normalIndex), [n = 0] () mutable { return n++; });
      randomIndex = normalIndex;
      std::random_shuffle(std::begin(randomIndex),std::end(randomIndex));

      for (size_t i = 0; i < normalIndex.size() ; ++i )
      {
          indexForward[i] = normalIndex[i];
          indexReverse[normalIndex.size() - i - 1] = normalIndex[i];
          indexRandom[i] = randomIndex[i];
      }
  }
  void SetUp(const ::benchmark::State& state)
  {
  }

  void TearDown(const ::benchmark::State& state)
  {

  }

  static constexpr size_t largArraySize = 32 * 1024 * 1024;
  int largArray[largArraySize];
  int indexForward[largArraySize];
  int indexReverse[largArraySize];
  int indexRandom[largArraySize];
};

BENCHMARK_DEFINE_F(CacheLargArrayWithLookup, IterateWihtLookupAndMultiplayOverLargArrayWithStep)(benchmark::State& state)
{
    size_t step = state.range(0);
    for (auto _ : state)
      for (size_t i = 0; i < largArraySize; i+= step) largArray[ indexForward[i] ] *= 3;
}

BENCHMARK_REGISTER_F(CacheLargArrayWithLookup, IterateWihtLookupAndMultiplayOverLargArrayWithStep)->DenseRange(1, 32);

BENCHMARK_DEFINE_F(CacheLargArrayWithLookup, IterateWihtLookupReverseAndMultiplayOverLargArrayWithStep)(benchmark::State& state)
{
    size_t step = state.range(0);
    for (auto _ : state)
      for (size_t i = 0; i < largArraySize; i+= step) largArray[ indexReverse[i] ] *= 3;
}

BENCHMARK_REGISTER_F(CacheLargArrayWithLookup, IterateWihtLookupReverseAndMultiplayOverLargArrayWithStep)->DenseRange(1, 32);

BENCHMARK_DEFINE_F(CacheLargArrayWithLookup, IterateWihtLookupRandomAndMultiplayOverLargArrayWithStep)(benchmark::State& state)
{
    size_t step = state.range(0);
    for (auto _ : state)
      for (size_t i = 0; i < largArraySize; i+= step) largArray[ indexRandom[i] ] *= 3;
}

BENCHMARK_REGISTER_F(CacheLargArrayWithLookup, IterateWihtLookupRandomAndMultiplayOverLargArrayWithStep)->DenseRange(1, 32);

class CacheArrayOfSize : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& state)
  {
    size_t arraySize = state.range(0);
    arrayWithSizeFromState = new int[arraySize];
  }

  void TearDown(const ::benchmark::State& state)
  {
    delete [] arrayWithSizeFromState;
  }

  int *arrayWithSizeFromState = nullptr;
  static constexpr int iterationSteps = 64 * 1024 * 1024;
};

BENCHMARK_DEFINE_F(CacheArrayOfSize, IterateOverDifferentSizeOfArray)(benchmark::State& state)
{
    size_t sizeOfArray = state.range(0);
    for (auto _ : state)
      for (size_t i = 0; i < iterationSteps; ++i) arrayWithSizeFromState[ (i * 16) % sizeOfArray ] *= 3;

    static_assert (4 == sizeof(int));
}

BENCHMARK_REGISTER_F(CacheArrayOfSize, IterateOverDifferentSizeOfArray)->DenseRange(1024 / 4, 64 * 1024 / 4, 1024 / 4);
BENCHMARK_REGISTER_F(CacheArrayOfSize, IterateOverDifferentSizeOfArray)->DenseRange(1024 * 1024 / 4, 64 * 1024 * 1024 / 4, 1024 * 1024 / 4);

