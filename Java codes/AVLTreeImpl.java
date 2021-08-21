import java.io.*;

class Node
{
	Node left;
	int data;
	Node right;
	int depth;
	Node(int data, int depth)
	{
		this.data = data;
		this.depth = depth;
	}
}

class Tree
{
	public Node root;
	Tree()
	{
		this.root = null;
	}

	public void insert(int val)
	{
		if (root == null)
			root = new Node(val);
		else
			insertIntoTree(root, val);
	}

	private void insertIntoTree(Node root, int val)
	{
		if (val < root.data && root.left == null)
		{
			root.left = new Node(val);
			root.left.parent = root;
		}
		if (val > root.data && root.right == null)
		{
			root.right = new Node(val);
			root.right.parent = root;
		}
		if (val < root.data)
			insertIntoTree(root.left, val);
		if (val > root.data)
			insertIntoTree(root.right, val);
	}

	public String delete(int val)
	{
		return "";
	}

	public String search(int val)
	{
		Node temp = root;
		while (temp != null && temp.data != val)
		{
			if (val < temp.data)
				temp = temp.left;
			else
				temp = temp.right;
		}
		if (temp == null) return "Unavailable";
		return "Available";
	}

	public int getHeight()
	{
		if (root == null) return -1;
		return root.height;
	}

	public int getNodeCount()
	{
		return nodeCount(root);
	}

	private int nodeCount(Node root)
	{
		if (root == null)
			return 0;
		if (root.left == null && root.right == null)
			return 1;
		if (root.left == null)
			return nodeCount(root.right)+1;
		if (root.right == null)
			return nodeCount(root.left)+1;
		return nodeCount(root.left)+nodeCount(root.right)+1;
	}

	public void preOrder()
	{
		printPreOrder(root);
	}

	private void printPreOrder(Node root)
	{
		if (root != null)
		{
			System.out.print(root.data+"\t");
			printPreOrder(root.left);
			printPreOrder(root.right);
		}
	}

	public void inOrder()
	{
		printInOrder(root);
	}

	private void printInOrder(Node root)
	{
		if (root != null)
		{
			printInOrder(root.left);
			System.out.print(root.data+"\t");
			printInOrder(root.right);
		}
	}

	public void postOrder()
	{
		printPostOrder(root);
	}

	private void printPostOrder(Node root)
	{
		if (root != null)
		{
			printPostOrder(root.left);
			printPostOrder(root.right);
			System.out.print(root.data+"\t");		
		}
	}

	public boolean isEmpty()
	{
		if (root == null) return true;
		return false;
	}

	private Node searchNode(int val)
	{
		Node temp = root;
		while (temp != null && temp.data != val)
		{
			if (val < temp.data)
				temp = temp.left;
			else
				temp = temp.right;
		}
		return temp;
	}
}

class AVLTreeImpl
{
	public static void main(String[] args)throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Tree tree = new Tree();
		while (true)
		{
			System.out.println("1- Insert\n2- Delete\n3- Search\n4- Get count of nodes\n5- Get height\n6- Preorder Traversal\n7- Inorder Traversal\n8- Postorder Traversal\n9- Quit");
			int choice = Integer.parseInt(br.readLine());
			switch (choice)
			{
				case 1:
					System.out.println("Value- ");
					tree.insert(Integer.parseInt(br.readLine()));
					break;

				case 2:
					if (tree.isEmpty())
						System.out.println("No nodes available");
					else
					{
						System.out.println("Value- ");
						System.out.println(tree.delete(Integer.parseInt(br.readLine())));
					}
					break;

				case 3:
					if (tree.isEmpty())
						System.out.println("No nodes available");
					else
					{
						System.out.println("Value- ");
						System.out.println(tree.search(Integer.parseInt(br.readLine())));
					}
					break;

				case 4:
					System.out.println(tree.getNodeCount());
					break;

				case 5:
					System.out.println(tree.getHeight());
					break;

				case 6:
					tree.preOrder();
					System.out.println();
					break;

				case 7:
					tree.inOrder();
					System.out.println();
					break;

				case 8:
					tree.postOrder();
					System.out.println();
					break;

				case 9:
					System.out.println("Quit");
					System.exit(0);

				default:
					System.out.println("Invalid Input");
			}
		}
	}
}