
if [ "$1" = "--clean" ]; then
  echo Cleaning...
  rm -Rf ./target
fi

export X_CMAKE_UNCRUSTIFY_ENABLED=1

echo Creating Target Directory...
mkdir ./target

cd ./target
(cmake .. && make && ctest -C Release --output-on-failure) || true
cd -
