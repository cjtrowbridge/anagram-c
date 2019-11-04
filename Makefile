# -*- indent-tabs-mode:t; -*-

#test: anagram
#	./anagram least dictionary.txt

anagram:
	clang anagram.c -o anagram

# Fetch the dictionary
dictionary.txt:
	wget https://github.com/dwyl/english-words/blob/master/words_alpha.txt?raw=true -O dictionary.txt
