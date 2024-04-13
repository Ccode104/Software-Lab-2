echo
echo "Use grep or egrep to pick out lines that have at least two p's followed by any number of letters followed by 'ore'. The p's do not have to be next to each other. (.* dot and then asterisk will find any characters in the search text)"
grep -n "p.p.*ore" poem.txt

