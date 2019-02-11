//
//  clist.hpp
//  P7-Shrey
//
//  Created by Shrey Pithava on 02/04/18.
//  Copyright © 2018 Shrey Pithava. All rights reserved.
//

#ifndef clist_hpp
#define clist_hpp

#include "tools.hpp"
#include "player.hpp"

template <class T>
class CList;
//---------------------------------------------------------------------------
//-------------Cell class----------------------------------------------------
template <class T>
class Cell {
private:
    T* p;
    Cell* next;
    static int no;
public:
    Cell( T* playerptr, Cell* nextptr = NULL ): p( playerptr ), next( nextptr ) { ++no; }
    ~Cell() {
        delete p;
        --no;
        if(!no) cout << "Cells: " << no << endl;
    }
    friend CList<T>;
};

template<typename T>
int Cell<T>::no = 0;
//---------------------------------------------------------------------------
//----------------List of Cells-----------------------------------------------
template <class T>
class CList {
private:
    int count;
    T* plyrptr;
    static int noL;
    Cell<T>* headptr;
    Cell<T>* tailptr;
    Cell<T>* cellptr;
public:
    CList(): headptr( nullptr ), tailptr( nullptr ), cellptr( nullptr ), count(0) { ++noL; }
    ~CList() {
        cellptr = headptr;
        while (count != 0) {
            Cell<T>* a = cellptr;
            cellptr = cellptr->next;
            delete a;
            --count;
        }
        --noL;
        if(!noL) cout << "CList: " << noL << endl;
    };
    T* next();
    T* first();
    void turn();
    void remove();
    void insertBack( T* );
    ostream& print( ostream& );
    T* rPptr()                   { return plyrptr; }
    bool empty()                 { return ( headptr == nullptr ); };
    bool onePlayer()             { return ( count == 1 ); }
};
//------------------------------------------------------------------------------
template <class T>
inline ostream& operator <<( ostream& out, CList<T>& c ) { return c.print( out ); }

template <typename T>
int CList<T>::noL = 0;
//------------------------------------------------------------------------------
//-------------------------Insert cell in CList---------------------------------
template <typename T>
void CList<T>::insertBack( T* p ) {
    if (headptr == nullptr) {
        Cell<T>* temp = new Cell<T>(p);
        cellptr = headptr = temp->next = tailptr = temp;
        plyrptr = temp->p;
    }
    else {
        Cell<T>* temp = new Cell<T>( p, headptr );
        tailptr->next = temp;
        tailptr = temp;
    }
    count++;
}
//----------------------------------------------------------------------------
//--------------------Print function------------------------------------------
template <typename T>
ostream& CList<T>::print( ostream& out ) {
    Cell<T>* a = headptr;
    out << endl;
    if (a == nullptr) {
        out << "No players in the list";
        return out;
    }
    out << "No of Players: " << count << endl;
    do {
        a->p->print(out);
        a = a->next;
    } while (a != headptr);
    out << endl;
    return out;
}
//-----------------------------------------------------------------------------
//----------------Returns next data--------------------------------------------
template <typename T>
T* CList<T>::next() {
    if (headptr == nullptr) {
        cout << "List is empty" << endl;
        return nullptr;
    }
    else {
        cellptr = cellptr->next;
        plyrptr = cellptr->p;
        return plyrptr;
    }
}
//------------------------------------------------------------------------------
//-------------------Remove Data------------------------------------------------
template <typename T>
void CList<T>::remove() {
    if (headptr == nullptr) { cout << "No players to remove" << endl; }
    else {
        Cell<T>* a = cellptr;
        plyrptr = next();
        if (count == 1) {
            a = headptr = tailptr = nullptr;
            free(a);
            cout << "All players removed" << endl;
        }
        else if (a == headptr) {
            tailptr->next = headptr = a->next;
            delete a;
        }
        else if (a == tailptr) {
            Cell<T>* before = headptr;
            Cell<T>* del;
            while (before->next != a) { before = before->next; }
            del = before->next;
            before->next = headptr;
            tailptr = before;
            delete del;
        }
        else {
            Cell<T>* before = headptr;
            Cell<T>* del;
            while (before->next != a) { before = before->next; }
            del = before->next;
            before->next = before->next->next;
            delete del;
        }
        count--;
    }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
template<typename T>
T* CList<T>::first() {
    if (headptr == nullptr) {
        cout << "List is empty" << endl;
        return nullptr;
    }
    cellptr = headptr;
    return cellptr->p;
}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
template<typename T>
void CList<T>::turn() { cout << "Player: " << plyrptr->plyrName() << ", " << plyrptr->getColor() << endl; }
#endif /* clist_hpp */
