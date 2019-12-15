#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <random>

using std::vector;
using std::string;
using std::pair;
// will be used during the work with program
 enum type_of_user {_fixed,// fixed probability of appearence of errors
                    _was_before_depend, // was before in story -> probability -= 2
                    _time_of_usage_depend}; //each 5 hours (ALL USAGE ) probability --
class user
{
private:
     type_of_user _type;
     string _name;
     struct debugStory{
        string _bug;
        int _time_of_appearence;
        int _time_of_fix;
        debugStory(string bug,int time_of_appearence,int time_of_fix);// need to pass error.type
     };
     void generate_type_of_user();
     /*
      * brief generate programs that uses user and average time for them
      */
     void set_program_and_average_time(std::vector<string> available_programs);
public:
    vector<pair<string,int>> program_and_average_time; // program- program that user uses
                                                        //int - average time of usage of this program
    vector <debugStory> story;
    string name() const;
    /*
     * brief cals set_program_and_average_time()
     */
    user(vector<string> available_programs, string user_name);
};

#endif // USER_H
