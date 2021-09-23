#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ====== START TREE ======
typedef struct tree {
  size_t size;   
  void *key;    
  struct tree *left, *right, *minimum, *maximum;
  int (*compare_key)(const void*, const void*);
} Tree;

Tree *init_tree(void *value, int (*compare)(const void*, const void*)) {
  Tree *root = (Tree*) calloc(1, sizeof(Tree));
  root->left = root->right = root->maximum = root->minimum = NULL;
  root->size = value == NULL ? 0 : 1; 
  root->key = value;
  root->compare_key = compare;
  return root;
}
/** TODO */
void detroy_tree(Tree *root) {}

/** TODO */
void delete(Tree *root, void* key) {}

void insert(Tree* root, void *key) {
  root->size++;
  if(root->key == NULL) {
    root->key = key;
    return;
  }

  if(root->minimum == NULL || root->compare_key(root->key, key) < 0)
    root->minimum = key;
  if(root->maximum == NULL || root->compare_key(root->key, key) > 0)
    root->maximum = key;

  if(root->compare_key(root->key, key) < 0) {
    if(root->left == NULL)
      root->left = init_tree(key, root->compare_key);
    else
      insert(root->left, key);
  } else if(root->compare_key(root->key, key) > 0) {
    if(root->right == NULL)
      root->right = init_tree(key, root->compare_key);
    else
      insert(root->right, key);
  } // se for igual não faz nada.
  return;
}

void* find(Tree* root, void* key) {
  if(root == NULL || key == NULL)
    return NULL;

  if(root->compare_key(root->key, key) < 0) 
    return find(root->left, key);
  else if(root->compare_key(root->key, key) > 0) 
    return find(root->right, key);
  else 
    return root->key;
}

void walk(Tree* root, void (*action)(void*)) {
  if(root == NULL) return;
  action(root->key);
  walk(root->left, action);
  walk(root->right, action);
}
// ============= END TREE =============

int main(void) {
  return EXIT_SUCCESS;
}

