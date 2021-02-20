/*
Title: SquareMatrix.hpp
Description: Implements a square matrix of elements of a specified type
Date: 9/27/20
*/

#ifndef _SquareMatrix_
#define _SquareMatrix_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iostream>
#include <utility>
using namespace std;

template<class T> class SquareMatrix
{
    private:
        T** squatrix; //pointer that points to an array of pointers, producing the 2d array that is the square matrix
        size_t rows; //length of rows and columns
        //void create(const size_t size); //parameterized constructor helper
        void create();
         void clear(); //destructor helper
    public:
        SquareMatrix(); //default constructor      
        SquareMatrix(const size_t size); //parameterized constructor

        //Big 5
        ~SquareMatrix(); //destructor
       
        SquareMatrix(const SquareMatrix& rhs); //copy constructor
        SquareMatrix(SquareMatrix&& rhs); //move constructor
        SquareMatrix& operator=(const SquareMatrix<T>& rhs); //copy assignment
        SquareMatrix& operator=(SquareMatrix<T>&& rhs); //move assignment

        //f(x)
        void resize(size_t new_size); 
        int size() const; 
        bool operator==(const SquareMatrix& A) const; 
        SquareMatrix<T> operator+(const SquareMatrix<T>& a_matrix) const; 
        T & at(int row, int col);
        void displayMatrix(const SquareMatrix<T> & sm); //delete
        void fill(const T& value);
}; //end declarations

//default constructor
template <class T>
SquareMatrix<T>::SquareMatrix():squatrix(nullptr), rows(0) {} //end default constructor

//create
//constructs 2d array
/*@param size The dimensions of the matrix
@post If the allocation is successful, the matrix has been constructed
@return The matrix */
template<class T>
void SquareMatrix<T>::create()
{
    // if (rows >= 0)
    // {
    //     squatrix = new T*[rows]; //create array of pointers to pointers
    //     for (int i = 0; i < rows; i++) 
    //     {
    //         squatrix[i] = new T[rows];
    //     }  //row array points to columns of equal size as rows 
    // } //construct matrix b4: create(size);  
} //end create

//parameterized constructor
//calls create and fills constructed array with 0s so that it does not display messy address values
/*@param size The dimensions of the matrix
@post If the allocation is successful, the matrix has been constructed*/
template<class T>
SquareMatrix<T>::SquareMatrix(const size_t size) : rows(size) 
{
    if (rows >= 0)
    {
        squatrix = new T*[rows]; //create array of pointers to pointers
        for (int i = 0; i < rows; i++) 
        {
            squatrix[i] = new T[rows];
        }  //row array points to columns of equal size as rows 
    } //construct matrix b4: create(size);  

   // create();
    for (int i = 0; i <rows; i++)
    {
        for (int j = 0; j <rows; j++)
        {
            squatrix[i][j] = 0;
        } 
    } //fill matrix with 0s
} //end parameterized constructor

//clear
//destructs 2d array
/* @post If the deallocation is successful, the matrix has been destructed */
template<class T>
void SquareMatrix<T>::clear()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] squatrix[i]; 
    }//delete every cell to prevent memory leak

    delete[] squatrix; 
    squatrix = nullptr; //deallocate first pointer itself

} //end clear

//destructor
//calls clear
/*@post If the deallocation is successful, the matrix has been destructed */
template<class T>
SquareMatrix<T>::~SquareMatrix()
{
    clear();
} //end destructor

//copy constructor
//produces deep copy of passed matrix and retains originial passed matrix
/*@param rhs A matrix
@post If copy is successful, a matrix has been copied */
template<class T>
SquareMatrix<T>::SquareMatrix(const SquareMatrix<T>& rhs): rows(rhs.rows) //copy rhs's size value
{
    T** copy_squatrix;
    copy_squatrix = new T*[rows]; //create array of pointers to pointers
    for (int i = 0; i < rows; i++) 
    {
        copy_squatrix[i] = new T[rows];
    }  //row array points to columns of equal size as rows 

    for (int i = 0; i < rows; i++)
    {           
        for (int j = 0; j < rows; j++) 
        {           
            copy_squatrix[i][j] = rhs.squatrix[i][j]; 
        }
    }     
 } //end copy constructor

//move constructor
//produces shallow copy of passed matrix and deletes original matrix
/*@param rhs A matrix
@post If the copy is successful, a matrix has been copied and deleted */
template<class T>
SquareMatrix<T>::SquareMatrix(SquareMatrix&& rhs): rows(rhs.rows), squatrix(rhs.squatrix) //copies values of rhs
{
    rhs.rows = 0; 
    rhs.squatrix = nullptr;//delets value in original object
} //end move constructor

//copy assignment
//gives matrix the same values as passed matrix while retaining the original
/*@param rhs A matrix
@post If the assignment is successful, current matrix has rhs's values and rhs is retained
@return The current matrix*/
template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(const SquareMatrix<T>& rhs)
{
    if (this == &rhs)
    {
        return *this;
    } //if the matrixes are equal there is no point in copying

    if (squatrix != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] squatrix[i]; 
        }
        delete[] squatrix;
        squatrix = nullptr;
    } //if matrix has already been constructed then delete it

    rows = rhs.rows; //copy size value of passed matrix
    squatrix = new T*[rows]; //create array of pointers to pointers

    for (int i = 0; i < rows; i++) 
        {
            squatrix[i] = new T[rows];
        }  //row array points to columns of equal size as rows 
     //construct matrix b4: create(size);  

    for (int i=0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            squatrix[i][j] = rhs.squatrix[i][j];
        }
    } //copy value of items in cells

    return *this; 
} //end copy assigment

//move assignment
//gives matrix the same values as passed matrix and leaves passed matrix in valid but intermediate state
/*@param rhs A matrix
@post If the assignment is successful, current matrix has rhs's values and rhs is set to null
@return The current matrix*/
template<class T>
SquareMatrix<T>& SquareMatrix<T>::operator=(SquareMatrix<T>&& rhs)
{
    if (this == &rhs)
    {
        return *this;
    } //if the matrixes are equal there is no point in copying

    if (squatrix != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] squatrix[i]; 
        }
        delete[] squatrix;
        squatrix = nullptr;
    } //if matrix has already been constructed then delete it

    rows = rhs.rows; //copy size value of passed matrix
    squatrix = new T*[rows];  

    for (int i=0; i < rows; i++)
    {
        squatrix[i] = new T[rows];
    } //construct with the same dimensions as passed matrix

    for (int i=0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            squatrix[i][j] = rhs.squatrix[i][j];
        }
    } //copy values of items in cells

    rhs.rows = 0;
    rhs.squatrix = nullptr; //set passed matrix to valid state

    return *this;
}  //end move assignment 

//size
//current size of the matrix
/*@return The row/column size of the matrix*/
template<class T>
int SquareMatrix<T>::size() const
{
    if (squatrix == nullptr)
    {
        return 0;
    }
    return rows;
} //end size

//resize
/*destroys all previous content of the matrix and releases all memory. 
then it allocates new memory. 
new elements are not specified (can have any value)*/
/*@param new_size the new dimensions of the matrix
@post If the resize is successful, the matrix has dimensions that reflect the new size */
template<class T>
void SquareMatrix<T>::resize(size_t new_size)
{
    clear(); //deallocate matrix

    rows = new_size;
    
    squatrix = new T*[rows];
    for (int i=0; i < rows; i++)
    {
            squatrix[i] = new T[rows];
    
    }

    //create(new_size); //allocate matrix with new size dimensions

    for (int i = 0; i < new_size; i++)
    {
        for (int j = 0; j < new_size; j++)
        {
            squatrix[i][j] = 0;
        }
    } //fill all cells with 0
} //end resize

//at
/*returns a reference to the element in the given row and column. 
It is important to return reference since we plan to use this function to modify the matrix content. 
It allows expressions like obj.at(0,4)=7 . 
If the suggested row or column doesn't exist, throw the std::out_of_range exception*/
/*@param row A row in the matrix
@param col A column in the matrix
@pre Row and col values can not exceed the dimensions of the matrix or be negative values
@post If the cell is successfully found, matrix produces a reference to that cell
@return A reference to the cell*/
template<class T>
T& SquareMatrix<T>::at(int row, int col)
{
    if ((row <= rows) && (col <= rows))
    {
        return squatrix[row][col];
    } //if row and col do not exceed the size of the matrix then return what is contained in that cell
    else
    {
        throw std::out_of_range ("STOP!!! Invalid row and col values");
    } //if not then send warning
} //end at

//equality comparision
//A and B are considered equal if their sizes are equal and all elements of A match the corresponding elements of B
/*@param a A matrix
@post If the comparision is successful, matrix will either be equal to or not equal to the current matrix
@return True if the matrices are equal, false if not*/
template<class T>
bool SquareMatrix<T>::operator==(const SquareMatrix& a)  const
{
    if (a.rows != rows)
    {
        return false;
    } //if the matrices are different sizes then they are not equal

    else
    {
        for (int i = 0; i < rows; i ++)
        {
            for (int j = 0; j <rows; j++)
            {
                if (a.squatrix[i][j] != squatrix[i][j])
                {
                    return false;
                }
            }
                
        }
        return true;
    } //check if the value in every cell is the same
    return true;
} //end equality comparision

//add
/*result of addition of two square matrices A and B of the same size is a square matrix C of the same size 
where each element of C is the sum of corresponding elements from A and B.
Consider the input to be always correct (matrix sizes match and matrix elements can be added)*/
/*@param a_matrix A matrix
@pre matrix sizes match and matrix elements can be added
@post If the addition is successful, a matrix with sums will be produced
@return New matrix of sums*/
template<class T>
SquareMatrix<T> SquareMatrix<T>::operator+(const SquareMatrix<T>& a_matrix) const
{
    SquareMatrix<T> new_squatrix;
    new_squatrix.squatrix = new T*[rows]; //create array of pointers to pointers
    for (int i = 0; i < rows; i++) 
    {
        new_squatrix.squatrix[i] = new T[rows];
    }  //row array points to columns of equal size as rows 
  

    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < rows; j++)
        {
            new_squatrix.squatrix[i][j] = a_matrix.squatrix[i][j] + squatrix[i][j];
        } //add cell values of existing matrix with cell values of passed matrix 
    }
    return new_squatrix;
} 

//delete
template<typename T>
void SquareMatrix<T>::displayMatrix(const SquareMatrix<T> & sm) {
    for (int i = 0; i < sm.rows; i++) 
    {
        for (int j = 0; j < sm.rows; j++) 
        {
            cout << sm.squatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

template<typename T>
void SquareMatrix<T>::fill(const T& value){
    for (int i = 0 ;i < rows; i++)
    {
        for (int j = 0 ;j < rows; j++)
        {
            squatrix[i][j] = value;
        }
    }
}

#endif

// int main()
// {
//     SquareMatrix<int> sqm(5);
//     SquareMatrix<int> sq;
    
//     //Testing Default Constructor (W)   Paramterized Constructor(W)   Display(W)  fill(W)    Destructor(W)

//     cout << "Testing  Default Paramterized Display fill Destructor Size: " << endl;
    
//     cout << "sqm display 5*5: " << endl;
//     sqm.displayMatrix(sqm);
    
//     cout << "sq 0*0: "<<endl;
//     sq.displayMatrix(sq);

//     cout << "sqm size 5: " << sqm.size() << endl;
//     cout << "sqm size 0: " << sq.size() << endl;

//     SquareMatrix<int> sqma(4);
//     sqma.fill(5);
//     cout<< "Display 4*4 fill 5: " <<endl;
//     sqma.displayMatrix(sqma);


//     //Resize
//     cout << "Testing Resize"<<endl;
//     SquareMatrix<int> res(2);
//     res.fill(10);
//     cout<<"print resize: "<<endl;
//     res.displayMatrix(res);
    
//     cout<<"after resize fx: "<<endl;
//     res.resize(4);    
//     res.displayMatrix(res);       
    
//     //Test Equality Operator    == (W)
//     SquareMatrix<int> sww;
//     SquareMatrix<int> smww;
//     cout << "When matrizes are same 0: "<<(sww == smww) << endl;    //T 1
//     SquareMatrix<int> sqy(4);
//     SquareMatrix<int> sqmy(4);
//     cout << "When matrizes are same: "<<(sqy == sqmy) << endl;   //T 1
//     SquareMatrix<int> sqtu(4);
//     sqtu.fill(10);
//     SquareMatrix<int> sqmtu(4);
//     sqmtu.fill(10);
//     cout << "When matrizes are same w fill "<<(sqtu == sqmtu) << endl;  //T 1
//     SquareMatrix<int> sqto(5);
//     sqto.fill(10);
//     SquareMatrix<int> sqmto(4);
//     sqmto.fill(10);
//     cout << "When matrizes are not same w fill "<<(sqto == sqmto) << endl;  //F0
//     SquareMatrix<int> sqtos(5);
//     sqtos.fill(5);
//     SquareMatrix<int> sqmtos(5);
//     sqmtos.fill(10);
//     cout << "When matrizes are same w diff fill "<<(sqtos == sqmtos) << endl;  //F0


//     // SquareMatrix<int> tot(4); 
//     // tot.fill(10); 
//     // tot.displayMatrix(tot);  //displays all 10s
//     // SquareMatrix<int> ip(4);
//     // ip.fill(5);        //new matrix with all 5s
//     // tot = ip;
//     // ip.displayMatrix(tot);

//     //Test Add Operator += (W)      //How to test add operator
//     cout <<endl<<"Testing Add operator and move assign"<<endl;
//     SquareMatrix<int> siya(2);
//     siya.fill(5);
//     siya.displayMatrix(siya);
//     SquareMatrix<int> smile(2);
//     smile.fill(1);
//     SquareMatrix<int> smqe(2);
//     smqe = smile + siya;
//     smqe.displayMatrix(smqe);

//     //Test at
//     cout <<endl<<"Testing At and move"<<endl;
//     SquareMatrix<int> sqmgh(4);
//     sqmgh.fill(5);
//     cout<< "before changing:  "<< sqmgh.at(0,1)<<endl;
//     sqmgh.at(0,1) = 9;
//     cout<< "after changing:  "<<sqmgh.at(0,1)<<endl;
//     sqmgh.displayMatrix(sqmgh);
//     cout<<sqmgh.at(0,1);
//     cout<<sqmgh.at(1,0);
//     cout<<sqmgh.at(0,0);
//     cout<<sqmgh.at(1,1);
    
   
//     //Test Copy Constructor (W)
//     cout << "Copy Constructor"<<endl;
//     SquareMatrix<int> sqmcopy(4);
//     sqmcopy.fill(10);
//     SquareMatrix<int> sqeel(sqmcopy);
//     sqmcopy.displayMatrix(sqmcopy);
//     sqeel.displayMatrix(sqeel);

//     //Testing Copy Assignment  (W)
//     cout << "Copy Assignment"<<endl;
//     SquareMatrix<int> sqmassi(4);
//     sqmassi.fill(10);
//     sqmassi.displayMatrix(sqmassi);
//     SquareMatrix<int> sqassignment;
//     sqassignment = sqmassi;
//     sqassignment.displayMatrix(sqassignment);
//     sqmassi.displayMatrix(sqmassi);

//     SquareMatrix<int> sqmr(4);
//     sqmr.fill(10);
//     sqmr.displayMatrix(sqmr);
//     SquareMatrix<int> sql(5);
//     sql.fill(5); 
//     sqmr = sql;
//     sqmr.displayMatrix(sqmr);
// }

// int main() {
//    //To test copy
//     SquareMatrix<int> sqm(4);

//     sqm.fill(5);
//     SquareMatrix<int> sq(sqm);
//     sqm.displayMatrix(sqm);
//     sq.displayMatrix(sq); 

//     sqm.at(0,1);
//     cout<< "before changing:  "<< (sqm.at(0,1)) <<endl;
//     sqm.displayMatrix(sqm);
//     sqm.at(0,1) = 9;
//     cout<< "after changing:  "<<(sqm.at(0,1)) <<endl;
//     sqm.displayMatrix(sqm);
//     cout << sqm.at(1,0);
//     cout << sqm.at(0,0);
//     cout << sqm.at(1,1);
//     sqm.fill(10);
//     cout << sqm.at(0,1);
//     cout << sqm.at(1,0);
//     cout << sqm.at(0,0);
//     cout << sqm.at(1,1);

//     // //Test Add Operator += (W)      //How to test add operator
//     cout <<endl<<"Testing Add operator and move assign"<<endl;
//     SquareMatrix<int> siya(2);
//     siya.fill(5);
//     siya.displayMatrix(siya);
//     SquareMatrix<int> smile(2);
//     smile.fill(1);
//     smile.displayMatrix(smile);
//     SquareMatrix<int> smqe(2);
//     smqe = smile + siya;
//     smqe.displayMatrix(smqe);
   
//     // //How to test resize, 
//      SquareMatrix<int> sm(2);
//      sm.displayMatrix(sm);
//      sm.resize(4);    
//      sm.displayMatrix(sm);      
    
//     //Move constructor
//     SquareMatrix<int> hello(4);
//     hello.fill(10);
//     hello.displayMatrix(hello);
//     SquareMatrix<int> hi(std::move(hello));
//     hi.displayMatrix(hi);
//     cout<<"after hi is dispalyed"<<endl;
//     hello.displayMatrix(hello);


//     //Test Equality Operator    == (W)
//     SquareMatrix<int> s;
//     SquareMatrix<int> nuz;
//     cout << "When matrizes are same 0: "<<(s == nuz) << endl;    //T 1
//     SquareMatrix<int> kai(4);
//     SquareMatrix<int> ksoo(4);
//     cout << "When matrizes are same: "<<(kai == ksoo) << endl;   //T 1
//     SquareMatrix<int> sqt(4);
//     sqt.fill(10);
//     SquareMatrix<int> sqmt(4);
//     sqmt.fill(10);
//     cout << "When matrizes are same w fill "<<(sqt == sqmt) << endl;  //T 1
//     SquareMatrix<int> sqto(5);
//     sqto.fill(10);
//     SquareMatrix<int> sqmto(4);
//     sqmto.fill(10);
//     cout << "When matrizes are not same w fill "<<(sqto == sqmto) << endl;  //F0
//     SquareMatrix<int> sqtos(5);
//     sqtos.fill(5);
//     SquareMatrix<int> sqmtos(5);
//     sqmtos.fill(10);
//     cout << "When matrizes are same w diff fill "<<(sqtos == sqmtos) << endl;  //F0

//     //Test Copy Constructor (W)
//     SquareMatrix<int> seer(4);
//     seer.fill(10);
//     SquareMatrix<int> nuzzy(seer);
//     seer.displayMatrix(seer);
//     nuzzy.displayMatrix(nuzzy);

//     // //Testing Copy Assignment  (W)
//     SquareMatrix<int> sqmr(4);
//     sqmr.fill(10);
//     sqmr.displayMatrix(sqmr);
//     SquareMatrix<int> sql(5);
//     sql.fill(5); 
//     sqmr = sql;
//     sqmr.displayMatrix(sqmr);

//     /* Testing Default Constructor (W)   Paramterized Constructor(W)   Display(W)  Fill(W)    Destructor(W) */
//     cout << "sqm: "<<endl;
//     sqm.displayMatrix(sqm);
//     cout <<endl;
//     cout << "sqm size: "<<sqm.size()<<endl;
//     cout << "sq: "<<endl;
//     sq.displayMatrix(sq);

//     SquareMatrix<int> sqma(4);
//     sqma.fill(5);
//     sqma.displayMatrix(sqma);

//     //Testing Size(W) 
//     cout << "SIZE OF SQ: "<<sq.size()<<endl;
//     cout << "SIZE OF SQM: "<<sqm.size()<<endl; 
    
// }