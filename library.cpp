#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <limits>

using namespace std; // namespace std 사용

class Book {
public:
    string title;
    string author;

    Book(const string& title, const string& author)
        : title(title), author(author) {}
};

class BorrowManager{
private:
    unordered_map<string, int> stock; //책 재고
public:
    //책 재고 초기화
    void initializeStock(string title, int quantity=3){
        stock[title]=quantity;
    }
    //책 대여
    void borrowBook(string title){
        auto it = stock.find(title);
        if (it != stock.end()) {
            if (stock[title] > 0) {
                stock[title]--;
                cout << "\"" << title << "\" 도서가 대여 가능합니다 ㅡ> 대여 완료";
                displayStock(title);
            } else {
                cout << "\"" << title << "\" 도서가 대여 불가능합니다";
                displayStock(title);
            }
        } else {
            cout << "\"" << title << "\" 도서가 존재하지 않습니다" << endl;
        }
    }
    //책 반납
    void returnBook(string title){
        auto it = stock.find(title);
        if (it != stock.end()) {
            stock[title]++;
            cout << "\"" << title << "\" 도서가 정상 반납되었습니다";
            displayStock(title);
        }
        else {
            cout << "\"" << title << "\" 도서는 저희 도서관 소유물이 아닙니다" << endl;
        }
    } 
    //재고 출력
    void displayStock (string title) {
        cout<<"(재고: "<<stock[title]<<")"<<endl;
    }
};

class BookManager {
private:
    vector<Book> books; // 책 목록 저장
    BorrowManager bM; //대여 관리
public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) {
        books.push_back(Book(title,author)); // push_back 사용
        bM.initializeStock(title);
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }
    // 모든 책 출력 메서드
    void displayAllBooks() {
        if (books.empty()) {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << " ";
            bM.displayStock(books[i].title);
        }
    }
    //책 이름 검색
    Book* findBookByTitle(string title){
        for(Book& b : books){
            if(b.title==title){
                cout << "검색된 도서: - " << b.title << " by " << b.author ;
                bM.displayStock(b.title);
                return &b;
            }
        }
        cout<<"검색된 도서가 존재하지 않습니다."<<endl;
        return NULL;
    }
    //책의 작가 이름 검색
    Book* findBookByAuthor(string author){
        for(Book& b : books){
            if(b.author==author){
                cout << "검색된 도서: - " << b.title << " by " << b.author ;
                bM.displayStock(b.title);
                return &b;
            }
        }
        cout<<"검색된 도서가 존재하지 않습니다."<<endl;
        return NULL;
    }
    //책 대여 가능 여부 제목으로 확인 및 대여
    void getBookByTitle(string title){
        Book* target=findBookByTitle(title);
        if(target==NULL){
            cout<<"요청하신 도서가 존재하지 않아 대여가 불가능합니다.";
        }
        else{
            bM.borrowBook(target->title);
        }
    }
    //책 대여 가능 여부 작가 이름으로 확인 및 대여
    void getBookByAuthor(string author){
        Book* target=findBookByAuthor(author);
        if(target==NULL){
            cout<<"요청하신 도서가 존재하지 않아 대여가 불가능합니다.";
        }
        else{
            bM.borrowBook(target->title);
        }
    }
    //반납
    void returnBook(string title){
        Book* target=findBookByTitle(title);
        if(target==NULL){
            cout<<"반납 요청하신 도서는 저희 도서관 소유물이 아닙니다.";
        }
        else{
            bM.returnBook(title);   
        }
    }
};

int main() {
    BookManager manager;

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 책 제목 검색" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "4. 책 작가 이름 검색" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "5. 책 제목으로 대여 가능 여부 검색 및 대여" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "6. 책 작가 이름으로 대여 가능 여부 검색 및 대여" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "7. 책 반납" <<endl; //책 반납
        cout << "8. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        //숫자가 아닌 입력에 대한 예외 처리
        if(cin.fail()){
            cin.clear(); //입력 스트림 상태 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n');//버퍼 비우기
            cout<<"잘못된 입력 감지. 숫자만 입력해주세요."<<endl;
            cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ구분선ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ";
            continue;
        }

        if (choice == 1) {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
        } else if (choice == 2) {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        } else if (choice == 3){
            //3번 선택: 책 제목 검색
            string title;
            cout<< "검색할 책 제목: ";
            cin.ignore();
            getline(cin,title);
            manager.findBookByTitle(title);
        } else if (choice == 4){
            //4번 선택: 책 작가 이름 검색
            string author;
            cout<< "검색할 책 작가 이름: ";
            cin.ignore();
            getline(cin,author);
            manager.findBookByAuthor(author);
        } else if (choice == 5){
            //5번 선택: 책 제목으로 대여 가능 여부 검색 및 대여
            string title;
            cout<< "대여할 책 제목: ";
            cin.ignore();
            getline(cin,title);
            manager.getBookByTitle(title);
        } else if (choice == 6){
            //6번 선택: 책 작가 이름으로 대여 가능 여부 검색 및 대여
            string author;
            cout<< "대여할 책 작가 이름: ";
            cin.ignore();
            getline(cin,author);
            manager.getBookByAuthor(author);
        } else if (choice == 7){
            //7번 선택: 책 반납
            string title;
            cout<< "반납할 책 제목: ";
            cin.ignore();
            getline(cin,title);
            manager.returnBook(title);
        } else if (choice == 8) {
            // 8번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        } else {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }
        cout<<"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ구분선ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ";
    }

    return 0; // 프로그램 정상 종료
}
