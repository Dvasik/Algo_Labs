#include <stdio.h>
#include <stdlib.h>

typedef struct tagTREE tree;
struct tagTREE
{
  int l;
  int r;
  int r_max;
  tree *left;
  tree *right;
};

tree * newNode( int l, int r )
{
  tree *node = (tree *)malloc(sizeof(tree));
  node->l = l;
  node->r = r;
  node->r_max = r;
  node->left = NULL;
  node->right = NULL;
  return node;
}

tree * insert( tree *root, int l, int r )
{
  if (root == NULL)
    return newNode(l, r);

  if (l < root->l)
    root->left = insert(root->left, l, r);
  else
    root->right = insert(root->right, l, r);

  if (root->r_max < r)
    root->r_max = r;

  return root;
}

tree* deleteNode( tree *root, int l, int r )
{
  tree* temp;

  if (root == NULL)
    return root;

  if (l < root->l)
    root->left = deleteNode(root->left, l, r);
  else if (l > root->l)
    root->right = deleteNode(root->right, l, r);
  else
  {
    if (root->left == NULL)
    {
      temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      temp = root->left;
      free(root);
      return temp;
    }

    temp = root->right;
    while (temp->left != NULL)
      temp = temp->left;

    root->l = temp->l;
    root->r = temp->r;
    root->right = deleteNode(root->right, temp->l, temp->r);
  }

  if (root != NULL)
  {
    if (root->left != NULL && root->right != NULL)
      root->r_max = (root->right->r_max > root->left->r_max) ? root->right->r_max : root->left->r_max;
    else if (root->left != NULL)
      root->r_max = root->left->r_max;
    else if (root->right != NULL)
      root->r_max = root->right->r_max;
  }

  return root;
}

tree * intersect( tree *root, int l, int r )
{
  while (root != NULL && (root->l > r || root->r < l))
    root = (root->left != NULL && root->left->r_max > l) ? root->left : root->right;
  return root;
}

void inOrderTraversal( tree *root ) {
  if (root == NULL)
  {
    printf("*");
    return;
  }
  printf("%i %i(", root->l, root->r);
  inOrderTraversal(root->left);
  printf(",");
  inOrderTraversal(root->right);
  printf(")");
}

int main( void )
{
  tree *root = NULL;
  int l = 12, r = 36;
  int delete_l = 15, delete_r = 20;
  tree *intersectNode;

  root = insert(root, 5, 10);
  root = insert(root, 15, 20);
  root = insert(root, 25, 30);
  root = insert(root, 35, 40);

  printf("Original tree: ");
  inOrderTraversal(root);
  printf("\n");

  intersectNode = intersect(root, l, r);

  printf("Segments intersecting with (%d, %d): ", l, r);
  inOrderTraversal(intersectNode);
  printf("\n");

  root = deleteNode(root, delete_l, delete_r);

  printf("Tree after deleting (%d, %d): ", delete_l, delete_r);
  inOrderTraversal(root);
  printf("\n");

  return 0;
}
