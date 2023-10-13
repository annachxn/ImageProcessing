
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <string.h>
using namespace std;

struct Image{
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Pixels{
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    };

    Header tgafile;
    vector<Pixels> pixelsvector;
    string fileName;

    Image(){};

    void readImage(string file){
        fileName = file;
        fstream image;
        image.open(fileName, ios_base::in | ios_base::binary);
        if (image.is_open()){
            image.read(&tgafile.idLength, sizeof(tgafile.idLength));
            image.read(&tgafile.colorMapType, sizeof(tgafile.colorMapType));
            image.read(&tgafile.dataTypeCode, sizeof(tgafile.dataTypeCode));
            image.read((char*)(&tgafile.colorMapOrigin), sizeof(tgafile.colorMapOrigin));
            image.read((char*)(&tgafile.colorMapLength), sizeof(tgafile.colorMapLength));
            image.read(&tgafile.colorMapDepth, sizeof(tgafile.colorMapDepth));
            image.read((char*)(&tgafile.xOrigin), sizeof(tgafile.xOrigin));
            image.read((char*)(&tgafile.yOrigin), sizeof(tgafile.yOrigin));
            image.read((char*)(&tgafile.width), sizeof(tgafile.width));
            image.read((char*)(&tgafile.height), sizeof(tgafile.height));
            image.read(&tgafile.bitsPerPixel, sizeof(tgafile.bitsPerPixel));
            image.read(&tgafile.imageDescriptor, sizeof(tgafile.imageDescriptor));

            unsigned int size = tgafile.height * tgafile.width;
            vector<Pixels> temp(size);

            for (unsigned int i = 0; i < size; i++){
                image.read((char*)&temp[i].blue, 1);
                image.read((char*)&temp[i].green, 1);
                image.read((char*)&temp[i].red, 1);
            }
            image.close();

            pixelsvector = temp;
        }
        else {
            cout << "image didnt read\n";
        }
    };

    void writeImage(string file){
        // The results of each task should be output to a new file named
        // output/partX.tga where X is the task number
        fileName = file;
        fstream image(fileName, ios_base::out | ios_base::binary);
        if (image.is_open()){
            image.write(&tgafile.idLength, sizeof(tgafile.idLength));
            image.write(&tgafile.colorMapType, sizeof(tgafile.colorMapType));
            image.write(&tgafile.dataTypeCode, sizeof(tgafile.dataTypeCode));
            image.write((char*)(&tgafile.colorMapOrigin), sizeof(tgafile.colorMapOrigin));
            image.write((char*)(&tgafile.colorMapLength), sizeof(tgafile.colorMapLength));
            image.write(&tgafile.colorMapDepth, sizeof(tgafile.colorMapDepth));
            image.write((char*)(&tgafile.xOrigin), sizeof(tgafile.xOrigin));
            image.write((char*)(&tgafile.yOrigin), sizeof(tgafile.yOrigin));
            image.write((char*)(&tgafile.width), sizeof(tgafile.width));
            image.write((char*)(&tgafile.height), sizeof(tgafile.height));
            image.write(&tgafile.bitsPerPixel, sizeof(tgafile.bitsPerPixel));
            image.write(&tgafile.imageDescriptor, sizeof(tgafile.imageDescriptor));

            for (unsigned int i = 0; i < pixelsvector.size(); i++){
                image.write((char*)&pixelsvector[i].blue, 1);
                image.write((char*)&pixelsvector[i].green, 1);
                image.write((char*)&pixelsvector[i].red, 1);
            }

            image.close();
        }
        else{
            cout << "didnt write image\n";
            image.close();
        }
    };

    void multiply(Image &one){
        for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
            float tempb = ((one.pixelsvector[i].blue/255.0f) * (pixelsvector[i].blue/255.0f)) * 255;
            float tempg = ((one.pixelsvector[i].green/255.0f) * (pixelsvector[i].green/255.0f)) * 255;
            float tempr = ((one.pixelsvector[i].red/255.0f) * (pixelsvector[i].red/255.0f)) * 255;

            pixelsvector[i].blue = (unsigned char)(tempb + 0.5f);
            pixelsvector[i].green = (unsigned char)(tempg + 0.5f);
            pixelsvector[i].red = (unsigned char)(tempr+ 0.5f);
        }
    };

    void screen(Image &one){
        for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
            float og = ((float)one.pixelsvector[i].green)/255.0;
            float ob = ((float)one.pixelsvector[i].blue)/255.0;
            float ore = ((float)one.pixelsvector[i].red)/255.0;

            float tg = ((float)pixelsvector[i].green)/255.0;
            float tb = ((float)pixelsvector[i].blue)/255.0;
            float tre = ((float)pixelsvector[i].red)/255.0;

            pixelsvector[i].blue =(unsigned char) ((1 - (1.0 - ob) * (1.0 - tb)) * 255 +0.5f);
            pixelsvector[i].green =(unsigned char) ((1 - (1.0 - og) * (1.0 - tg)) * 255 +0.5f);
            pixelsvector[i].red =(unsigned char) ((1 - (1.0 - ore) * (1.0 - tre)) * 255 +0.5f);


//            pixelsvector[i].blue =(int) ((255 - ((255.0 - one.pixelsvector[i].blue)) * ((255.0 - pixelsvector[i].blue)) / 255)+0.5f);
//            pixelsvector[i].green =(int) ((255 - ((255.0 - one.pixelsvector[i].green)) * ((255.0 - pixelsvector[i].green)) / 255)+0.5f);
//            pixelsvector[i].red =(int) ((255 - ((255.0 - one.pixelsvector[i].red)) * ((255.0 - pixelsvector[i].red)) / 255)+0.5f);
        }
    };

    void subtract(Image &one){
        for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
            int tempblue = (int)one.pixelsvector[i].blue - (int)pixelsvector[i].blue;
            int tempgreen = (int)one.pixelsvector[i].green - (int)pixelsvector[i].green;
            int tempred = (int)one.pixelsvector[i].red - (int)pixelsvector[i].red;
            // check for whether negative or above max of 255
            if (tempblue < 0){
                tempblue = 0;
            }if (tempgreen < 0){
                tempgreen = 0;
            }if (tempred < 0){
                tempred = 0;
            }
            // reassign
            pixelsvector[i].blue = (unsigned char)tempblue;
            pixelsvector[i].green = (unsigned char)tempgreen;
            pixelsvector[i].red = (unsigned char)tempred;
        }
    };

    void morph(Image &one){
        for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
            pixelsvector[i].green = one.pixelsvector[i].green;
            pixelsvector[i].blue = one.pixelsvector[i].blue;
            pixelsvector[i].red = one.pixelsvector[i].red;
        }

    }

    void onlyblue() {
        unsigned char val = 0;
        for (int i = 0; i < pixelsvector.size(); i++) {
            val = pixelsvector[i].blue;
            pixelsvector[i].green = val;
            pixelsvector[i].red = val;
        }
    }

    void onlygreen() {
        unsigned char val = 0;
        for (int i = 0; i < pixelsvector.size(); i++) {
            val = pixelsvector[i].green;
            pixelsvector[i].blue = val;
            pixelsvector[i].red = val;
        }
    }

    void onlyred() {
        unsigned char val = 0;
        for (int i = 0; i < pixelsvector.size(); i++) {
            val = pixelsvector[i].red;
            pixelsvector[i].green = val;
            pixelsvector[i].blue = val;
        }
    }

    void flip(){
        Image flipped;
        flipped.readImage("input/layer1.tga");
        int curr = 0;
        for (int i = pixelsvector.size()-1; i >= 0; i--){
            flipped.pixelsvector[i] = pixelsvector[curr];
            curr++;
        }
        for (int i = 0; i < pixelsvector.size(); i++){
            pixelsvector[i] = flipped.pixelsvector[i];
        }
    }

    void scalegreen(signed int value){
        for(unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].green * value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            // reassign
            pixelsvector[i].green = (unsigned char)(temp);
//            float temp = ((pixelsvector[i].green/255.0f) * value/255.0) * 255;
//
//            pixelsvector[i].green = (unsigned char)(temp + 0.5f);
        }
    }

    void scaleblue(signed int value){
        for (unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].blue * value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            // reassign
            pixelsvector[i].blue = (unsigned char)(temp);

//            float temp = ((pixelsvector[i].blue/255.0f) * value/255.0) * 255;
//
//            pixelsvector[i].blue = (unsigned char)(temp + 0.5f);
        }
    }

    void scalered(signed int value){
        for (unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].red * value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            // reassign
            pixelsvector[i].red = (unsigned char)(temp);
//            float temp = ((pixelsvector[i].red/255.0f) * value/255.0) * 255;
//
//            pixelsvector[i].red = (unsigned char)(temp + 0.5f);
        }
    }

    void addgreen(signed int value){
        for (unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].green + value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            if (temp < 0) {
                temp = 0;
            }
            // reassign
            pixelsvector[i].green = (unsigned char)(temp);
        }
    };

    void addblue(signed int value){
        for (unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].blue + value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            if (temp < 0) {
                temp = 0;
            }
            // reassign
            pixelsvector[i].blue = (unsigned char)(temp);
        }
    };

    void addred(signed int value){
        for (unsigned int i = 0; i < pixelsvector.size(); i++) {
            signed int temp = (signed int) pixelsvector[i].red + value;
            // check if above max of 255
            if (temp > 255) {
                temp = 255;
            }
            if (temp < 0) {
                temp = 0;
            }
            // reassign
            pixelsvector[i].red = (unsigned char)(temp);
        }
    };

    void overlay(Image &one){
        // if NP2 <= 0.5 : 2 * multiply
        // if NP@ > 0.5 : 1 - [2 * Screen]
        for (int i = 0; i < pixelsvector.size(); i++){
            float og = ((float)pixelsvector[i].green)/255.0;
            float ob = ((float)pixelsvector[i].blue)/255.0;
            float ore = ((float)pixelsvector[i].red)/255.0;

            float tg = ((float)one.pixelsvector[i].green)/255.0;
            float tb = ((float)one.pixelsvector[i].blue)/255.0;
            float tre = ((float)one.pixelsvector[i].red)/255.0;

            if (tg <= 0.5){
                pixelsvector[i].green = (unsigned char)((2 * (og * tg) * 255.0) + 0.5f);
            }
            else if (tg > 0.5) {
                pixelsvector[i].green = (unsigned char)((1-(2 * (1-og) * (1-tg)))* 255 +0.5f);
            }
            if (tb <= 0.5){
                pixelsvector[i].blue = (unsigned char)((2 * (ob * tb) * 255.0) + 0.5f);
            }
            else if (tb > 0.5){
                pixelsvector[i].blue = (unsigned char)((1-(2 * (1-ob) * (1-tb)))* 255 +0.5f);
            }
            if (tre <= 0.5){
                pixelsvector[i].red = (unsigned char)((2 * (ore * tre) * 255.0) + 0.5f);
            }
            else if (tre > 0.5){
                pixelsvector[i].red = (unsigned char)((1-(2 * (1-ore) * (1-tre)))* 255 +0.5f);
            }
        }
    };

    void combo(Image &green, Image &blue){
        for (int i = 0; i < pixelsvector.size(); i++){
            pixelsvector[i].green = blue.pixelsvector[i].green;
            pixelsvector[i].blue = green.pixelsvector[i].blue;
        }
    }

    void combo2(Image &green, Image &blue){
        for (int i = 0; i < pixelsvector.size(); i++){
            pixelsvector[i].green = green.pixelsvector[i].green;
            pixelsvector[i].blue = blue.pixelsvector[i].blue;
        }
    }

};

bool exists(string file){
    string fileName = file;
    fstream image;
    image.open(fileName, ios_base::in | ios_base::binary);
    if (image.is_open()){
        return true;
    }
    else {
        return false;
    }
}

bool validfilename(string file){
    if (file.substr(file.size()-4,file.size()) == ".tga"){
        return true;
    }
    else {
        return false;
    }
}

bool check(vector<string> args, vector<string> methods){
    for (int p = 2; p < args.size(); p++) {
        for (int i = 0; i < 15; i++) {
            if (args[p] == methods[i]) {
                if (i == 0) { // 2 images
                    string firstimage = args[p + 1];
                    string secondimage = args[p + 2];
                    if (validfilename(firstimage) && validfilename(secondimage)) {
                        if (exists(firstimage) && exists(secondimage)) {
                            p += 2;
                            break;
                        } else {
                            cout << "Invalid argument, file does not exist.\n";
                            return false;
                        }
                    } else {
                        cout << "Invalid argument, invalid file name.\n";
                        return false;
                    }
                } else if (i < 5) {
                    int sizing = args.size();
                    if (sizing - 1 <= p){
                        cout << "Missing argument.\n";
                        return false;
                    }// 1 image
                    string firstimage = args[p + 1];
                    if (validfilename(firstimage)) {
                        if (i == 1 || i == 2 || i == 3 || i == 4) { // screen
                            if (exists(firstimage)) {
                                p++;
                                break;
                            } else {
                                cout << "Invalid argument, file does not exist.\n";
                                return false;
                            }
                        }
                    } else {
                        cout << "Invalid argument, invalid file name.\n";
                        return false;
                    }
                } else if (i < 11) { // 1 number
                    int sizing = args.size();
                    if (sizing - 1 <= p){
                        cout << "Missing argument.\n";
                        return false;
                    }
                    try {
                        string nombre = args[p+1];
                        int num = stoi(nombre);
                    }
                    catch (...) {
                        cout << "Invalid argument, expected number.\n";
                        return false;;
                    }
                    string nombre = args[p+1];
                    int thenum = stoi(nombre);
                    if (i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10) { //scalered
                        p++;
                        break;
                    }
                } else if (i < 15 && i > 10) { // no arguments
                    if (i == 11 || i == 12 || i == 13 || i == 14) { // onlyred
                        break;
                    }
                }
            } else if (i == 14){
                cout << "Invalid method name.\n";
                return false;
            }
        }
    }
    return true;
}

vector<int> methodpositions(vector<string> args, vector<string> methods){
    vector<int> methodpos;
    for (int p = 3; p <= args.size(); p++) {
        methodpos.push_back(p);
        for (int i = 0; i < 15; i++) {
            if (args[i] == methods[i]) {
                if (i == 0) { // 2 images
                    p += 2;
                    break;
                } else if (i < 5) { // 1 image
                    p++;
                    break;
                } else if (i < 11) { // 1 number
                    p++;
                    break;
                } else if (i < 15 && i > 10) { // no arguments
                    break;
                }
            }
        }
    }
    return methodpos;
}

//void multiply(Image &one, Image &two){
//    for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
//        float tempb = ((one.pixelsvector[i].blue/255.0f) * (two.pixelsvector[i].blue/255.0f)) * 255;
//        float tempg = ((one.pixelsvector[i].green/255.0f) * (two.pixelsvector[i].green/255.0f)) * 255;
//        float tempr = ((one.pixelsvector[i].red/255.0f) * (two.pixelsvector[i].red/255.0f)) * 255;
//
//        one.pixelsvector[i].blue = (tempb + 0.5f);
//        one.pixelsvector[i].green = (tempg + 0.5f);
//        one.pixelsvector[i].red = (tempr+ 0.5f);
//    }
//};
//
//void screen(Image &one, Image &two){
//    for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
//        one.pixelsvector[i].blue =(int) (255 - (((255.0 - one.pixelsvector[i].blue)) * ((255.0 - two.pixelsvector[i].blue)) / 255)+0.5f);
//        one.pixelsvector[i].green =(int) (255 - (((255.0 - one.pixelsvector[i].green)) * ((255.0 - two.pixelsvector[i].green) / 255))+0.5f);
//        one.pixelsvector[i].red =(int) (255 - (((255.0 - one.pixelsvector[i].red)) * ((255.0 - two.pixelsvector[i].red)) / 255)+0.5f);
//    }
//};
//
//void subtract(Image &one, Image &two){
//    for (unsigned int i = 0; i < one.pixelsvector.size(); i++){
//        int tempblue = (int)two.pixelsvector[i].blue - (int)one.pixelsvector[i].blue;
//        int tempgreen = (int)two.pixelsvector[i].green - (int)one.pixelsvector[i].green;
//        int tempred = (int)two.pixelsvector[i].red - (int)one.pixelsvector[i].red;
//        // check for whether negative or above max of 255
//        if (tempblue < 0){
//            tempblue = 0;
//        }if (tempgreen < 0){
//            tempgreen = 0;
//        }if (tempred < 0){
//            tempred = 0;
//        }
//        // reassign
//        one.pixelsvector[i].blue = tempblue;
//        one.pixelsvector[i].green = tempgreen;
//        one.pixelsvector[i].red = tempred;
//    }
//};

void addition(Image &one, Image &two){
    for (unsigned int i = 0; i < one.pixelsvector.size(); i++) {
        int tempblue = (int) one.pixelsvector[i].blue + (int) two.pixelsvector[i].blue;
        int tempgreen = (int) one.pixelsvector[i].green + (int) two.pixelsvector[i].green;
        int tempred = (int) one.pixelsvector[i].red + (int) two.pixelsvector[i].red;
        // check if above max of 255
        if (tempblue > 255) {
            tempblue = 255;
        }
        if (tempgreen > 255) {
            tempgreen = 255;
        }
        if (tempred > 255) {
            tempred = 255;
        }
        // reassign
        one.pixelsvector[i].blue = tempblue;
        one.pixelsvector[i].green = tempgreen;
        one.pixelsvector[i].red = tempred;
    }
};


//void overlay(Image &one, Image &two){
//    // if NP2 <= 0.5 : 2 * multiply
//    // if NP@ > 0.5 : 1 - [2 * Screen]
//    for (int i = 0; i < two.pixelsvector.size(); i++){
//        float og = ((float)one.pixelsvector[i].green)/255.0;
//        float ob = ((float)one.pixelsvector[i].blue)/255.0;
//        float ore = ((float)one.pixelsvector[i].red)/255.0;
//
//        float tg = ((float)two.pixelsvector[i].green)/255.0;
//        float tb = ((float)two.pixelsvector[i].blue)/255.0;
//        float tre = ((float)two.pixelsvector[i].red)/255.0;
//
//        if (tg <= 0.5){
//            one.pixelsvector[i].green = (unsigned char)((2 * (og * tg) * 255.0) + 0.5f);
//        }
//        else if (tg > 0.5) {
//            one.pixelsvector[i].green = (unsigned char)((1-(2 * (1-og) * (1-tg)))* 255 +0.5f);
//        }
//        if (tb <= 0.5){
//            one.pixelsvector[i].blue = (unsigned char)((2 * (ob * tb) * 255.0) + 0.5f);
//        }
//        else if (tb > 0.5){
//            one.pixelsvector[i].blue = (unsigned char)((1-(2 * (1-ob) * (1-tb)))* 255 +0.5f);
//        }
//        if (tre <= 0.5){
//            one.pixelsvector[i].red = (unsigned char)((2 * (ore * tre) * 255.0) + 0.5f);
//        }
//        else if (tre > 0.5){
//            one.pixelsvector[i].red = (unsigned char)((1-(2 * (1-ore) * (1-tre)))* 255 +0.5f);
//        }
//    }
//};
//
//void combo(Image &red, Image &blue, Image &green){
//    for (int i = 0; i < red.pixelsvector.size(); i++){
//        red.pixelsvector[i].green = green.pixelsvector[i].green;
//        red.pixelsvector[i].blue = blue.pixelsvector[i].blue;
//    }
//}





// char someVariable = 65;
// cout << someVariable; prints out 'A' instead of 65
// cout << (int)someVariable; prints out 65 instead of 'A'