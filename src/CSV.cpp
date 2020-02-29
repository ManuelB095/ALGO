#include "CSV.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


using std::string;
using std::vector;

CSV::CSV(std::string &file_path, char delimiter)
{
    m_file_path = file_path;
    m_delimiter = delimiter;
}

vector<string> CSV::split(const string &line)
{
    vector<string> row;
    string cell;
    std::istringstream s(line);
    while (getline(s, cell, m_delimiter))
    {
        row.push_back(cell);
    }
    return row;
}

string CSV::get_new_row(const std::vector<std::string> &row)
{
    string new_row;
    for (int i = 0; i < row.size(); i++)
    {
        string last = ",";
        if (i == row.size() - 1)
            last = "\n";
        new_row += row[i] + last;
    }
    return new_row;
}

vector<vector<string>> CSV::read()
{
    vector<vector<string>> data;
    std::ifstream f_out(m_file_path);
    if (f_out.is_open())
    {
        string line;
        while (getline(f_out, line))
        {
            vector<string> row = split(line);
            data.push_back(row);
        }
    }
    f_out.close();
    return data;
}

void CSV::write_row(const vector<string> &row, char method)
{
    std::ofstream file;
    if (method == 'w')
        file.open(m_file_path, std::ios_base::out);
    else
        file.open(m_file_path, std::ios_base::app);
    if (file.is_open())
    {
        string new_row = get_new_row(row);
        file << new_row;
    }
    file.close();
}

void CSV::write_rows(const std::vector<std::vector<std::string>> &rows, char method)
{
    std::ofstream file;
    if (method == 'w')
        file.open(m_file_path, std::ios_base::out);
    else
        file.open(m_file_path, std::ios_base::app);
    if (file.is_open())
    {
        for (auto row : rows)
        {
            string new_row = get_new_row(row);
            file << new_row;
        }
    }
    file.close();
}

