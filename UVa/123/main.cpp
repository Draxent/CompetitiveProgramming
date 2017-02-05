#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>


// Defined variables specified by the text of the problem
const int kMaxWordsIgnore = 50;
const int kMaxLengthWordIgnore = 10;
const int kMaxNumTitles = 200;
const int kMaxNumWords = 15;

/// Data structure that holds a pointer to a title and a pointer to a word inside that title
struct RefTitleWord {
  RefTitleWord( const std::vector<std::string>& t, const std::string& w )
      : title(&t), word(&w) { }
  RefTitleWord( const RefTitleWord& other )
      : title(other.title), word(other.word) { }
  RefTitleWord& operator=( const RefTitleWord& other ) {
    title = other.title; word = other.word;
    return *this;
  }
  const std::vector<std::string>* title;
  const std::string* word;
};

/**
 * Since the line must contain no characters other than 'a' - 'z', 'A' - 'Z', and white space
 * the line contains a spearator if its first character is ':'
 * @param line  the line to parse
 * @return      \c true if the line contains the separator, \c false otherwise
 */
inline bool check_separator( const std::string& line ){
  return (line[0] == ':');
}

/**
 * Read and init the vector of the words to ignore
 * @return  the vector containing the words to ignore
 */
std::vector<std::string> read_words_ignore(){
  std::vector<std::string> words_ignore;
  words_ignore.reserve(kMaxWordsIgnore);

  std::string line;
  line.reserve(kMaxLengthWordIgnore);
  // Read from input until EOF or separator field
  while ( std::getline(std::cin, line) && !check_separator(line) ){
    // Move the string read into the vector
    words_ignore.push_back( std::move(line) );
    // Reset the space allocation for the line string
    line.reserve(kMaxLengthWordIgnore);
  }

  return words_ignore;
}

/**
 * Read from input title and insert spaces into the title vector
 * @param iss       input stream
 * @param word      space word to insert
 * @param title     vector where to store the words
 */
void insert_spaces( std::istringstream& iss, std::string& word, std::vector<std::string>& title ){
  while( iss.peek() == ' ' ){
    iss.get();
    word += ' ';
  }
  if ( !word.empty() )
    title.push_back( std::move(word) );
}

/**
 * Read and init the current title and insert all the keywords found into the keywords vector
 * @param line          line where extract the title
 * @param title         vector where to store the words
 * @param words_ignore  the vector containing the words to ignore
 * @param keywords      the vector of keywords
 */
void read_title( const std::string& line, std::vector<std::string>& title,
                 const std::vector<std::string>& words_ignore, std::vector<RefTitleWord>& keywords ){
  std::istringstream iss(line);
  // Insert the words in the line into the current entry vector
  std::string word;
  insert_spaces( iss, word, title );
  while ( getline( iss, word, ' ' ) ){
    // Move the string read into the current title
    title.push_back( std::move(word) );
    // If the word is not to ignore
    if ( !std::binary_search(words_ignore.begin(), words_ignore.end(), title.back()) ){
      // Add a reference to this word and its title into the keywords vector
      keywords.push_back( RefTitleWord(title, title.back()) );
    }
    // Insert spaces after the word read, except for the last word read
    if ( iss.peek() != EOF ){
      word = " ";
      insert_spaces( iss, word, title );
    }
  }
}

/**
 * Read and init the array of titles and insert all the keywords found into the keywords vector
 * @param words_ignore  the vector containing the words to ignore
 * @param keywords      the vector of keywords
 * @return              the array containing the titles
 */
std::vector<std::vector<std::string>> read_titles( const std::vector<std::string>& words_ignore,
                                                   std::vector<RefTitleWord>& keywords ){
  std::vector<std::vector<std::string>> titles;
  titles.reserve(kMaxNumTitles);

  size_t k = 0;
  std::string line;
  // Read from input until EOF
  while ( std::getline(std::cin, line) ){
    if ( line.empty() ) continue;
    // Transform the line into lower case
    std::transform( line.begin(), line.end(), line.begin(), tolower );

    // Add new title
    titles.push_back( std::vector<std::string>() );
    titles[k].reserve(2*kMaxNumWords+1); // store the spaces too
    read_title( line, titles[k], words_ignore, keywords );
    k++;
  }

  return titles;
}

/// MAIN
int main(){
	std::ios_base::sync_with_stdio(false);

	// DEBUG: Redirection of stdin
  //  std::ifstream in( "/home/draxent/Scrivania/Contests/UVa/123/input2.txt" );
  //  std::cin.rdbuf( in.rdbuf() );

  // Read the words to ignore and sort them
  std::vector<std::string> words_ignore = read_words_ignore();
  std::sort( words_ignore.begin(), words_ignore.end() );

  // DEBUG: Print the word to ignore
  //  for ( const std::string& word : words_ignore )
  //    std::cout << word << ", ";
  //  std::cout << std::endl << std::endl;

  // Vector that stores all the keywords of the list of titles
  std::vector<RefTitleWord> keywords;
  // Read the titles (variable unused but its contents it is used indirectly trough keywords)
  std::vector<std::vector<std::string>> titles = read_titles( words_ignore, keywords );

  // DEBUG: Print the titles
  //  for ( const std::vector<std::string>& words : titles ){
  //    std::cout << (&words - &titles[0]) << ") ";
  //    for( const std::string& word : words )
  //      std::cout << word << " ";
  //    std::cout << std::endl;
  //  }
  //  std::cout << std::endl;

  // Sort the keywords
  std::sort( keywords.begin(), keywords.end(), [](const RefTitleWord& a, const RefTitleWord& b) {
    // Compare the two keyword string
    int res = strcmp( a.word->c_str(), b.word->c_str() );
    // If they are not equal return the comparison, otherwise respect the original order of the titles
    // If a title as more the an equal keyword, respect the order of the words inside the title
    if ( res == 0 ){
      if ( a.title == b.title ) return (a.word < b.word);
      else return (a.title < b.title);
    }
    else return (res < 0);
  });

  // DEBUG: Print the keywords
  //  for( const RefTitleWord& ref : keywords )
  //    std::cout << "(" << *ref.word << "," << (ref.title - &titles[0]) << "," << (ref.word - &(*ref.title)[0]) << "); ";
  //  std::cout << std::endl << std::endl;

  for( const RefTitleWord& ref : keywords ){
    for( const std::string& word : *(ref.title) ){
      // Check if the current word is equal of the keyword
      if ( &word == ref.word ){
        // Convert the keyword in uppercase and print it
        std::string uppercase;
        uppercase.resize(word.size());
        std::transform( word.begin(), word.end(), uppercase.begin(), toupper );
        std::cout << uppercase;
      }
      else
        std::cout << word;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  return 0;
}