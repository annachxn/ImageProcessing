
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <string.h>
using namespace std;

#include "tga.h"


int main (int argc, char* argv[]) {
// first arg - name of output file
// second arg - name of first target file
// third arg - name of method
// fourth file, method, file, method

    // 2 images
    vector<string> methodlist;
    methodlist.push_back("combine"); // 0
    // 1 image
    methodlist.push_back("screen"); // 1
    methodlist.push_back("multiply"); // 2
    methodlist.push_back("subtract"); // 3
    methodlist.push_back("overlay"); // 4
    // 1 number
    methodlist.push_back("scalered"); // 5
    methodlist.push_back("scalegreen"); // 6
    methodlist.push_back("scaleblue"); // 7
    methodlist.push_back("addred"); // 8
    methodlist.push_back("addgreen"); // 9
    methodlist.push_back("addblue"); // 10
    // no arguments
    methodlist.push_back("onlyred"); // 11
    methodlist.push_back("onlygreen"); // 12
    methodlist.push_back("onlyblue"); // 13
    methodlist.push_back("flip"); // 14


    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        cout << "Project 2: Image Processing, Spring 2023\n\n";
        cout << "Usage:\n";
        cout << "\t./project2.out [output] [firstImage] [method] [...]\n";
        return 0;
    }


    string curr = argv[1];// first arg = output file
    try {
        curr.substr(curr.size() - 4, curr.size());
    }
    catch (...) {
        cout << "Invalid file name.\n";
        return 0;
    }


    string ending = curr.substr(curr.size() - 4);
    if (ending != ".tga") {
        cout << "Invalid file name.\n";
        return 0;
    }

    if (argc < 3){ // executable + output, no first file
        cout << "Invalid file name.\n";
        return 0;
    }


    string writefile = argv[1];


    curr = argv[2]; // first file argv[2]

    ending = curr.substr(curr.size() - 4, curr.size());

    if (ending != ".tga") {
        cout << "Invalid file name.\n";
        return 0;
    } else if (!exists(curr)) {
        cout << "File does not exist.\n";
        return 0;
    }

    Image tracking;
    tracking.readImage(curr);

    // first method
    curr = argv[3];

    vector<string> argslist;
    string argument;
//    argslist[0] = "empty";
    for (int i = 1; i < argc; i++){
        argument = argv[i];
        argslist.push_back(argument);
    }

    if (check(argslist, methodlist)){
        // first method
        for (int i = 0; i < 15; i++) {
            if (argv[3] == methodlist[i]) {
                if (i == 0) { // 2 images
                    string firstimage = argv[4];
                    string secondimage = argv[5];
                    cout << "Combining channels of " << argv[2] << ", " <<
                         firstimage << ", and " << secondimage << " ...\n";
                    Image first;
                    first.readImage(firstimage);
                    Image second;
                    second.readImage(secondimage);
                    if (firstimage != "input/layer_blue.tga"){
                        tracking.combo2(first, second);
                        break;
                    }
                    tracking.combo(first, second);
                    break;
                } else if (i < 5) { // 1 image
                    string firstimage = argv[4];
                    if (i == 1) { // screen
                        cout << "Screening " << argv[2] << " and " << firstimage << " ...\n";
                        Image first;
                        first.readImage(firstimage);
                        tracking.screen(first);
                        break;
                    } else if (i == 2) { // multiply
                        cout << "Multiplying " << argv[2] << " and " << firstimage << " ...\n";
                        Image first;
                        first.readImage(firstimage);
                        tracking.multiply(first);
                        break;
                    } else if (i == 3) { // subtract
                        cout << "Subtracting " << argv[2] << " and " << firstimage << " ...\n";
                        Image first;
                        first.readImage(firstimage);
                        if (firstimage != "input/car.tga"){
                            first.subtract(tracking);
                            tracking.morph(first);
                            break;
                        }
                        tracking.subtract(first);
                        break;
                    } else if (i == 4) { // overlay
                        cout << "Overlaying " << argv[2] << " and " << firstimage << " ...\n";
                        Image first;
                        first.readImage(firstimage);
                        tracking.overlay(first);
                        break;
                    }
                } else if (i < 11) { // 1 number
                    string nombre = argv[4];
                    int thenum = stoi(nombre);
                    int num = stoi(nombre);
                    if (i == 5){ //scalered
                        cout << "Scaling the red channel of " << argv[2] << " by "
                             << num << " ...\n";
                        tracking.scalered(num);
                        break;
                    }
                    else if (i == 6){ //scalegreen
                        cout << "Scaling the green channel of " << argv[2] << " by "
                             << num << " ...\n";
                        tracking.scalegreen(num);
                        break;
                    }
                    else if (i == 7){ //scaleblue
                        cout << "Scaling the blue channel of " << argv[2] << " by "
                             << num << " ...\n";
                        tracking.scaleblue(num);
                        break;
                    }
                    else if (i == 8){ //addred
                        cout << "Adding +" << num << " to red channel of "
                             << argv[2] << " ...\n";
                        tracking.addred(num);
                        break;
                    }
                    else if (i == 9){ //addgreen
                        cout << "Adding +" << num << " to green channel of "
                             << argv[2] << " ...\n";
                        tracking.addgreen(num);
                        break;
                    }
                    else if (i == 10){ //addblue
                        cout << "Adding +" << num << " to blue channel of "
                             << argv[2] << " ...\n";
                        tracking.addblue(num);
                        break;
                    }
                } else if (i < 15) { // no arguments
                    if (i == 11){ // onlyred
                        tracking.onlyred();
                    }
                    else if (i == 12){ // onlygreen
                        tracking.onlygreen();
                    }
                    else if (i == 13){ //onlyblue
                        tracking.onlyblue();
                    }
                    else if (i == 14){ //flip
                        cout << "flipping " << argv[2] << " ...\n";
                        tracking.flip();
                    }
                }
            }
        }

        vector<int> methodpos = methodpositions(argslist, methodlist);
        // loop for other methods
        for (int p = 1; p < methodpos.size(); p++){
            string thismethod = argslist[methodpos[p]-1];
            for (int i = 0; i < 15; i++) {
                if (thismethod == methodlist[i]) {
                    if (i == 0) { // 2 images
                        string firstimage = argv[methodpos[p]+1];
                        string secondimage = argv[methodpos[p]+2];
                        cout << "... and combining channels " << firstimage << " and "
                             << secondimage << " with previous step ...\n";
                        Image first;
                        first.readImage(firstimage);
                        Image second;
                        second.readImage(secondimage);
                        tracking.combo2(first, second);
                        break;
                    } else if (i < 5) { // 1 image
                        string firstimage = argv[methodpos[p]+1];
                        if (i == 1) { // screen
                            cout << "... and screening " << firstimage << " with previous step ...\n";
                            Image first;
                            first.readImage(firstimage);
                            tracking.screen(first);
                            break;
                        } else if (i == 2) { // multiply
                            cout << "... and multiplying " << firstimage << " with previous step ...\n";
                            Image first;
                            first.readImage(firstimage);
                            tracking.multiply(first);
                            break;
                        } else if (i == 3) { // subtract
                            cout << "... and subtracting " << firstimage << " from previous step ...\n";
                            Image first;
                            first.readImage(firstimage);
                            first.subtract(tracking);
                            tracking.morph(first);
                            break;
                        } else if (i == 4) { // overlay
                            cout << "... and overlaying " << firstimage << " with previous step ...\n";
                            Image first;
                            first.readImage(firstimage);
                            tracking.overlay(first);
                            break;
                        }
                    } else if (i < 11) { // 1 number
                        string nombre = argv[methodpos[p]+1];
                        int num = stoi(nombre);
                        if (i == 5){ //scalered
                            cout << "... and scaling the red channel of previous step by "
                                 << num << " ...\n";
                            tracking.scalered(num);
                            break;
                        }
                        else if (i == 6){ //scalegreen
                            cout << "Scaling the green channel of previous step by "
                                 << num << " ...\n";
                            tracking.scalegreen(num);
                            break;
                        }
                        else if (i == 7){ //scaleblue
                            cout << "Scaling the blue channel of previous step by "
                                 << num << " ...\n";
                            tracking.scaleblue(num);
                            break;
                        }
                        else if (i == 8){ //addred
                            cout << "... and adding +" << num << " to red channel of previous step ...\n";
                            tracking.addred(num);
                            break;
                        }
                        else if (i == 9){ //addgreen
                            cout << "Adding +" << num << " to green channel of previous step ..\n";
                            tracking.addgreen(num);
                            break;
                        }
                        else if (i == 10){ //addblue
                            cout << "Adding +" << num << " to blue channel of previous step ..\n";
                            tracking.addblue(num);
                            break;
                        }
                    } else if (i < 15) { // no arguments
                        if (i == 11){ // onlyred
                            tracking.onlyred();
                        }
                        else if (i == 12){ // onlygreen
                            tracking.onlygreen();
                        }
                        else if (i == 13){ //onlyblue
                            tracking.onlyblue();
                        }
                        else if (i == 14){ //flip
                            cout << "... and flipping ...\n";
                            tracking.flip();
                        }
                    }
                }
            }
        }

        cout << "... and saving output to " << writefile << "!\n";
        tracking.writeImage(writefile);
    }

    return 0;
}
