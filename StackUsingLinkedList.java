import java.io.*;

class Node
{
	int data;
	Node next;
	Node(int data)
	{
		this.data = data;
	}
}

class Stack
{
	private Node top;
	Stack()
	{
		top = null;
	}

	public void push(int val)
	{
		Node newNode = new Node(val);
		newNode.next = top;
		top = newNode;
	}

	public int pop()
	{
		int val = top.data;
		top = top.next;
		return val; 
	}

	public int checkTop()
	{
		return top.data;
	}

	public boolean isEmpty()
	{
		if (top == null)
			return true;
		return false;
	}
}

class StackUsingLinkedList
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Stack stack = new Stack();
		int val = 0;
		while (true)
		{
			System.out.println("1- Push\n2- Pop\n3- Check top\n4- Check if empty\n5- Quit");
			int choice = Integer.parseInt(br.readLine());
			switch(choice)
			{
				case 1:
					System.out.println("Value- ");
					stack.push(Integer.parseInt(br.readLine()));
					break;

				case 2:
					if (stack.isEmpty())
						System.out.println("Empty Stack");
					else
						System.out.println(stack.pop()+" popped");
					break;

				case 3:
					if (stack.isEmpty())
						System.out.println("Empty Stack");
					else
						System.out.println("At Top- "+stack.checkTop());
					break;

				case 4:
					if (stack.isEmpty())
						System.out.println("Empty");
					else
						System.out.println("Not empty");
					break;

				case 5:
					System.out.println("Quit");
					System.exit(0);

				default:
					System.out.println("Invalid Input");
			}
		}
	}
}