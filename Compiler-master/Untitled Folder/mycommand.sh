bison -d -y 1305053.y
echo '1'
g++ -w -c -o y.o y.tab.c
echo '2'
flex 1305053.l
echo '3'
g++ -fpermissive -w -c -o l.o lex.yy.c
echo '4'
g++ -o a.out y.o l.o -lfl -ly
echo '5'
./a.out input4.txt
