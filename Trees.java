import java.io.IOException;
import java.util.Collection;
import java.util.Collections;
import java.util.Scanner;

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

    public static void main(String[] args) throws IOException {

    }
}