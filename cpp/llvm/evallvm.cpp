#include "./src/evallvm.h"

int main(int argc, char* argv[]) {
  std::string program = R"(
    42
  )";

  // Compiler instance
  EvaLLVM vm;

  // Generate LLVM IR
  vm.exec(program);

  return 0;
}
