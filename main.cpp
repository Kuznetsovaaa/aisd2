#include <iostream>
import linked_list;

template <typename T>
bool has_cycle(Node<T>* head) {
    if (head == nullptr) return false;
    
    Node<T>* slow = head;
    Node<T>* fast = head;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

template <typename T>
void print_list_safe(Node<T>* head) {
    if (head == nullptr) {
        std::cout << "[]" << std::endl;
        return;
    }

    Node<T>* slow = head;
    Node<T>* fast = head;
    bool cycle_found = false;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            cycle_found = true;
            break;
        }
    }

    std::cout << "[";
    
    if (!cycle_found) {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) std::cout << ", ";
            current = current->next;
        }
    } else {
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        
        Node<T>* current = head;
        while (current != slow) {
            std::cout << current->data << ", ";
            current = current->next;
        }
        
        std::cout << "(";
        Node<T>* cycle_start = current;
        do {
            std::cout << current->data;
            current = current->next;
            if (current != cycle_start) std::cout << ", ";
        } while (current != cycle_start);
        std::cout << ")";
    }
    
    std::cout << "]" << std::endl;
}

int main() {
    LinkedList<int> list1;
    list1.push_tail(10);
    list1.push_tail(20);
    list1.push_tail(30);

    std::cout << "List 1 (no cycle): ";
    print_list_safe(list1.get_head());
    
    if (has_cycle(list1.get_head())) {
        std::cout << "Has cycle: YES" << std::endl;
    } else {
        std::cout << "Has cycle: NO" << std::endl;
    }

    std::cout << "-----------------------" << std::endl;

    LinkedList<int> list2;
    list2.push_tail(1);
    list2.push_tail(2);
    list2.push_tail(3);
    list2.push_tail(4);
    list2.push_tail(5);

    Node<int>* head2 = list2.get_head();
    Node<int>* target = head2->next;
    Node<int>* tail2 = head2;
    while (tail2->next != nullptr) {
        tail2 = tail2->next;
    }
    tail2->next = target; 

    std::cout << "List 2 (with cycle): ";
    print_list_safe(list2.get_head());
    
    if (has_cycle(list2.get_head())) {
        std::cout << "Has cycle: YES" << std::endl;
    } else {
        std::cout << "Has cycle: NO" << std::endl;
    }

    tail2->next = nullptr;

    return 0;
}