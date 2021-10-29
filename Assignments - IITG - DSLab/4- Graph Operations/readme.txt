================================
Instructions to execute the code	
================================

\item If you're using Dev C++, Follow the steps to support $unordered\_map$. Go to tools--compiler option--general tab--tick mark option (add the following commands when calling compiler)--add -std=c++11 there. Then build and execute the project.

\item In linux or GNU windows compiler, open the terminal or command prompt and type "g++ GraphImpl.cpp" and hit enter.
	
\item Then for linux type "./a.out". For windows type "a.exe" or "GraphImpl.exe" (One of them should work). Hit enter.
	
\item You can also write "./GraphImpl" and hit enter to execute the makefile which is provided.
	
\item Now the prompt will be displayed. Enter 0 or 1 for windows or linux respectively.
	
\item Give a name for all the files which are going to be generated during execution.
	
\item Write a .txt file according to the given format and enter the file name there.
	
\item The entire execution process can be visualized in $<user\_given\_name>Output.txt$.
	
\item After printing a graph, you can view the images in the same directory. The respective file names are written in the output file.
	
\item You can give multiple .txt files one after another. For example- in the first run, you can create a very dense graph, find the minimal graph and replace it with the original one, remove a few edges and then proceed for shortest paths or strongly connected components. Later you can create a new graph and do the same processing on it. All the images will be stored simultaneously.
	
\item You can run the batch file or shell script to manually generate the images.
	
\item Avoid giving percentage more than $50$. It is going to create a mess and you won't be able to visualize it. Moreover, there is a huge possibility of having only a single strongly connected component.
	
\item There will always be an option to go back to the main menu so that you can either generate all the images for the graphviz files written till now or quit.