// Axel '0vercl0k' Souchet - March 8 2020
#pragma once
#include "FuzzerExtFunctions.h"
#include "FuzzerMutate.h"
#include "corpus.h"
#include "honggfuzz.h"
#include <memory>

class LibfuzzerMutator_t {
  using CustomMutatorFunc_t =
      decltype(fuzzer::ExternalFunctions::LLVMFuzzerCustomMutator);
  fuzzer::Random Rand_;
  fuzzer::MutationDispatcher Mut_;
  std::unique_ptr<fuzzer::Unit> CrossOverWith_;

public:
  explicit LibfuzzerMutator_t(std::mt19937_64 &Rng);

  size_t Mutate(uint8_t *Data, const size_t DataLen, const size_t MaxSize);
  void RegisterCustomMutator(const CustomMutatorFunc_t F);
  void SetCrossOverWith(const Testcase_t &Testcase);
};

class HonggfuzzMutator_t {
  honggfuzz::dynfile_t DynFile_;
  honggfuzz::honggfuzz_t Global_;
  std::mt19937_64 &Rng_;
  honggfuzz::run_t Run_;

public:
  explicit HonggfuzzMutator_t(std::mt19937_64 &Rng);
  size_t Mutate(uint8_t *Data, const size_t DataLen, const size_t MaxSize);
  void SetCrossOverWith(const Testcase_t &Testcase);
};