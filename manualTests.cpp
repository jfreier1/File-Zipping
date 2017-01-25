#include "zipfunctions.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    ZipFunctions* zipfunctions = new ZipFunctions;
    for(int i = 1; i<5; i++) {
        string num = to_string(i);
        cout << "zipping file " << num << endl;
        zipfunctions->zipFile("/Users/Joshua_Freier/pennapps/txt/original" + num,
        "/Users/Joshua_Freier/pennapps/txt/zipped" + num);
    }
    for(int i = 1; i<5; i++) {
        string num = to_string(i);
        cout << "unzipping file " << num << endl;
        zipfunctions->unZipFile("/Users/Joshua_Freier/pennapps/txt/zipped" + num,
        "/Users/Joshua_Freier/pennapps/txt/unzipped" + num);
    }
  /*  zipfunctions->zipFile("/Users/Joshua_Freier/pennapps/txt/double",
    "/Users/Joshua_Freier/pennapps/txt/zippeddouble");
    cout << "done";*/

  return 0;
};
