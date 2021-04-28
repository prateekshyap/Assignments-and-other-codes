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

class Queue
{
	private Node front;
	private Node rear;

	Queue()
	{
		this.front = this.rear = null;
	}

	public void enqueue(int val)
	{
		if (front == null && rear == null)
		{
			rear = new Node(val);
			front = rear;
		}
		else
		{
			rear.next = new Node(val);
			rear = rear.next;
		}
	}

	public int dequeue()
	{
		int val = front.data;
		if (front == rear)
			front = rear = null;
		else
			front = front.next;
		return val;
	}

	public int checkFront()
	{
		return front.data;
	}

	public boolean isEmpty()
	{
		if (front == null && rear == null)
			return true;
		return false;
	}
}

class QueueUsingLinkedList
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Queue queue = new Queue();
		while (true)
		{
			System.out.println("1- Enqueue\n2- Dequeue\n3- Check Front\n4- Check if empty\n5- Quit");
			int choice = Integer.parseInt(br.readLine());
			switch(choice)
			{
				case 1:
					System.out.println("Value- ");
					queue.enqueue(Integer.parseInt(br.readLine()));
					break;

				case 2:
					if (queue.isEmpty())
						System.out.println("Empty Queue");
					else
						System.out.println(queue.dequeue()+" removed");
					break;

				case 3:
					if (queue.isEmpty())
						System.out.println("Empty Queue");
					else
						System.out.println(queue.checkFront()+" is at the front");
					break;

				case 4:
					if (queue.isEmpty())
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