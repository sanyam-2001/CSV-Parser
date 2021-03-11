#include <bits/stdc++.h>

using namespace std;

class CSVParser{
    private:
    //Members
    ifstream file; //Pointer to the CSV file
    vector<string> headings; //Stores Columns
    vector<vector<string>> rows; //Stores Column-wise Rows

    //Utility Function to Parse Rows with respect to Delimiter
    vector<string> parse_rows(string unparsed_row, char delimiter);
    public:

    //Default Constructor
    CSVParser(string path, char delimiter=',');
    //Member Functions
    vector<string> getHeadings(){return headings;}
    vector<vector<string>> getRows(){return rows;}
    vector<string> operator[](string identifier);
    vector<int> shape();
    void display();

};

//Function Definitions
CSVParser::CSVParser(string path, char delimiter){
        file.open(path);
        int current_line=0;
        string line;
        while(getline(file, line)){
            vector<string> parsed_row = parse_rows(line, delimiter);
            if(current_line==0){
                headings = parsed_row;//Initializing Headings
            }
            else{
                rows.push_back(parsed_row); // Initializing Rows
            }
            current_line++;
        }
        file.close();
}
//To parse strings into rows
//This can also be accomplished by using strtok
vector<string> CSVParser::parse_rows(string unparsed_row, char delimiter){
    vector<string> parsed_row;
    string temp="";
    for(auto i:unparsed_row){
        if(i==delimiter){
            parsed_row.push_back(temp);
            temp="";
        }
        else{
            temp+=i;
        }
    }
    if(temp!="")parsed_row.push_back(temp);
    return parsed_row;
}
//Selecting one Row based on heading identifier
vector<string>CSVParser::operator[](string identifier){
    vector<string> column_values;
    try{
        int i;
        for(i=0;i<headings.size();i++){
            if(headings[i]==identifier)break;
        }
        if(i==headings.size())throw -1;
        for(int j=0;j<rows.size();j++){
            column_values.push_back(rows[j][i]);
        }
        return column_values;
    }
    catch(int err){
        if(err==-1){
            cout<<"No such Identifier exists"<<endl;
            vector<string> temparr;
            return column_values;
        }
    }
}
//Shape of Parser
vector<int> CSVParser::shape(){
    vector<int> shape_arr(2);
    shape_arr[0] = headings.size();
    shape_arr[1] = rows.size();
    return shape_arr;
}
void CSVParser::display(){
    for(int i=0;i<headings.size();i++){
            cout << left << setw(15) << setfill(' ') << headings[i];
    }
    cout<<endl;
    cout<<endl;
    for(int i=0;i<rows.size();i++){
        for(int j=0;j<rows[0].size();j++){
                cout << left << setw(15) << setfill(' ') << rows[i][j];
        }
        cout<<endl;
    }
}

int main()
{
    CSVParser parser("csvfile.csv");//Creating CSVParser Object
    parser.display(); // Displaying the Data Frame
    vector<string> headings = parser.getHeadings();//Getting the Column Names
    vector<vector<string>> rows = parser.getRows();//Getting corresponding Values
    cout<<endl<<"Headings"<<endl;

    for(auto i:headings)cout<<i<<" ";
    cout<<endl;
    cout<<endl<<"Rows"<<endl;
    for(auto i:rows){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }

    cout<<endl;


    vector<string> age_series =  parser["age"], handle = parser["not_present"];//Showcases the selection of a particular row

    for(int i=0;i<age_series.size();i++){
        cout<<age_series[i]<<" ";
    }
    cout<<endl;

    for(int i=0;i<handle.size();i++){
        cout<<handle[i]<<endl;
    }
    return 0;
}
