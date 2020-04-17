echo Creating Target Directory...
mkdir ./target
cd ./target
(cmake .. && make && make test) || true
cd -
