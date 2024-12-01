for file in *.cpp *.hpp; do
  if [[ -f "$file" ]]; then
    clang-format --style="{BasedOnStyle: llvm, ColumnLimit: 63}" -i "$file"
    echo "Formatted $file"
  else
    echo "No .cpp or .hpp files found to format."
  fi
done
