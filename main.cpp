#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <vector>

using namespace std;

const long int SECONDS = 3;
mutex isBusy;
int table[3] = {1, 1, 1}; // [tobacoo, paper, match]
string ingrids[3] = {"tobacoo", "paper", "match"};



void show_message( string msg) {
    cout << endl << msg << endl;
}

void pause_all(){
    std::this_thread::sleep_for( std::chrono::seconds(SECONDS) );
}

void broker(){
    isBusy.lock();
    int summ = 0;
    for (int i = 0; i < 3; i++){
        summ += table[i];
    }
    if (summ == 3) {
        show_message("Broker watch for ingridients...");
        int num = 0;
        for ( int i = 0; i < 3; i++ ) table[i] = 0;
        pause_all();
        cout << "And puts : ";
        while ( num < 2 ){
            int pos = random()%3;
            if ( table[ pos ] == 0 ) {
                num++;
                table[ pos ] = 1;
                cout << ingrids[ pos ] << " ";
            }
        }
        cout << endl;


    }
    isBusy.unlock();
}

void tobacoo_smoker(){
    isBusy.lock();
    if ( table[0] == 0 ){
        for ( int i = 0; i < 3; i++ ) table[i] = 1;
        show_message("Smoker with tobacoo smokes... ");
        pause_all();
    }
    isBusy.unlock();
}

void paper_smoker(){
    isBusy.lock();
    if ( table[1] == 0 ){
        for ( int i = 0; i < 3; i++ ) table[i] = 1;
        show_message("Smoker with paper smokes... ");
        pause_all();
    }
    isBusy.unlock();
}

void match_smoker(){
    isBusy.lock();
    if ( table[2] == 0 ){
        for ( int i = 0; i < 3; i++ ) table[i] = 1;
        show_message("Smoker with match smokes... ");
        pause_all();
    }
    isBusy.unlock();
}




int main()
{
    vector<thread> th;

    while( true ){
        th.push_back( thread(&broker) );
        th.push_back( thread(&tobacoo_smoker) );
        th.push_back( thread(&paper_smoker) );
        th.push_back( thread(&match_smoker) );
        for ( int i = 0; i < 4; i++){
            th[i].join();
        }
        th.clear();
    }


    return 0;
}
