#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <limits>

using namespace std; // namespace std ���

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BorrowManager{
private:
    unordered_map<string, int> stock; //å ���
public:
    //å ��� �ʱ�ȭ
    void initializeStock(string title, int quantity=3){
        stock[title]=quantity;
    }
    //å �뿩
    void borrowBook(string title){
        auto it = stock.find(title);
        if (it != stock.end()) {
            if (stock[title] > 0) {
                stock[title]--;
                cout << "\"" << title << "\" ������ �뿩 �����մϴ� ��> �뿩 �Ϸ�";
                displayStock(title);
            } else {
                cout << "\"" << title << "\" ������ �뿩 �Ұ����մϴ�";
                displayStock(title);
            }
        } else {
            cout << "\"" << title << "\" ������ �������� �ʽ��ϴ�" << endl;
        }
    }
    //å �ݳ�
    void returnBook(string title){
        auto it = stock.find(title);
        if (it != stock.end()) {
            stock[title]++;
            cout << "\"" << title << "\" ������ ���� �ݳ��Ǿ����ϴ�";
            displayStock(title);
        }
        else {
            cout << "\"" << title << "\" ������ ���� ������ �������� �ƴմϴ�" << endl;
        }
    } 
    //��� ���
    void displayStock (string title) {
        cout<<"(���: "<<stock[title]<<")"<<endl;
    }
};

class BookManager {
private:
    vector<Book> books; // å ��� ����
    BorrowManager bM; //�뿩 ����
public:
    // å �߰� �޼���
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title,author)); // push_back ���
        bM.initializeStock(title);
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
    }
    // ��� å ��� �޼���
    void displayAllBooks() {
        if (books.empty()) {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << " ";
            bM.displayStock(books[i].title);
        }
    }
    //å �̸� �˻�
    Book* findBookByTitle(string title){
        for(Book& b : books){
            if(b.title==title){
                cout << "�˻��� ����: - " << b.title << " by " << b.author ;
                bM.displayStock(b.title);
                return &b;
            }
        }
        cout<<"�˻��� ������ �������� �ʽ��ϴ�."<<endl;
        return NULL;
    }
    //å�� �۰� �̸� �˻�
    Book* findBookByAuthor(string author){
        for(Book& b : books){
            if(b.author==author){
                cout << "�˻��� ����: - " << b.title << " by " << b.author ;
                bM.displayStock(b.title);
                return &b;
            }
        }
        cout<<"�˻��� ������ �������� �ʽ��ϴ�."<<endl;
        return NULL;
    }
    //å �뿩 ���� ���� �������� Ȯ�� �� �뿩
    void getBookByTitle(string title){
        Book* target=findBookByTitle(title);
        if(target==NULL){
            cout<<"��û�Ͻ� ������ �������� �ʾ� �뿩�� �Ұ����մϴ�.";
        }
        else{
            bM.borrowBook(target->title);
        }
    }
    //å �뿩 ���� ���� �۰� �̸����� Ȯ�� �� �뿩
    void getBookByAuthor(string author){
        Book* target=findBookByAuthor(author);
        if(target==NULL){
            cout<<"��û�Ͻ� ������ �������� �ʾ� �뿩�� �Ұ����մϴ�.";
        }
        else{
            bM.borrowBook(target->title);
        }
    }
    //�ݳ�
    void returnBook(string title){
        Book* target=findBookByTitle(title);
        if(target==NULL){
            cout<<"�ݳ� ��û�Ͻ� ������ ���� ������ �������� �ƴմϴ�.";
        }
        else{
            bM.returnBook(title);   
        }
    }
};

int main() {
    BookManager manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. å ���� �˻�" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "4. å �۰� �̸� �˻�" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "5. å �������� �뿩 ���� ���� �˻� �� �뿩" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "6. å �۰� �̸����� �뿩 ���� ���� �˻� �� �뿩" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "7. å �ݳ�" <<endl; //å �ݳ�
        cout << "8. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        //���ڰ� �ƴ� �Է¿� ���� ���� ó��
        if(cin.fail()){
            cin.clear(); //�Է� ��Ʈ�� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//���� ����
            cout<<"�߸��� �Է� ����. ���ڸ� �Է����ּ���."<<endl;
            cout<<"�ѤѤѤѤѤѤѤѤѤѤѤѤѱ��м��ѤѤѤѤѤѤѤѤѤѤѤѤ�";
            continue;
        }

        if (choice == 1) {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
        } else if (choice == 2) {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        } else if (choice == 3){
            //3�� ����: å ���� �˻�
            string title;
            cout<< "�˻��� å ����: ";
            cin.ignore();
            getline(cin,title);
            manager.findBookByTitle(title);
        } else if (choice == 4){
            //4�� ����: å �۰� �̸� �˻�
            string author;
            cout<< "�˻��� å �۰� �̸�: ";
            cin.ignore();
            getline(cin,author);
            manager.findBookByAuthor(author);
        } else if (choice == 5){
            //5�� ����: å �������� �뿩 ���� ���� �˻� �� �뿩
            string title;
            cout<< "�뿩�� å ����: ";
            cin.ignore();
            getline(cin,title);
            manager.getBookByTitle(title);
        } else if (choice == 6){
            //6�� ����: å �۰� �̸����� �뿩 ���� ���� �˻� �� �뿩
            string author;
            cout<< "�뿩�� å �۰� �̸�: ";
            cin.ignore();
            getline(cin,author);
            manager.getBookByAuthor(author);
        } else if (choice == 7){
            //7�� ����: å �ݳ�
            string title;
            cout<< "�ݳ��� å ����: ";
            cin.ignore();
            getline(cin,title);
            manager.returnBook(title);
        } else if (choice == 8) {
            // 8�� ����: ����
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        } else {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
        cout<<"�ѤѤѤѤѤѤѤѤѤѤѤѤѱ��м��ѤѤѤѤѤѤѤѤѤѤѤѤ�";
    }

    return 0; // ���α׷� ���� ����
}
