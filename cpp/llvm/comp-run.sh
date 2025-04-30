llvm=/opt/homebrew/opt/llvm/bin

cmd="$llvm/clang++ -o evallvm $($llvm/llvm-config --cxxflags --ldflags --system-libs --libs core) ./evallvm.cpp"

echo "BUILD: $cmd"

$cmd

./evallvm

$llvm/lli ./out.ll
