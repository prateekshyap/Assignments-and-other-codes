import java.io.*;

class Node
{
	Node prev;
	int data;
	Node next;
	Node(int data)
	{
		this.data = data;
	}
}

class LinkedList
{
	public Node head, tail;
	private int listLength;

	LinkedList()
	{
		head = tail = null;
		listLength = 0;
	}

	public void addAtBeginning(int val)
	{
		if (head == null && tail == null)
		{
			head = new Node(val);
			tail = head;
		}
		else
		{
			head.prev = new Node(val);
			head.prev.next = head;
			head = head.prev;
		}
		++listLength;
	}

	public void addAtEnd(int val)
	{
		if (head == null && tail == null)
		{
			head = new Node(val);
			tail = head;
		}
		else
		{
			tail.next = new Node(val);
			tail.next.prev = tail;
			tail = tail.next;
		}
		++listLength;
	}

	public void addAtPosition(int pos, int val)
	{
		if (head == null && tail == null)
		{
			head = new Node(val);
			tail = head;
		}
		else
		{
			Node temp = head;
			while (pos > 1)
			{
				temp = temp.next;
				--pos;
			}
			if (temp == tail)
				addAtEnd(val);
			else {
			Node newNode = new Node(val);
			newNode.next = temp.next;
			newNode.prev = temp;
			newNode.next.prev = newNode;
			temp.next = newNode;}
		}
		++listLength;
	}

	public int deleteFromBeginning()
	{
		if (head == tail && listLength == 1)
		{
			int val = head.data;
			head = tail = null;
			listLength = 0;
			return val;
		}
		int val = head.data;
		head = head.next;
		--listLength;
		return val;
	}

	public int deleteFromEnd()
	{
		if (head == tail && listLength == 1)
		{
			int val = head.data;
			head = tail = null;
			listLength = 0;
			return val;
		}
		int val = tail.data;
		tail = tail.prev;
		--listLength;
		return val;
	}

	public int deleteFromPosition(int pos)
	{
		Node temp = head;
		if (pos == 1)
			return deleteFromBeginning();
		else if (pos == getLength())
			return deleteFromEnd();
		while (pos > 1)
		{
			temp = temp.next;
			--pos;
		}
		temp.next.prev = temp.prev;
		temp.prev.next = temp.next;
		--listLength;
		return temp.data;
	}

	public int deleteAllNodesWithValue(int val)
	{
		Node temp = head;
		int counter = 0;
		while (temp != null)
		{
			if (temp.data == val)
			{
				if (temp == head && head == tail)
				{
					head = tail = temp = null;
					++counter;
				}
				else if (temp == head)
				{
					deleteFromBeginning();
					++counter;
					temp = head;
				}
				else if (temp == tail)
				{
					deleteFromEnd();
					++counter;
				}
				else
				{
					Node nextPtr = temp.next;
					temp.prev.next = temp.next;
					temp.next.prev = temp.prev;
					temp = nextPtr;
					++counter;
				}
			}
			else
				temp = temp.next;
		}
		listLength-=counter;
		return counter;
	}

	public void traverseForward()
	{
		Node temp = head;
		while (temp != tail)
		{
			System.out.print(temp.data+"->");
			temp = temp.next;
		}
		System.out.println(temp.data);
	}

	public void traverseBackward()
	{
		Node temp = tail;
		while (temp != head)
		{
			System.out.print(temp.data+"<-");
			temp = temp.prev;
		}
		System.out.println(temp.data);
	}

	public boolean isEmpty()
	{
		if (head == null && tail == null)
			return true;
		return false;
	}

	public int getLength()
	{
		return this.listLength;
	}
}

class LinkedListImpl
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		LinkedList list = new LinkedList();
		int pos = -1, val = -1;
		while(true)
		{
			System.out.println("1- Insert a node\n2- Delete a node\n3- Delete all nodes containing the same value\n4- Forward traversal\n5- Backward traversal\n6- Quit\nEnter your choice-");
			int choice = Integer.parseInt(br.readLine());
			switch(choice)
			{
				case 1:
					System.out.println("1- At the beginning\n2- At the end\n3- After some node");
					pos = Integer.parseInt(br.readLine());
					switch(pos)
					{
						case 1:
							System.out.println("Value- ");
							list.addAtBeginning(Integer.parseInt(br.readLine()));
						break;

						case 2:
							System.out.println("Value- ");
							list.addAtEnd(Integer.parseInt(br.readLine()));
						break;

						case 3:
							System.out.println("Position- ");
							pos = Integer.parseInt(br.readLine());
							if (pos > list.getLength())
								System.out.println("Position Unavailable");
							else {
							System.out.println("Value- ");
							list.addAtPosition(pos,Integer.parseInt(br.readLine()));}
						break;

						default:
							System.out.println("Invalid Input");
					}
				break;

				case 2:
					if (list.isEmpty()) System.out.println("Empty List");
					else {
					System.out.println("1- From the beginning\n2- From the end\n3- Some specific node");
					pos = Integer.parseInt(br.readLine());
					switch(pos)
					{
						case 1:
							val = list.deleteFromBeginning();
							System.out.println(val+" deleted");
						break;

						case 2:
							val = list.deleteFromEnd();
							System.out.println(val+" deleted");
						break;

						case 3:
							System.out.println("Position- ");
							pos = Integer.parseInt(br.readLine());
							if (pos > list.getLength())
								System.out.println("Position Unavailable");
							else {
							val = list.deleteFromPosition(pos);
							System.out.println(val+" deleted");}
						break;

						default:
							System.out.println("Invalid Input");
					}}
				break;

				case 3:
					if (list.isEmpty()) System.out.println("Empty List");
					else {
					System.out.println("Value- ");
					val = list.deleteAllNodesWithValue(Integer.parseInt(br.readLine()));
					System.out.println(val+" nodes deleted");}
				break;

				case 4:
					if (list.isEmpty()) System.out.println("Empty List");
					else list.traverseForward();
				break;

				case 5:
					if (list.isEmpty()) System.out.println("Empty List");
					else list.traverseBackward();
				break;

				case 6:
					System.out.println("Quit");
					System.exit(0);

				default:
					System.out.println("Invalid Input");
			}
		}
	}
}