#! bin/bash
echo
echo "Use grep or egrep to pick out the blank lines in the file: (find lines that start and end with nothing in between)"
echo 
egrep -n -v '[a-z]' poem.txt
