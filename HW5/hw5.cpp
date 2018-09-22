/**
*  Author: 范真瑋
*  Date: Oct. 20, 2016
*  Purpose: Implement the addition and multiplication of two polynomials
*/

#include <iostream>
using namespace std;

typedef struct Term {
    int coef, exp;  // coefficient & exponent
    struct Term *next;  // next node
}Term;

class Polynomial {
public:
    Polynomial(int, int*, int*);  //  constructor for creating a polynomial
    ~Polynomial();  //  destructor for cleaning the polynomial
    void print() const;  //  output polynomial
    Term* getTerm() const;  //  get polynomial's terms
    Polynomial operator + (const Polynomial&) const;  //  operator overloading +
    Polynomial operator * (const Polynomial&) const;  //  operator overloading *
    void clean();
private:
    Term *term;  //  polynomial's terms
};

Polynomial::Polynomial(int terms, int* coef, int* exp) {  //  constructor for creating a polynomial
    Term *tTemp;
    term = new Term;

    for (int i = 0; i < terms-1; ++i) {  //  sorting by exponent in descending order
        for (int j = i+1; j < terms; ++j) {
            if (exp[i]==exp[j] && coef[i]!=0) {  //  merge those elements with the same exponent
                coef[i] += coef[j];
                coef[j] = 0;
                exp[j] = 0;
                if (coef[i] == 0) {
                    exp[i] = 0;
                }
            }
            else if (exp[i]<exp[j]) {
                swap(exp[i], exp[j]);
                swap(coef[i], coef[j]);
            }
        }
    }

    for (int i = 0; i < terms-1; ++i) {  //  put the highest coefficient to the front (with the same exponent)
        for (int j = i+1; j < terms; ++j) {
            if (exp[i]==exp[j] && coef[i]<coef[j]) {
                swap(coef[i], coef[j]);
            }
        }
    }

    //create the polynomial
    if (terms==0 || coef[0]==0) {
        terms = 0;
        term->coef = 0;
        term->exp = 0;
        term->next = NULL;
    }
    else {
        term->coef = coef[0];
        term->exp = exp[0];
        term->next = NULL;
    }
    for (int i = 1; i < terms; ++i) {  //  setting the terms
        tTemp = new Term;

        Term* current = term;
        while (current->next != NULL) {
            current = current->next;
        }
        tTemp->coef = coef[i];
        tTemp->exp = exp[i];
        tTemp->next = NULL;
        current->next = tTemp;
    }
}

Polynomial::~Polynomial() {  //  destructor for cleaning the polynomial
    Term *temp;

    while (term != NULL) {
        temp = term;
        term = term->next;
        delete temp;
        temp = NULL;
    }
}

void Polynomial::print() const{  //  output polynomial
    Term *prev, *temp;
    Term *c = term;
    int check = term->coef;

    if (check == 0) {  //  0 0
        cout << c->coef << " " << c->exp << endl;
        return;
    }

    while(c != NULL) {
        if (c->coef==0) {  //  remove the element of a zero-coefficient
            temp = c;
            prev->next = c->next;
            c = c->next;
            delete temp;
            temp = NULL;
        }
        else {
            cout << c->coef << " " << c->exp << endl;
            prev = c;
            c = c->next;
        }
    }
}

Term* Polynomial::getTerm() const {  //  get polynomial's terms
    return term;
}

Polynomial Polynomial::operator + (const Polynomial& b) const {  // add
    Term *ptr1 = getTerm();
    Term *ptr2 = b.getTerm();
    Term *temp = NULL, *poly = NULL, *current;
    int coef, exp, c = 0;  //  c for calculating the terms

    while (ptr1!=NULL && ptr2!=NULL) {
        if (ptr1->exp == ptr2->exp) {  //  equal
            coef = ptr1->coef + ptr2->coef;
            exp = ptr1->exp;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }
        else if (ptr1->exp > ptr2->exp) {  //  ptr1's exponent is grater than ptr2's exponent
            coef = ptr1->coef;
            exp = ptr1->exp;
            ptr1 = ptr1->next;
        }
        else if (ptr1->exp < ptr2->exp) {  //  ptr1's exponent is less than ptr2's exponent
            coef = ptr2->coef;
            exp = ptr2->exp;
            ptr2 = ptr2->next;
        }

        if (poly == NULL) {  //  the first term
            if (coef == 0) {  //  If the result is zero
                return Polynomial(0, 0, 0);
            }
            temp = new Term;
            poly = temp;
        }
        else {
            temp = new Term;
            current = poly;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = temp;
        }
        temp->coef = coef;
        temp->exp = exp;
        temp->next = NULL;
        ++c;

        if (ptr1 == NULL) {
            while (ptr2 != NULL) {  //  ptr2's terms are grater than ptr1's terms
                coef = ptr2->coef;
                exp = ptr2->exp;
                ptr2 = ptr2->next;
                temp = new Term;
                if (poly == NULL) {  //  the first term
                    poly = temp;
                }
                else {
                    current = poly;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = temp;
                }
                temp->coef = coef;
                temp->exp = exp;
                temp->next = NULL;
                ++c;
            }
        }
        else if (ptr2 == NULL) {
            while (ptr1 != NULL) {  //  ptr1's terms are grater than ptr2's terms
                coef = ptr1->coef;
                exp = ptr1->exp;
                ptr1 = ptr1->next;
                temp = new Term;
                if (poly == NULL) {  //  the first term
                    poly = temp;
                }
                else {
                    current = poly;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = temp;
                }
                temp->coef = coef;
                temp->exp = exp;
                temp->next = NULL;
                ++c;
            }

        }
    }

    //  create a polynomial
    int i = 0;
    int _coef[c];
    int _exp[c];
    while (poly != NULL) {
        _coef[i] = poly->coef;
        _exp[i] = poly->exp;
        ++i;
        temp = poly;
        poly = poly->next;
        delete temp;
        temp = NULL;
    }

    return Polynomial(c, _coef, _exp);
}

Polynomial Polynomial::operator * (const Polynomial& b) const {  // multiply
    Term *ptr1 = getTerm();
    Term *ptr2;
    Term *temp = NULL, *poly = NULL, *current = NULL;
    int c = 0;  //  c for calculating the terms

    while (ptr1 != NULL) {
        ptr2 = b.getTerm();
        while (ptr2 != NULL) {
            temp = new Term;
            temp->coef = ptr1->coef * ptr2->coef;
            temp->exp = ptr1->exp + ptr2->exp;
            temp->next = NULL;
            ptr2 = ptr2->next;
            if (poly == NULL) {  //  the first term
                if (temp->coef == 0) {  //  If the result is zero
                    delete temp;

                    return Polynomial(0, 0, 0);
                }
                poly = temp;
            }
            else {
                current = poly;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }
            ++c;
        }
        ptr1 = ptr1->next;
    }

    //  create a polynomial
    int i = 0;
    int coef[c];
    int exp[c];
    while (poly != NULL) {
        coef[i] = poly->coef;
        exp[i] = poly->exp;
        ++i;
        temp = poly;
        poly = poly->next;
        delete temp;
        temp = NULL;
    }

    return Polynomial(c, coef, exp);
}

int main() {
    int p, q, *coef1, *exp1, *coef2, *exp2, t, c = 0;  //  c for calculating the test cases

    while (true) {
        cin >> p;  //  number of elements
        if (p != 0) {
            t = p;
            coef1 = new int[p];
            exp1 = new int[p];
            while (t--) {  //  enter coefficient & exponent
                cin >> coef1[p-t-1] >> exp1[p-t-1];
            }
        }
        else {  //  zero
            coef1 = 0;
            exp1 = 0;
        }
        Polynomial A(p, coef1, exp1);


        cin >> q;  //  number of elements
        if (q == 0) {
            if (p == 0) {  //  p = 0 and q = 0, input stops
                break;
            }
        }

        if (q != 0) {
            t = q;
            coef2 = new int[q];
            exp2 = new int[q];
            while (t--) {  //  enter coefficient & exponent
                cin >> coef2[q-t-1] >> exp2[q-t-1];
            }
        }
        else {  //  zero
            coef2 = 0;
            exp2 = 0;
        }
        Polynomial B(q, coef2, exp2);

        Polynomial C = A + B;  //  add
        Polynomial D = A * B;  //  multiply
        ++c;
        cout << "Case" << c << ":\n"
             << "ADD\n";
        C.print();
        cout << "MULTIPLY\n";
        D.print();

        if (p!=0) {
            delete[] coef1;
            delete[] exp1;
        }
        if (q != 0) {
            delete[] coef2;
            delete[] exp2;
        }
    }

    return 0;
}
