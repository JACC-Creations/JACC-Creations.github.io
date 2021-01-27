/**********************************************************/
/*                                                        */
/*   Written by: Catherine Leung                          */
/*   Version 1.0                                          */
/*                                                        */
/*   This program uses a text file with a list of         */
/*   words and creates a Trie Object from it.             */
/*   It will then use it to Trie the text of              */
/*   various full text books                              */
/*                                                        */
/*   This version of the tester is meant to be used if    */
/*   you are working on it locally on your own machine.   */
/*                                                        */
/*   If you are working on matrix                         */
/*   please use the other tester, and it will read        */
/*   the files from my directory and you won't            */
/*   need your own copy of the files.                     */
/*                                                        */
/*   To compile this program:                             */
/*     c++ a3main.local.cpp trie.cpp timer.cpp -std=c++0x */
/*                                                        */
/*   To experiment:                                       */
/*      a.out <number of lookups> <number of suggestions> */
/*                                                        */
/**********************************************************/

#include <cctype>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
#include "trie.h"
#include "timer.h"

#define ON 1
#define OFF 0
#define DEBUG OFF


void toLower(char* word);
const int numWords=234368;
const int numInitial=10000;
const int numFiles=62;
const char filenames[62][45]={"advsh12.txt","bskrv11.txt",
"lcrfx10.txt","lostw10.txt","memho11.txt","rholm10.txt",
"totam10.txt","ttmgd10.txt","dracula.txt","frankenstein.txt",
"pg100.txt", "pg11.txt", "pg1184.txt", "pg120.txt","pg1260.txt",
"pg1342.txt","pg135.txt", "pg1400.txt", "pg16.txt", "pg161.txt",
"pg1644.txt", "pg2147.txt","pg22381.txt", "pg2343.txt", "pg2344.txt",
"pg2345.txt","pg2346.txt","pg2347.txt","pg2349.txt","pg236.txt",
"pg244.txt","pg2591.txt","pg2600.txt","pg2701.txt","pg30601.txt",
"pg356.txt","pg36.txt","pg37712.txt","pg41.txt","pg5000.txt",
"pg521.txt","pg730.txt","pg74.txt","pg76.txt","pg766.txt",
"pg98.txt","pg158.txt","pg1399.txt","pg2148.txt","pg526.txt",
"pg863.txt","pg1155.txt","pg47.txt","pg45.txt","pg51.txt",
"pg544.txt","pg1354.txt","pg5340.txt","pg316.txt","pg5341.txt",
"pg5342.txt","pg3796.txt"
};
const char suggestions[11][45]={
    "apple", "carrot", "sublime","cart",
    "dramat","famil","city","world",
    "yard","adver","event"
};

int main(int argc, char* argv[]){
    Timer createTimer;
    std::string path="a3textfiles/";
    FILE* fp=fopen("a3textfiles/a3dictionary.txt","r");
    FILE* fp2;
    FILE* fp3;
    int numNotFound=38329;
    int numLookupTrie = numWords+numNotFound;
    int numSuggestTrie = numWords+numNotFound;
    if(argc == 2){
        numLookupTrie=atoi(argv[1]);
    }
    if(argc== 3){
        numLookupTrie=atoi(argv[1]);
        numSuggestTrie=atoi(argv[2]);
    }
    if(!fp){
        cout << "could not open file a3dictionary.txt." << endl;
        cout << "You need to get a copy of this from a3textfiles folders" << endl;
        return 0;
    }
    char curr[1000];              //used to read in words from text file
    char curr2[1000];              //used to read in words from text file
    std::string* wordList;
    std::string* suggestList;
    std::string* correctSuggestions; 
    bool rc,error;
    int correctNumSuggestions;
    int numSuggestions;
    suggestList=new std::string[5000];
    correctSuggestions=new std::string[60];
    wordList=new std::string[numWords+numNotFound];
    for(int i=0;i<numWords;i++){
        fscanf(fp,"%s\n",curr);                
        toLower(curr);
        wordList[i].append(curr);            
    }
    createTimer.start();
    Trie checker(wordList,numInitial);
    createTimer.stop();
    cout << numInitial << " words added to the Trie" << endl;
    for(int i=numInitial;i<numWords;i++){
        rc=checker.lookup(wordList[i]);
        if(rc){
            cout << "The word: " << wordList[i] << " should not currently be in Trie" << endl;
            return 0;
        }
        createTimer.start();
        checker.addWord(wordList[i]);
        createTimer.stop();
        if(i%10000==9999){
            cout << i+numInitial << " words added to the Trie" << endl;
        }
    }
    fclose(fp);
    cout << "Trie loaded: " << numWords << " stored" << endl;
    cout << "Time for loading Trie: " << createTimer.currtime() << endl;

    fp=fopen("a3textfiles/suggestions.txt","r");

    //for(int i=0;i<11;i++){
    //    fscanf(fp,"%d\n",&correctNumSuggestions);        //read in a word from data file
    //    for(int j=0;j<correctNumSuggestions;j++){
    //        fscanf(fp,"%s\n",curr);
    //        toLower(curr);
    //        correctSuggestions[j]=curr;                   //record it
    //    }
    //    numSuggestions=checker.suggest(suggestions[i],suggestList);
    //    if(correctNumSuggestions != numSuggestions){
    //        cout << "return value from suggest function is not correct" << endl;
    //        cout << "For the partial word "<< suggestions[i]  << endl;
    //        cout << "Correct return value is: " << correctNumSuggestions << endl;
    //        cout << "Your return value is: " << numSuggestions << endl;
    //        return 0;
    //    }
    //    else{
    //        bool isSame=true;
    //        for(int j=0;isSame && j<numSuggestions;j++){
    //            if(suggestList[j] != correctSuggestions[j]){
    //                isSame=false;
    //            }
    //        }
    //        if(!isSame){
    //            cout << "your suggestions list is not correct." << endl;
    //            cout << "Checking for the partial word: " << suggestions[i] << endl;
    //            for(int j=0;j<numSuggestions;j++){
    //                cout << "Correct word #" << j+1<< ": " << correctSuggestions[j];
    //                cout << " Your Suggestion List #" << j+1<< ": " << suggestList[j] << endl;
    //            }
    //            return 0;
    //        }
    //    }
    //}
    //fscanf(fp,"%d\n",&correctNumSuggestions);                //read in a word from data file
    //for(int j=0;j<correctNumSuggestions;j++){
    //    fscanf(fp,"%s\n",curr);
    //    toLower(curr);
    //    correctSuggestions[j]=curr;                   //record it
    //}
    for(int i=0;i<numWords;i++){
        rc=checker.lookup(wordList[i]);
        if(!rc){
            cout << i << endl;
            cout << "Error: " << wordList[i] << " is not in the Trie and it should have been" << endl;
            return 0;
        }
    }

    fp3=fopen("a3textfiles/notfound.txt","w");   

    for(int i=0;i<numFiles;i++){

        fp2=fopen((path+filenames[i]).c_str(),"r");  
        if(!fp2){
            cout << "could not open the file: " << filenames[i] << endl;
            cout << "You need to get a copy of this from a3textfiles folders" << endl;

            return 0;
        }
        else{
            fscanf(fp2,"%[^A-Za-z]*",curr);  
            toLower(curr);
            int j=0;
            while(!feof(fp2)&& fscanf(fp2,"%[A-Za-z]*",curr)==1){
                toLower(curr);
                rc=checker.lookup(curr);
                if(!rc){
                    createTimer.start();
                    checker.addWord(curr);
                    createTimer.stop();
                    fprintf(fp3,"%s\n",curr);
                }
                j++;
                //read non-word
                fscanf(fp2,"%[^A-Za-z]*",curr);
                toLower(curr);
            }
            cout << "completed spell check of: " << filenames[i] << endl;
            fclose(fp2);
        }
    }
    fclose(fp3);
    //numSuggestions=checker.suggest("event",suggestList);
    //if(correctNumSuggestions != numSuggestions){
    //    cout << "return value from suggest function is not correct" << endl;
    //    cout << "For the partial word "<< "event"  << endl;
    //    cout << "Correct return value is: " << correctNumSuggestions << endl;
    //    cout << "Your return value is: " << numSuggestions << endl;
    //    return 0;
    //}
    //else{
    //    bool isSame=true;
    //    for(int j=0;isSame && j<numSuggestions;j++){
    //        if(suggestList[j] != correctSuggestions[j]){
    //            isSame=false;
    //        }
    //    }
    //    if(!isSame){
    //        cout << "your suggestions list is not correct." << endl;
    //        cout << "Checking for the partial word: " << "event" << endl;
    //        for(int j=0;j<numSuggestions;j++){
    //            cout << "Correct word #" << j+1<< ": " << correctSuggestions[j];
    //            cout << " Your Suggestion List #" << j+1<< ": " << suggestList[j] << endl;
    //        }
    //        return 0;
    //    }
    //}

    int notfound=0;
    for(int i=0;i<numFiles;i++){

        fp2=fopen((path+filenames[i]).c_str(),"r");
        if(!fp2){
            cout << "could not open the file: " << filenames[i] << endl;
            cout << "You need to get a copy of this from a3textfiles folders" << endl;
           return 0;
        }   
        else{
            fscanf(fp2,"%[^A-Za-z]*",curr);
            while(!feof(fp2)&& fscanf(fp2,"%[A-Za-z]*",curr)==1){
                toLower(curr);
                rc=checker.lookup(curr);
                if(!rc){
                    notfound++;
                    #if DEBUG == ON
                    cout << "the word: " << curr << " should be in the Trie" << endl;
                    #endif
                }
                fscanf(fp2,"%[^A-Za-z]*",curr);
            }
            cout << "completed 2nd pass of : " << filenames[i] << endl;
            fclose(fp2);
        }
    }
    if(notfound!=0){
        cout << "you have a bug in your program.  A word that was added" << endl;
        cout << "and not found when searched for again" << endl;
    }
    else{

        fp2=fopen("a3textfiles/notfoundcheck.txt","r");
        fp3=fopen("a3textfiles/notfound.txt","r");
        if(!fp2){
            cout << "could not open the file: notfoundcheck.txt" << endl;
            cout << "You need to get a copy of this from a3textfiles folders" << endl;
            return 0;
        }
        fscanf(fp2,"%s\n",curr);
        fscanf(fp3,"%s\n",curr2);
        error=false;
        int i=0;
        while(!feof(fp2) && !feof(fp3)){

            if(strcmp(curr,curr2)!=0){
                error=true;
            }
            else{
                wordList[numWords+i] = curr;
                i++;
            }
            fscanf(fp2,"%s\n",curr);
            fscanf(fp3,"%s\n",curr2);
        }
        if(!(feof(fp2)&&feof(fp3)) || error){
            cout << "your output of words not in Trie does not match expected list" << endl;
            cout << "looks like you will have to fix your program still" << endl;
        }
        else{
            cout << "Congratulations! It appears that your assignment is working!" << endl;
            cout << "Time for loading words into your Trie: " << createTimer.currtime() << endl;
            Timer lookupTimer;
            Timer suggestionTimer;

            int j=0;
            for(int i=0;i<numLookupTrie;i++){
                lookupTimer.start();
                rc=checker.lookup(wordList[j]);
                lookupTimer.stop();
                j=(j+1)%numWords;
            }
            cout << "Time for " << numLookupTrie << " lookups: " << lookupTimer.currtime() << endl;
            j=0;
            for(int i=0;j<numSuggestTrie;i=(i+1)%numWords){
                if(wordList[i].length() > 3){
                    suggestionTimer.start();
                    numSuggestions=checker.suggest(wordList[i],suggestList);
                    suggestionTimer.stop();
                    j++;
                }
            }
            cout << "Time for " << numSuggestTrie << " suggestions: " << suggestionTimer.currtime() << endl;
        }
        fclose(fp2);
        fclose(fp3);
    }

    delete [] wordList;
    delete [] suggestList;
    delete [] correctSuggestions;

}

void toLower(char* word){
    for(int i=0;word[i]!='\0';i++){
        word[i]=tolower(word[i]);
    }
}


