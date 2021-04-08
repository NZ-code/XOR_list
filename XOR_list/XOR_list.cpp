#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#define TEST 0


struct Node {
    int element;
    Node* XOR = nullptr;

public:
    Node() {
        this->element = NULL;
        this->XOR = nullptr;
    }
    Node(int element, Node* XOR) {
        this->element = element;
        this->XOR = XOR;
    }

    void set_Xor(Node* Xor) {
        this->XOR = Xor;
    }

    Node* get_XOR() {
        return this->XOR;
    }
};
Node* do_XOR(Node* prev, Node* next) {
    return (Node*)((uintptr_t)prev ^ (uintptr_t)next);
}

class MyList {

    Node* actual;
    Node* actual_next;
    Node* actual_prev;
    Node* begin;
    Node* end;
public:
    MyList() {
        actual = nullptr;
        actual_next = nullptr;
        actual_prev = nullptr;
        begin = nullptr;
        end = nullptr;
    }
    void add_begin(int N) {
        // get element
        Node* new_element = new Node(N, nullptr);
        if (begin == nullptr) { //no element case

            begin = new_element;
            end = new_element;
            actual = new_element;
            // TO DO ACTUAL PREV AND NEXT
        }
        else {
            if (begin == actual) {          // case when begin is actual
                actual_prev = new_element;

            }

            // only one element
            begin->set_Xor(do_XOR(begin->get_XOR(), new_element));

            new_element->set_Xor(begin);
            begin = new_element;
        }
    }
    void add_end(int N) {

        Node* new_element = new Node(N, nullptr);
        if (end == nullptr) // no element case
        {
            begin = new_element;
            end = new_element;
            actual = new_element;
        }
        else {
            if (end == actual) {
                actual_next = new_element;
            }
            end->set_Xor(do_XOR(end->get_XOR(), new_element));
            new_element->set_Xor(end);
            end = new_element;
        }
    }
    void get_actual() {
        if (actual == nullptr) {
            printf("NULL\n"); // no element_case
        }
        else {
            //std::cout << actual->element << std::endl; //at least 1 element 
            printf("%d\n", actual->element);
        }
    }
    void do_next() {
        if (actual == nullptr) {
            printf("NULL\n"); // no element_case
        }
        else if (end == actual) { // actual is last
            //std::cout << begin->element << std::endl;
            printf("%d\n", begin->element);
            //actual_prev = actual;
            actual = begin;
            actual_next = actual->get_XOR();
        }
        else if (actual_next == nullptr) { // one element case
           // std::cout << actual->element << std::endl;
            printf("%d\n", actual->element);
        }

        else { // next exist 
            //std::cout << actual_next->element << std::endl;
            printf("%d\n", actual_next->element);
            actual_prev = actual;
            actual = actual_next;
            actual_next = do_XOR(actual_prev, actual->get_XOR());
        }
    }
    void do_prev() {
        if (actual == nullptr) {
            printf("NULL\n"); // no element_case
        }
        else if (begin == actual) { // actual is first
            //std::cout << end->element << std::endl;
            printf("%d\n", end->element);
            //actual_next = actual;
            actual = end;
            actual_prev = actual->get_XOR();
        }
        else if (actual_prev == nullptr) { // one element case
           // std::cout << actual->element << std::endl;
            printf("%d\n", actual->element);
        }

        else { // prev exist
            //std::cout << actual_prev->element << std::endl;
            printf("%d\n", actual_prev->element);
            actual_next = actual;
            actual = actual_prev;
            actual_prev = do_XOR(actual_next, actual->get_XOR());
        }
    }
    void delete_begin() {
        if (begin == nullptr) { // 0 element case
           // printf("NULL\n");
        }
        else {
            Node* temp = begin;
            Node* begin_next = begin->get_XOR();
            if (begin_next != NULL) { // 2 and more case
                Node* begin_next_next = do_XOR(begin, begin_next->get_XOR());
                begin_next->set_Xor(begin_next_next);
            }
            if (begin == actual) {
                actual = begin_next;
            }
            if (begin == actual_prev) {
                actual_prev = begin_next;
            }
            if (begin == actual_next) {
                actual_next = begin_next;
            }
            if (begin == end) {
                end = begin_next;
            }
            begin = begin_next;

            delete(temp);
        }
    }
    void delete_end() {
        if (end == nullptr) { // 0 element case
          //  printf("NULL\n");
        }
        else {
            Node* temp = end;
            Node* end_prev = end->get_XOR();
            if (end_prev != NULL) { // 2 and more case
                Node* end_prev_prev = do_XOR(end, end_prev->get_XOR());
                end_prev->set_Xor(end_prev_prev);
            }
            if (end == actual) {
                actual = end_prev;
            }
            if (end == actual_prev) {
                actual_prev = end_prev;
            }
            if (end == actual_next) {
                actual_next = end_prev;
            }
            if (end == begin) {
                begin = end_prev;
            }
            end = end_prev;

            delete(temp);
        }
    }
    void delete_actual() {
        if (actual == nullptr) { //no element case
          //  printf("NULL\n");
        }
        else if (actual == begin && actual == end) {
            delete(actual);
            actual = nullptr;
            begin = nullptr;
            end = nullptr;
        }
        else if (actual == begin) {
            Node* begin_next = begin->get_XOR();
            Node* begin_next_next = do_XOR(begin_next->get_XOR(), begin);
            if (begin_next_next != begin_next) {// begin_next_next exist
                begin_next->set_Xor(begin_next_next);
            }
            else {
                begin_next->set_Xor(nullptr);
            }
            begin = begin_next;
            delete(actual);
            actual = end;
            actual_prev = end->get_XOR();
            actual_next = nullptr;
        }
        else if (actual == end) {
            Node* actual_prev_prev = do_XOR(actual_prev->get_XOR(), actual);
            Node* end_prev = end->get_XOR();
            Node* end_prev_prev = do_XOR(end_prev->get_XOR(), end);
            if (end_prev_prev != end_prev) {
                end_prev->set_Xor(end_prev_prev);
            }
            else {
                end_prev->set_Xor(nullptr);
            }

            end = end_prev;
            delete(actual);
            actual = actual_prev;
            if (actual_prev != begin) { // exists

                actual_prev = actual_prev_prev;
            }
            else {

                actual_prev = nullptr;
            }
            actual_next = nullptr;

        }
        else {
            Node* actual_prev_prev = do_XOR(actual_prev->get_XOR(), actual);
            Node* actual_next_next = do_XOR(actual_next->get_XOR(), actual);
            if (actual_prev_prev != actual_prev) {
                actual_prev->set_Xor(do_XOR(actual_prev_prev, actual_next));
            }
            else {
                actual_prev->set_Xor(actual_next);
            }
            if (actual_next_next != actual_next) { // not begin
                actual_next->set_Xor(do_XOR(actual_next_next, actual_prev));
            }
            else {
                actual_next->set_Xor(actual_prev);
            }


            delete(actual);
            actual = actual_prev;
            actual_prev = actual_prev_prev;
        }
    }
    void print_forward() {
        if (begin == nullptr) { // 0 element case
            printf("NULL\n");
        }
        else if (begin->get_XOR() == nullptr) { // 1 element
            //std::cout << begin->element << std::endl;
            printf("%d\n", begin->element);
        }
        else { // other cases
            Node* pointer_prev = nullptr;
            Node* pointer = begin;
            while (pointer->get_XOR() != pointer || pointer->get_XOR() != begin) {
                // std::cout << pointer->element << " ";
                printf("%d ", pointer->element);
                Node* pointer_next = do_XOR(pointer->get_XOR(), pointer_prev);

                if (pointer_next == nullptr) {
                    break;
                }
                pointer_prev = pointer;
                pointer = pointer_next;
            }
            printf("\n");
        }
    }
    void print_backward() {
        if (end == nullptr) { // 0 element case
            printf("NULL\n");
        }
        else if (end->get_XOR() == nullptr) { // 1 element
            //std::cout << end->element << std::endl;
            printf("%d\n", end->element);
        }
        else { // other cases
            Node* pointer_next = nullptr;
            Node* pointer = end;
            while (pointer->get_XOR() != pointer || pointer->get_XOR() != end) {
                //  std::cout << pointer->element << " ";
                printf("%d ", pointer->element);
                Node* pointer_prev = do_XOR(pointer->get_XOR(), pointer_next);

                if (pointer_prev == nullptr) {
                    break;
                }
                pointer_next = pointer;
                pointer = pointer_prev;
            }
            printf("\n");
        }
    }
    void add_actual(int N) {

        Node* new_element = new Node(N, nullptr);
        if (actual == nullptr) { //no element case
            begin = new_element;
            end = new_element;
            actual = new_element;
            // TO DO ACTUAL PREV AND NEXT
        }
        else if (actual == begin) {
            new_element->set_Xor(actual);
            actual->set_Xor(do_XOR(new_element, actual->get_XOR()));
            begin = new_element;
            actual_prev = new_element;
        }
        else {
            actual->set_Xor(do_XOR(actual_next, new_element));
            Node* actual_prev_prev = do_XOR(actual_prev->get_XOR(), actual);
            actual_prev->set_Xor(do_XOR(new_element, actual_prev_prev));
            new_element->set_Xor(do_XOR(actual_prev, actual));
            actual_prev = new_element;
        }
    }
    static void delete_element(Node*& prev, Node*& cur) {

        Node* prev_prev = nullptr;
        if (prev != nullptr) { prev_prev = do_XOR(prev->get_XOR(), cur); }
        Node* next = do_XOR(cur->get_XOR(), prev);
        Node* next_next = nullptr;
        if (next != nullptr) { next_next = do_XOR(cur, next->get_XOR()); }



        if (prev_prev != prev && prev_prev != nullptr) {
            prev->set_Xor(do_XOR(prev_prev, next));
        }
        else {
            prev->set_Xor(next);
        }
        if (next_next != next && next_next != nullptr) {
            next->set_Xor(do_XOR(next_next, prev));
        }
        else {
            next->set_Xor(prev);
        }
        delete cur;
    }
    void delete_val(int N) {

        if (begin == nullptr) { // 0 element case
            printf("NULL\n");
        }
        else if (begin->get_XOR() == nullptr) { // 1 element
            //std::cout << begin->element << std::endl;
            if (begin->element == N) {
                delete_begin();
            }
        }

        else { // other cases
            //Node* pointer_prev_last = nullptr;
            Node* pointer_prev = nullptr;
            Node* pointer = begin;

            while (pointer->get_XOR() != pointer || pointer->get_XOR() != begin) {
                // std::cout << pointer->element << " ";
                //printf("%d ", pointer->element);
                Node* pointer_next = do_XOR(pointer->get_XOR(), pointer_prev);
                int del_flag = 0;
                //pointer_prev_last = pointer_prev; // saving
                if (pointer->element == N) {
                    if (pointer == begin) {
                        delete_begin();
                    }
                    else if (pointer == end)
                    {
                        delete_end();
                    }
                    else if (pointer == actual) {
                        delete_actual();
                    }
                    else if (pointer == actual_prev) {
                        actual_prev = pointer_prev;
                        delete_element(pointer_prev, pointer);
                    }
                    else if (pointer == actual_next) {
                        if (pointer_next != pointer) {
                            actual_next = pointer_next;
                        }
                        else {
                            actual_next = nullptr;
                        }
                        delete_element(pointer_prev, pointer);
                    }
                    else {
                        delete_element(pointer_prev, pointer);
                    }
                    del_flag = 1;
                }
                if (del_flag == 1) {
                    pointer = pointer_next;
                }
                else {
                    pointer_prev = pointer;
                    pointer = pointer_next;
                }
                if (pointer_next == nullptr) {
                    break;
                }

            }
            //printf("\n");
        }
    }
};

int convert_command(const std::string& cmd) {
    if (cmd == "ADD_BEG") return 0;
    else if (cmd == "ADD_END") return 1;
    else if (cmd == "ACTUAL") return 2;
    else if (cmd == "NEXT") return 3;
    else if (cmd == "PREV") return 4;
    else if (cmd == "DEL_BEG") return 5;
    else if (cmd == "DEL_END") return 6;
    else if (cmd == "DEL_ACT") return 7;
    else if (cmd == "PRINT_FORWARD") return 8;
    else if (cmd == "PRINT_BACKWARD") return 9;
    else if (cmd == "ADD_ACT") return 10;
    else if (cmd == "DEL_VAL") return 11;
    else return -1;
}

int main()
{

    MyList* list = new MyList();

    while (!std::cin.eof()) {
        std::string cmd;
        std::cin >> cmd;
        int command = convert_command(cmd);


        switch (command)
        {
        case 0: { //ADD_BEG !
            int N;
            scanf("%d", &N);
            list->add_begin(N);
            break;
        }
        case 1://ADD_END    
        {
            int N;
            scanf("%d", &N);
            list->add_end(N);
            break;
        }
        case 2:
        {//actual 
            list->get_actual();
            break;
        }
        case 3:
        {//NEXT    
            list->do_next();
            break;
        }
        case 4:
        {//PREV   
            list->do_prev();
            break;
        }
        case 5: {
            //DEL_BEG
            list->delete_begin();
            break;
        }
        case 6: {
            //DEL END
            list->delete_end();
            break;
        }
        case 7:
        {//DEL_ACTUAL

            list->delete_actual();


            break;
        }
        case 8://PRINT_FORWARD  !
        {
            list->print_forward();
            break;
        }
        case 9://PRINT_BACKWARD     !
        {
            list->print_backward();
            break;
        }
        case 10://ADD_ACT
        {
            int N;
            scanf("%d", &N);
            list->add_actual(N);

            break;
        }
        case 11: // DEL_VAL
            int N;
            scanf("%d", &N);
            list->delete_val(N);
            break;
        default:
            break;
        }

#if TEST>0
        if (actual_next != nullptr) {
            std::cout << "actual_next  val:" << actual_next->element << std::endl;
        }
        else {
            std::cout << "actual_next NULL" << std::endl;
        }

        if (actual != nullptr) {
            std::cout << "actual val:" << actual->element << std::endl;

        }
        else {
            std::cout << "actual NULL" << std::endl;
        }


        if (actual_prev != nullptr) {
            std::cout << "actual_prev val:" << actual_prev->element << std::endl;


        }
        else {
            std::cout << "actual_prev NULL" << std::endl;
        }
        if (begin != nullptr) {
            std::cout << "begin val:" << begin->element << std::endl;
        }
        else {
            std::cout << "begin NULL" << std::endl;
        }
        if (end != nullptr) {
            std::cout << "end val:" << end->element << std::endl;
        }
        else {
            std::cout << "end NULL" << std::endl;
        }
        std::cout << std::endl << std::endl;
#endif        
    }


}

/*  TO_DO
    Problems:

*/