import java.io.*;

class Node
{
	Node left;
	int data;
	Node right;
	Node parent;
	Node(int data)
	{
		this.data = data;
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

	private Node transplant(Node parent, Node curr, Node replace)
	{
		if (parent.left == curr)
			parent.left = replace;
		else
			parent.right = replace;
		return parent;
	}

	public String delete(int val)
	{
		Node curr = searchNode(val);
		if (curr == null) return "Node unavailable";
		if (curr.left == null && curr.right == null) //leaf node
		{
			curr.parent = transplant(curr.parent,curr,null);
			return "Success";
		}
		else if (curr.left == null) //single child
		{
			curr.parent = transplant(curr.parent,curr,curr.right);
			return "Success";
		}
		else if (curr.right == null) //single child
		{
			curr.parent = transplant(curr.parent,curr,curr.left);
			return "Success";
		}
		//double children, replacing with successor strategy
		Node successorNode = searchNode(getSuccessor(curr.data));
		successorNode.parent = transplant(successorNode.parent,successorNode,successorNode.right);
		if (curr == root)
			root = successorNode;
		else
			curr.parent = transplant(curr.parent,curr,successorNode);
		successorNode.left = curr.left;
		successorNode.right = curr.right;
		return "Success";
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
		return getTreeHeight(root);
	}

	private int getTreeHeight(Node root)
	{
		if (root == null)
			return -1;
		if (root.left == null && root.right == null)
			return 0;
		return Math.max(getTreeHeight(root.left),getTreeHeight(root.right))+1;
	}

	public int getFullNodeCount()
	{
		return nodeCount("full",root);
	}

	public int getLeafCount()
	{
		return nodeCount("leaf",root);
	}

	public int getNonLeafCount()
	{
		return nodeCount("nonleaf",root);
	}

	private int nodeCount(String type, Node root)
	{
		if (root == null)
			return 0;
		if (root.left == null && root.right == null)
			return type.equals("leaf") ? 1 : 0;
		if (root.left == null)
			return type.equals("nonleaf") ? nodeCount(type,root.right)+1 : nodeCount(type,root.right);
		if (root.right == null)
			return type.equals("nonleaf") ? nodeCount(type,root.left)+1 : nodeCount(type,root.left);
		return nodeCount(type,root.left)+nodeCount(type,root.right)+(type.equals("leaf") ? 0 : 1);
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

	public int getSuccessor(int val)
	{
		Node curr = searchNode(val);
		if (curr == null) return -1;
		if (curr.right != null)
		{
			curr = curr.right;
			while (curr.left != null)
				curr = curr.left;
			return curr.data;
		}
		while (curr != root && curr.parent.right == curr)
			curr = curr.parent;
		if (curr == root) return -1;
		return curr.parent.data;
	}

	public int getPredecessor(int val)
	{
		Node curr = searchNode(val);
		if (curr == null) return -1;
		if (curr.left != null)
		{
			curr = curr.left;
			while (curr.right != null)
				curr = curr.right;
			return curr.data;
		}
		while (curr != root && curr.parent.left == curr)
			curr = curr.parent;
		if (curr == root) return -1;
		return curr.parent.data;
	}

	public boolean isEmpty()
	{
		if (root == null) return true;
		return false;
	}

	public Node searchNode(int val)
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

class BinarySearchTreeThreaded
{
	public static void main(String[] args) throws IOException
	{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		Tree tree = new Tree();
		while (true)
		{
			System.out.println("1- Insert\n2- Delete\n3- Search\n4- Get Height\n5- Get Count of Full Nodes\n6- Get Count of Leaf Nodes\n7- Get count of Non-leaf Nodes\n8- Preorder Traversal\n9- Inorder Traversal\n10- Postorder Traversal\n11- Successor\n12- Predecessor\n13- Quit");
			int choice = Integer.parseInt(br.readLine());
			int val = 0;
			switch(choice)
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
					System.out.println(tree.getHeight());
					break;
				
				case 5:
					System.out.println(tree.getFullNodeCount());
					break;
				
				case 6:
					System.out.println(tree.getLeafCount());
					break;
				
				case 7:
					System.out.println(tree.getNonLeafCount());
					break;
				
				case 8:
					tree.preOrder();
					System.out.println();
					break;
				
				case 9:
					tree.inOrder();
					System.out.println();
					break;
				
				case 10:
					tree.postOrder();
					System.out.println();
					break;

				case 11:
					if (tree.isEmpty())
						System.out.println("No nodes available");
					else
					{
						System.out.println("Value- ");
						System.out.println(tree.getSuccessor(Integer.parseInt(br.readLine())));
					}
					break;

				case 12:
					if (tree.isEmpty())
						System.out.println("No nodes available");
					else
					{
						System.out.println("Value- ");
						System.out.println(tree.getPredecessor(Integer.parseInt(br.readLine())));
					}
					break;

				case 13:
					System.out.println("Quit");
					System.exit(0);

				default:
					System.out.println("Invalid Input");
			}
		}
	}
}