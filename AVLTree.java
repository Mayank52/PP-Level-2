class AVLTree {
    class Node {
        int data;
        Node left;
        Node right;
        int height;

        public Node(int data) {
            this.data = data;
            this.left = this.right = null;
            this.height = 1;
        }
    };

    // AVL Tree Insertion
    // https://practice.geeksforgeeks.org/problems/avl-tree-insertion/1#
    public Node ll(Node root) {
        if (root == null)
            return null;

        Node B = root.left;
        Node rightOfB = B.right;

        B.right = root;
        root.left = rightOfB;

        updateHeight(root);
        updateHeight(B);

        return B;
    }

    public Node rr(Node root) {
        if (root == null)
            return null;

        Node B = root.right;
        Node leftOfB = B.left;

        B.left = root;
        root.right = leftOfB;

        updateHeight(root);
        updateHeight(B);

        return B;
    }

    // While checking rotation check LR before LL and RL before RR
    public Node checkRotation(Node root) {
        if (root == null)
            return null;

        int lh = height(root.left);
        int rh = height(root.right);

        root.height = Math.max(lh, rh) + 1;

        int bal = lh - rh;

        if (bal == 2) {
            int leftBal = height(root.left.left) - height(root.left.right);
            if (leftBal == -1) { // lr
                root.left = rr(root.left);
                return ll(root);
            } else { // ll
                return ll(root);

            }
        } else if (bal == -2) {
            int rightBal = height(root.right.left) - height(root.right.right);
            if (rightBal == 1) { // rl
                root.right = ll(root.right);
                return rr(root);
            } else { // rr
                return rr(root);
            }
        }

        return root;
    }

    public int height(Node node) {
        if (node == null)
            return 0;

        return node.height;
    }

    public void updateHeight(Node node) {
        int lh = height(node.left);
        int rh = height(node.right);

        node.height = Math.max(lh, rh) + 1;
    }

    public Node insertToAVL(Node node, int data) {
        if (node == null)
            return new Node(data);

        if (data < node.data)
            node.left = insertToAVL(node.left, data);
        else if (data > node.data)
            node.right = insertToAVL(node.right, data);

        return checkRotation(node);
    }

    // AVL Tree Deletion
    // https://practice.geeksforgeeks.org/problems/avl-tree-deletion/1
    public Node deleteNode_(Node root, int key) {
        if (root == null)
            return null;

        if (key < root.data)
            root.left = deleteNode_(root.left, key);
        else if (key > root.data)
            root.right = deleteNode_(root.right, key);
        else {
            if (root.left == null || root.right == null)
                return root.left == null ? root.right : root.left;

            Node leftChild = root.left;
            while (leftChild.right != null)
                leftChild = leftChild.right;

            root.data = leftChild.data;
            root.left = deleteNode_(root.left, leftChild.data);
        }

        return checkRotation(root);
    }

    public Node deleteNode(Node root, int key) {
        // code here.
        return deleteNode_(root, key);
    }

    public static void main(String[] args) {

    }
}