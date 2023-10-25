// C++ code
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <iomanip>
using namespace std;

class BST;
class TreeNode{
private:
    TreeNode *leftchild;
    TreeNode *rightchild;
    TreeNode *parent;
    int key;
    string element;
public:
    TreeNode():leftchild(0),rightchild(0),parent(0),key(0),element(""){};
    TreeNode(int a, string b):leftchild(0),rightchild(0),parent(0),key(a),element(b){};

    int GetKey(){return key;}              // 為了在main()要能夠檢視node是否正確
    string GetElement(){return element;}   // 才需要這兩個member function讀取private data

    // 其餘情況, 因為class BST是class TreeNode的friend class
    // 在class BST的member function中, 可以直接存取class TreeNode的private data

    friend class BST;   // 放在 private 或 public 都可以
};

class BST{
private:
    TreeNode *root;
    TreeNode* Leftmost(TreeNode *current);
    TreeNode* Successor(TreeNode *current);

public:
    BST():root(0){};
    TreeNode* Search(int key);
    void InsertBST(int key, string element);
    void InorderPrint();
    void PrintTree(TreeNode *current, int level);   //新增的function 以列印出樹的形狀
};
TreeNode* BST::Search(int KEY){

    TreeNode *current = root;               // 將curent指向root作為traversal起點

    while (current != NULL && KEY != current->key) {  // 兩種情況跳出迴圈：
    	                                              // 1.沒找到 2.有找到
        if (KEY < current->key){
            current = current->leftchild;   // 向左走
        }
        else {
            current = current->rightchild;  // 向右走
        }
    }
    return current;
}
void BST::InsertBST(int key, string element){

    TreeNode *y = 0;        // 準新手爸媽
    TreeNode *x = 0;        // 哨兵
    TreeNode *insert_node = new TreeNode(key, element);

    x = root;
    while (x != NULL) {                // 在while中, 以如同Search()的方式尋找適當的位置
        y = x;
        if (insert_node->key < x->key){
            x = x->leftchild;
        }
        else{
            x = x->rightchild;
        }
    }                                  // 跳出迴圈後, x即為NULL
                                       // y即為insert_node的parent
    insert_node->parent = y;           // 將insert_node的parent pointer指向y

    if (y == NULL){                    // 下面一組if-else, 把insert_node接上BST
        this->root = insert_node;
    }
    else if (insert_node->key < y->key){
        y->leftchild = insert_node;
    }
    else{
        y->rightchild = insert_node; 
    }
}
TreeNode* BST::Leftmost(TreeNode *current){

    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}
TreeNode* BST::Successor(TreeNode *current){

    if (current->rightchild != NULL){
        return Leftmost(current->rightchild);
    }

    TreeNode *new_node = current->parent;

    while (new_node != NULL && current == new_node->rightchild) {
        current = new_node;
        new_node = new_node->parent;
    }

    return new_node;
}
void BST::InorderPrint(){
    TreeNode *current = new TreeNode;
    current = Leftmost(root);
    while(current){
        cout << "Branch " << current->element << "'s profit: " << current->key << endl;  //按照格式輸出
        current = Successor(current);
    }
}

void BST::PrintTree(TreeNode *current, int level){  
    if (current != NULL) {                                        // if current != NULL 用preorder 
        for (int i = 1; i < level; i++) {
        cout << "\t";                                             //透過counter每做一次就+1 控制要印幾個"\t"(8個空白)
        //cout << setw(10*i);
        }                                                               
        cout << current->element << " " << current->key << endl; //按照格式輸出
        PrintTree(current->leftchild, level+1);       // L遞迴
        PrintTree(current->rightchild, level+1);      // R遞迴
        
    }    
}

int main(){
    BST T;                                                    //二元搜尋樹物件
    ifstream in;
    ofstream out;                                             //建立檔案相關物件
    in.open("profit.txt");                                    //開啟讀取檔案
    string a;
    int b, c;
    cout << "\nReading data(profit.txt)....." << endl;
    while(!in.eof()){                                         //只要還沒讀到完，條件成立就繼續一直讀
        in >> a >> b >> c;                                    //傳入檔案內的資料並依照讀取順序輸出
        cout << "Branch " << a << "'s profit: " << c-b <<endl;
        T.InsertBST(c-b, a);                                  //將檔案內資料插入進二元搜尋樹
    }
out.close();                                                  //關檔


    cout << "\nThe shape of the tree:\n";
    TreeNode *node = T.Search(29);
    T.PrintTree(node,1);                                      //輸出樹的形狀(從level 1開始) 
    cout << "\nAfter Inorder Traversal:\n";
    T.InorderPrint();                                         //inorder 結果(由小到大排列)


    return 0;
};
