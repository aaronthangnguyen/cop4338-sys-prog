#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct t_node
{
  int value;
  struct t_node *left;
  struct t_node *right;
};
typedef struct t_node t_node;

void insert(t_node **root_p, int value)
{
  if (*root_p == NULL)
  {
    *root_p = malloc(sizeof(t_node));
    (*root_p)->value = value;
    (*root_p)->left = (*root_p)->right = NULL;
  }

  if (value == (*root_p)->value)
  {
    return;
  }
  else if (value < (*root_p)->value)
  {
    insert(&((*root_p)->left), value);
  }
  else
  {
    insert(&((*root_p)->right), value);
  }
}

void print_inorder(t_node *root)
{
  if (root == NULL)
  {
    return;
  }
  print_inorder(root->left);
  printf("%c", root->value);
  print_inorder(root->right);
}

void insert_string(t_node **root, char *string)
{
  for (int i = 0; i < strlen(string); i++)
  {
    insert(root, string[i]);
  }
}

void print_unique_alphabetical(t_node *root)
{
  print_inorder(root);
  printf("\n");
}

void free_bst_helper(t_node *root)
{
  if (root == NULL)
  {
    return;
  }
  free_bst_helper(root->left);
  free_bst_helper(root->right);
  free(root);
}

void free_bst(t_node **bst)
{
  free_bst_helper(*bst);
  free(bst);
}

int main(void)
{
  t_node **bst = malloc(sizeof(t_node *));
  insert_string(bst, "hello world");
  print_unique_alphabetical(*bst);
  free_bst(bst);
  return 0;
}
