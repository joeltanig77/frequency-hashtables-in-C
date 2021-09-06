# Frequency (Dynamically Growing Hashtable)

This program reads words from one or more files and prints out a list
of the most frequently occurring sequential pairs of words and the number of times they occurred, in decreasing order occurrence. It does this by using a dynamically growing hashtable that grows when half the size of the hashtable is equal to the items already inside the hashtable by tracking its size. For an example of what a hashtable does click [here](https://www.cs.usfca.edu/~galles/visualization/OpenHash.html)
## How to run
First compile the code by typing
```
make
```
into the terminal

## Usage
```
./wordpairs <-count> fileName1 <filename2> ...
```
Where count is the number to display and <> are optional settings that can be used. If count is not specified, then it prints all the words pairs of the text file/files
## Example runs
Example 1
```
./wordpairs -5 dracula.txt
          897 of the
          630 in the
          383 to the
          340 and the
          329 and i
```
Example 2
```
./wordpairs -5 gettysburg.txt gettysburg.txt
          6 it is
          6 the people
          6 to the
          6 we cannot
          4 here have
```
