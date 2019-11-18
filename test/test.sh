cd `dirname $0`
../bin/bfc < input.txt > output.txt
diff ./output.txt ./target.txt
make run