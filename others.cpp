//    if (argc = 2){
//        cout << "Invalid file name.\n";
//        return 0;
//    }
//    else if (strcmp(argv[1], "multiply") == 0) {
//
//    }
//    else if (strcmp((argv[1]), "add") == 0) {
//
//    }
//    else if (strcmp((argv[1]), "sub") == 0) {
//
//    }

// cmake-build-debug/output/part1.tga input/layer.tga multiply input/pattern1.tga

//    Image car;
//    Image circles;
//    Image layer1;
//    Image layer2;
//    Image pattern1;
//    Image pattern2;
//    Image text;
//    Image text2;
//    Image layer_blue;
//    Image layer_green;
//    Image layer_red;
//
//    // read files
//    car.readImage("car.tga");
//    circles.readImage("circles.tga");
//    layer1.readImage("layer1.tga");
//    layer2.readImage("layer2.tga");
//    pattern1.readImage("pattern1.tga");
//    pattern2.readImage("pattern2.tga");
//    text.readImage("text.tga");
//    text2.readImage("text2.tga");
//    layer_blue.readImage("layer_blue.tga");
//    layer_green.readImage("layer_green.tga");
//    layer_red.readImage("layer_red.tga");

//    // to check tasks in terminal:
//    // fc.exe /b .\cmake-build-debug\output\part1.tga .\examples\EXAMPLE_part1.tga
//    // task 1
//    multiply(layer1, pattern1);
//    layer1.writeImage("part1.tga");
//    cout << "p1 done!\n";
//    layer1.readImage("layer1.tga");
//
//    // task 2
//    subtract(layer2, car);
//    layer2.writeImage("part2.tga");
//    cout << "p2 done!\n";
//    layer2.readImage("layer2.tga");
//
//    // task 3
//    multiply(layer1, pattern2);
//    screen(text, layer1);
//    text.writeImage("part3.tga");
//    cout << "p3 done!\n";
//    text.readImage("text.tga");
//
//    // task 4
//    multiply(layer2, circles);
//    subtract(pattern2, layer2);
//    pattern2.writeImage("part4.tga");
//    cout << "p4 done!\n";
//    pattern2.readImage("pattern2.tga");
//
//    // task 5 wrong
//    layer1.readImage("layer1.tga");
//    pattern1.readImage("pattern1.tga");
//    overlay(layer1, pattern1);
//    layer1.writeImage("part5.tga");
//    cout << "p5 done!\n";
//    layer1.readImage("layer1.tga");
//
//    // task 6
//    addcolor(car, "green", 200);
//    car.writeImage("part6.tga");
//    cout << "p6 done!\n";
//    car.readImage("car.tga");
//
//    // task 7
//    multiplycolor(car, "red", 4);
//    multiplycolor(car, "blue", 0);
//    car.writeImage("part7.tga");
//    cout << "p7 done!\n";
//    car.readImage("car.tga");
//
//    // task 8
//    channelColor(car, "red");
//    car.writeImage("part8_r.tga");
//    car.readImage("car.tga");
//
//    channelColor(car, "green");
//    car.writeImage("part8_g.tga");
//    car.readImage("car.tga");
//
//    channelColor(car, "blue");
//    car.writeImage("part8_b.tga");
//    car.readImage("car.tga");
//
//    cout << "p8 done!\n";
//
//    // task 9
//    combo(layer_red, layer_blue, layer_green);
//    layer_red.writeImage("part9.tga");
//    layer_red.readImage("layer_red.tga");
//    cout << "p9 done!\n";
//
//    // task 10
//    upsidedown(text2);
//    text2.writeImage("part10.tga");
//    text2.readImage("text2.tga");
//    cout << "p10 done!\n";
//
//    // run command line by typing :
//    // ./cmake-build-debug/executablename arg1 arg2 arg3...
//
//

// for loop
//// first method
//    for (int i = 0; i < 15; i++) {
//        if (curr == methodlist[i]) {
//            if (i == 0) { // 2 images
//                string firstimage = argv[4];
//                string secondimage = argv[5];
//                if (validfilename(firstimage) && validfilename(secondimage)) {
//                    if (exists(firstimage) && exists(secondimage)) {
//                        cout << "Combining channels of " << argv[2] << ", " <<
//                             firstimage << ", and " << secondimage << " ...\n";
//                        Image first;
//                        first.readImage(firstimage);
//                        Image second;
//                        second.readImage(secondimage);
//                        tracking.combo(first, second);
//                        position += 3;
//                        break;
//                    } else {
//                        cout << "Invalid argument, file does not exist.\n";
//                        return 0;
//                    }
//                } else {
//                    cout << "Invalid argument, invalid file name.\n";
//                    return 0;
//                }
//            } else if (i < 5) { // 1 image
//                string firstimage = argv[4];
//                if (validfilename(firstimage)) {
//                    if (i == 1) { // screen
//                        if (exists(firstimage)) {
//                            cout << "Screening " << argv[2] << "and " << firstimage << " ...\n";
//                            Image first;
//                            first.readImage(firstimage);
//                            tracking.screen(first);
//                            position += 2;
//                            break;
//                        } else {
//                            cout << "Invalid argument, file does not exist.\n";
//                            return 0;
//                        }
//                    } else if (i == 2) { // multiply
//                        if (exists(firstimage)) {
//                            cout << "Multiplying " << argv[2] << "and " << firstimage << " ...\n";
//                            Image first;
//                            first.readImage(firstimage);
//                            tracking.multiply(first);
//                            position += 2;
//                            break;
//                        } else {
//                            cout << "Invalid argument, file does not exist.\n";
//                            return 0;
//                        }
//                    } else if (i == 3) { // subtract
//                        if (exists(firstimage)) {
//                            cout << "Subtracting " << argv[2] << "and " << firstimage << " ...\n";
//                            Image first;
//                            first.readImage(firstimage);
//                            tracking.subtract(first);
//                            position += 2;
//                            break;
//                        } else {
//                            cout << "Invalid argument, file does not exist.\n";
//                            return 0;
//                        }
//                    } else if (i == 4) { // overlay
//                        if (exists(firstimage)) {
//                            cout << "Overlaying " << argv[2] << "and " << firstimage << " ...\n";
//                            Image first;
//                            first.readImage(firstimage);
//                            tracking.overlay(first);
//                            position += 2;
//                            break;
//                        } else {
//                            cout << "Invalid argument, file does not exist.\n";
//                            return 0;
//                        }
//                    } else {
//                        cout << "Invalid argument, invalid file name.\n";
//                        return 0;
//                    }
//                }
//            } else if (i < 11) { // 1 number
//                try{
//                    int num = stoi(argv[4]);
//                }
//                catch(...){
//                    cout << "Invalid argument\n";
//                    return 0;
//                }
//                int num = stoi(argv[4]);
//                if (i == 5){ //scalered
//                    cout << "Scaling the red channel of " << argv[2] << " by "
//                        << num << " ...\n";
//                    tracking.scalered(num);
//                    position += 2;
//                    break;
//                }
//                else if (i == 6){ //scalegreen
//                    cout << "Scaling the green channel of " << argv[2] << " by "
//                         << num << " ...\n";
//                    tracking.scalegreen(num);
//                    position += 2;
//                    break;
//                }
//                else if (i == 7){ //scaleblue
//                    cout << "Scaling the blue channel of " << argv[2] << " by "
//                         << num << " ...\n";
//                    tracking.scaleblue(num);
//                    position += 2;
//                    break;
//                }
//                else if (i == 8){ //addred
//                    cout << "Adding +" << num << " to red channel of "
//                        << argv[2] << " ...\n";
//                    tracking.addred(num);
//                    position+=2;
//                    break;
//                }
//                else if (i == 9){ //addgreen
//                    cout << "Adding +" << num << " to green channel of "
//                         << argv[2] << " ...\n";
//                    tracking.addgreen(num);
//                    position+=2;
//                    break;
//                }
//                else if (i == 10){ //addblue
//                    cout << "Adding +" << num << " to blue channel of "
//                         << argv[2] << " ...\n";
//                    tracking.addblue(num);
//                    position+=2;
//                    break;
//                }
//            } else if (i < 15) { // no arguments
//                if (i == 11){ // onlyred
//                    tracking.onlyred();
//                }
//                else if (i == 12){ // onlygreen
//                    tracking.onlygreen();
//                }
//                else if (i == 13){ //onlyblue
//                    tracking.onlyblue();
//                }
//                else if (i == 14){ //flip
//                    tracking.flip();
//                }
//            }
//        } else if (i == 14) {
//            cout << "Invalid method name.\n";
//            return 0;
//        }
//    }
//
//    // loop for other methods
//
//    cout << "... and saving output to " << writefile << "!\n";
//    tracking.writeImage(writefile);
