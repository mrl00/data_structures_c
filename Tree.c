#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree {
  size_t size;   
  void *key;    
  struct tree *left, *right;
  int (*compare_key)(void*, void*);
} Tree;

Tree *init_tree(void *value, int (*compare)(void*, void*)) {
  Tree *root = 
    (Tree*) calloc(1, sizeof(Tree));
  root->left = root->right = NULL;
  root->size = 
    value == NULL ? 0 : 1; 
  root->key = value;
  root->compare_key = compare;
  return root;
}

void detroy_tree(Tree *root) {}
void insert(Tree* root, void *key) {
  root->size++;
  if(root->key == NULL) {
    root->key = key;
    return;
  }
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

