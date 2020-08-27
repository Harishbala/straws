
#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int val;
  struct Node *next;
};

struct Node *
insert_node (struct Node **current, int val)
{
  if (current)
    {
      struct Node *node = malloc (sizeof (struct Node));
      node->val = val;
      node->next = NULL;
      if (*current)
	{
	  struct Node *temp = (*current)->next;
	  (*current)->next = node;
	  node->next = temp;
	}
      else
	{
	  *current = node;
	}
      return node;
    }
  return NULL;
}

void
print_list (struct Node *root)
{
  struct Node *current = root;
  while (current)
    {
      printf ("%d\n", current->val);
      current = current->next;
    }
}

struct Node *
find_node (struct Node *root, int val)
{
  struct Node *current = root;

  while (current)
    {
      if (current->val == val)
	return current;
      current = current->next;
    }
  return NULL;
}

int
delete_node (struct Node **root, int val)
{
  struct Node *current = *root;
  struct Node *prev = *root;

  while (current)
    {
      if (current->val == val)
	{
	  if (current == *root)
	    {
	      *root = current->next;
	      free (current);
	      return 1;
	    }
	  else
	    {
	      prev->next = current->next;
	      free (current);
	      return 1;
	    }
	}
      prev = current;
      current = current->next;
    }
  return 0;
}

int
main ()
{
  struct Node *root = NULL;
  struct Node *current = insert_node (&root, 1);
  current = insert_node (&current, 2);
  current = insert_node (&current, 3);
  current = insert_node (&current, 4);

  current = find_node (root, 2);
  if (current)
    {
      insert_node (&current, 0);
    }
  print_list (root);
  printf ("-------------\n");
  
  delete_node (&root, 1);  
  print_list (root);


  return 0;
}
