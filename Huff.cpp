// C++ program to encode and decode a string using
// Huffman Coding.
#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;
 
// to strore the corresponding huffman representation of the character
map<char, string> codes;
 
// To store the frequency of character of the input string
map<char, int> freq;
 
// A Huffman tree node
struct MinHeapNode {
    char data; // One of the input characters
    int freq; // Frequency of the character
    MinHeapNode *left, *right; // Left and right child
 
    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
 
// utility function for the priority queue
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};
 
// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, string str)
{
    if (!root)
        return;
        
    // when we reached to the leaf node we store the huffman code for the correseponding character
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode* root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}
 
// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare>
    minHeap;
 
// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct MinHeapNode *left, *right, *top;
    
    // creating the leaf nodes of the huffman-tree
    for (auto v: freq)
        minHeap.push(new MinHeapNode(v.first, v.second)); // here we are creating the node and pusing it into the minheap and the min heap will make sure that the node are all arranged in small to big order
    while (minHeap.size() != 1) {
    	// we are taking out the top two elements prsent in the min heap 
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        
        // we are creating the node by adding the frequencies of the top two min elements of the minheap
        top = new MinHeapNode('$',left->freq + right->freq);
        
    	// now we are making the links and in this way we genetrate the huffman tree
        top->left = left;
        top->right = right;
        
        // again we push the created new node into the min heap so that it will be also considered in the process of making the tree in the next iteration
        minHeap.push(top);
    }
    // till now we have generated the tree 
    // now we will store the huffamn representation the characters 
    storeCodes(minHeap.top(), "");
}
 
// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}
 
// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;
 
        // reached leaf node
        if (curr->left == NULL and curr->right == NULL) {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans + '\0';
}

string toBinary(int n, int len)
{
    string binary;
    for (unsigned i = (1 << len - 1); i > 0; i = i / 2) {
        binary += (n & i) ? "1" : "0";
    }
 
    return binary;
}
 
// Driver code
int main()
{
    string str;
    cout<<"Enter the string of your choice"<<endl;
    getline(cin,str);
    
    
    calcFreq(str, str.length());
    
    cout<<"The encoded message as per ASCII representation will be"<<endl;
    
    int cnt=0;
    
    for(auto i:str)
    {
        int n = 20;
        int len = 32;
 
        string curr = toBinary(n, len);
        cout<<curr;
        cnt+=curr.size();
    }
    
    cout<<"\nThe size of the above mentioned ASCII encoded message is ";
    
    cout<<"\n"<<cnt*2<<endl;
    
    //generating the huffan codes basig on the optimal merge pattern
    HuffmanCodes(str.length());
    
    cout << "The variable length encodings of the characters in the string that you have given are:\n";
    
    for (auto v = codes.begin(); v != codes.end(); v++)
        cout << v->first << ' ' << v->second << endl;
        
    string encodedString, decodedString;
    
    for (auto i : str)
        encodedString += codes[i];
    
 
    cout << "\nEncoded Huffman data:\n"
         << encodedString << endl;
    
    cout<<"The size of the encoded Huffman data is"<<endl;
    cout<<encodedString.size()*2<<endl;
 
      // Function call
    decodedString
        = decode_file(minHeap.top(), encodedString);
    cout << "Decoded Huffman Data:\n"
         << decodedString << endl;
    return 0;
}
