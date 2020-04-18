echo Creating Target Directory...
mkdir ./target
cd ./target
(cmake .. && make && ctest --output-on-failure) || true
cd -
