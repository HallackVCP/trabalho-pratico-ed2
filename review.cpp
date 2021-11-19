#include "Review.h"
#include<string>
#include "const.h"
#include <fstream>
#include <stdlib.h>
#include<stdio.h>
#include <iostream>
using namespace std;

Review::Review(){}

Review::~Review(){}


// GETTERS
/*string Review::getId(){
    return id;
};

string Review::getText(){
    return text;
};

string Review::getUpVotes(){
    return upVotes;
};

string Review::getAppVersion(){
    return appVersion;
};

string Review::getPostedDate(){
    return postedDate;
};
*/

// SETTERS

void Review::setId(string id){
    this->id = id;
}

void Review::setText(string text){
    this->text = text;
}

void Review::setUpVotes(string upVotes){
    this->upVotes = upVotes;
}

void Review::setAppVersion(string appVersion){
    this->appVersion = appVersion;
}

void Review::setPostedDate(string postedDate){
    this->postedDate = postedDate;
}

void Review::printReview() {
    cout<<"----------------------------------------------------------------"<<endl;
    cout<<"Review"<<endl;
    cout<<"ID--> ";
    cout<<this->id<<endl;
    cout<<"Text--> ";
    cout<<this->text<<endl;
    cout<<"UpVotes--> ";
    cout<<this->upVotes<<endl;
    cout<<"AppVersion--> ";
    cout<<this->appVersion<<endl;
    cout<<"PostedDate--> ";
    cout<<this->postedDate<<endl;
    cout<<"----------------------------------------------------------------"<<endl;
}