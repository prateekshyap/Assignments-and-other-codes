import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Queue;

class Graph
{
	ArrayList<ArrayList<Integer>> graph;
	int v;
	String type;
	Graph(int v, String type)
	{
		graph = new ArrayList<ArrayList<Integer>>();
		this.v = v;
		if (type.equalsIgnoreCase("D"))
			this.type = "D";
		else
			this.type = "U";
		for (int i = 0; i < v; ++i)
			graph.add(new ArrayList<Integer>());
		printGraph();
	}
	public String addEdge(int source, int destination)
	{
		if (source >= v || destination >= v)
			return "Node unavailable";
		graph.get(source).add(destination);
		if (type.equals("U"))
			graph.get(destination).add(source);
		printGraph();
		return "Success";
	}
	public String addNode()
	{
		++v;
		graph.add(new ArrayList<Integer>());
		printGraph();
		return (v-1)+" added";
	}
	public String removeEdge(int source, int destination)
	{
		if (source >= v || destination >= v)
			return "Node unavailable";
		graph.get(source).remove(new Integer(destination));
		if (type.equals("U"))
			graph.get(destination).remove(new Integer(source));
		printGraph();
		return "Success";
	}
	public ArrayList<Integer> getAdjacentNodes(int node)
	{
		if (node >= v)
			return new ArrayList<Integer>();
		return graph.get(node);
	}
	public void printGraph()
	{
		System.out.println(graph);
	}
	public ArrayList<Integer> breadthFirstTraversal(int source)
	{
		ArrayList<Integer> bfs = new ArrayList<Integer>();
		boolean[] visited = new boolean[v];
		Queue<Integer> queue = new Queue<Integer>();
		visited[source] = true;
		bfs.add(source);
		queue.add(source);
		while(!queue.isEmpty())
		{
			int node = queue.remove();
			ArrayList<Integer> adjacentNodes = graph.get(node);
			for (Integer adjacentNode: adjacentNodes)
			{
				if (!visited[adjacentNode])
				{
					visited[adjacentNode] = true;
					bfs.add(adjacentNode);
					queue.add(adjacentNode);
				}
			}
		}
		return bfs;
	}
	public ArrayList<Integer> depthFirstTraversal(int source)
	{
		return new ArrayList<Integer>();
	}
}

class GraphImpl
{
	public static void main(String[] args)throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Initial number of nodes- ");
		int v = Integer.parseInt(br.readLine());
		System.out.println("Enter D/U (Directed/Undirected)- ");
		String st = br.readLine();
		Graph graph = new Graph(v, st);
		while (true)
		{
			System.out.println("1- Add Edge\n2- Add Node\n3- Remove Edge\n4- Find adjacent nodes\n5- BFS\n6- DFS\n7- Quit");
			int choice = Integer.parseInt(br.readLine());
			int src, dest;
			switch (choice)
			{
				case 1:
					System.out.println("Source- ");
					src = Integer.parseInt(br.readLine());
					System.out.println("Destination- ");
					dest = Integer.parseInt(br.readLine());
					System.out.println(graph.addEdge(src,dest));
					break;

				case 2:
					System.out.println(graph.addNode());
					break;

				case 3:
					System.out.println("Source- ");
					src = Integer.parseInt(br.readLine());
					System.out.println("Destination- ");
					dest = Integer.parseInt(br.readLine());
					System.out.println(graph.removeEdge(src,dest));
					break;

				case 4:
					System.out.println("Node- ");
					System.out.println(graph.getAdjacentNodes(Integer.parseInt(br.readLine())));
					break;

				case 5:
					System.out.println("Source- ");
					System.out.println(graph.breadthFirstTraversal(Integer.parseInt(br.readLine())));
					break;

				case 6:
					System.out.println("Source- ");
					System.out.println(graph.depthFirstTraversal(Integer.parsInt(br.readLine())));
					break;

				case 7:
					System.out.println("Quit");
					System.exit(0);

				default:
					System.out.println("Invalid Input");
			}
		}
	}	
}

/*

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Iterator;

class DFSTreeInfo implements Comparable<DFSTreeInfo>
{
	int parent;
	int count;

	DFSTreeInfo(int p, int c)
	{
		this.count = c;
		this.parent = p;
	}

	@Override
	public int compareTo(DFSTreeInfo obj)
	{
		return this.count - obj.count;
	}
}

class CityGraph
{
	ArrayList<ArrayList<Integer>> graph;
	HashMap<Integer,Integer> wTV; //stores weight to vertex mappings
	int[] population;
	int v;

	//additionals
	int totalPopulation;
	boolean[] visited;
	ArrayList<ArrayList<Integer>> dfsInfo;
	int weight;
	int[] parent;
	HashMap<Integer, Integer> parentCount; //stores the number of times a vertex is present as a parent

	CityGraph(int v, int[] population)
	{
		graph = new ArrayList<ArrayList<Integer>>();
		wTV = new HashMap<Integer,Integer>();
		this.v = v;
		this.population = population;
		for (int i = 0; i < v; ++i)
		{
			graph.add(new ArrayList<Integer>());
			wTV.put(population[i],i);
		}
		printGraph();
	}
	public String addEdge(int source, int destination)
	{
		graph.get(wTV.get(source)).add(wTV.get(destination));
		graph.get(wTV.get(destination)).add(wTV.get(source));
		return "Success";
	}
	public void printGraph()
	{
		System.out.println(graph);
	}

	public void modifiedDFS()
	{
		//find out the total population
		totalPopulation = 0;
		for (int i = 0; i < v; ++i)
			totalPopulation += population[i];

		//run dfs
		dfsInfo = new ArrayList<ArrayList<Integer>>();

		//build a DFS Tree starting from any vertex
		parent = new int[v];
		visited = new boolean[v];
		parentCount = new HashMap<Integer,Integer>();
		for (int i = 0; i < v; ++i)
			parentCount.put(i,0);
		visited[0] = true;
		parent[0] = -1;
		runDFS(0,-1);

		//add all the parent count to the min heap
		PriorityQueue<DFSTreeInfo> minHeap = new PriorityQueue<DFSTreeInfo>();
		Iterator iterator = parentCount.entrySet().iterator();
		while (iterator.hasNext())
		{
			Map.Entry elem = (Map.Entry)iterator.next();
			minHeap.add(new DFSTreeInfo((Integer)elem.getKey(),(Integer)elem.getValue()));
		}

		//extract from the min heap and calculate the traffic
		while (!minHeap.isEmpty())
		{
			DFSTreeInfo obj = minHeap.poll();
			minHeap.remove(new DFSTreeInfo(parent[obj.parent],parentCount.get(parent[obj.parent])));
			parentCount.put(parent[obj.parent],parentCount.get(parent[obj.parent])-1);
			if (parentCount.get(parent[obj.parent]) != -1)
				minHeap.add(new DFSTreeInfo(parent[obj.parent],parentCount.get(parent[obj.parent])));
			

			//list to store the dfs info for ith vertex
			ArrayList<Integer> temp = new ArrayList<Integer>();

			//get the adjacent vertices
			ArrayList<Integer> adjVertices = graph.get(i);

			
		}

		/*for (int i = 0; i < v; ++i)
		{
			//list to store the dfs info for ith vertex
			ArrayList<Integer> temp = new ArrayList<Integer>();

			//get the adjacent vertices
			ArrayList<Integer> adjVertices = graph.get(i);

			//if there is only one adjacent vertex, everyone will come except the people in that city
			if (adjVertices.size() == 1)
			{
				parentCount.put(i,parentCount.get(i)-1);
				temp.add(totalPopulation-population[i]);
			}

			/*else
			{
				//run dfs on all the adjacent vertices but do not consider the path through ith vertex
				for (int adjVertex : adjVertices)
				{
					visited = new boolean[v];
					weight = population[adjVertex];
					visited[adjVertex] = true;
					runDFS(adjVertex, i);
					temp.add(weight);
				}
			}

			dfsInfo.add(temp);
		}
		System.out.println(dfsInfo);*/
	}

	public void runDFS(int currNode, int exclude)
	{
		ArrayList<Integer> adjVertices = graph.get(currNode);
		for (Integer adjVertex : adjVertices)
		{
			if (!visited[adjVertex] && adjVertex != exclude)
			{
				parent[adjVertex] = currNode;
				parentCount.put(currNode, parentCount.get(currNode)+1);
				visited[adjVertex] = true;
				weight += population[adjVertex];
				runDFS(adjVertex,exclude);
			}
		}
	}
}

class Traffic
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int v = 9;

		//taking node weights
		int[] population = new int[]{1,4,3,5,2,7,8,15,38};

		//create the graph
		CityGraph graph = new CityGraph(v, population);

		//add edges
		String addMore = "y";
		graph.addEdge(1,5);
		graph.addEdge(4,5);
		graph.addEdge(3,5);
		graph.addEdge(5,2);
		graph.addEdge(2,15);
		graph.addEdge(2,7);
		graph.addEdge(7,8);
		graph.addEdge(8,38);
		graph.printGraph();

		//run DFS
		graph.modifiedDFS();
	}
}

*/