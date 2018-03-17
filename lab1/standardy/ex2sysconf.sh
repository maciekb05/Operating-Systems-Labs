#!/bin/bash

echo "#include <stdio.h>"
echo "#include <unistd.h>"
echo "#include <limits.h>"

echo "int main(void) {"
echo "long r;"

for i in `cat sysconf.list.txt | grep _SC`
do
    echo '#ifdef '$i
    echo "r = sysconf($i);"
	echo "if(r == -1){printf(\"The $i is defined without value\\n\");}"
	echo "else{"
    echo "printf(\"The value of $i is %ld\\n\", r);"
	echo "}"
    echo "#else"
    echo "printf(\"The $i is undefined.\\n\");"
    echo '#endif'
done

echo "return 0;"
echo "}"
