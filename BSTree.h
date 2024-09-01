#pragma once
#include<iostream>
using namespace std;

template<class K>
struct BSTreeNode  //二叉搜索树
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};

template<class K>
class BSTree  //二叉搜索树
{
typedef BSTreeNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);  //创建一个节点并把key给它
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;  //树里已经有与插入值一样的数，无法插入
			}
		}

		cur = new Node(key);
		if (parent->_key < key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		return true;
	}

	bool Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//找到了，开始删除;分为如下3种情况：
				//1.左为空    2.右为空    3.左右都不为空
				if (cur->_left == nullptr)  //左为空，父亲指向我的右，删除自己
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
						}
						else
						{
							parent->_left = cur->_right;
						}
					}
					
					delete cur;
				}
				else if (cur->_right == nullptr)  //右为空，父亲指向我的左，删除自己
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}
					
				    delete cur;
				}
				else  //左右都不为空，不能直接删除，使用替换法
				{
					Node* rightMinParent = cur;
					Node* rightMin = cur->_right;
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}

					//替换(用右子树最小节点替换要删除的节点)
					cur->_key = rightMin->_key;

					//转换成了删除rightMin(rightMin是左为空，父亲指向它的右)
					if (rightMin == rightMinParent->_left)
					{
						rightMinParent->_left = rightMin->_right;
					}
					else
					{
						rightMinParent->_right = rightMin->_right;
					}

					delete rightMin;
				}

				return true;
			}
		}

		return false;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		else
		{
			//中序遍历
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};

void TestBSTree()
{
	BSTree<int> t;
	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();

	//1.叶子
	t.Erase(2);
	t.InOrder();
	//2.左或右为空
	t.Erase(8);
	t.Erase(1);
	t.InOrder();
	//3.左右都不为空
	t.Erase(5);
	t.InOrder();
	//4.全部删除
	for (auto e : a)
	{
		t.Erase(e);
		t.InOrder();
	}
}