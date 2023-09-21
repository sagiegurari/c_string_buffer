
if [ "$1" = "--clean" ]; then
  echo Cleaning...
  rm -Rf ./target
fi

export X_CMAKE_DOC_STEPS=true

echo Creating Target Directory...
mkdir ./target

cd ./target

set -e

cmake .. && make && ctest -C Release --output-on-failure

if [ "$1" = "--memcheck" ]; then
  # memory check
  ctest -T memcheck || true
elif [ "$1" = "--valgrind" ]; then
  # memory check
  for testfile in ./bin/test_*
  do
    echo "------------------------------------------------"
    echo "Testing ${testfile}"
    valgrind --leak-check=yes --undef-value-errors=no --error-exitcode=1 "${testfile}"
  done
fi

cd -
