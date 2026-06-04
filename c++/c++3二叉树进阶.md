# c++二叉树进阶

下面是这份 **《Lesson03--二叉树进阶》** 的学习总结。核心内容是：**二叉搜索树 BST 的概念、查找/插入/删除、应用场景、性能分析，以及一些二叉树进阶面试题**。

------

# 一、本节主要讲什么？

这节课叫“二叉树进阶”，不是重新讲普通二叉树，而是围绕 **二叉搜索树 BST** 做铺垫。

它的作用主要有两个：

1. 为后面学习 `map` 和 `set` 做准备。
2. 总结一些稍难的二叉树面试题。

因为 `map` 和 `set` 底层通常和搜索树结构有关，理解二叉搜索树之后，再学红黑树、`map`、`set` 会更顺。

------

# 二、二叉搜索树 BST 的概念

**二叉搜索树**又叫：

```cpp
二叉排序树
Binary Search Tree
BST
```

它满足三个性质：

```cpp
1. 左子树所有节点的值 < 根节点的值
2. 右子树所有节点的值 > 根节点的值
3. 左右子树本身也都是二叉搜索树
```

例如插入：

```cpp
int a[] = {5, 3, 4, 1, 7, 8, 2, 6, 0, 9};
```

可以形成一棵满足左小右大的搜索树。

你可以记成一句话：

> 二叉搜索树的核心规则：左边比我小，右边比我大。

------

# 三、二叉搜索树的查找

查找过程很简单：

```cpp
从根节点开始比较
```

假设要查找 `key`：

```cpp
if key == root->_data
    找到了
else if key < root->_data
    去左子树找
else
    去右子树找
```

直到找到目标节点，或者走到 `nullptr`，说明不存在。

伪代码：

```cpp
Node* Find(const T& key)
{
    Node* cur = _root;

    while (cur)
    {
        if (key < cur->_data)
            cur = cur->_left;
        else if (key > cur->_data)
            cur = cur->_right;
        else
            return cur;
    }

    return nullptr;
}
```

查找的本质就是：

```cpp
每比较一次，就排除一边子树
```

所以如果树比较平衡，效率会很高。

------

# 四、二叉搜索树的插入

插入分两种情况。

## 1. 空树

如果树为空，直接让新节点成为根节点：

```cpp
_root = new Node(data);
```

## 2. 非空树

从根开始，根据 BST 性质找插入位置：

```cpp
data < cur->_data  去左边
data > cur->_data  去右边
data == cur->_data 插入失败
```

一般二叉搜索树不允许插入重复值。

插入时需要记录父节点 `parent`，因为新节点最后要挂到父节点的左孩子或者右孩子上：

```cpp
if (data < parent->_data)
    parent->_left = newNode;
else
    parent->_right = newNode;
```

核心逻辑：

```cpp
bool Insert(const T& data)
{
    if (_root == nullptr)
    {
        _root = new Node(data);
        return true;
    }

    Node* cur = _root;
    Node* parent = nullptr;

    while (cur)
    {
        parent = cur;

        if (data < cur->_data)
            cur = cur->_left;
        else if (data > cur->_data)
            cur = cur->_right;
        else
            return false;
    }

    cur = new Node(data);

    if (data < parent->_data)
        parent->_left = cur;
    else
        parent->_right = cur;

    return true;
}
```

------

# 五、二叉搜索树的删除

删除是 BST 中最难的操作。

删除前，先查找目标值是否存在。如果不存在，直接返回 `false`。

找到之后，删除节点主要分三大类。

------

## 情况一：要删除的节点没有右孩子

也就是：

```cpp
cur->_right == nullptr
```

这种情况包括：

```cpp
1. cur 没有孩子
2. cur 只有左孩子
```

处理方法：

```cpp
让父节点指向 cur 的左孩子
```

如果删除的是根节点，则：

```cpp
_root = cur->_left;
```

------

## 情况二：要删除的节点没有左孩子

也就是：

```cpp
cur->_left == nullptr
```

这种情况包括：

```cpp
1. cur 只有右孩子
```

处理方法：

```cpp
让父节点指向 cur 的右孩子
```

如果删除的是根节点，则：

```cpp
_root = cur->_right;
```

------

## 情况三：左右孩子都存在

这是最复杂的情况。

不能直接删除，因为删除后左右子树不好重新连接。

常用方法是找一个“替代节点”。

替代节点有两种选法：

```cpp
1. 左子树中的最大节点
2. 右子树中的最小节点
```

课件里重点提到的是：

```cpp
找右子树中的最小节点
```

因为右子树中的最小节点，一定比左子树所有节点大，又比右子树其他节点小，适合替代当前节点。

处理步骤：

```cpp
1. 找到右子树中最小节点
2. 用它的值覆盖待删除节点
3. 再删除那个替代节点
```

举例：

```cpp
        5
      /   \
     3     7
          / \
         6   8
```

如果删除 `5`，可以找右子树最小节点 `6`，让 `6` 替代 `5`。

------

# 六、二叉搜索树的代码结构

课件中给出的节点结构大致是：

```cpp
template<class T>
struct BSTNode
{
    BSTNode(const T& data = T())
        : _pLeft(nullptr)
        , _pRight(nullptr)
        , _data(data)
    {}

    BSTNode<T>* _pLeft;
    BSTNode<T>* _pRight;
    T _data;
};
```

树结构：

```cpp
template<class T>
class BSTree
{
    typedef BSTNode<T> Node;
    typedef Node* PNode;

public:
    BSTree()
        : _pRoot(nullptr)
    {}

    ~BSTree();

    PNode Find(const T& data);
    bool Insert(const T& data);
    bool Erase(const T& data);

private:
    PNode _pRoot;
};
```

这里重点掌握：

```cpp
_pRoot 表示整棵树的根节点
Find 负责查找
Insert 负责插入
Erase 负责删除
```

------

# 七、二叉搜索树的应用

课件中讲了两个模型。

------

## 1. K 模型

K 模型就是：

```cpp
只存 key
```

例如：判断一个单词是否拼写正确。

可以把词库中的所有单词作为 `key` 插入 BST。

查询时：

```cpp
如果单词存在，说明拼写正确
如果单词不存在，说明拼写错误
```

类似：

```cpp
BSTree<string> dict;
```

------

## 2. KV 模型

KV 模型就是：

```cpp
key-value 键值对
```

例如：

```cpp
<word, chinese>
```

表示英文单词和中文解释。

或者：

```cpp
<word, count>
```

表示单词和出现次数。

这种结构就很像 `map`：

```cpp
map<string, string> dict;
map<string, int> countMap;
```

注意：KV 模型中，比较大小时主要比较 `key`，不是比较 `value`。

节点结构可以设计成：

```cpp
template<class K, class V>
struct BSTNode
{
    BSTNode(const K& key = K(), const V& value = V())
        : _left(nullptr)
        , _right(nullptr)
        , _key(key)
        , _value(value)
    {}

    BSTNode<K, V>* _left;
    BSTNode<K, V>* _right;
    K _key;
    V _value;
};
```

------

# 八、二叉搜索树的性能分析

BST 的查找、插入、删除，本质都依赖查找。

所以它们的效率主要取决于树的高度。

## 最优情况

如果 BST 接近完全二叉树：

```cpp
时间复杂度：O(logN)
```

例如：

```cpp
        6
      /   \
     4     8
    / \   / \
   3   5 7   9
```

这种结构比较平衡，查找效率高。

------

## 最差情况

如果插入数据本身有序，比如：

```cpp
3 4 5 6 7 8 9
```

BST 可能退化成单支树：

```cpp
3
 \
  4
   \
    5
     \
      6
       \
        7
         \
          8
           \
            9
```

这时候查找效率就退化成：

```cpp
时间复杂度：O(N)
```

这和链表差不多，BST 的优势就没了。

所以后面才会引出：

```cpp
AVL树
红黑树
```

它们的目的就是：

> 让搜索树尽量保持平衡，避免退化成单支树。

------

# 九、课件最后列出的二叉树进阶面试题

课件最后列了 10 个经典题目：

```cpp
1. 二叉树创建字符串
2. 二叉树的分层遍历 1
3. 二叉树的分层遍历 2
4. 二叉树最近公共祖先
5. 二叉搜索树转换成排序双向链表
6. 根据前序和中序构造二叉树
7. 根据中序和后序构造二叉树
8. 二叉树前序遍历非递归
9. 二叉树中序遍历非递归
10. 二叉树后序遍历非递归
```

这些题基本覆盖了二叉树面试中的核心内容。

其中比较重要的是：

```cpp
层序遍历
最近公共祖先
前中序建树
中后序建树
非递归遍历
BST 转双向链表
```

------

# 十、这节课你应该重点掌握什么？

按照重要程度排序：

```cpp
1. 二叉搜索树的性质：左小右大
2. BST 的查找过程
3. BST 的插入过程
4. BST 的删除过程，尤其是左右孩子都存在的情况
5. BST 的 K 模型和 KV 模型
6. BST 的性能分析：最好 O(logN)，最坏 O(N)
7. 为什么需要 AVL 树和红黑树
```

------

