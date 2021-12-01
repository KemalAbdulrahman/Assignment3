//
//  main.cpp
//  Assignment 3
//
//  Created by Kemal Abdulrahman on 4/20/20.
//  Copyright © 2020 Kemal Abdulrahman. All rights reserved.
//
#include<iostream>
#include<deque>
#include<vector>
#include<fstream>
#include<regex>
#include<string>
#include<sstream>
using namespace std;

string reverse_line(string line){
   string reversed_line;

   for(auto end = line.rbegin(); end != line.rend(); end++){
      reversed_line += *end;
   }

   return reversed_line;
}

deque<string> readfile_in_reverse(string filename){

   ifstream sentences(filename);
   string readline;
   string fixed_sentence;
   deque<string> paragrah;

   if(sentences.is_open()){
      while(getline(sentences, readline)){
         fixed_sentence = reverse_line(readline);
         paragrah.push_back(fixed_sentence);
      }

      sentences.close();
   }
   else{
      cout<<"Oops the file does not exist. Closing the program"<<endl;
      exit(1);
   }

   return paragrah;
}

vector<int> count_words_in_sentences(deque<string> &paragraph, vector<string> query){
   vector<int> word_location;
   int index = 1;
   bool words_exist = true;
   regex pattern;

   for(auto &sentence: paragraph){
      for(auto &word: query){
         regex pattern("\\b"+word+"\\b", regex_constants::icase);

         if(!regex_search(sentence, pattern)) words_exist = false;

      }
      if(words_exist){
         word_location.push_back(index);
      }
      words_exist = true;
      index++;
   }

   return word_location;
}

int main(){
   string filename;
   cout<<"Enter the file name"<<endl;
   getline(cin,filename);
   deque<string> A = readfile_in_reverse(filename);
   for(int i=0;i < A.size();i++){
      cout<<A.at(i)<<endl;
   }

   vector<string> listWords;
   string line;
   string word;
   while(true){
      cout<<"Enter space-separated words: ";
      getline(cin,line);
      if(line=="quit"){
         return 0;
      }
      cout<<"The co-occurance for word: " << line << endl;
      stringstream a (line);


      while(a>>word){
         listWords.push_back(word);


      }


      vector<int> B =count_words_in_sentences(A, listWords);

      cout << "Lines: ";
      for(int x = 0; x < B.size(); x++){
         if(x == B.size() - 1)
            cout << B.at(x) << endl;
         else
            cout << B.at(x) << ", ";
      }
      if(B.size()==0)
         cout<<"None"<<endl;
   }






   return 0;
}


