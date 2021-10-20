# Example Test Case

1 <br>
9 <br>
1 <br>
5 <br>
1 <br>
15 <br>
1 <br>
3 <br>
1 <br>
7 <br>
1 <br>
11 <br>
1 <br>
17 <br>
9 <br>
6 <br>
10 <br>
2 <br>
15 <br>
5 <br>
4 <br>
7 <br>
9 <br>
16 <br>
10 <br><br>

The above sequence can be written as a test case in an input file, which indicates the following. <br>
1 (Insert the next value) <br>
9 <br>
1 (Insert the next value) <br>
5 <br>
1 (Insert the next value) <br>
15 <br>
1 (Insert the next value) <br>
3 <br>
1 (Insert the next value) <br>
7 <br>
1 (Insert the next value) <br>
11 <br>
1 (Insert the next value) <br>
17 <br>
9 (Print the tree) <br>
6 (Split the tree around next value) <br>
10 <br>
2 (Search the next value) <br>
15 <br>
5 (Find successor of the last searched value) <br>
4 (Get reverse inorder list) <br>
7 (Find the elements between next value and its next value i.e. 9 and 16) <br>
9 <br>
9 <br>
16 <br>
10 (Quit) <br>
 
# Instructions to execute the code

1. Be careful while executing the program.

2. If you're using Dev C++, Follow the steps to support unordered map. Go to tools->compiler option->general tab->add the following commands when calling compiler-> add -std=c++11 there. Then build and execute the project.

3. In linux or GNU windows compiler, open the terminal or command prompt and type ```g++ BinarySearchTreeImpl.cpp``` and hit enter.

4. Then for linux type ```./a.out```. For windows type ```a.exe``` or ```BinarySearchTreeImpl.exe``` (One of them should work). Hit enter.

5. Now the prompt will be displayed. Enter 0 or 1 for windows or linus respectively.

6. Write a .txt file according to the given format and enter the file name there. If you give wrong sequence, it can destroy the execution.

7. If you give an option to split the tree, there will be another prompt to replace your current tree with any of the splitted ones. Give proper option. Wrong choice can lead to destruction of the execution.

8. The entire execution process can be visualized in _output.txt_.

9. After splitting or printing a tree, you can view the images in the same directory. The file names are written in _output.txt_.

10. You can give multiple .txt files one after another. For example- in the first run, you can insert a few nodes and find kth largest element. It will print the result and ask you to give another file name. You can now split the tree around the kth largest element and may be discard the higher half and replace the original root with the lower half and then continue execution.

11. 10 is used for quit. Do not write 10 unnecessarily inside the _.txt_ file. It is better to keep it at the end.

12. You can run the batch file or shell script to manually generate the images.

# Want to improve the project?

Fork this repository, make the required changes and create a pull request.