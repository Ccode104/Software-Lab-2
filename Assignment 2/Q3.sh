#! bin/bash
echo
echo "Use grep or egrep to pick out lines with rep, word, or more. (use the alternator |)"
echo
egrep -n 'rep|word|more' poem.txt
