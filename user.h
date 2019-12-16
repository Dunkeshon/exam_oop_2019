#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <random>
#include "error.h"

using std::vector;
using std::string;
using std::pair;
// will be used during the work with program
 enum type_of_user {_fixed,// fixed probability of appearence of errors
                    _was_before_depend, // was before in story -> probability -= 2
                    _time_of_usage_depend}; //each 10-20 hours (ALL USAGE ) probability --
class user
{
private:

     pair<string,int> _current_program;
     bool _occupied;
     int _necessary_work_time; // necessary_work_time_with_current_program
     type_of_user _type;
     string _name;
     struct debugStory{
        string _bug;
        int _time_of_appearence;
        int _time_of_fix;
        debugStory(string bug,int time_of_appearence);// need to pass error.type
     };
     void generate_type_of_user();
     /*
      * brief generate programs that uses user and average time for them
      */
     void set_program_and_average_time(std::vector<string> available_programs);
     int get_final_chance(int chance,int hours_passed,string name_of_possible_chance); // receive final chance based on the type of the user
     /*
      * return true if bug spotted
      */
     bool randomise_appearence_of_a_bug(int chance);
public:
     /*
      * working on program and try to avoid bugs
      * if there is a bug put it in the story and say that there is a bug and you need to fix it
      */
     void working_on_program(vector<error> available_errors,int hours_passed);
     bool bug_spotted;
     int current_bug_working_time_left; // firstly set full time, then time --
     /*
      * randomize and sets value inside the function
      */
     void create_time_of_usage();
     /*
      * randomize and sets value inside the function
      */
     void pick_up_random_program();

     vector<error> shuffle_bugs(vector<error> available_errors);
     pair<string,int> current_program() const;
     void Set_current_program(pair <string,int> program);
     bool occupied() const;
     void Set_occupied(bool occupied);
     int necessary_work_time() const;
     void Set_necessary_work_time(int time);
     void Set_time_of_fix(int time_of_fix);
    vector<pair<string,int>> program_and_average_time; // program- program that user uses
                                                        //int - average time of usage of this program
    vector <debugStory> story;
    string name() const;
    /*
     * brief cals set_program_and_average_time()
     */
    user(vector<string> available_programs, string user_name);
    user();
    user(const user &obj);
};

#endif // USER_H
