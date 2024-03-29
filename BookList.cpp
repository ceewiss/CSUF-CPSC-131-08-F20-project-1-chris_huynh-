#include <algorithm> // find(), move(), move_backward(), equal(), swap(), lexicographical_compare() // written by Chris Huynh

#include <cstddef> // size_t

#include <iomanip> // setw()

#include <string>

#include <cstdlib>

#include <cmath>

#include <fstream>

#include "BookList.hpp"

namespace // written by Chris Huynh

{

// Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is

// represented by Epsilon. Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three

// decimal places) we can be a bit more tolerant. Two floating point values are considered equal if they are withing EPSILON of

// each other.

constexpr auto EPSILON = 1.0E-4;

}

/**********************************************

** Private implementations, types, and objects

** for class Book

************************************************/

/************************

** Constructor

************************/

Book::Book( const std::string& title,

const std::string& author,

const std::string& isbn,

const double & price )

// Use the constructor initialization list

: _isbn (isbn), _title (title), _author( author ),

_price ( price )

{} // Avoid setting values in constructor's body (when possible)

// written by Chris Huynh

/*************************

** Queries or getters

**************************/

std::string Book::get_isbn() const

{ return _isbn; }

std::string Book::get_title() const

{ return _title; }

std::string Book::get_author() const

{ return _author; }

double Book::get_price() const

{ return _price; }

/***********************************

** Mutators or setters

************************************/

// written by Chris Huynh

void Book::set_isbn( const std::string& newIsbn )

{ _isbn = newIsbn; }

void Book::set_title( const std::string& newTitle )

{ _title = newTitle; }

void Book::set_author( const std::string& newAuthor )

{ _author = newAuthor; }

void Book::set_price( double newPrice )

{ _price = newPrice; }

/***********************************

** Friend functions: read and write

************************************/

std::istream & operator>>( std::istream & stream, Book & book )

{

Book workingItem;

char delimiter = ',';

// Assume fields are separated by commas and string attributes are

// enclosed with double quotes. For example:

// "9789998287532", "Over in the Meadow", "Ezra Jack Keats", 91.11

stream >> std::quoted( workingItem._isbn ) >> delimiter

>> std::quoted( workingItem._title ) >> delimiter

>> std::quoted( workingItem._author ) >> delimiter

>> workingItem._price;

// If all okay, move workingItem into the returned book. Copying the

// information also "works" but moving is more efficient. Note this

// uses Book's move assignment operator.

if(stream) book = std::move( workingItem );

return stream;

}

std::ostream & operator<<( std::ostream & stream, const Book & book )

{

const std::string delimiter = ", ";

stream << std::quoted( book.get_isbn() ) << delimiter

<< std::quoted( book.get_title() ) << delimiter

<< std::quoted( book.get_author() ) << delimiter

<< book.get_price();

return stream;

}

// written by Chris Huynh

/*************************************************

** Ordinary functions: Relational Operators

**************************************************/

bool operator==( const Book & lhs, const Book & rhs )

{

// Implement equality in terms of less than to enforce identical

// column priority ordering and floating point epsilon comparison tolerance.

return lhs._isbn == rhs._isbn

&& lhs._title == rhs._title

&& lhs._author == rhs._author

&& std::abs( lhs._price - rhs._price ) < EPSILON;

}

bool operator!=( const Book & lhs, const Book & rhs )

{ return !( lhs == rhs ); }

/**********************************************

** Private implementations, types, and objects

** for class BookList

************************************************/

/*************************************

** Friend functions: read and write

**************************************/

std::ostream & operator<<( std::ostream & stream, const BookList & bookList )

{

for (unsigned i=0; i< bookList._books_array_size; i++) {

stream << '\n' << std::setw(5) << i << ": " << bookList[i];

}

return stream;

}



std::istream & operator>>( std::istream & stream, BookList & bookList )

// read at most <_capacity> books

{

Book book;

unsigned counter = 0;

while(stream && counter < bookList._capacity) {

stream >> book;

bookList._bookArray[counter++] = std::move(book);

}

if (counter < bookList._capacity)

// written by Chris Huynh

// read less books than <_capacity>

// so set it to actual number of books read

bookList._books_array_size = counter;

return stream;

}

/***********************

** Constructor

************************/

// TO DO

BookList::BookList(const std::size_t & newSize)

{

_capacity = newSize;

_books_array_size = 0;

_bookArray = new Book[newSize];

}

/************************

** Assignment operator

************************/

// TO DO

BookList & BookList::operator+=( const BookList & rhs)

{

// Concatenate the righthand side book list of books to this list

// by repeatedly adding each book at the end of the current book list

// as long as it does not exceed <_capacity>

// If exceeds, then stop adding

// written by Chris Huynh

int right_hand_book_list_index = 0;

while(_books_array_size < _capacity && right_hand_book_list_index < rhs.size()) {

_bookArray[_books_array_size++] = rhs[right_hand_book_list_index++];

}

return *this;

}

/*********************

** Destructor

*********************/

// TO DO

BookList::~BookList()

{

delete []_bookArray;

}

/***********************

** Queries or getters

************************/

// TO DO

std::size_t BookList::size() const

{

return _books_array_size;

}

//TO DO

std::size_t BookList::find( const Book & book ) const

// Locate the book in this book list and return the zero-based position

// of that book. If the book does not exist, return the size of this

// book list as an indicator the book does not exist.

{

for(int i = 0; i < _books_array_size; i++) {

if(_bookArray[i] == book) {

return i;

}
// written by Chris Huynh
}

return _books_array_size;

}

Book BookList::operator[](std::size_t index) const {

return _bookArray[index];

}

/*************************

** Read from the file

**************************/

// written by Chris Huynh

void BookList::readInFile(const std::string& filename) {

std::ifstream inFile(filename);

Book newBook;

unsigned i=0;

// Read each line

while ((inFile >> newBook) && (i < _capacity)) {

_bookArray[i++] = newBook;

}

_books_array_size = i;

}

// written by Chris Huynh
