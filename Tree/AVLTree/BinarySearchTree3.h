#pragma once
// ���� Ž�� Ʈ�� ����

#include "BinaryTree3.h"

typedef BTData BSTData;

// BST�� ���� �� ����
void BSTMakeAndInit(BTreeNode** pRoot);

// ��忡 ����� ������ ��ȯ
BSTData BSTGetNodeData(BTreeNode* bst);

// BST�� ������� ������ ����(����� �������� ����)
void BSTInsert(BTreeNode** pRoot, BSTData data);

// BST�� ������� ������ Ž��
BTreeNode* BSTSearch(BTreeNode* bst, BSTData target);

// Ʈ������ ��带 �����ϰ� ���ŵ� ����� �ּ� ���� ��ȯ�Ѵ�.
BTreeNode* BSTRemove(BTreeNode** pRoot, BSTData target);

// ���� Ž�� Ʈ���� ����� ��� ����� �����͸� ����Ѵ�.
void BSTShowAll(BTreeNode* bst);