import java.io.*;

class Stack
{
	private int[] stack;
	private int capacity;
	private int top;
	Stack()
	{
		this.stack = new int[1];
		this.capacity = 1;
		this.top = -1;
	}

	public void push(int val)
	{
		if (top+1 == capacity)
		{
			int[] temp = new int[capacity*2];
			for (int i = 0; i < capacity; ++i)
				temp[i] = stack[i];
			capacity *= 2;
			stack = temp;
		}
		stack[++top] = val;
	}

	public int pop()
	{
		int val = stack[top];
		--top;
		return val; 
	}

	public int checkTop()
	{
		return stack[top];
	}

	public boolean isEmpty()
	{
		if (top == -1)
			return true;
		return false;
	}
}

class StackUsingArray
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