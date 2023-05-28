#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include<windows.h>
using namespace std;
// Reading stopping word from file and storing in vector
std::vector<string> vector_word()
{
    fstream file;
    string line;
    vector<string> stop_word;
    file.open("word.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line, '\n');
        stop_word.push_back(line);
    }
    file.close();
    return stop_word;
}
// node
class node
{
public:
    string review;
    node *next;
    node()
    {
        review = " ";
        next = NULL;
    }
    node(string r)
    {
        review = r;
        next = NULL;
    }
    string get_review()
    {
        return review;
    }
    void set_review(string r)
    {
        review = r;
    }
    ~node()
    {
        delete next;
    }
};
// linklist
class linklist
{
public:
    node *head;
    long double no; // number of review
    linklist()
    {
        head = NULL;
        no = 0;
    }
    void addnode(node *n)
    {
        node *temp = head;
        if (temp == NULL)
        {
            head = n;
            no = no + 1;
        }
        else
        {

            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = n;
            no = no + 1;
        }
    }
    void print_node()
    {
        node *n = head;
        int i = 0, a = 0;
        for (n = head; n != NULL; n = n->next)
        {
            cout << n->get_review() << endl;
        }
    }
    ~linklist()
    {
        delete head;
    }
};
// mapping class
class mapping
{
public:
    map<string, long double> pos_review;
    map<string, long double> neg_review;
    mapping() {}
    void mapping_review(linklist *negative, linklist *positive)
    {
        cout << "\n                  LOADING....";
        int len;
        vector<string> stop_word = vector_word();
        int n = 0, a = 0, flag = 0, k = 0;
        string line;
        // int w=0;
        node *temp = NULL;
        for (temp = negative->head; temp != NULL; temp = temp->next)
        {
            line = temp->get_review();
            len=line.size();
            for (int i = 0; line[i] != '\0'; i++)
            {
                
                string ch;
                for (int b = 0; line[i] != 32 && line[i]!='\0'; b++)
                {
                    ch = ch + line[i];
                    i++;
                }
                flag = 0;
                for (auto j = stop_word.begin(); j < stop_word.end(); j++)
                {
                    if (ch == *j)
                    {
                        flag += 1;
                    }
                }
                if (flag == 0)
                {
                    if (neg_review[ch] < 0)
                    {
                        neg_review.insert(pair<string, long double>(ch, 1));
                    }
                    else
                    {

                        a = neg_review[ch];
                        neg_review[ch] = a + 1;
                    }
                }
            }
        }
        iterate_neg(negative->no);
        system("cls");
       cout << "\n                  WAIT FOR A WHILE....";
       // cout << "\nmapping_pos\n";
        for (temp = positive->head; temp != NULL; temp = temp->next)
        {
            line = temp->get_review();
            len=line.size();
            for (int i = 0; line[i] != '\0'; i++)
            {
                string ch;
                for (int b = 0; line[i] != 32 && line[i]!='\0'; b++)
                {
                    ch = ch + line[i];
                    i++;
                }
                flag = 0;
                for (auto j = stop_word.begin(); j < stop_word.end(); j++)
                {
                    if (ch == *j)
                    {
                        flag += 1;
                    }
                }
                if (flag == 0)
                {
                    if (pos_review[ch] < 0)
                    {
                        pos_review.insert(pair<string, long double>(ch, 1));
                    }
                    else
                    {

                        a = pos_review[ch];
                        pos_review[ch] = a + 1;
                    }
                }
            }
        }
        system("cls");
        cout << "\n                  SORRY FOR YOUR INCONVIENCE BUT THE DATA IS BIG....";
        cout << pos_review.size();
        iterate_pos(positive->no);

        return;
    }
    void iterate_pos(long double no)
    {
        system("cls");
        cout << "\n                  LOADING";
        string line;
        map<string, long double>::iterator itr;
        for (itr = pos_review.begin(); itr != pos_review.end(); itr++)
        {
            line = itr->first;
            pos_review[line] = pos_review[line] / no;
        }
    }
    void iterate_neg(long double no)
    {
        cout << "\niterate neg";
        string line;
        map<string, long double>::iterator itr;
        for (itr = neg_review.begin(); itr != neg_review.end(); itr++)
        {
            line = itr->first;
            neg_review[line] = neg_review[line] / no;
        }
    }
    ~mapping() {}
};
class node_tree
{
public:
    string data;
    node_tree *r, *l;
    node_tree()
    {
        data = " ";
        r = NULL;
        l = NULL;
    }
    node_tree(string d)
    {
        data = d;
        r = NULL;
        l = NULL;
    }
    ~node_tree()
    {
        delete r;
        delete l;
    }
};
class BST
{
public:
    node_tree *root;
    BST()
    {
        root = NULL;
    }
    void add_node(string ch)
    {
        node_tree *n = new node_tree(ch);
        int flag = 0;
        node_tree *temp = root;
        vector<string> stop_word = vector_word();
        if (root == NULL)
        {
            for (auto j = stop_word.begin(); j < stop_word.end(); j++)
            {
                if (n->data == *j)
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                return;
            }
            else
            {
                root = n;
            }
        }
        else
        {
            flag = 0;
            for (auto j = stop_word.begin(); j < stop_word.end(); j++)
            {
                if (n->data == *j)
                {
                    flag = 1;
                    break;
                }
            }
            temp = root;
            if (flag == 1)
            {
                while (temp->l != NULL)
                {
                    temp = temp->l;
                }
                temp->l = n;
            }
            else if (flag == 0)
            {
                while (temp->r != NULL)
                {
                    temp = temp->r;
                }
                temp->r = n;
            }
        }
    }
    ~BST()
    {
        delete root;
    }
};
void drawing(long double totalp,long double totaln){
    long double perp=totalp*100;
    long double pern=totaln*100;
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    cout<<"\n******Positivity percentage******\n       "<<perp<<"%";
    cout<<"\n******Negativity percentage******\n       "<<pern<<"%";
    int line=20;
    cout<<endl;
     for(auto i=0 ;i<=20 ;i++ ){
        while(i<=20*(perp/100)){
            SetConsoleTextAttribute(
             console_color,1);
              cout<<"|";
              i++;
        }
        SetConsoleTextAttribute(
             console_color,4);
              cout<<"|";
    }
    SetConsoleTextAttribute(
             console_color,7);
             return;
}
void algorithm(linklist *positive, linklist *negative)
{
    //cout<<"positive->no"<<positive->no;

    int len;
    mapping m;
    long double pvalue = 1, nvalue = 1;
    m.mapping_review(negative, positive);
    string line;
    string ch;
    vector<string> word;
    long double totalp = 0;
    long double totaln = 0;
    char option = 'y';
    system("cls");
    while (1)
    {
        pvalue = 1;
        nvalue = 1;
        BST *a = new BST();
        node_tree *temp = NULL;
        if (option == 'y' || option == 'Y')
        {
            cout << "\n******Enter Review******"<< endl;
            fflush(stdin);
            getline(cin, line);
            len = line.size();
            for (int i = 0, len = line.size() ; i < len; i++)
                {
                    if (ispunct(line[i]))
                    {
                        line.erase(i--, 1);
                        len = line.size();
                    }
                }
            len = line.size();
            for (int i = 0; i < len; i++)
            {
                string ch;
                for (int b = 0; line[i] != 32 && i != len; b++)
                {
                    ch = ch + line[i];
                    i++;
                }
                a->add_node(ch);
            }
            temp = a->root;
            pvalue = 1;
            while (temp != NULL)
            {
                
                if (m.pos_review[temp->data] > 0)
                {
                   // cout<<"\nm.pos_review["<<temp->data<<"]="<<m.pos_review[temp->data];
                    pvalue *= m.pos_review[temp->data];
                }
                temp = temp->r;
            }
            long double p=1;
            p=positive->no/(positive->no+negative->no);
            //cout<<"\np="<<p;
             pvalue=pvalue*p;
            // cout << "\npvalue"<< pvalue;
            temp = a->root;
            nvalue = 1;
            while (temp != NULL)
            {
                    
                if (m.neg_review[temp->data] > 0)
                {
                   // cout<<"\nm.neg_review["<<temp->data<<"]="<< m.neg_review[temp->data];
                    nvalue *= m.neg_review[temp->data];
                }
                temp = temp->r;
            }
            long double n=1;
            n=negative->no/(positive->no+negative->no);
            // cout<<"\nn="<<n;
            nvalue=nvalue*n;
            // cout << "\nnvalue"<< nvalue;
            totalp = pvalue / (pvalue + nvalue);
            totaln = 1 - totalp;

            // cout<<"\nFor positive"<<totalp;
            // cout<<"\nfor negative"<<totaln;
            // cout << endl;
            if (totalp > totaln)
            {
                cout << "Positive review";
            }
            else if (totalp == totaln)
            {
                cout << "Netural review";
            }
            else
            {
                cout << "Negative review";
            }
        }
        else
        {
            break;
        }
        delete (a);
        delete (temp);
        drawing(totalp,totaln);
        cout << "Do you want to continue" << endl;
        cin >> option;
        system("cls");
    }
}
// seperating positive and negative comments and storing in linklist
void seperation(linklist *positive, linklist *negative)
{
    ifstream fout;
   // int raabia=0;
    string line;
    int total = 0, len = 0;
    int value = -1;
    string pos = "positive";
    string neg = "negative";
    fout.open("projectdataset.csv");
    getline(fout, line, '\n');
    while (!fout.eof())
    {
        //raabia++;
        total = total + 1;
        getline(fout, line, '\n');

        value = line.find(pos);
        if (value != -1)
        {
            if (line[value - 1] == ',')
            {
                line[value - 1] = ' ';
                for (int i = 0, len = line.size() ; i < len; i++)
                {
                    if (ispunct(line[i]))
                    {
                        line.erase(i--, 1);
                        len = line.size();
                    }
                }
                node *n = new node(line);
                positive->addnode(n);
            }
            else
            {
                line[value - 1] = ' ';
                for (int i = 0, len = line.size(); i < len; i++)
                {
                    if (ispunct(line[i]))
                    {
                        line.erase(i--, 1);
                        len = line.size();
                    }
                }
                node *n = new node(line);
                negative->addnode(n);
            }
        }
        else
        {
            value = line.find(neg);
            line[value - 1] = ' ';

            for (int i = 0, len = line.size(); i < len; i++)
            {
                if (ispunct(line[i]))
                {
                    line.erase(i--, 1);
                    len = line.size();
                }
            }
            node *n = new node(line);
            negative->addnode(n);
        }
        value = -1;
    }
}
// displaying linklist
void display_linklist(linklist *positive, linklist *negative)
{
    int n;
    cout << "\n1)Positive linklist\n2)Negative Linklist ";
    cin >> n;
    if (n == 1)
    {
        positive->print_node();
    }
    else if (n == 2)
    {
        negative->print_node();
    }
    else
    {
        cout << "\nwrong option";
    }
}

int main()
{

    char character = 'y';
    linklist *positive = new linklist();
    linklist *negative = new linklist();
    seperation(positive, negative);
   
    cout<<"                                        -----------------------------------";
    cout<<"\n                                               Sentimental analysis"<<endl;
    cout<<"                                        -----------------------------------";
    algorithm(positive, negative);

    // while (1)
    // {
    //     cout << "\nDo you want to prink linklist y OR n ";
    //     cin >> character;
    //     if (character == 'n' || character == 'N')
    //     {
    //         break;
    //     }
    //     else if (character == 'y' || character == 'Y')
    //     {
    //         display_linklist(positive, negative);
    //     }
    //     else
    //     {
    //         cout << "\nWrong option\nEnter again";
    //     }
    // }
  
}
