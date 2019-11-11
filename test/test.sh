cd `dirname $0`
../bin/bfc < input.txt > output.txt
diff ./input.txt ./output.txt
make run