#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

//Структуры

struct Node 
{
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) 
    {
        this->data = data;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
};

struct Compare 
{
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

//Процедура кодирования

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) 
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) 
    {
        huffmanCode[root->data] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

//Процедура раскодирования

void decode(Node* root, int& index, string str) 
{
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        cout << root->data;
        return;
    }

    index++;

    if (str[index] == '0')
        decode(root->left, index, str);
    else
        decode(root->right, index, str);
}

//Построение дерева Хаффмана

void buildHuffmanTree(string text) 
{
    unordered_map<char, int> frequencies;
    for (char c : text) 
    {
        frequencies[c]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : frequencies) 
    {
        Node* newNode = new Node(pair.first, pair.second);
        pq.push(newNode);
    }

    while (pq.size() > 1) 
    {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        Node* newNode = new Node('#', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Закодированные символы:" << endl;
    for (auto pair : huffmanCode) 
    {
        cout << pair.first << " : " << pair.second << endl;
    }

    cout << "Первоначальный текст: " << text << endl;

    string encodedText;
    for (char c : text) 
    {
        encodedText += huffmanCode[c];
    }
    cout << "Закодированный текст: " << encodedText << endl;

    cout << "Раскодированный текст: ";
    if (root == nullptr) 
    {
        cout << "Дерево Хаффмана не было построено";
    }
    else {
        int index = -1;
        while (index < (int)encodedText.size() - 2) 
        {
            decode(root, index, encodedText);
        }
    }
    delete root;
}

int main() {
    setlocale(LC_ALL, "Russian");
    string text = "Лабораторная 7";
    buildHuffmanTree(text);

    return 0;
}