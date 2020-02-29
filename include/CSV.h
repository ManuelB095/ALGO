#ifndef CSV_H
#define CSV_H

#include <vector>
#include <string>


using std::vector;
using std::string;
class CSV
{
private:
    string m_file_path;
    char m_delimiter;

    vector<string> split(const string &line);

    string get_new_row(const vector<string> &row);

public:
    CSV(string &file_path, char delimiter = ',');

    vector<vector<string>> read();

    void write_row(const vector<string> &row, char method = 'w');
    void write_rows(const vector<vector<string>> &rows, char method = 'w');
};


#endif
