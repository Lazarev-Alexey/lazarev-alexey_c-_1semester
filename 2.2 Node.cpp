struct Node{
    Node* next;
    Node(Node* n)
    {
        next = n;
    }
    Node()
    {
        next = nullptr;
    }
    ~Node()
    {
        delete next;
    }
};

Node* ReverseList(Node* head){
    Node* tail = nullptr;
    Node n;
    while((*head).next != nullptr)
    {
        n = (*head).next -> next;
        (*((*head).next)).next = tail;
        tail = (*head).next;
        (*head).next = &n;
    }
    (*head).next = tail;
    return head;
}

Node* DelNodeAtHead(Node* head)
{
    return head->next;
}

Node* AddNodeAtHead(Node* head, Node* node)
{
    node->next = head;
    return node;
}
