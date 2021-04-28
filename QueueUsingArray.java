import java.io.*;

class Queue
{
	private int[] queue;
	private int capacity;
	private int size;
	private int front;
	private int rear;

	Queue()
	{
		this.queue = new int[2];
		this.capacity = 2;
		this.size = 0;
		this.front = -1;
		this.rear = -1;
	}

	public void enqueue(int val)
	{
		if (size == capacity)
		{
			int[] temp = new int[capacity*2];
			int j = 0;
			for (int i = front; i != rear; i = (i+1)%capacity)
				temp[j++] = queue[i];
			temp[j] = queue[rear];
			front = 0;
			rear = j;
			capacity *= 2;
			queue = temp;
		}
		if (size == 0)
			front = rear = 0;
		else
			rear = (rear+1)%capacity;
		queue[rear] = val;
		++size;
	}

	public int dequeue()
	{
		int val = queue[front];
		if (size == 1)
			front = rear = -1;
		else
			front = (front+1)%capacity;
		--size;
		return val;
	}

	public int checkFront()
	{
		return queue[front];
	}

	public boolean isEmpty()
	{
		if (front == rear && front == -1)
			return true;
		return false;
	}
}

class QueueUsingArray
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