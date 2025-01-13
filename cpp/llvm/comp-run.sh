llvm=/opt/homebrew/opt/llvm/bin

$llvm/clang++ -o evallvm $($llvm/llvm-config --cxxflags --ldflags --system-libs --libs core) ./evallvm.cpp

./evallvm

$llvm/lli ./out.ll
