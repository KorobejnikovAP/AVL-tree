#pragma once

#include <iostream>
#include <iomanip>

struct Node {
	int key;
	unsigned char height;
	Node* left;
	Node* right;
	Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

unsigned char height(Node* p)
{
	return p ? p->height : 0;
}

int bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(Node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateright(Node* p) // правый поворот вокруг p
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Node* rotateleft(Node* q) // левый поворот вокруг q
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

Node* balance(Node* p) // балансировка узла p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

Node* insert(Node* p, int k) // вставка ключа k в дерево с корнем p
{
	if (!p) return new Node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

Node* findmin(Node* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left ? findmin(p->left) : p;
}

Node* removemin(Node* p) // удаление узла с минимальным ключом из дерева p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

Node* remove(Node* p, int k) // удаление ключа k из дерева p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		Node* q = p->left;
		Node* r = p->right;
		delete p;
		if (!r) return q;
		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void print(std::ostream& o, Node* p, int indent)
{
	if (p != NULL) {
		if (p->right) {
			print(o, p->right, indent + 4);
		}
		if (indent) {
			o << std::setw(indent) << ' ';
		}
		if (p->right) o << " /\n" << std::setw(indent) << ' ';
		o << p->key << "\n ";
		if (p->left) {
			o << std::setw(indent) << ' ' << " \\\n";
			print(o, p->left, indent + 4);
		}
	}
}




class AVL {
	Node* root;

public:
	AVL(int k) {
		root = new Node(k);
	}

	void add(int k) {
		root = insert(root, k);
	}

	void del(int k) {
		root = remove(root, k);
	}

	friend std::ostream& operator<<(std::ostream& o, AVL& _t)
	{
		print(o, _t.root, 0);
		return o;
	}
};