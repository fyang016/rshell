# rshell
This project is created by Marco Rubio (mrubi005) and Franklin Yang (fyang016)

## What is rshell?
Hello!
Rshell is a basic command shell. We are making our own version of bash (Bourne Again SHell) to better understand how the real thing works and to improve software construction skills.
This project will be expanded upon as we progress through this course.

## How does it work?
Rshell is designed to mimic bash (mentioned earlier) using C++ code. When run, the program will dispay a "$" sign, which means that it is prompting you to enter commands.
For example, typing in "ls" and then pressing Enter should display a list of all the files and folders in the current directory.
Commands can also be chained or ignored using connectors. 
There are three connectors:
||
&&
;

To illustrate the following examples, we will assume that the capital letters A and B are commands (although that isn't the case in actuality).

The || connector stands for "or". A || B means "A or B". To be precise, it means "run B if A fails to run". Why does it mean this? The most efficient way to perform "A or B" would be to move on and ignore B if A runs successfully (because B, whether or not it would fail, would not change anything at that point).

The && connector stands for "and". A && B means "A and B". This is more straightforward; in order for the whole statement to be true, both cannot fail. If at least one fails, then the whole statement is false.

The ; connector allows the user to chain statements in one line. If this did not exist, the user would have to enter in statements one by one.

WARNING!! Please keep in mind that the first two connectors have to be typed in exactly that way. Putting a space or another character in between (e.g. | | instead of ||) means something different!


### Known bugs
Code will not throw an error with more than two of the '&' and the '|' characters in a row. (e.g. "&&&&&")
MASSIVE bug that makes three glitched files after using g++

