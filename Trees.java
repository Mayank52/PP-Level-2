import java.io.IOException;
import java.util.Collections;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import java.util.HashMap;

class Trees {
    public class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    class Node {
        int data;
        Node left, right;

        Node(int item) {
            data = item;
            left = right = null;
        }
    }

    // 144. Binary Tree Preorder Traversal (Morris Traversal)
    /*
     * Morris Traversal : O(3n), O(1) Each node is visited 3 times max. When the
     * root is visited 1st time, make the connection with rightmost child of its
     * left child, and add root to ans. When root is visited 2nd time, break the
     * connection and move to right child.
     */
    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();

        while (root != null) {
            if (root.left == null) {
                ans.add(root.val);
                root = root.right;
            } else {
                TreeNode rootp1 = root.left;

                while (rootp1.right != null && rootp1.right != root) {
                    rootp1 = rootp1.right;
                }

                if (rootp1.right == null) { // 1st time -> make connection, add to ans
                    ans.add(root.val);
                    rootp1.right = root;
                    root = root.left;
                } else { // 2nd time -> break connection
                    rootp1.right = null;
                    root = root.right;
                }
            }
        }

        return ans;
    }

    // 94. Binary Tree Inorder Traversal (Morris Traversal)
    /*
     * Morris Traversal : O(3n), O(1) Each node is visited 3 times max. When the
     * root is visited 1st time, make the connection with rightmost child of its
     * left child. When root is visited 2nd time, break the connection, , add root
     * to ans and move to right child.
     */
    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();

        while (root != null) {
            if (root.left == null) {
                ans.add(root.val);
                root = root.right;
            } else {
                TreeNode rootp1 = root.left;

                while (rootp1.right != null && rootp1.right != root) {
                    rootp1 = rootp1.right;
                }

                if (rootp1.right == null) { // 1st time
                    rootp1.right = root;
                    root = root.left;
                } else { // 2nd time -> break connection, add to ans
                    ans.add(root.val);
                    rootp1.right = null;
                    root = root.right;
                }
            }
        }

        return ans;
    }

    // 145. Binary Tree Postorder Traversal
    /*
     * Morris Traversal does not exist for postorder, but you can use a jugaad. //
     * If we write a reverse Preorder, then reverse it, that gives us postorder. //
     * To get reverse Preorder, we just reverse the left right calls. // So instead
     * of Root Left Right , we do Root Right Left //So use this and then reverse the
     * traversal
     * 
     * But this will require extra space to store and reverse the reverse preorder.
     * So, it is not exactly morris traversal. But if you have to do it then this is
     * the way to do it.
     */
    public List<Integer> postorderTraversal(TreeNode root) {
        List<Integer> ans = new ArrayList<>();

        // write exact same as preorder, and
        // make all left-> right, and right -> left
        while (root != null) {
            if (root.right == null) {
                ans.add(root.val);
                root = root.left;
            } else {
                TreeNode rootp1 = root.right;

                while (rootp1.left != null && rootp1.left != root) {
                    rootp1 = rootp1.left;
                }

                if (rootp1.left == null) { // 1st time -> make connection, add to ans
                    ans.add(root.val);
                    rootp1.left = root;
                    root = root.right;
                } else { // 2nd time -> break connection
                    rootp1.left = null;
                    root = root.left;
                }
            }
        }

        Collections.reverse(ans);
        return ans;
    }

    // 199. Binary Tree Right Side View
    public List<Integer> rightSideView(TreeNode root) {
        if (root == null)
            return new ArrayList<>();

        TreeNode node = root;
        List<Integer> ans = new ArrayList<>();
        LinkedList<TreeNode> que = new LinkedList<>();

        que.add(node);

        while (que.size() > 0) {
            int size = que.size();

            boolean firstNode = true;
            while (size-- > 0) {
                TreeNode rnode = que.poll();

                // add first node of each reverse level into ans
                if (firstNode) {
                    ans.add(rnode.val);
                    firstNode = false;
                }

                // add right node first -> to get the level in reverse
                if (rnode.right != null)
                    que.add(rnode.right);

                // add left node
                if (rnode.left != null)
                    que.add(rnode.left);
            }
        }

        return ans;
    }

    // Left View of Binary Tree (GFG)
    ArrayList<Integer> leftView(Node root) {
        if (root == null)
            return new ArrayList<>();

        Node node = root;
        ArrayList<Integer> ans = new ArrayList<>();
        LinkedList<Node> que = new LinkedList<>();

        que.add(node);

        while (que.size() > 0) {
            int size = que.size();

            boolean firstNode = true;
            while (size-- > 0) {
                Node rnode = que.poll();

                // add first node of each level into ans
                if (firstNode) {
                    ans.add(rnode.data);
                    firstNode = false;
                }

                // add left node
                if (rnode.left != null)
                    que.add(rnode.left);

                // add right node
                if (rnode.right != null)
                    que.add(rnode.right);
            }
        }

        return ans;
    }

    // Top View of Binary Tree
    // (https://practice.geeksforgeeks.org/problems/top-view-of-binary-tree/1)
    static class pair {
        Node node;
        int vl;

        pair(Node node, int vl) {
            this.node = node;
            this.vl = vl;
        }
    }

    // Approach 1:
    static int rightwidth = Integer.MIN_VALUE;
    static int leftwidth = Integer.MAX_VALUE;
    static int leftMinValue = 0;
    static int rightMaxValue = 0;

    static void width(Node node, int lev) {
        if (node == null)
            return;

        leftwidth = Math.min(leftwidth, lev);
        rightwidth = Math.max(rightwidth, lev);

        width(node.left, lev - 1);
        width(node.right, lev + 1);
    }

    static ArrayList<Integer> topView(Node node) {
        // add your code
        if (node == null)
            return new ArrayList<>();

        width(node, 0);

        int[] ans = new int[rightwidth - leftwidth + 1];
        Arrays.fill(ans, -1);

        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(node, -leftwidth));

        while (que.size() != 0) {
            int size = que.size();

            while (size-- > 0) {
                pair rpair = que.removeFirst();

                if (ans[rpair.vl] == -1)
                    ans[rpair.vl] = rpair.node.data;

                if (rpair.node.left != null)
                    que.addLast(new pair(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pair(rpair.node.right, rpair.vl + 1));
            }
        }

        ArrayList<Integer> temp = new ArrayList<>();
        for (int ele : ans)
            if (ele != -1)
                temp.add(ele);

        return temp;
    }

    // Approach 2: without finding the width -> use a hashmap instead of array to
    // store the
    // vertical level
    static ArrayList<Integer> topView(Node node) {
        // add your code
        if (node == null)
            return new ArrayList<>();

        HashMap<Integer, Integer> map = new HashMap<>();

        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(node, 0));
        int min = 0; // leftMin
        int max = 0; // rightMax

        while (que.size() != 0) {
            int size = que.size();

            while (size-- > 0) {
                pair rpair = que.removeFirst();

                // update the leftMin, rightMax
                min = Math.min(min, rpair.vl);
                max = Math.max(max, rpair.vl);

                // add only the first value of each vertical level in map
                if (map.containsKey(rpair.vl) == false) {
                    map.put(rpair.vl, rpair.node.data);
                }

                if (rpair.node.left != null)
                    que.addLast(new pair(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pair(rpair.node.right, rpair.vl + 1));
            }
        }

        // add the top view nodes in answer
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = min; i <= max; i++) {
            ans.add(map.get(i));
        }

        return ans;
    }

    // Bottom View of Binary Tree
    // (https://practice.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1)
    static class pair {
        Node node;
        int vl;

        pair(Node node, int vl) {
            this.node = node;
            this.vl = vl;
        }
    }

    // Approach 1:
    static int rightwidth = Integer.MIN_VALUE;
    static int leftwidth = Integer.MAX_VALUE;
    static int leftMinValue = 0;
    static int rightMaxValue = 0;

    static void width(Node node, int lev) {
        if (node == null)
            return;

        leftwidth = Math.min(leftwidth, lev);
        rightwidth = Math.max(rightwidth, lev);

        width(node.left, lev - 1);
        width(node.right, lev + 1);
    }

    public ArrayList<Integer> bottomView(Node root) {
        // Code here
        Node node = root;
        if (node == null)
            return new ArrayList<>();

        width(node, 0);

        int[] ans = new int[rightwidth - leftwidth + 1];

        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(node, -leftwidth));

        while (que.size() != 0) {
            int size = que.size();

            while (size-- > 0) {
                pair rpair = que.removeFirst();

                ans[rpair.vl] = rpair.node.data;

                if (rpair.node.left != null)
                    que.addLast(new pair(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pair(rpair.node.right, rpair.vl + 1));
            }
        }

        ArrayList<Integer> temp = new ArrayList<>();
        for (int ele : ans)
            if (ele != 0)
                temp.add(ele);

        return temp;
    }

    // Approach 2: without finding width -> use hashmap instead of array
    public ArrayList<Integer> bottomView(Node node) {
        // add your code
        if (node == null)
            return new ArrayList<>();

        HashMap<Integer, Integer> map = new HashMap<>();

        LinkedList<pair> que = new LinkedList<>();
        que.addLast(new pair(node, 0));
        int min = 0; // leftMin
        int max = 0; // rightMax

        while (que.size() != 0) {
            int size = que.size();

            while (size-- > 0) {
                pair rpair = que.removeFirst();

                // update the leftMin, rightMax
                min = Math.min(min, rpair.vl);
                max = Math.max(max, rpair.vl);

                // update the node for the vertical level in hashmap
                map.put(rpair.vl, rpair.node.data);

                if (rpair.node.left != null)
                    que.addLast(new pair(rpair.node.left, rpair.vl - 1));
                if (rpair.node.right != null)
                    que.addLast(new pair(rpair.node.right, rpair.vl + 1));
            }
        }

        // add the bottom view nodes in answer
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = min; i <= max; i++) {
            ans.add(map.get(i));
        }

        return ans;
    }

    // 987. Vertical Order Traversal of a Binary Tree
    public class Pair implements Comparable<Pair> {
        public TreeNode node;
        public int level; // stores either vertical or horizontal level

        public Pair(TreeNode n, int lvl) {
            this.node = n;
            this.level = lvl;
        }

        @Override
        public int compareTo(Pair o) {
            // if horizontal level is different -> sort according to horizontal level
            if (this.level != o.level)
                return this.level - o.level;
            // if same horiontal level -> sort according to node values
            else
                return this.node.val - o.node.val;
        }

    }

    public List<List<Integer>> verticalTraversal(TreeNode root) {
        TreeNode node = root;
        LinkedList<Pair> que = new LinkedList<>();
        HashMap<Integer, ArrayList<Pair>> map = new HashMap<>();

        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;

        que.addFirst(new Pair(node, 0));
        int hl = 0;

        while (que.size() > 0) {
            int size = que.size();

            while (size-- > 0) {
                Pair rpair = que.removeFirst();

                min = Math.min(min, rpair.level);
                max = Math.max(max, rpair.level);

                if (!map.containsKey(rpair.level)) {
                    map.put(rpair.level, new ArrayList<Pair>());
                }

                map.get(rpair.level).add(new Pair(rpair.node, hl));

                if (rpair.node.left != null)
                    que.addLast(new Pair(rpair.node.left, rpair.level - 1));
                if (rpair.node.right != null)
                    que.addLast(new Pair(rpair.node.right, rpair.level + 1));
            }

            hl++;
        }

        List<List<Integer>> ans = new ArrayList<>();
        for (int i = min; i <= max; i++) {
            ArrayList<Pair> nodes = map.get(i);

            // Sort the vertical level such that nodes on same horizontal level are sorted
            // in increasing order
            Collections.sort(nodes);
            List<Integer> lvl = new ArrayList<>();
            for (Pair pr : nodes) {
                lvl.add(pr.node.val);
            }
            ans.add(lvl);
        }

        return ans;
    }

    // Diagonal Traversal of Binary Tree
    // (https://practice.geeksforgeeks.org/problems/diagonal-traversal-of-binary-tree/1)
    /*
     * On GFG, the diagonal order is taken in DFS form, not levelOrder. So, BFS
     * gives the correct elements in a diagonal but in wrong order.
     * 
     * The DFS Solution passes in C++. But in java gets a TLE
     */
    // Approach 1: BFS
    public ArrayList<Integer> diagonal(TreeNode root) {
        TreeNode node = root;
        LinkedList<Pair> que = new LinkedList<>();
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();

        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;

        que.addFirst(new Pair(node, 0));

        while (que.size() > 0) {
            int size = que.size();

            while (size-- > 0) {
                Pair rpair = que.removeFirst();

                min = Math.min(min, rpair.level);
                max = Math.max(max, rpair.level);

                if (!map.containsKey(rpair.level)) {
                    map.put(rpair.level, new ArrayList<Integer>());
                }

                map.get(rpair.level).add(rpair.node.val);

                if (rpair.node.left != null)
                    que.addLast(new Pair(rpair.node.left, rpair.level - 1));
                if (rpair.node.right != null)
                    que.addLast(new Pair(rpair.node.right, rpair.level + 0));
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = min; i <= max; i++) {
            ArrayList<Integer> nodes = map.get(i);
            for (int j = 0; j < nodes.size(); j++) {
                ans.add(nodes.get(j));
            }
        }

        return ans;
    }

    // Approach 2: DFS
    public int leftMin = Integer.MAX_VALUE;
    public int rightMax = Integer.MIN_VALUE;

    public void diagonal(Node node, int lvl, HashMap<Integer, ArrayList<Integer>> map) {
        if (node == null)
            return;

        if (!map.containsKey(lvl))
            map.put(lvl, new ArrayList<Integer>());

        map.get(lvl).add(node.data);

        leftMin = Math.min(leftMin, lvl);
        rightMax = Math.max(rightMax, lvl);

        diagonal(node.left, lvl - 1, map);
        diagonal(node.right, lvl + 0, map);

    }

    public ArrayList<Integer> diagonal(Node root) {
        // add your code here.
        HashMap<Integer, ArrayList<Integer>> map = new HashMap<>();

        diagonal(root, 0, map);

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = rightMax; i >= leftMin; i--) {
            ArrayList<Integer> nodes = map.get(i);
            for (int j = 0; j < nodes.size(); j++) {
                ans.add(nodes.get(j));
            }
        }

        return ans;
    }

    // 878 · Boundary of Binary Tree
    public TreeNode leftMostNode = null;
    public TreeNode rightMostNode = null;

    public void leftBoundary(TreeNode node, List<Integer> res) {
        if (node == null)
            return;

        res.add(node.val);

        if (node.left != null)
            leftBoundary(node.left, res);
        else if (node.right != null)
            leftBoundary(node.right, res);
        else
            leftMostNode = node;
    }

    public void rightBoundary(TreeNode node, List<Integer> res) {
        if (node == null)
            return;

        if (node.right != null)
            rightBoundary(node.right, res);
        else if (node.left != null)
            rightBoundary(node.left, res);
        else
            rightMostNode = node;

        if (node != rightMostNode)
            res.add(node.val);
    }

    public void leafNodes(TreeNode node, List<Integer> res) {
        if (node == null)
            return;

        if (node.left == null && node.right == null) {
            if (node != leftMostNode)
                res.add(node.val);
            return;
        }

        if (node.left != null)
            leafNodes(node.left, res);
        if (node.right != null)
            leafNodes(node.right, res);
    }

    public List<Integer> boundaryOfBinaryTree(TreeNode root) {
        // write your code here
        if (root == null)
            return new ArrayList<>();

        List<Integer> res = new ArrayList<>();

        res.add(root.val);

        leftBoundary(root.left, res);
        leafNodes(root.left, res);
        leafNodes(root.right, res);
        rightBoundary(root.right, res);

        return res;
    }

    // 1145. Binary Tree Coloring Game
    /*
     * To win you have to choose a one of 3 nodes: parent of x, left child of x,
     * right of x You can only win if 1 of # conditions is true: 1. Count of nodes
     * in left subtree of x node > totalNodes/2 2. Count of nodes in right subtree
     * of x node > totalNodes/2 3. Count of nodes in rest of the tree i.e. n -
     * leftCount - rightCount - 1(for node x) > totalNodes/2
     */
    public boolean res = false;

    public int countNodes(TreeNode node, int n, int x) {
        if (node == null)
            return 0;

        int leftCount = countNodes(node.left, n, x);
        int rightCount = countNodes(node.right, n, x);

        if (node.val == x) {
            if (leftCount > n / 2 || rightCount > n / 2 || n - (leftCount + rightCount + 1) > n / 2)
                res = true;
        }

        return leftCount + rightCount + 1;
    }

    public boolean btreeGameWinningMove(TreeNode root, int n, int x) {
        res = false;
        countNodes(root, n, x);
        return res;
    }

    // 222. Count Complete Tree Nodes
    public int getLeftHeight(TreeNode root) {
        int count = 1;
        while (root.left != null) {
            root = root.left;
            count++;
        }

        return count;
    }

    public int getRightHeight(TreeNode root) {
        int count = 1;
        while (root.right != null) {
            root = root.right;
            count++;
        }

        return count;
    }

    public int countNodes(TreeNode root) {
        if (root == null)
            return 0;

        int lh = getLeftHeight(root);
        int rh = getRightHeight(root);

        if (lh == rh)
            return (1 << lh) - 1;

        return countNodes(root.left) + countNodes(root.right) + 1;
    }

    // 105. Construct Binary Tree from Preorder and Inorder Traversal
    public TreeNode preAndIn(int[] pre, int psi, int pei, int[] in, int isi, int iei, HashMap<Integer, Integer> map) {
        if (psi > pei || isi > iei)
            return null;

        TreeNode root = new TreeNode(pre[psi]);

        int idx = map.get(pre[psi]);

        int tot = idx - isi;

        root.left = preAndIn(pre, psi + 1, psi + tot, in, isi, idx - 1, map);
        root.right = preAndIn(pre, psi + tot + 1, pei, in, idx + 1, iei, map);

        return root;
    }

    public TreeNode buildTree(int[] preorder, int[] inorder) {
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }
        return preAndIn(preorder, 0, preorder.length - 1, inorder, 0, inorder.length - 1, map);
    }

    // 106. Construct Binary Tree from Inorder and Postorder Traversal
    public static TreeNode postAndIn(int[] post, int psi, int pei, int[] in, int isi, int iei,
            HashMap<Integer, Integer> map) {
        if (psi > pei || isi > iei)
            return null;

        TreeNode root = new TreeNode(post[pei]);

        int idx = map.get(post[pei]);

        int tot = idx - isi;

        root.left = postAndIn(post, psi, psi + tot - 1, in, isi, idx - 1, map);
        root.right = postAndIn(post, psi + tot, pei - 1, in, idx + 1, iei, map);

        return root;
    }

    public TreeNode buildTree(int[] inorder, int[] postorder) {
        HashMap<Integer, Integer> map = new HashMap<>();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }
        return postAndIn(postorder, 0, postorder.length - 1, inorder, 0, inorder.length - 1, map);
    }

    public static void main(String[] args) throws IOException {

    }
}