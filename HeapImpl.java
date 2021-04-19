import java.io.*;

class Heap
{
	private String heapType;
	private int capacity;
	private int heapSize;
	private int[] heap;

	public int getCapacity() { return this.capacity; }
	public int getHeapSize() { return this.heapSize; }

	public int left(int root) { return (root*2)+1; } 
	public int right(int root) { return (root*2)+2; }
	public int parent(int root) { return (root-1)/2; }

	Heap(String heapType, int[] arr)
	{
		this.capacity = arr.length;
		this.heapSize = arr.length;
		this.heapType = heapType;
		this.heap = arr;
		buildHeap();
		printHeap();
	}

	public void buildHeap()
	{
		if (heapType.equalsIgnoreCase("max"))
		{
			for (int i = (heapSize/2)-1; i >=0; --i)
				maxHeapify(i);
		}
		else if (heapType.equalsIgnoreCase("min"))
		{
			for (int i = (heapSize/2)-1; i >=0; --i)
				minHeapify(i);
		}
	}

	public void maxHeapify(int root)
	{
		int max = root;
		if (left(root) < heapSize && heap[left(root)] > heap[max])
			max = left(root);
		if (right(root) < heapSize && heap[right(root)] > heap[max])
			max = right(root);
		if (max != root)
		{
			int temp = heap[max];
			heap[max] = heap[root];
			heap[root] = temp;
			maxHeapify(max);
		}
	}

	public void minHeapify(int root)
	{
		int min = root;
		if (left(root) < heapSize && heap[left(root)] < heap[min])
			min = left(root);
		if (right(root) < heapSize && heap[right(root)] < heap[min])
			min = right(root);
		if (min != root)
		{
			int temp = heap[min];
			heap[min] = heap[root];
			heap[root] = temp;
			minHeapify(min);
		}
	}

	public void insertElement(int elem)
	{
		++heapSize;
		if (heapSize > capacity)
		{
			int[] temp = new int[capacity*2];
			for (int i = 0; i < capacity; ++i)
				temp[i] = heap[i];
			heap = temp; //set new heap
			capacity *= 2; //set new capacity
		}
		heap[heapSize-1] = elem;
		int i = heapSize-1;
		if (heapType.equalsIgnoreCase("max"))
		{
			while (heap[i] > heap[parent(i)])
			{
				int temp = heap[i];
				heap[i] = heap[parent(i)];
				heap[parent(i)] = temp;
				i = parent(i);
			}
		}
		else if (heapType.equalsIgnoreCase("min"))
		{
			while (heap[i] < heap[parent(i)])
			{
				int temp = heap[i];
				heap[i] = heap[parent(i)];
				heap[parent(i)] = temp;
				i = parent(i);
			}
		}
		printHeap();
	}

	public int extractRoot()
	{
		int val = heap[0];
		heap[0] = heap[heapSize-1];
		--heapSize;
		if (heapType.equalsIgnoreCase("max"))
			maxHeapify(0);
		else if (heapType.equalsIgnoreCase("min"))
			minHeapify(0);
		printHeap();
		return val;
	}

	private void printHeap()
	{
		for (int i = 0; i < heapSize; ++i)
			System.out.print(heap[i]+" ");
		System.out.println();
	}
}

class HeapImpl
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Heap minHeap = null, maxHeap = null;
		String input = "";
		String[] tokens;
		int[] arr;
		while (true)
		{
			System.out.println("1- Create a Min heap\n2- Create a Max heap\n3- Insert\n4- Extract root\n5- Get Heap Size\n6- Get Heap Capacity\n7- Quit");
			int choice = Integer.parseInt(br.readLine());
			switch(choice)
			{
				case 1:
					if (minHeap != null)
					{
							System.out.println("Want to replace?");
							input = br.readLine();
							if (input.equalsIgnoreCase("no"))
								break;
					}
					tokens = br.readLine().trim().split(" +");
					arr = new int[tokens.length];
					for (int i = 0; i < tokens.length; ++i)
						arr[i] = Integer.parseInt(tokens[i]);
					minHeap = new Heap("min", arr);
					break;

				case 2:
					if (maxHeap != null)
					{
							System.out.println("Want to replace?");
							input = br.readLine();
							if (input.equalsIgnoreCase("no"))
								break;
					}
					tokens = br.readLine().trim().split(" +");
					arr = new int[tokens.length];
					for (int i = 0; i < tokens.length; ++i)
						arr[i] = Integer.parseInt(tokens[i]);
					maxHeap = new Heap("max", arr);
					break;

				case 3:
					System.out.println("min or max?");
					input = br.readLine();
					if (input.equalsIgnoreCase("min"))
					{
						if (minHeap != null)
							minHeap.insertElement(Integer.parseInt(br.readLine()));
						else
							System.out.println("Doesn't exist");
					}
					else if (input.equalsIgnoreCase("max"))
					{
						if (maxHeap != null)
							maxHeap.insertElement(Integer.parseInt(br.readLine()));
						else
							System.out.println("Doesn't exist");
					}
					else
						System.out.println("Invalid input");
					break;

				case 4:
					System.out.println("min or max?");
					input = br.readLine();
					if (input.equalsIgnoreCase("min"))
					{
						if (minHeap != null)
							System.out.println(minHeap.extractRoot());
						else
							System.out.println("Doesn't exist");
					}
					else if (input.equalsIgnoreCase("max"))
					{
						if (maxHeap != null)
							System.out.println(maxHeap.extractRoot());
						else
							System.out.println("Doesn't exist");
					}
					else
						System.out.println("Invalid input");
					break;
				
				case 5:
					System.out.println("min or max?");
					input = br.readLine();
					if (input.equalsIgnoreCase("min"))
					{
						if (minHeap != null)
							System.out.println(minHeap.getHeapSize());
						else
							System.out.println("Doesn't exist");
					}
					else if (input.equalsIgnoreCase("max"))
					{
						if (maxHeap != null)
							System.out.println(maxHeap.getHeapSize());
						else
							System.out.println("Doesn't exist");
					}
					else
						System.out.println("Invalid input");
					break;

				case 6:
					System.out.println("min or max?");
					input = br.readLine();
					if (input.equalsIgnoreCase("min"))
					{
						if (minHeap != null)
							System.out.println(minHeap.getCapacity());
						else
							System.out.println("Doesn't exist");
					}
					else if (input.equalsIgnoreCase("max"))
					{
						if (maxHeap != null)
							System.out.println(maxHeap.getCapacity());
						else
							System.out.println("Doesn't exist");
					}
					else
						System.out.println("Invalid input");
					break;

				case 7:
					System.out.println("Quit");
					System.exit(0);
				default:
					System.out.println("Invalid input");
			}
		}
	}
}