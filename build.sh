export X_CMAKE_UNCRUSTIFY_ENABLED=1
echo Creating Target Directory...
mkdir ./target
cd ./target
(cmake .. && make && ctest --output-on-failure) || true
cd -
