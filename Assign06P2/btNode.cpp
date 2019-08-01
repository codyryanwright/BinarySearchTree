// NAME: Cody Wright
// DATE: 4/3/2019
// LAST MODIFIED: 4/3/2019
// FILE: btNode.cpp
// ABSTRACT: A practice program for implementing recursive and iterative
//           methods for a binary search tree
#include "btNode.h"

void dumpToArrayInOrder(btNode* bst_root, int* dumpArray)
{
   if (bst_root == 0) return;
   int dumpIndex = 0;
   dumpToArrayInOrderAux(bst_root, dumpArray, dumpIndex);
}

void dumpToArrayInOrderAux(btNode* bst_root, int* dumpArray, int& dumpIndex)
{
   if (bst_root == 0) return;
   dumpToArrayInOrderAux(bst_root->left, dumpArray, dumpIndex);
   dumpArray[dumpIndex++] = bst_root->data;
   dumpToArrayInOrderAux(bst_root->right, dumpArray, dumpIndex);
}

void tree_clear(btNode*& root)
{
   if (root == 0) return;
   tree_clear(root->left);
   tree_clear(root->right);
   delete root;
   root = 0;
}

int bst_size(btNode* bst_root)
{
   if (bst_root == 0) return 0;
   return 1 + bst_size(bst_root->left) + bst_size(bst_root->right);
}

void bst_insert(btNode*& root, int insInt)
{
   if (root == 0)
   {
      root = new btNode;
      root->data = insInt;
      root->left = root->right = 0;
      return;
   }

   btNode* cursor = root;

   while (cursor)
   {
      if (cursor->data == insInt)
      {
         cursor->data = insInt;
         break;
      }

      if (cursor->data > insInt)
      {
         if (cursor->left == 0)
         {
            cursor->left = new btNode;
            cursor->left->data = insInt;
            cursor->left->left = cursor->left->right = 0;
            break;
         }
         else cursor = cursor->left;
      }
      else if (cursor->data < insInt)
      {
         if (cursor->right == 0)
         {
            cursor->right = new btNode;
            cursor->right->data = insInt;
            cursor->right->left = cursor->right->right = 0;
            break;
         }
         else cursor = cursor->right;
      }
   }
}

bool bst_remove(btNode*& root, const int remInt)
{
   if (root == 0)
      return false;
   if (root->data > remInt)
      return bst_remove(root->left, remInt);
   if (root->data < remInt)
      return bst_remove(root->right, remInt);
   else if (root->left == 0 || root->right == 0)
   {
      btNode* old_root = root;
      if (root->left == 0 && root->right == 0)
         root = 0;
      else if (root->left == 0)
         root = root->right;
      else if (root->right == 0)
         root = root->left;
      delete old_root;
   }
   else
      bst_remove_max(root->left, root->data);

   return true;
}

void bst_remove_max(btNode*& root, int& removed)
{
   if(root->right == 0)
   {
      removed = root->data;
      btNode* old_root = root;
      root = root->left;
      delete old_root;
   }
   else bst_remove_max(root->right, removed);
}
