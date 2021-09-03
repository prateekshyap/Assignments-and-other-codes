=================
Example Test Case
=================
1
9
1
5
1
15
1
3
1
7
1
11
1
17
2
15
3
5
4
5

The above sequence can be written as a test case in an
input file, which indicates the following.
1 (Insert the next value)
9
1 (Insert the next value)
5
1 (Insert the next value)
15
1 (Insert the next value)
3
1 (Insert the next value)
7
1 (Insert the next value)
11
1 (Insert the next value)
17
2 (Delete the next value)
15
3 (Search the next value)
5
4 (Print the tree)
5 (Quit)

================================
Instructions to execute the code
================================

1. If you're using Dev C++, Follow the steps to support
unordered map. Go to tools->compiler option->general tab
->tick mark option (add the following commands when
calling compiler)->add-std=c++11 there. Then build and
execute the project.

2. In linux or GNU windows compiler, open the terminal
or command prompt and type "g++ AVLTreeImpl.cpp"
and hit enter.

3. Then for linux type "./a.out". For windows type "a.exe"
or "AVLTreeImpl.exe" (One of them should work).
Hit enter.

4. You can also write "./AVLTreeImpl" and hit enter to
execute the makefile which is provided.

5. Now the prompt will be displayed. Enter 0 or 1 for
windows or linux respectively.

6. Give a name for all the files which are going to be
generated during execution.

7. Write a .txt file according to the given format and
enter the file name there. If you give wrong sequence,
it can destroy the execution.

8. You can write "quit" or "view" instead of file name
to exit from the program or to generate the images till
now respectively.

9. The entire execution process can be visualized in
<given_name>output.txt.

10. After printing a tree, you can view the images in
the same directory. The respective file names
are written in <given_name>output.txt.

11. You can give multiple .txt files one after another.
For example- in the first run, you can insert a
few nodes and delete one of them to check how the tree
rotates, and after seeing the result you can write
another .txt file to delete the root node.

12. 5 is used for quit. Do not write 5 unnecessarily
inside the .txt file. It is better to keep it at the
end.

13. You can run the batch file or shell script to manually
generate the images.