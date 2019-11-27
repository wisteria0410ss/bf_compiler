cd `dirname $0`
make run

echo "++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++
++++++++++++++++++++++++++++++++
++++++++.
+++++++.
--------.
--." > input.txt
echo -n "hoge" > target.txt
../bin/bfc -S < input.txt > test.asm
as test.asm -o test.o && ld test.o -o test_asm.out
./test_asm.out > output.txt
diff output.txt target.txt

../bin/bfc input.txt > a.out
chmod +x a.out
./a.out > output.txt
diff output.txt target.txt

echo ">+++++++++[<++++++++>-]<.>+++++++[<++++>-]<+.+++++++..+++.[-]>++++++++[<++
++>-]<.>+++++++++++[<+++++>-]<.>++++++++[<+++>-]<.+++.------.--------.[-]>
++++++++[<++++>-]<+.[-]++++++++++." > input.txt
echo "Hello World!" > target.txt
../bin/bfc -S input.txt -o test.asm
as test.asm -o test.o && ld test.o -o test_asm.out
./test_asm.out > output.txt
diff output.txt target.txt

../bin/bfc input.txt -o a.out
./a.out > output.txt
diff output.txt target.txt
