// 20210105_AVLtree_cpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <ostream>

using namespace std;
#define STR_SIZE	1024
#define SPACE		6
typedef int T;
class avlNode
{
public:
	T key;                // 关键字(键值)
	int height;         // 高度
	avlNode* left;    // 左孩子
	avlNode* right;    // 右孩子

	avlNode(T value, avlNode* l, avlNode* r) :
		key(value), height(0), left(l), right(r) {}
};

class AVLTree {
private:
	avlNode* mRoot;    // 根结点
public:
	AVLTree();
	~AVLTree();

	// 获取树的高度
	int height();
	// 获取树的高度
	int max(int a, int b);

	// 前序遍历"AVL树"
	void preOrder();
	// 中序遍历"AVL树"
	void inOrder();
	// 后序遍历"AVL树"
	void postOrder();

	// (递归实现)查找"AVL树"中键值为key的节点
	avlNode* search(T key);
	// (非递归实现)查找"AVL树"中键值为key的节点
	avlNode* iterativeSearch(T key);

	// 查找最小结点：返回最小结点的键值。
	T minimum();
	// 查找最大结点：返回最大结点的键值。
	T maximum();

	// 将结点(key为节点键值)插入到AVL树中
	void insert(T key);

	//// 删除结点(key为节点键值)
	//void remove(T key);

	// 销毁AVL树
	void destroy();

	// 打印AVL树
	void print();
	//画AVL树
	void drawTree();
	
private:
	// 获取树的高度
	int height(avlNode* tree);

	// 前序遍历"AVL树"
	void preOrder(avlNode* tree) const;
	// 中序遍历"AVL树"
	void inOrder(avlNode* tree) const;
	// 后序遍历"AVL树"
	void postOrder(avlNode* tree) const;

	// (递归实现)查找"AVL树x"中键值为key的节点
	avlNode* search(avlNode* x, T key) const;
	// (非递归实现)查找"AVL树x"中键值为key的节点
	avlNode* iterativeSearch(avlNode* x, T key) const;

	// 查找最小结点：返回tree为根结点的AVL树的最小结点。
	avlNode* minimum(avlNode* tree);
	// 查找最大结点：返回tree为根结点的AVL树的最大结点。
	avlNode* maximum(avlNode* tree);

	// LL：左左对应的情况(左单旋转)。
	avlNode* RotateL(avlNode* ptr);

	// RR：右右对应的情况(右单旋转)。
	avlNode* RotateR(avlNode* k3);

	// LR：左右对应的情况(左双旋转)。
	avlNode* RotateLR(avlNode* k3);

	// RL：右左对应的情况(右双旋转)。
	avlNode* RotateRL(avlNode* k1);

	// 将结点(z)插入到AVL树(tree)中
	avlNode* insert(avlNode*& tree, T key);

	//// 删除AVL树(tree)中的结点(z)，并返回被删除的结点
	//avlNode* remove(avlNode*& tree, avlNode* z);

	// 销毁AVL树
	void destroy(avlNode*& tree);

	// 打印AVL树
	void print(avlNode* tree, T key, int direction);


	/*****************************************************************************/
	void draw_level(avlNode* root, bool left, char* str);
	void draw(avlNode* root);

};
/*构造函数*/
AVLTree::AVLTree() :mRoot(NULL)
{

}
/*析构函数*/
AVLTree::~AVLTree()
{
	destroy(mRoot);
}

/*获取树的高度*/
int AVLTree::height(avlNode* tree)
{
	if (tree != NULL)
		return tree->height;

	return 0;
}
int AVLTree::height()
{
	return height(mRoot);
}
/*比较两个值的大小 */
int AVLTree::max(int a, int b)
{
	return a > b ? a : b;
}





/*前序遍历"AVL树"*/

void AVLTree::preOrder(avlNode* tree) const
{
	if (tree != NULL)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}
void AVLTree::preOrder()
{
	preOrder(mRoot);
}

/*中序遍历"AVL树"*/
void AVLTree::inOrder(avlNode* tree) const
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}
void AVLTree::inOrder()
{
	inOrder(mRoot);
}

/*后序遍历"AVL树"*/
void AVLTree::postOrder(avlNode* tree) const
{
	if (tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}
void AVLTree::postOrder()
{
	postOrder(mRoot);
}

/*(递归实现)查找"AVL树x"中键值为key的节点*/
avlNode* AVLTree::search(avlNode* x, T key) const
{
	if (x == NULL || x->key == key)
		return x;

	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}
avlNode* AVLTree::search(T key)
{
	return search(mRoot, key);
}

/*(非递归实现)查找"AVL树x"中键值为key的节点*/
avlNode* AVLTree::iterativeSearch(avlNode* x, T key) const
{
	while ((x != NULL) && (x->key != key))
	{
		if (key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	return x;
}
avlNode* AVLTree::iterativeSearch(T key)
{
	return iterativeSearch(mRoot, key);
}

/*查找最小结点：返回tree为根结点的AVL树的最小结点。*/
avlNode* AVLTree::minimum(avlNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;
	return tree;
}
T AVLTree::minimum()
{
	avlNode* p = minimum(mRoot);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}

/*查找最大结点：返回tree为根结点的AVL树的最大结点。*/

avlNode* AVLTree::maximum(avlNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;
	return tree;
}
T AVLTree::maximum()
{
	avlNode* p = maximum(mRoot);
	if (p != NULL)
		return p->key;
	return (T)NULL;
}


/*
 * RotateL：左左对应的情况(左单旋转)。
 * 返回值：旋转后的根节点
 */
avlNode* AVLTree::RotateL(avlNode* ptr)
{
	avlNode* k1;

	k1 = ptr->left;
	ptr->left = k1->right;
	k1->right = ptr;

	ptr->height = max(height(ptr->left), height(ptr->right)) + 1;
	k1->height = max(height(k1->left), ptr->height) + 1;

	return k1;
}
/*
 * RotateR：右右对应的情况(右单旋转)。
 * 返回值：旋转后的根节点
 */
avlNode* AVLTree::RotateR(avlNode* k1)
{
	avlNode* k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;

	return k2;
}
/*
 * RotateLR：左右对应的情况(左双旋转)。
 * 返回值：旋转后的根节点
 */
avlNode* AVLTree::RotateLR(avlNode* k3)
{
	k3->left = RotateR(k3->left);

	return RotateL(k3);
}
/*
 * RotateRL：右左对应的情况(右双旋转)。
 * 返回值：旋转后的根节点
 */
avlNode* AVLTree::RotateRL(avlNode* k1)
{
	k1->right = RotateL(k1->right);

	return RotateR(k1);
}
/*
 * 将结点插入到AVL树中，并返回根节点
 * 参数说明：
 *     tree AVL树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
avlNode* AVLTree::insert(avlNode*& tree, T key)
{
	if (tree == NULL)
	{
		// 新建节点
		tree = new avlNode(key, NULL, NULL);
		if (tree == NULL)
		{
			cerr << "ERROR: create avltree node failed!" << endl;
			return NULL;
		}
	}
	else if (key < tree->key) // 应该将key插入到"tree的左子树"的情况
	{
		tree->left = insert(tree->left, key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (height(tree->left) - height(tree->right) == 2)
		{
			if (key < tree->left->key)
				tree = RotateL(tree);
			else
				tree = RotateLR(tree);
		}
	}
	else if (key > tree->key) // 应该将key插入到"tree的右子树"的情况
	{
		tree->right = insert(tree->right, key);
		// 插入节点后，若AVL树失去平衡，则进行相应的调节。
		if (height(tree->right) - height(tree->left) == 2)
		{
			if (key > tree->right->key)
				tree = RotateR(tree);
			else
				tree = RotateRL(tree);
		}
	}
	else //key == tree->key)
	{
		cerr << "添加失败：不允许添加相同的节点！" << endl;
	}

	tree->height = max(height(tree->left), height(tree->right)) + 1;

	return tree;
}
void AVLTree::insert(T key)
{
	insert(mRoot, key);
}

/*
 * 销毁AVL树
 */
void AVLTree::destroy(avlNode*& tree)
{
	if (tree == NULL)
		return;

	if (tree->left != NULL)
		destroy(tree->left);
	if (tree->right != NULL)
		destroy(tree->right);

	delete tree;
}
void AVLTree::destroy()
{
	destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
void AVLTree::print(avlNode* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->key << " is root" << endl;
		else                // tree是分支节点
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}
void AVLTree::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}

/*画树*/
/*****************************************************************************
* @data  : 2020/11/16
* @brief : 水平画树
* @input :
*   root: 树
*	left: 判断左右
*	str : 可变字符串
* @output:
*   none: none
*****************************************************************************/
void AVLTree::draw_level(avlNode* root, bool left, char* str) {
	if (root->right) {
		draw_level(root->right, false, strcat(str, (left ? "|     " : "      ")));
	}
	cout << str;
	cout << (left ? '\\' : '/');
	cout << "-----";
	cout << root->key << endl;
	if (root->left) {
		draw_level(root->left, true, strcat(str, (left ? "      " : "|     ")));
	}
	str[strlen(str) - SPACE] = '\0';
}
/*****************************************************************************
* @data  : 2020/11/16
* @brief : 根节点画树
* @input :
*   root : 树
* @output:
*   none : none
*****************************************************************************/
void AVLTree::draw(avlNode* root) {

	char str[STR_SIZE];
	memset(str, '\0', STR_SIZE);

	if (root->right) {
		draw_level(root->right, false, str);
	}
	cout << root->key << endl;
	if (root->left) {
		draw_level(root->left, true, str);
	}
}
void AVLTree::drawTree()
{
	if (mRoot != NULL)
		draw(mRoot);
}


/**
 * C++语言: AVL树
 */
//static int arr[] = { 16 ,3 ,7 ,11 ,9 ,26 ,18 ,14 ,15 };
//#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

 void exe1()
 {
     fstream inAVL("inAVL.txt", ios::in);
     if (!inAVL) { 
         cerr << "文件inAVL打开有错.\n" << endl;
         exit(1);
     }
	 /************************************************************************/
	 cout << "第一棵树的构建:\n";
	 int num1;
	 inAVL >> num1;
	 int* arr1 = new int[num1];
	 for (int i = 0; i < num1; i++)
	 {
		 inAVL >> *(arr1 + i);
	 }
	 AVLTree* tree1 = new AVLTree();

	 cout << "添加的数目:" << num1 << "______依次添加: ";
	 for (int i = 0; i < num1; i++)
	 {
		 cout << arr1[i] << " ";
	 }
	 for (int i = 0; i < num1; i++)
	 {
		 cout << endl << endl;
		 tree1->insert(arr1[i]);
		 cout << "第" << i + 1 << "次插入:\n";
		 tree1->drawTree();
	 }

	 cout << "\n== 前序遍历: ";
	 tree1->preOrder();

	 cout << "\n== 中序遍历: ";
	 tree1->inOrder();

	 cout << "\n== 后序遍历: ";
	 tree1->postOrder();
	 

	 cout << "\n== 高度: " << tree1->height() << endl;
	 cout << "== 最小值: " << tree1->minimum() << endl;
	 cout << "== 最大值: " << tree1->maximum() << endl;
	 cout << "== 树的详细信息: " << endl;
	 tree1->print();
	 /**************************************************************************/
	 cout << "\n\n**********************************************************\n\n";
	 cout << "第二棵树的构建:\n";
	 int num2;
	 inAVL >> num2;
	 int* arr2 = new int[num2];
	 for (int i = 0; i < num2; i++)
	 {
		 inAVL >> *(arr2 + i);
	 }
	 AVLTree* tree2 = new AVLTree();

	 cout << "添加的数目:" << num2 << "______依次添加: ";
	 for (int i = 0; i < num2; i++)
	 {
		 cout << arr2[i] << " ";
	 }
	 for (int i = 0; i < num2; i++)
	 {
		 cout << endl << endl;
		 tree2->insert(arr2[i]);
		 cout << "第" << i + 1 << "次插入:\n";
		 tree2->drawTree();
	 }

	 cout << "\n== 前序遍历: ";
	 tree2->preOrder();

	 cout << "\n== 中序遍历: ";
	 tree2->inOrder();

	 cout << "\n== 后序遍历: ";
	 tree2->postOrder();

	 cout << "\n== 高度: " << tree2->height() << endl;
	 cout << "== 最小值: " << tree2->minimum() << endl;
	 cout << "== 最大值: " << tree2->maximum() << endl;
	 cout << "== 树的详细信息: " << endl;
	 tree2->print();

     inAVL.close(); 
 }

int main()
{

	exe1();

	return 0;
}





//bool Search(avlNode*& ptr, T key)
//{
//
//}
//void execCH7_3()
//{
//    fstream inAVL("inAVL1.txt", ios::in);
//    if (!inAVL) { 
//        cerr << "文件inAVL打开有错.\n" << endl;
//        exit(1);
//    }
//    fstream outAVL("outAVL1.txt", ios::out);
//    if (!outAVL) {
//        cerr << "文件outAVL打开有错.\n" << endl;
//        exit(1);
//    }
//    AVL avlTree;
//    cout << "\n从文件创建一棵AVL树.\n";
//    avlTree.createAVL(inAVL);
//    avlTree.outputAVL(outAVL);
//    cout << "\nAVL树：\n";
//    avlTree.displayAVL();
//    T tmpKey;
//    bool isfind;
//    for (int j = 0; j <= 1; j++)
//    {
//        cout << "\n输入一个查找的值：";
//        cin >> tmpKey;
//        isfind = avlTree.Search(tmpKey);
//        if (isfind)cout << "\n在AVL树中找到" << tmpKey << endl;
//        else cout << "\n树中没有" << tmpKey << endl;
//
//
//    }
//    inAVL.close(); outAVL.close();
//}
//bool insertNode(avlNode*& ptr,T key)
//{
//    int nodeNum;
//    int direction;
//    avlNode* tPtr;
//    avlNode* Parent = ptr;
//    avlNode* qPtr = NULL;
//    std::stack<avlNode*> Sp;
//    if (Parent == NULL)
//    {
//        tPtr = new avlNode(key);
//        if (tPtr == NULL) {
//            cerr << "\n结点空间分配失败\n";
//            exit(1);
//        }
//        nodeNum++;
//        ptr = Parent = tPtr;
//
//    }
//    else
//    {
//
//    }
//    return true;
//}