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

    public Node checkRotation(Node root) {
        if (root == null)
            return null;

        int lh = height(root.left);
        int rh = height(root.right);

        root.height = Math.max(lh, rh) + 1;

        int bal = lh - rh;

        if (bal == 2) {
            if (root.left.left != null) { // ll
                return ll(root);
            } else { // lr
                root.left = rr(root.left);
                return ll(root);
            }
        } else if (bal == -2) {
            if (root.right.right != null) { // rl
                return rr(root);
            } else { // rr
                root.right = ll(root.right);
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

    public Node addNode(Node node, int data) {
        if (node == null)
            return new Node(data);

        if (data < node.data)
            node.left = insertToAVL(node.left, data);
        else if (data > node.data)
            node.right = insertToAVL(node.right, data);

        return checkRotation(node);
    }

    public void display(Node node) {
        if (node == null)
            return;

        display(node.left);
        System.out.print(node.data + " ");
        display(node.right);
    }

    public Node insertToAVL(Node node, int data) {
        // code here
        Node ans = addNode(node, data);

        display(ans);
        System.out.println();

        return ans;

    }

    public static void main(String[] args) {

    }
}