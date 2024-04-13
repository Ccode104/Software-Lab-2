#! /usr/bin/bash
echo ""
echo "1. Use grep to show all the times Edgar Allen Poe's poem \"The Raven\" contains the word \"raven\". (All following questions refer to this same poem.)"
echo ""
grep -n "raven" poem.txt
echo ""
echo "2. Use grep or egrep to pick out the blank lines in the file: (find lines that start and end with nothing in between.)"
echo ""
grep -n -v -i "[a-z]" poem.txt
echo ""
echo "3. Use grep or egrep to pick out lines with rep, word, or more. (use the alternator |)"
echo ""
egrep -n "rep|more|word" poem.txt
echo ""
echo "4. Use grep or egrep to pick out lines that have at least two p's followed by any number of letters followed by 'ore'. The p's do not ha
ve to be next to each other. ( .* dot and then asterisk will find any characters in the search text)"
echo ""
grep -n "p.*p.*ore.*" poem.txt
echo ""
echo "5. Use grep or egrep to pick out all the lines with v, z or I in them: use the class brackets [ ] to solve this one"
echo ""
grep -n "[vzI]" poem.txt
echo ""
echo "6. Use grep or egrep to pick out all the lines that do not start with an uppercase letter."
echo ""
grep -n -v "^[A-Z]" poem.txt
echo ""
echo "7.Use grep or egrep to pick out all the lines that end with a dash -"
echo ""
grep -n "\-.$" poem.txt
echo ""
echo "8. Use grep or egrep to pick out all the words that end with ore"
echo ""
grep -n -o -i "\w*ore\>" poem.txt
echo ""
echo "9. Use grep or egrep to pick out all the words that start with f or F"
echo ""
grep -n -o -i "\<F\w*" poem.txt 
echo ""
echo "10. Use grep or egrep to pick out lines that uses first letter alliteration - starting two
words with the same letter. ( .* dot and then asterisk will find any characters in the
search text)"
echo ""
egrep -n -i "\<a\w* \<a\w*|\<b\w* \<b\w*|\<c\w* \<c\w*|\<d\w* \<d\w*|\<e\w* \<e\w*|\<f\w* \<f\w*|\<g\w* \<g\w*|\<h\w* \<h\w*|\<i\w* \<i\w*|\<j\w* \<j\w*|\<k\w* \<k\w*|\<l\w* \<l\w*|\<m\w* \<m\w*|\<n\w* \<n\w*|\<o\w* \<o\w*|\<p\w* \<p\w*|\<q\w* \<q\w*|\<r\w* \<r\w*|\<s\w* \<s\w*|\<t\w* \<t\w*|\<u\w* \<u\w*|\<v\w* \<v\w*|\<w\w* \<w\w*|\<x\w* \<x\w*|\<y\w* \<y\w*|\<z\w* \<z\w*" poem.txt        
