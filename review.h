#ifndef REVIEW_H
#define REVIEW_H
#include <string>
#include "const.h"
#include <fstream>

using namespace std;
class Review
{
    public:
        Review();
        ~Review();

        /*string getId();
        string getText();
        string getUpVotes();
        string getAppVersion();
        string getPostedDate();
        */
        void setId(string id);
        void setText(string text);
        void setUpVotes(string upVotes);
        void setAppVersion(string appVersion);
        void setPostedDate(string postedDate);
        void printReview();

    private:
        string id;
        string text;
        string upVotes;
        string appVersion;
        string postedDate;

};

#endif // REVIEW_H